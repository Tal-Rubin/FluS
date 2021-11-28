#include <iostream>
#include <valarray>
#include <array>


#include "../FluS/dynamic_variable.h"

int main() {

  Dynamic_Variable a(10,4,2);
  int i =0;
  for (auto &val: a.data_){
    val = i++;
    std::cout<<val<<" ";
  }
  std::cout<<std::endl;

  a.element(5) += a.element(1);

  for (auto val: a.get_field_coeff(0,0)){
    std::cout<<val<<" ";
  }
  std::cout<<std::endl;
  for (std::size_t i = 0; i < a.coeff_num(); i++){
      a.field_coeff(1,i) +=a.get_field_coeff(0,i);
  }

  for (auto val: a.data_){
    std::cout<<val<<" ";
  }
  std::cout<<std::endl;


  return 0;
}

  
