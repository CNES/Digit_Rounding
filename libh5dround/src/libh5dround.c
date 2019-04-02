/*
 * Copyright (c) 2019, CNES.
 *
 * This source code is licensed under MIT-style license (found in the
 * COPYING file in the root directory of this source tree).
 */

#include "libh5dround.h"

#include <stdlib.h>
#include <H5PLextern.h>

#include "libdround.h"

#define FILTER_NAME		"H5Zdround"		// filter name
#define NPARAMS_FILTER	3				// number of parameters

#define NSD_OPT_POS		0				// position of the nsd option in the parameter list
#define DATA_SIZE_POS	1				// position of the data size in the parameter list
#define DATA_TYPE_POS	2				// position of the data type in the parameter list


#define NSD_DEFAULT		3				// default value for NSD

// Prototypes
htri_t can_apply(hid_t dcpl, hid_t type, hid_t space);
htri_t set_local(hid_t dcpl, hid_t type, hid_t space);
size_t dround_filter(unsigned flags, size_t cd_nelmts, const unsigned cd_values[], size_t nbytes, size_t* buf_size,
		void** buf);

// Filter registration
const H5Z_class2_t H5Z_DROUND[1] = { {				//
		H5Z_CLASS_T_VERS, 							// H5Z_class_t version
				(H5Z_filter_t) H5Z_FILTER_DROUND, 	// filter id
				1, 									// encoder_present flag (set to true)
				1, 									// decoder_present flag (set to true)
				FILTER_NAME, 						// filter name
				can_apply, 							// "can apply" callback
				set_local, 							// "set local" callback
				(H5Z_func_t) dround_filter, 		// actual filter function
		} };

// Get plugin type
H5PL_type_t H5PLget_plugin_type(void)
{
	return H5PL_TYPE_FILTER;
}

// Get plugin info
const void *H5PLget_plugin_info(void)
{
	return H5Z_DROUND;
}

// Can the filter be applied ?
htri_t can_apply(hid_t dcpl, hid_t type, hid_t space)
{
	// data space must be simple
	if (H5Sis_simple(space) <= 0) {
		fprintf(stderr, "Warning: Cannot apply %s filter. Data space is not simple.\n", FILTER_NAME);
		return 0;
	}

	// filter can be applied
	return 1;
}


// Set any parameters that are specific to this dataset
htri_t set_local(hid_t dcpl, hid_t type, hid_t space)
{

	// initialize the filter parameters with the default values
	unsigned int params[NPARAMS_FILTER] = {NSD_DEFAULT, 0, 0};

	// initialize the output variable for the call to H5Pget_filter_by_id
	unsigned int flags = 0;
	size_t cd_nelmts = NPARAMS_FILTER;
	unsigned int * cd_values = params;
	// retrieve user parameters
	if (H5Pget_filter_by_id(dcpl, H5Z_FILTER_DROUND, &flags, &cd_nelmts,
			cd_values, 0, NULL, NULL) < 0) {
		fprintf(stderr, "Error: Cannot get %s filter parameters.\n", FILTER_NAME);
		return 0;
	}

	// get the data type
	int data_type = (int) H5Tget_class(type);
	if (data_type < 0)
	{
		fprintf(stderr, "Error: Cannot get a valid data type for applying %s filter.\n", FILTER_NAME);
		return 0;
	}

	// set the data_size in the filter parameters list
	params[DATA_TYPE_POS] = data_type;

	// get the data size
	size_t data_size = H5Tget_size(type);
	if (data_size <= 0)
	{
		fprintf(stderr, "Error: Cannot get a valid data size for applying %s filter.\n", FILTER_NAME);
		return 0;
	}

	// set the data_size in the filter parameters list
	params[DATA_SIZE_POS] = data_size;

	// update the filter parameters
	//cd_values = (unsigned int *) (&params);
	if (H5Pmodify_filter(dcpl, H5Z_FILTER_DROUND, flags, NPARAMS_FILTER, cd_values) < 0)
	{
		fprintf(stderr, "Error: Cannot set %s filter parameters.\n", FILTER_NAME);
		return 0;
	}

	// success
	return 1;
}


// Apply dround filter on a buffer of float values
void dround_on_flt(void **buf, size_t nbytes, int nsd)
{
	// cast the input buffer to float
	float * buf_flt = (float *) *buf;

	// round the data values
	for (size_t i = 0; i < nbytes / sizeof(float); i++)
		buf_flt[i] = (float) droundFast((double) buf_flt[i], nsd);

}


// Apply dround filter on a buffer of double values
void dround_on_dbl(void **buf, size_t nbytes, int nsd)
{
	// cast the input buffer to double
	double * buf_dbl = (double *) *buf;

	// round the data values
	for (size_t i = 0; i < nbytes / sizeof(double); i++)
		buf_dbl[i] = droundFast(buf_dbl[i], nsd);
}


// Apply dround filter
size_t dround_filter(unsigned int flags, size_t cd_nelmts, const unsigned int cd_values[], size_t nbytes,
		size_t *buf_size, void **buf)
{
	if (flags & H5Z_FLAG_REVERSE)
	{
		// reverse filter: nothing needs to be done
		// return the input number of bytes
		return nbytes;
	}
	else
	{
		// forward filter: apply dround

		// set the parameters
		int nsd = cd_values[NSD_OPT_POS];
		size_t data_size = cd_values[DATA_SIZE_POS];
		H5T_class_t data_type = (H5T_class_t) cd_values[DATA_TYPE_POS];

		if (data_type == H5T_FLOAT)
		{
			// floating-point data
			// apply dround after a cast on the input buffer
			switch(data_size)
			{
			case 4:
				dround_on_flt(buf, nbytes, nsd);
				break;
			case 8:
				dround_on_dbl(buf, nbytes, nsd);
				break;
			default:
				fprintf(stderr, "Error: Invalid data type for %s filter.\n", FILTER_NAME);
			}

		}

		return nbytes;
	}

}

