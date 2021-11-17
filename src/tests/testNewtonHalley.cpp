#include <iostream>
#include <array>
#include <iomanip>
#include "../extFunc/externalMath.hpp"


class functor {
  public:
  static std::array<double,3> f(double x){
    return std::array<double,3> {x*x*x+2*x+5, 3*x*x+2, 6*x};
  }
};


int main(int argc, char **argv) {
  double newton_sol = extaMath::newton(functor::f, -1., -200.,200., 1e-5, 10);
  double halley_sol = extaMath::halley(functor::f, -1., -200.,200., 1e-5, 10);
  std::cout.setf(std::ios::fixed, std::ios::floatfield);
  std::cout.precision(16);
  std::cout<<newton_sol<<" "<<halley_sol<<std::endl;

  return 0;  
}

  
