#define _USE_MATH_DEFINES

#include <iostream>
#include <cstddef>
#include <cmath>

#include "../mocks/mesh_mock.h"
#include "../FluS/dynamic_variable.h"
#include "../FluS/models/advection_1d.h"
#include "../FluS/forward_euler.h"


int main() { 

  std::size_t num_ele = 10;

  const Mesh_1d_mock mesh(num_ele, 0., 1.);

  Dynamic_Variable u (num_ele+2, 1); 
  Advection_1D advect (0.1, mesh);
  
  int i = 0;
  for (auto el: mesh.elem_vect){
    u.data_[i++] =  0.25*std::sqrt(M_PI/5.) * (std::erf(std::sqrt(5.)*(2*mesh.node_vect[el.nodes[1]].position[0]-1))  \
                                          -std::erf(std::sqrt(5.)*(2*mesh.node_vect[el.nodes[0]].position[0]-1)));
  }
  u.data_ /= mesh.element_volume;


  // set bc:
  u.element(mesh.ghost_elements[0]) = u.element(mesh.ghost_elements[1]-1);
  u.element(mesh.ghost_elements[1]) = u.element(mesh.ghost_elements[0]+1);


  for (auto v: u.data_) {
    std::cout<<v<<" ";
  }
  std::cout<<std::endl;
  for (int i = 0; i<7; i++) {
    
    Dynamic_Variable ddt (u.dim_); 

    double max_dt = advect.flux(0, u, ddt);

    for (auto v: mesh.ghost_elements){
      ddt.element(v) = 0;
    }
    u = forward_euler(max_dt, u, ddt);// set bc:
    u.element(mesh.ghost_elements[0]) = u.element(mesh.ghost_elements[1]-1);
    u.element(mesh.ghost_elements[1]) = u.element(mesh.ghost_elements[0]+1);

  }



  for (auto v: u.data_) {
    std::cout<<v<<" ";
  }
  std::cout<<std::endl;





  return 0;

}