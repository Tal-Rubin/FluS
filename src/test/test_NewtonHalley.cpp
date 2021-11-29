#include <iostream>
#include <array>
#include <iomanip>
#include <cmath>
#include "../extFunc/externalMath.hpp"


class functor {
  public:
  static std::array<double,3> f0(double x){
    return std::array<double,3> {x*x*x+2*x+5, 3*x*x+2, 6*x};
  }
  static double res0() {
    return (4 * std::pow(540+12*std::sqrt(2121), -1./3.) - std::pow(540+12*std::sqrt(2121), 1./3.) / 6.);
  }
};


int main() {
  double newton_sol = ExtaMath::newton(functor::f0, -1., -200.,200., 1e-5, 10);
  double halley_sol = ExtaMath::halley(functor::f0, -1., -200.,200., 1e-5, 10);
  std::cout.setf(std::ios::fixed, std::ios::floatfield);
  std::cout.precision(16);
  std::cout<<"Solving for x^3 + 2 x + 5 = 0:"<< std::endl;
  std::cout<<"Newton method:\t\t "<<newton_sol<<" \tHalley method:\t\t "<<halley_sol<<std::endl;
  std::cout<<"Newton method error:\t "<<newton_sol-functor::res0()<<" \tHalley method error:\t "<<halley_sol-functor::res0()<<std::endl;

  return 0;  
}

  
