/*
 * Copyright (c) 2019, CNES.
 *
 * This source code is licensed under MIT-style license (found in the
 * COPYING file in the root directory of this source tree).
 */


#ifndef DROUND_H5PLUGIN_H_
#define DROUND_H5PLUGIN_H_

#define H5Z_FILTER_DROUND		47987			// filter id


#include "H5PLextern.h"

H5PL_type_t H5PLget_plugin_type(void);
const void* H5PLget_plugin_info(void);


#endif /* DROUND_H5PLUGIN_H_ */
