/*
 * Copyright (c) 2019, CNES.
 *
 * This source code is licensed under MIT-style license (found in the
 * COPYING file in the root directory of this source tree).
 */


#ifndef TEST_HELPER_H_
#define TEST_HELPER_H_


/*
 * Declare a pointer on the generic test functions prototype.
 */
typedef int (*tstFunc)(void);

/*
 * Tests initialization function.
 */
int testInit(const char * funcName);

/*
 * Run a test function.
 */
int runTest(tstFunc func);

/*
 * Return EXIT_FAILURE if a != b .
 */
int assertEqual(int a, int b, char * msg);

/*
 * Return EXIT_FAILURE if |b - a| > tol .
 */
int assertApprox(double a, double b, double tol, char * msg);


#endif /* TEST_HELPER_H_ */
