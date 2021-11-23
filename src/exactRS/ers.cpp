#include <cmath>
#include <iostream>
#include <iomanip>
#include <functional>
#include <stdexcept>


#include "ers.h"
#include "../extFunc/externalMath.hpp"

Ers::Ers(std::array<double, 5> left, std::array<double, 5> right, double gamma): gamma_(gamma){
  state_[0] = left;
  state_[1] = right;
  G1_ = 2/(gamma_ - 1);
  G2_ = 2/(gamma_ + 1);

  sound_speed();

  // check for vacumm in solution
  if (G1_*(a_[0]+a_[1])<state_[1][1]-state_[0][1]){
    std::cerr<<"Vacumm solution"<<std::endl;
    return;
  }
  p_star_ = extaMath::halley(std::bind(&Ers::functor_p_star, this, std::placeholders::_1), guess_p_star(), -1.,100*(state_[0][4]+state_[1][4]), 1e-12, 20);
  
  density_speed();
}

Ers::~Ers(){
  
}
std::array<double,5> Ers::U(double t, double x) {
  std::array<double,5> res = W(t,x);

  res[4] = res[4]/(gamma_-1)+0.5*res[0]*(res[1]*res[1]+res[2]*res[2]+res[3]*res[3]);
  res[1] = res[0]*res[1];
  res[2] = res[0]*res[2];
  res[3] = res[0]*res[3];
  return res;
}


std::array<double,5> Ers::W(double t, double x) {
  if (t == 0. && x > 0) return state_[1];
  if (t == 0. && x < 0) return state_[0];
  if (t == 0. && x == 0) return std::array<double,5> {0.5*(state_[0][0]+state_[1][0]),
                                                      0.5*(state_[0][1]+state_[1][1]),
                                                      0.5*(state_[0][2]+state_[1][2]),
                                                      0.5*(state_[0][3]+state_[1][3]),
                                                      0.5*(state_[0][4]+state_[1][4])};


  if (t < 0.) throw std::out_of_range("t out of range");

  double speed = x/t;
  // Left state
  if (speed < S_[0][0]) return state_[0]; 
  // Right state
  if (speed > S_[1][0]) return state_[1];
  std::array<double,5> res = {0};
  // Right rarefaction
  if ((speed <= S_[1][0]) && (speed >= S_[1][1])) {
    res[0] = state_[1][0] * std::pow(G2_* (1 - (state_[1][1]-speed)/(G1_ * a_[1])) ,G1_);
    res[1] = G2_ * (speed + state_[1][1]/G1_ - a_[1]);
    res[2] = state_[1][2];
    res[3] = state_[1][3];
    res[4] = state_[1][4] * std::pow(G2_*(1-(state_[1][1]-speed)/(a_[1]*G1_)),gamma_ * G1_);
  }
  // Right star region
  if (speed < S_[1][1] && speed > u_star_) {
    res[0] = rho_star_[1];
    res[1] = u_star_;
    res[2] = state_[1][2];
    res[3] = state_[1][3];
    res[4] = p_star_;
  }
  // Right star region
  if (speed == u_star_) {
    res[0] = 0.5*(rho_star_[1]+rho_star_[0]);
    res[1] = u_star_;
    res[2] = 0.5*(state_[1][2]+state_[0][2]);
    res[3] = 0.5*(state_[1][3]+state_[0][3]);
    res[4] = p_star_;
  }


  // Left star region
  if (speed > S_[0][1] && speed < u_star_) {
    res[0] = rho_star_[0];
    res[1] = u_star_;
    res[2] = state_[0][2];
    res[3] = state_[0][3];
    res[4] = p_star_;
  }
  // Left rarefaction
  if ((speed <= S_[0][1]) && (speed >= S_[0][0])) {
    res[0] = state_[0][0] * std::pow(G2_ * (1 + (state_[0][1]-speed)/(G1_ * a_[0])) ,G1_);
    res[1] = G2_ * (speed + state_[0][1]/G1_ + a_[0]);
    res[2] = state_[0][2];
    res[3] = state_[0][3];
    res[4] = state_[0][4] * std::pow(G2_ * (1 + (state_[0][1]-speed)/(G1_ * a_[0])),gamma_ * G1_);
  }
  // Left Shock
  if ((speed == S_[0][1]) && SR_[0]) {
    res[0] = 0.5*(rho_star_[0] + state_[0][0]);
    res[1] = 0.5*(u_star_ + state_[0][1]);
    res[2] = state_[0][2];
    res[3] = state_[0][3];
    res[4] = 0.5*(p_star_ + state_[0][4]);
  }

  // Right Shock
  if ((speed == S_[1][0]) && SR_[1]) {
    res[0] = 0.5*(rho_star_[1] + state_[1][0]);
    res[1] = 0.5*(u_star_ + state_[1][1]);
    res[2] = state_[1][2];
    res[3] = state_[1][3];
    res[4] = 0.5*(p_star_ + state_[1][4]);
  }


  return res;
}



