/**
 * @file test_dynamic_variable.cpp
 * @author Tal Rubin (trubin@princeton.edu)
 * @brief 
 * @version 0.1
 * @date 2021-11-30
 * 
 * @test Dynamic_Variable
 * @copyright Copyright (c) 2021
 * 
 */


#include "../FluS/dynamic_variable.h"

#include "catch.hpp"

TEST_CASE( "Dynamic_Variable data access and manupulation", "[dynamic_variable]" ) {
  std::array<std::size_t,3> state_dims = {5/*elements*/, 3 /*fields*/, 2 /*parameters*/};
  Dynamic_Variable state (state_dims);
  REQUIRE(state.data_.size() == 30);
  REQUIRE(state.dim() == state_dims);

  Dynamic_Variable ddt (state.dim());
  
  for (std::size_t i = 0; i < state.data_.size(); i++) state.data_[i] = i;
  /* state.data_ = {0,1,    2,3,    4,5, 
  *                 6,7,    8,9,    10,11,
  *                 12,13,  14,15,  16,17,
  *                 18,19,  20,21,  22,23 };*/

  ddt.data_ =  {0.5,0.3,    8.7,3.4,    45,86, 
                1.5,1.3,    8.7,3.4,    45,86,
                2.5,2.3,    8.7,3.4,    45,86,
                3.5,3.3,    8.7,3.4,    45,86 };

  Dynamic_Variable IC(state);  

  SECTION( "Data access" ) {
    std::size_t el = GENERATE (0,1,2,3,4);
    std::size_t field = GENERATE (0,1,2);
    std::size_t param = GENERATE(0,1);
    REQUIRE (state.elem_field_coeff(el,field,param) == state.data_[param +field*state.coeff_num()+ el*state.element_size()]);
  }    
  state.element(2) += ddt.element(2);
  SECTION( "Data manipulation" ) {

    std::size_t el = GENERATE (0,1,3,4);
    std::size_t field = GENERATE (0,1,2);
    std::size_t param = GENERATE(0,1);

    REQUIRE (state.elem_field_coeff(el,field,param) == IC.elem_field_coeff(el,field, param));
    REQUIRE (state.elem_field_coeff(2,field,param) == IC.elem_field_coeff(2,field, param) + ddt.elem_field_coeff(2,field,param));
  }
  // now we know it works
  IC.element(2) += ddt.element(2);
  state.field_coeff(0,1) += 0.4*ddt.get_field_coeff(0,0);

  SECTION( "Global field manipulation" ) {

    std::size_t el = GENERATE (0,1,2,3,4);
    std::size_t field = GENERATE (1,2);
    std::size_t param = GENERATE(0);
    // some data remains unchanged
    REQUIRE (state.elem_field_coeff(el,field,param) == IC.elem_field_coeff(el,field, param));
    REQUIRE (state.elem_field_coeff(el,0,1) == IC.elem_field_coeff(el, 0, 1)+0.4*ddt.elem_field_coeff(el, 0, 0));

  }
}