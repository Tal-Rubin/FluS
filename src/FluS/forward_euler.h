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
/**
 * @brief Forward Euler time-stepper
 * 
 * @param dt The time-step
 * @param state The state vector
 * @param ddt The time derivative vector
 * @return Dynamic_Variable State vector with values  /f$state + dt * ddt /f$ 
 */
Dynamic_Variable forward_euler(const double dt, const Dynamic_Variable &state, const Dynamic_Variable &ddt);


#endif  // FLUS_FOR_EULER_H_
