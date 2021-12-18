/**
 * @file echo_advection.cpp
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
#include <fstream>

#include "../mocks/mesh.h"
#include "../FluS/dynamic_variable.h"
#include "../FluS/models/advection_1d.h"
#include "../FluS/forward_euler.h"
#include "../FluS/preproc.h"
int main() { 
  std::size_t num_ele = 20;

  Mesh mesh(num_ele, std::vector<double> {0., 1.}, true);
  std::ofstream OutputFile;
  OutputFile.open ("mesh.txt");
  OutputFile << mesh;
  OutputFile.close ();

  Advection_1d_Upwind advect (0.1, mesh);
  
  Dynamic_Variable u (mesh.num_elements(), advect.fields(),advect.parameters()); 
  Preprocessor::initial_conditions(" ", u, 0, mesh);
  
  double t =0;
  std::cout<<advect.fields()<<" "<<advect.parameters()<<"\n";
  std::cout<<t<<" "<<u;


  

  for (int i = 0; i<100; i++) {
    
    Dynamic_Variable ddt (u.dim()); 

    double max_dt = advect.flux(0, u, ddt);

    for (auto v: mesh.ghost_elements){
      ddt.element(v) = 0;
    }
    u.data_= forward_euler(0.9*max_dt, u, ddt).data_;
    t += 0.9*max_dt;
    std::cout<<t<<" "<<u;

  }



  std::cout<<"FIN\n";

  return 0;

}