void Ers::sound_speed() {
  for (int i = 0; i < 2; i++){
    a_[i] = std::sqrt(gamma_ * state_[i][4]/state_[i][0]);
  }
}




std::array<double,3> Ers::functor_p_star(double p){
  std::array<double,2> A;
  std::array<double,2> B;
  std::array<double,3> f = {state_[1][1]-state_[0][1], 0., 0.};
  u_star_ = 0.;

  double ftmp;
  for (int i = 0; i < 2; i++){
    if (p > state_[i][4]){
      SR_[i] = true;
      A[i] = G2_ / state_[i][0];
      B[i] = state_[i][4] * G2_ / G1_;
      
      ftmp = (p-state_[i][4]) * std::sqrt(A[i]/(p+B[i]));

      f[0] += ftmp;
      f[1] += (1-0.5*(p-state_[i][4])/(B[i]+p)) * std::sqrt(A[i]/(p+B[i]));
      f[2] += -0.25* (4*B[i]+3*p+state_[i][4])/std::pow(B[i]+p,2) * std::sqrt(A[i]/(p+B[i]));
    } else {
      SR_[i] = false;

      ftmp = G1_ * a_[i] * (std::pow(p/state_[i][4],1./(gamma_ * G1_))-1);

      f[0] += ftmp;
      f[1] += std::pow(state_[i][4]/p,1./(gamma_ * G2_)) / (state_[i][0]*a_[i]);
      f[2] += -a_[i]/(G2_*std::pow(gamma_ * state_[i][4],2)* std::pow(p/state_[i][4],0.5*(3*gamma_+1)/gamma_));
    }

    u_star_ += (i-0.5)*ftmp+0.5*state_[i][1];
  }
  return f;
}


double Ers::guess_p_star(){
  double CUP = 0.25*(state_[0][0] + state_[1][0])*(a_[0] + a_[1]);
  double PPV = fmax(0.5*(state_[0][4] + state_[1][4]) + 0.5*(state_[0][1] - state_[1][1])*CUP, 0);
  double pmin = fmin(state_[0][4],state_[1][4]);
  double pmax = fmax(state_[0][4],state_[1][4]);
  double qmax = pmax/pmin;
  double quser = 2.0;
  
  if ((qmax<=quser)&&(pmin<=PPV)&&(PPV<=pmax)) return PPV;
  if (PPV < pmin) {
    double PQ = std::pow(state_[0][4]/state_[1][4], 1./(gamma_ * G1_));
    double UM = (PQ*state_[0][1]/a_[0] + state_[1][1]/a_[1] + G1_*(PQ - 1.0))/(PQ/a_[0] + 1.0/a_[1]);
    double PTL = 1.0 + (state_[0][1] - UM)/(G1_*a_[0]);
    double PTR = 1.0 + (UM - state_[1][1])/(G1_*a_[1]);
    return 0.5*(state_[0][4]*std::pow(PTL,gamma_*G1_) + state_[1][4]*std::pow(PTR,gamma_*G1_));
  }
  
  double GEL = std::sqrt((G2_/state_[0][0])/(G2_/G1_*state_[0][4] + PPV));
  double GER = std::sqrt((G2_/state_[1][0])/(G2_/G1_*state_[1][4] + PPV));
  return (GEL*state_[0][4] + GER*state_[1][4] - (state_[1][1] - state_[0][1]))/(GEL + GER);
  return 0.5*(state_[0][4]+state_[1][4]);
}


void Ers::density_speed() {
  for (int i =0; i < 2; i++) {
    if (SR_[i]) {
      rho_star_[i] = state_[i][0] * (p_star_/state_[i][4]+G2_/G1_)/(G2_*p_star_/(G1_*state_[i][4])+1);
      S_[i][0] = state_[i][1] +2*(i-0.5)* a_[i]*std::sqrt(p_star_/state_[i][4]/(gamma_ * G2_)+1./(gamma_ * G1_));
      S_[i][1] = S_[i][0];
    } else {
      rho_star_[i] = state_[i][0] * std::pow(p_star_/state_[i][4],1./gamma_);
      S_[i][0] = state_[i][1] +2*(i-0.5)* a_[i];
      S_[i][1] = u_star_ +2*(i-0.5)* a_[i] * std::pow(p_star_/state_[i][4],1./(gamma_*G1_));
    }
  }
}