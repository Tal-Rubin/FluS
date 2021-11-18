/**
 * @file 
 * Test code for the Exact Riemann Solver portion
 * 
 * \copyright Copyright (c) 2021 Tal Rubin Distributed under MIT License.
*/


#include <cstdio>
#include <array>
#include <stdexcept>

#include "ers.h"
/**
 * @brief Test code for the Exact Riemann Solver portion
 * 
 * @param argc Number of comman line arguments
 * @param argv List of command line arguments
 * @return int Success / Failure code
 * 
 * Gets either one integer (0-4) for one of five pre-selected test cases (as in Toro's book)
 * or 11 floating point parameters defining the two states \f$(\rho, u, v, w, p)\f$ and time.
 */


void test(std::array<double,5> ,std::array<double,5>, double);

int main(int argc, char **argv) {
  if (argc ==2) {
    //! State std::arrays containing \f$\rho, u, v, w, p\f$ 
    std::array<std::array<double, 5>,5> left_state = {{{1., 0., 0., 0., 1.},
                                                      {1., -2., 0., 0., .4},
                                                      {1., 0., 0., 0., 1000.},
                                                      {1., 0., 0., 0., .01},
                                                      {5.99924, 19.5975, 0., 0., 460.894}}}; 
    //! State std::arrays containing \f$\rho, u, v, w, p\f$ 
    std::array<std::array<double, 5>,5> right_state = {{{.125, 0., 0., 0., .1},
                                                      {1., 2., 0., 0., .4},
                                                      {1., 0., 0., 0., .01},
                                                      {1., 0., 0., 0., 100.},
                                                      {5.99242, -6.19633, 0., 0., 46.0950}}}; 
    //! sampling times
    std::array<double,5> times = {0.25, 0.15, 0.012, 0.035, 0.035};
    //! Initilizes the exact solution for the Euler problem 
    int i = atoi(argv[1]);
    test(left_state[i],right_state[i],times[i]);
  } else if (argc == 12) {
    std::array<double, 5> left_state;
    std::array<double, 5> right_state;
    double time = atof(argv[11]);
    for (int i = 0; i < 5; i++){
      left_state[i] = atof(argv[i+1]);
      right_state[i] = atof(argv[i+6]);
    }
    test(left_state,right_state,time);


  } else throw std::invalid_argument("Need a number 0-4, or 11 floating points for density, 3-velocity and pressure for right and left, and time");

  return 0;  
}


void test(std::array<double,5> left,std::array<double,5> right, double time) {
  double gamma = 7./5;
  Ers ers(left, right, gamma);
  printf("%15.8f\n", gamma);
  double x;
  double dx = 1./100;
  std::array<double,5> res;
  for (int i =0; i <101; i++){
    x = -0.5+i*dx;
    res = ers.sample(time, x);
    printf("%15.8f ", x);
    for (int j = 0; j < 5; j++) printf("%15.8f ", res[j]);
    printf("\n");
  }
}
