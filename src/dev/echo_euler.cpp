/**
 * @file echo_euler.cpp
 * @author Tal Rubin (trubin@princeton.edu)
 * @brief 
 * @version 0.1
 * @date 2021-12-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <cstddef>

#include "../FluS/mesh.h"
#include "../FluS/dynamic_variable.h"
#include "../FluS/models/euler_1d.h"
#include "../FluS/forward_euler.h"
#include "../FluS/preproc.h"

int main() { 

  std::size_t num_ele = 20;

  Mesh mesh(num_ele,std::vector<double> {0.,1.}, false);
  
  Euler_1d_Godunov advect (1.4  , mesh);
  
  Dynamic_Variable u (num_ele+2, advect.fields(),advect.parameters()); 

  Preprocessor::gaussian_initial_conditions(1., u, 0, mesh);
  Preprocessor::gaussian_initial_conditions(1., u, 1, mesh);

  std::valarray<double> a (u.dim()[0]);
  a=1;
  u.field_coeff(0,0)+=a;
  u.field_coeff(4,0)+=a;


  // set bc:
  u.element(mesh.ghost_elements[0]) = u.element(mesh.ghost_elements[1]-1);
  u.element(mesh.ghost_elements[1]) = u.element(mesh.ghost_elements[0]+1);


  for (auto v: u.data_) {
    std::cout<<v<<" ";
  }
  std::cout<<std::endl;
  for (int i = 0; i<100; i++) {
    
    Dynamic_Variable ddt (u.dim()); 

    double max_dt = advect.flux(0, u, ddt);

    for (auto v: mesh.ghost_elements){
      ddt.element(v) = 0;
    }
    u.data_= forward_euler(0.9*max_dt, u, ddt).data_;
    // set bc:
    u.element(mesh.ghost_elements[0]) = u.element(mesh.ghost_elements[1]-1);
    u.element(mesh.ghost_elements[1]) = u.element(mesh.ghost_elements[0]+1);

  }



  for (auto v: u.data_) {
    std::cout<<v<<" ";
  }
  std::cout<<std::endl;





  return 0;

}