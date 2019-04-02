/*
 * Copyright (c) 2019, CNES.
 *
 * This source code is licensed under MIT-style license (found in the
 * COPYING file in the root directory of this source tree).
 */


#include <stdio.h>
#include <stdlib.h>

#include "hdf5.h"
#include "libh5dround.h"
#include "test_helper.h"

#define FILE                "sample.h5"
#define DATASET_NAME_FLT    "flt_data"
#define DATASET_NAME_DBL    "dbl_data"
#define DATASET_NAME_INT    "int_data"
#define DATASET_NAME_SHORT  "short_data"
#define DIM0                5
#define CHUNK0              DIM0

int testH5ZDround(void)
{
	// initialize the test
	int result = testInit(__func__);

	// test data
	float input_data_flt[DIM0] = { 3.14159265, 0.0101, 0.101, 10.1, -55.0 };
	double input_data_dbl[DIM0] = { 3.14159265, 0.0101, 0.101, 10.1, -55.0 };
	int input_data_int[DIM0] = { 3, 0, 0, 10, -55};
	// number of digits preserved
	const int nsd = 2;
	// tolerance on the rounded values
	double tol[5] = { 0.05, 0.0005, 0.005, 0.5, 0.5};

	// initialize the output buffers
	float output_data_flt[DIM0] = {0, 0, 0, 0, 0};
	double output_data_dbl[DIM0] = {0, 0, 0, 0, 0};
	int output_data_int[DIM0] = {0, 0, 0, 0, 0};

	herr_t status = 0;
	hsize_t dims[1] = { DIM0 };
	hsize_t chunk[1] = { CHUNK0 };
	const unsigned int cd_values[1] = { nsd };     // keep nsd digits
	unsigned filter_config;


	// create a new file using the default properties
	hid_t file = H5Fcreate(FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
	// create dataspace
	hid_t space = H5Screate_simple(1, dims, NULL);

	// create the dataset creation property list, add the dround filter and set the chunk size.
	hid_t dcpl = H5Pcreate(H5P_DATASET_CREATE);
#ifdef DEBUG
		printf("\nInfo: Setting filter parameters.");
#endif
	status |= H5Pset_filter(dcpl, H5Z_FILTER_DROUND, H5Z_FLAG_MANDATORY, (size_t) 1, cd_values);

	// check that filter is registered
	// if it is registered, retrieve filter's configuration
	if (H5Zfilter_avail(H5Z_FILTER_DROUND))
	{
		status = H5Zget_filter_info(H5Z_FILTER_DROUND, &filter_config);
		if (! (filter_config & H5Z_FILTER_CONFIG_ENCODE_ENABLED))
		{
			fprintf(stderr, "\nError: Encoding mode not available in H5Zdround filter! \n");
			return EXIT_FAILURE;
		}
#ifdef DEBUG
		printf("\nInfo: H5Zdround filter is available.");
#endif
	}
	else
	{
		fprintf(stderr,
				"\nError: H5Zdround filter not available! Check your HDF5_PLUGIN_PATH environment variable.\n");
		return EXIT_FAILURE;
	}

	// set chunking
	status = H5Pset_chunk(dcpl, 1, chunk);

	// create the datasets
#ifdef DEBUG
		printf("\nInfo: Creating the dataset.");
#endif
	hid_t dset_flt = H5Dcreate(file, DATASET_NAME_FLT, H5T_IEEE_F32LE, space, H5P_DEFAULT, dcpl, H5P_DEFAULT);
	hid_t dset_dbl = H5Dcreate(file, DATASET_NAME_DBL, H5T_IEEE_F64LE, space, H5P_DEFAULT, dcpl, H5P_DEFAULT);
	hid_t dset_int = H5Dcreate(file, DATASET_NAME_INT, H5T_STD_I32LE, space, H5P_DEFAULT, dcpl, H5P_DEFAULT);

	// write the data to the dataset
#ifdef DEBUG
	printf("\nInfo: Writing rounded data ... ");
#endif
	status = H5Dwrite(dset_flt, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, input_data_flt);
	status = H5Dwrite(dset_dbl, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, input_data_dbl);
	status = H5Dwrite(dset_int, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, input_data_int);

	// close and release resources
	status = H5Dclose(dset_flt);
	status = H5Dclose(dset_dbl);
	status = H5Dclose(dset_int);
	status = H5Pclose(dcpl);
	status = H5Sclose(space);
	status = H5Fclose(file);

#ifdef DEBUG
	printf("\nInfo: Close the file and reopen for reading ... ");
#endif

	// open the file for reading
	file = H5Fopen(FILE, H5F_ACC_RDONLY, H5P_DEFAULT);
	// open the dataset
	dset_flt = H5Dopen(file, DATASET_NAME_FLT, H5P_DEFAULT);
	dset_dbl = H5Dopen(file, DATASET_NAME_DBL, H5P_DEFAULT);
	dset_int = H5Dopen(file, DATASET_NAME_INT, H5P_DEFAULT);


#ifdef DEBUG
	char filter_name[80];
	H5Z_filter_t filter_id = 0;
	unsigned int flags;
	unsigned int values_out[1] = { 99 };
	size_t nelmts = 2;            // number of elements in cd_values

	// get the property list
	dcpl = H5Dget_create_plist(dset_flt);

	// get the filter id
	filter_id = H5Pget_filter2(dcpl, (unsigned) 0, &flags, &nelmts, values_out, sizeof(filter_name), filter_name, NULL);

	printf("\nInfo: Filter info read from the dataset creation property ");
	printf("\nInfo:\t Filter identifier is ");
	switch (filter_id)
	{
	case H5Z_FILTER_DROUND:
		printf("%d", filter_id);
		printf("\nInfo:\t Number of parameters is %u with the first value being %u", (unsigned int) nelmts, values_out[0]);
		break;
	default:
		printf("\nInfo:\t Warning: Filter %d not expected.", filter_id);
		break;
	}
#endif


#ifdef DEBUG
	printf("\nInfo: Reading rounded data ...");
#endif
	status = H5Dread(dset_flt, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, output_data_flt);
	status = H5Dread(dset_dbl, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, output_data_dbl);
	status = H5Dread(dset_int, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, output_data_int);

#ifdef DEBUG
	status = H5Pclose(dcpl);
#endif
	status = H5Dclose(dset_flt);
	status = H5Dclose(dset_dbl);
	status = H5Dclose(dset_int);
	status = H5Fclose(file);

	// Initialize the error message
	char msg[256] = { '\0' };
#ifdef DEBUG
	printf("\nChecking results on float data:");
#endif
	for (int i = 0; i < DIM0; i++)
	{
		// Call the assert with the function to be tested
		sprintf(msg, "H5Zdround(%f, nsd=%d)", input_data_flt[i], nsd);
		result |= assertApprox(output_data_flt[i], input_data_flt[i], tol[i], msg);
	}
#ifdef DEBUG
	printf("\nChecking results on double data:");
#endif
	for (int i = 0; i < DIM0; i++)
	{
		// Call the assert with the function to be tested
		sprintf(msg, "H5Zdround(%f, nsd=%d)", input_data_dbl[i], nsd);
		result |= assertApprox(output_data_dbl[i], input_data_dbl[i], tol[i], msg);
	}
#ifdef DEBUG
	printf("\nChecking results on integer data: dround does not apply on int. input and output should be the same.");
#endif
	for (int i = 0; i < DIM0; i++)
	{
		// Call the assert with the function to be tested
		sprintf(msg, "H5Zdround(%d, nsd=%d)", input_data_int[i], nsd);
		result |= assertEqual(output_data_int[i], input_data_int[i], msg);
	}

	return result;
}
