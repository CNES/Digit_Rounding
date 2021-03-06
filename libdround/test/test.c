/*
 * Copyright (c) 2019, CNES.
 *
 * This source code is licensed under MIT-style license (found in the
 * COPYING file in the root directory of this source tree).
 */


#include <stdio.h>
#include <stdlib.h>

#include "test_helper.h"

/*
 * Declare the tests.
 */
int testDroundFastPi(void);
int testDroundFastRange(void);
int testDroundFastOthers(void);

/*
 * Run all tests.
 */
int main(void)
{

	// Initialize the tests results
	int result = EXIT_SUCCESS;

	// Run the tests
	result |= runTest(testDroundFastPi);
	result |= runTest(testDroundFastRange);
	result |= runTest(testDroundFastOthers);

	// Return the tests results
	if (result == EXIT_FAILURE)
		printf("Error: Tests failed!\n");

	return result;
}
