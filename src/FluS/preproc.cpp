/**
 * @file preproc.cpp
 * @author Tal Rubin (trubin@princeton.edu)
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

  void gaussian_initial_conditions(double amplitude, Dynamic_Variable & state, const std::size_t field, const Mesh & mesh){
    // Average 
    for (std::size_t i = 0; i < mesh.elem_vect.size(); i++){
      state.elem_field_coeff(i, field, 0) +=  amplitude * 0.25*std::sqrt(M_PI/5.) * (std::erf(std::sqrt(5.)*(2*mesh.elem_vect[i].nodes[1]->position[0]-1))  \
                                          -std::erf(std::sqrt(5.)*(2*mesh.elem_vect[i].nodes[0]->position[0]-1)))/mesh.elem_vect[i].volume;
    }
    // 1sr Legendre polynomial
    if (state.num_param() > 1) {
      for (std::size_t i = 0; i < mesh.elem_vect.size(); i++){
        state.elem_field_coeff(i, field, 1) +=  amplitude * 3./(20 * pow(mesh.elem_vect[i].volume, 2.))*(mesh.elem_vect[i].nodes[1]->position[0] + mesh.elem_vect[i].nodes[0]->position[0] -1)  \
                              *std::sqrt(5*M_PI)*(std::erf(std::sqrt(5.)*(2*mesh.elem_vect[i].nodes[0]->position[0]-1)) \
                              -std::erf(std::sqrt(5.)*(2*mesh.elem_vect[i].nodes[1]->position[0]-1)));
        state.elem_field_coeff(i, field, 1) += amplitude* 3./(20 * pow(mesh.elem_vect[i].volume, 2.))*std::exp(-5*std::pow(2*mesh.elem_vect[i].nodes[0]->position[0]-1,2.))-std::exp(-5*std::pow(2*mesh.elem_vect[i].nodes[1]->position[0]-1, 2.));
      }
    }
  }


  void low_half_domain(double amplitude, int dim, Dynamic_Variable & state, const std::size_t field, const Mesh & mesh){
    double min_node = INFINITY;
    double max_node = -INFINITY;
    double mid ;
    for (auto node:mesh.node_vect){
      min_node = std::min(min_node, node.position[dim]);
      max_node = std::max(max_node, node.position[dim]);
    }
    mid  = 0.5*(min_node+max_node);
    
    for (std::size_t i =0; i < mesh.elem_vect.size(); i++) {
      auto el = mesh.elem_vect[i];
      bool is_low_half = true;
      for (auto node:el.nodes) {
        is_low_half = is_low_half && (node->position[dim]<mid);
      }
      
      state.elem_field_coeff(i, field, 0) +=  amplitude*is_low_half;
    }

  }
}