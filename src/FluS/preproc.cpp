/**
 * @file preproc.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include "preproc.h"


namespace Preprocessor{

  void initial_conditions(std::string expression, Dynamic_Variable & state, const std::size_t field, const Mesh & mesh){
    (void) expression;
    // makes a gaussian C* exp(-B*(x-C)^2)
    // Average 
    for (std::size_t i = 0; i < mesh.elem_vect.size(); i++){
      state.elem_field_coeff(i, field, 0) +=  0.25*std::sqrt(M_PI/5.) * (std::erf(std::sqrt(5.)*(2*mesh.elem_vect[i].nodes[1]->position[0]-1))  \
                                          -std::erf(std::sqrt(5.)*(2*mesh.elem_vect[i].nodes[0]->position[0]-1)))/mesh.elem_vect[i].volume;
    }
    // 1sr Legendre polynomial
    if (state.num_param() > 1) {
      for (std::size_t i = 0; i < mesh.elem_vect.size(); i++){
        state.elem_field_coeff(i, field, 1) +=  3./(20 * pow(mesh.elem_vect[i].volume, 2.))*(mesh.elem_vect[i].nodes[1]->position[0] + mesh.elem_vect[i].nodes[0]->position[0] -1)  \
                              *std::sqrt(5*M_PI)*(std::erf(std::sqrt(5.)*(2*mesh.elem_vect[i].nodes[0]->position[0]-1)) \
                              -std::erf(std::sqrt(5.)*(2*mesh.elem_vect[i].nodes[1]->position[0]-1)));
        state.elem_field_coeff(i, field, 1) += 3./(20 * pow(mesh.elem_vect[i].volume, 2.))*std::exp(-5*std::pow(2*mesh.elem_vect[i].nodes[0]->position[0]-1,2.))-std::exp(-5*std::pow(2*mesh.elem_vect[i].nodes[1]->position[0]-1, 2.));
      }
    }
  }
}