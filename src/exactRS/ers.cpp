#include <cmath>
#include <iostream>

#include "ers.h"

Ers::Ers(std::array<double, 5> left, std::array<double, 5> right, double gamma): gamma_(gamma), left_(left), right_(right){
  a_[0] = sound_speed(left_);
  a_[1] = sound_speed(right_);

  // check for vacumm in solution
  if (2/(gamma_-1)*(a_[0]+a_[1])<right_[1]-left_[1]){
    std::cerr<<"Vacumm solution"<<std::endl;
    return;
  }

  find_pu_star();




}

Ers::~Ers(){
    
}

double Ers::sound_speed(std::array<double, 5> state){
  return sqrt(gamma_ * state[4]/state[0]);  
}


void Ers::find_pu_star() {
  p_star_ = guess_p_star();

  
}


double Ers::guess_p_star(){
  return 0.5*(left_[4]+right_[4]);
  //EXPAND
}