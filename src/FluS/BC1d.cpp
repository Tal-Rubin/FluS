/**
 * 
 */

#include <iostream>
#include <valarray>
#include <array>

#include "mesh1d.h"

int BC(int num_Elems, Dynamic_Variable& state, const double t,
       std::valarray<double> * f_pr(double)) {
  /*
   * @brief Member function of a Stepper to set the boundary conditions: 
   *        for the ghost cells, override with a prescribed field and 
   *        calculate the flux through the edge 
   *
   * @param num_Elems Number of real elements
   * @param state A set of Dynamic_Variable
   * @param t Time of the current loop
   * @param f_pr Pointer to the time-independent fields imposed on the ghost cells
   */

  for (int i = 0; i < num_Elems + 2; i++) {
    // Scan the elements, impose a field if they are ghost elements
    if (i == 0) {
      // Ghost cell on the left end
      state.element(i) = f_pr(t)[0];
    }

    if (i == num_Elems_ + 1) {
      // Ghost cell on the right end
      state.element(i) = f_pr(t)[1];   
    }
  }

  return 0;
}
  
    
    
