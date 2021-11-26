#include <iostream>
#include <valarray>
#include <array>


#include "../FluS/dynamic_variable.h"
#include "../FluS/forward_euler.h"

int main(int argc, char **argv) {

  Dynamic_Variable a(10,4,1);
  int i =0;
  for (auto &val: a.data_){
    val = i++;
    std::cout<<val<<" ";
  }
  std::cout<<std::endl;

  a.element(5) += a.element(1);

  for (auto val: a.get_element(5)){
    std::cout<<val<<" ";
  }
  std::cout<<std::endl;

  return 0;
}

  
