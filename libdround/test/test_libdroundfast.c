/*
 * Copyright (c) 2019, CNES.
 *
 * This source code is licensed under MIT-style license (found in the
 * COPYING file in the root directory of this source tree).
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../../libtestdround/include/test_helper.h"
#include "libdround.h"

#define PI	3.14159265


/*
 * Test droundFast algo on the value Pi with different numbers of nsd.
 */
int testDroundFastPi(void)
{
	// Initialize the test
	int result = testInit(__func__);
	// Initialize the error message
	char msg[256] = { '\0' };

	// Loop over nsd values
	for (int nsd = 0; nsd < 10; nsd++)
	{
		// Tolerance on the rounded values is 5e-nsd
		double tol = 5.0 * pow(10, -nsd);

		// Call the assert with the function to be tested
		sprintf(msg, "droundFast(%f, %d)", PI, nsd);
		result |= assertApprox(droundFast(PI, nsd), PI, tol, msg);
	}

	return result;

}


/*
 * Test droundFast algo on the range [1, 2[
 * and compute the maximum absolute error for nsd varying from 1 to 8.
 */
int testDroundFastRange(void)
{
	// Initialize the test
	int result = testInit(__func__);

	// Configure the interval
	double a = 1.0;
	double b = 2.0;

	// Configure the step increrment
	double step = 1e-6;

	// Compute the number of points for the mean absolute error computation
	int n = (int) ((b-a)/step);

#ifdef DEBUG
		printf("\n\tError metrics for the Digit Rounding algorithm on the interval [%.2f,%.2f[\n", a, b);
		printf("\tnsd; Max abs error; Mean abs error; Mean error\n");
#endif

	for (int nsd=1; nsd<8; nsd++)
	{
		// Set the tolerance
		double tol = 5.0 * pow(10, -nsd);

		// Initialize the maximum absolute error value
		double max_abs_error = 0;
		// Initialize the mean absolute error value
		double mean_abs_error = 0;
		// Initialize the mean error value
		double mean_error = 0;

		// Test droundFast algo on the range [1, 2[.
		for (double v=a; v<b; v+=step)
		{
			// Call the droundFast() function
			double r = droundFast(v, nsd);

			// Compute the absolute error
			double e = fabs(r-v);

			// Compute the maximum absolute error
			if (e > max_abs_error)
				max_abs_error = e;

			// Compute the mean absolute error
			mean_abs_error += e;
			// Compute the mean error
			mean_error += (r-v);
		}

		// Compute the mean absolute error
		mean_abs_error /= n;
		// Compute the mean error
		mean_error /= n;


#ifdef DEBUG
		printf("\t%3d; %.11f; %.12f; %.10f\n", nsd, max_abs_error, mean_abs_error, mean_error);
#endif

		if (max_abs_error > tol)
		{
			printf("\n\tTest fails: Maximum absolute error of droundFast([%.2f,%.2f[, nsd=%d) is > %f\n", a, b, nsd, tol);
			result = EXIT_FAILURE;
		}
	}

	return result;

}



/*
 * Test droundFast algo on several values with different numbers of nsd.
 */
int testDroundFastOthers(void)
{
	// Initialize the test
	int result = testInit(__func__);
	// Initialize the error message
	char msg[256] = { '\0' };

	// Perform a test of droundFast
	float v = 118.128716;
	int nsd = 2;
	float tol = 5;
	sprintf(msg, "droundFast(%f, %d)", v, nsd);
        result |= assertApprox(droundFast(v, nsd), v, tol, msg);
	
	// Perform a test of droundFast
	v = 118.128716;
	nsd = 3;
	tol = 0.5;
	sprintf(msg, "droundFast(%f, %d)", v, nsd);
        result |= assertApprox(droundFast(v, nsd), v, tol, msg);
	
	// Perform a test of droundFast
	v = 145;
	nsd = 2;
	tol = 5;
	sprintf(msg, "droundFast(%f, %d)", v, nsd);
        result |= assertApprox(droundFast(v, nsd), v, tol, msg);
	
	// Perform a test of droundFast
	v = 145;
	nsd = 3;
	tol = 0.5;
	sprintf(msg, "droundFast(%f, %d)", v, nsd);
        result |= assertApprox(droundFast(v, nsd), v, tol, msg);
	
	return result;
}
