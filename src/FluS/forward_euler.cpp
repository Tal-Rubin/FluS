/**
 * @file forward_euler.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "forward_euler.h"

Dynamic_Variable forward_euler(const double dt, const Dynamic_Variable &state, const Dynamic_Variable &ddt) {
  Dynamic_Variable res(state.dim());
  
  res.data_ = state.data_+dt * ddt.data_;
  return res;
}
