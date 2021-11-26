/**
 * @file dynamic_variable.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "dynamic_variable.h"

Dynamic_Variable::Dynamic_Variable(std::size_t num_ele, std::size_t num_fields, std::size_t num_dg_dof): 
                    dim_{num_ele, num_fields,num_dg_dof}, data_(dim_[0]*dim_[1]*dim_[2]) {}
Dynamic_Variable::Dynamic_Variable(std::array<std::size_t, 3> dim):dim_(dim), data_(dim_[0]*dim_[1]*dim_[2]){}


Dynamic_Variable::Dynamic_Variable(std::size_t num_ele, std::size_t num_fields): 
                    dim_{num_ele, num_fields,1}, data_(dim_[0]*dim_[1]*dim_[2]) {}

//Dynamic_Variable::Dynamic_Variable(const Dynamic_Variable &DV): dim_(DV.dim_), data_(DV.data_){}

