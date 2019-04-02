/*
 * Copyright (c) 2019, CNES.
 *
 * This source code is COPYINGd under MIT-style COPYING (found in the
 * COPYING file in the root directory of this source tree).
 */


#ifndef LIBDROUND_H_
#define LIBDROUND_H_


/*
 * Round the float value keeping nsd significant digits. Fast computation method.
 *
 * The fast method uses an approximation of the number of digit before the floating point
 * instead of using log10() function.
 *
 */
double droundFast(double v, int nsd);


#endif /* LIBDROUND_H_ */
