/**
 * 
 */

#include <iostream>
#include <valarray>
#include <array>

#include "mesh1d.h"
#include "mesh2d.h"

int BC(int num_Elems, std:vector<Elem> elem_vect, Dynamic_Variable& state,
       const double t, std::valarray<double> * f_pr(double)) {
  /*
   * @brief Member function of a Stepper to set the boundary conditions: 
   *        for the ghost cells, override with a prescribed field and 
   *        calculate the flux through the edge 
   *
   * @param num_Elems Number of real elements
   * @param elem_vect The vector of elements 
   * @param state A set of Dynamic_Variable
   * @param t Time of the current loop
   * @param f_pr Pointer to the time-independent fields imposed on the ghost cells
   */

  for (int i = 0; i < num_Elems + 2; i++) {
    // Scan the elements, impose a field if they are ghost elements
    Elem elem = elem_vect[i];
    if (elem.ghost == true) {
      state.element(elem.elem_number) = f_pr[elem.elem_number];
    }

  return 0;
}
