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

Dynamic_Variable::Dynamic_Variable(std::size_t num_ele, std::size_t num_fields, std::size_t num_coeff): 
                    data_(num_ele * num_fields * num_coeff), dim_{num_ele, num_fields, num_coeff}, element_size_(num_fields * num_coeff) {}
Dynamic_Variable::Dynamic_Variable(std::array<std::size_t, 3> dim): data_(dim[0]*dim[1]*dim[2]), dim_(dim), element_size_(dim[1]*dim[2])  {}


Dynamic_Variable::Dynamic_Variable(std::size_t num_ele, std::size_t num_fields): 
                    data_(num_ele * num_fields), dim_{num_ele, num_fields, 1}, element_size_(dim_[1]*dim_[2]) {}

//Dynamic_Variable::Dynamic_Variable(const Dynamic_Variable &DV): data_(DV.data_), dim_(DV.dim_), element_size_(DV.element_size_)  {}

std::array<std::size_t, 3> Dynamic_Variable::dim() const {return dim_;}
std::size_t Dynamic_Variable::element_size() const {return element_size_;}
std::size_t Dynamic_Variable::coeff_num() const {return dim_[2];}

