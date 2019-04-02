/*
 * Copyright (c) 2019, CNES.
 *
 * This source code is licensed under MIT-style license (found in the
 * COPYING file in the root directory of this source tree).
 */


#include <stdlib.h>
#include <float.h>
#include <math.h>

#ifndef __STDC_IEC_559__
#error "Implemented for IEEE-754 (STDC_IEC_559) format only!\n");
#else
/* using IEEE-754 */

/*
 * Returns the binary representation of the input IEEE 754 binary32 floating-point value v
 * in the string str.
 */
void fltBinRepr(char * str, float v)
{
	// initialize a string with 34 characters
	for (int i = 0; i < 34; i++)
		str[i] = 'x';
	// sign-exponent separator in the binary string
	str[1] = ' ';
	// exponent-significand separator in the binary string
	str[10] = ' ';
	// end of string marker
	str[34] = '\0';

	// convert the float value to its unsigned int representation
	unsigned int * vIntPtr = (unsigned int*) (&v);
	unsigned int vInt = *vIntPtr;

	// significand bits are the 23 least significant bits
	// they are stored from character 33 to 11 in the binary string
	for (int i = 0; i < 23; i++)
	{
		if (vInt & 1)
			str[33 - i] = '1';
		else
			str[33 - i] = '0';

		vInt = vInt >> 1;
	}

	// exponent bits are the 8 next
	// they are stored from character 9 to 2 in the binary string
	for (int i = 0; i < 8; i++)
	{
		if (vInt & 1)
			str[9 - i] = '1';
		else
			str[9 - i] = '0';

		vInt = vInt >> 1;
	}

	// sign bit is the last one
	// it is stored in character 0
	if (vInt & 1)
		str[0] = '1';
	else
		str[0] = '0';
}

#endif

// TODO double case

