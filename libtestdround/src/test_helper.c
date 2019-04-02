/*
 * Copyright (c) 2019, CNES.
 *
 * This source code is licensed under MIT-style license (found in the
 * COPYING file in the root directory of this source tree).
 */

#include "../../libtestdround/include/test_helper.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>



#ifdef DEBUG
// prototype of the fltBinRepr() function defined in file dfloat.c
void fltBinRepr(char *, float);
#endif

/*
 * Tests initialization function.
 */
int testInit(const char * funcName)
{
	printf("Running %s ...", funcName);
	return EXIT_SUCCESS;
}

/*
 * Run a test function.
 */
int runTest(tstFunc test)
{
	// call the test function
	int result = (*test)();

	// print the result
	if (result == EXIT_FAILURE)
		printf("\t Failed!\n");
	else
		printf("\t Success.\n");
	return result;
}


/*
 * Return EXIT_FAILURE if a != b .
 */
int assertEqual(int a, int b, char * msg)
{
	int result = EXIT_SUCCESS;

	if (a != b)
	{
		printf("\n\t Test fails: %s != %i", msg, b);
		result = EXIT_FAILURE;
	}

#ifdef DEBUG
	printf("\n\t%s = %i", msg, a);
#endif

	return result;
}


/*
 * Return EXIT_FAILURE if |b - a| > tol .
 */
int assertApprox(double a, double b, double tol, char * msg)
{
	int result = EXIT_SUCCESS;

	if (fabs(b-a) > tol)
	{
		printf("\n\tTest fails: %s = %f\n", msg, a);
		printf("\t            and |%f - %f| > %f\n", a, b, tol);
		result = EXIT_FAILURE;
	}

#ifdef DEBUG
	char binRepr[256];
	printf("\n\t%s = %.8f", msg, a);
	fltBinRepr(binRepr, (float) a);
	printf("\n\t%s\t%.8f", binRepr, a);
	if (result == EXIT_FAILURE)
	{
		fltBinRepr(binRepr, (float) b);
		printf("\n\t%s\t%.8f", binRepr, b);
	}
#endif

	return result;
}
