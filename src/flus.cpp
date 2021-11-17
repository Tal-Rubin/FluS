/**
 * @file 
 * Driver code for the Exact Riemann Solver portion
 * 
 * \copyright Copyright (c) 2021 Tal Rubin Distributed under MIT License.
*/


#include <iostream>
#include <array>
#include <iomanip>

#include "exactRS/ers.h"
#include "extFunc/externalMath.hpp"
/**
 * @brief Driver code for the Exact Riemann Solver portion
 * 
 * @param argc Number of comman line arguments
 * @param argv List of command line arguments
 * @return int Success / Failure code
 */




int main(int argc, char **argv) {
  //! State std::arrays containing \f$\rho, u, v, w, p\f$ 
  std::array<double, 5> left_state; 
  //! State std::arrays containing \f$\rho, u, v, w, p\f$ 
  std::array<double, 5> right_state; 

  //! Initilizes the exact solution for the Euler problem 
  Ers ers(left_state, right_state);


  return 0;  
}