/**
 * @file forward_euler.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef FLUS_FOR_EULER_H_
#define FLUS_FOR_EULER_H_

#include "dynamic_variable.h"

Dynamic_Variable forward_euler(const double dt, const Dynamic_Variable &state, const Dynamic_Variable &ddt);


#endif  // FLUS_FOR_EULER_H_
