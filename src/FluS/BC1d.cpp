/**
 * 
 */

#include <iostream>
#include <valarray>
#include <array>

#include "mesh1d.h"

int BC(std::size_t ele_number, Dynamic_Variable& state, const double t,
       std::valarray<double> f) {
  /*
   * @brief Member function of a Stepper to set the boundary conditions: 
   *        for the ghost cells, override with a prescribed field and 
   *        calculate the flux through the edge 
   * @param ele_number Element number to be accessed
   * @param state A set of Dynamic_Variable
   * @param t Time of the current loop
   * @param f Field(time-dependent) imposed on the ghost cells
   */
  if (ele_number == 0) {
    // Ghost cell on the left end
    state.element(ele_number) = f[0]; 
  }

  if (ele_number == Mesh1D::Num_Elems_+1) {
    // Ghost cell on the right end
    state.element(ele_number) = f[1];   
  }
  
  else
    return 0;
}
    
    
