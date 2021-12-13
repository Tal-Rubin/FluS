#include <iostream>
#include <cstddef>

#include "../mocks/mesh_mock.h"
#include "../FluS/dynamic_variable.h"
#include "../FluS/models/advection_1d.h"
#include "../FluS/forward_euler.h"
#include "../mocks/preproc_mock.h"

int main() { 

  std::size_t num_ele = 20;

  const Mesh_1d_mock mesh(num_ele, 0., 1.);
  
  Advection_1d_Upwind advect (0.1, mesh);
  
  Dynamic_Variable u (num_ele+2, advect.fields(),advect.parameters()); 

  Preprocessor::initial_conditions(" ", u, 0, mesh);


  // set bc:
  u.element(mesh.ghost_elements[0]) = u.element(mesh.ghost_elements[1]-1);
  u.element(mesh.ghost_elements[1]) = u.element(mesh.ghost_elements[0]+1);


  std::cout<<u;

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



  std::cout<<u;






  return 0;

}