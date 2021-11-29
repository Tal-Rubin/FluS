#include <iostream>
#include <cstddef>

#include "../mocks/mesh_mock.h"
#include "../FluS/dynamic_variable.h"
#include "../FluS/models/advection_1d.h"
#include "../FluS/forward_euler.h"
#include "../mocks/preproc_mock.h"

int main() { 

  std::size_t num_ele = 5;

  const Mesh_1d_mock mesh(num_ele, 0., 1.);

  Dynamic_Variable u (num_ele+2, 1,2); 
  Advection_1D advect (0.1, mesh);
  
  Preprocessor::initial_conditions(" ", u, 0, mesh);


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