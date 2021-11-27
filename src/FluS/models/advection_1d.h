/**
 * @file advection_1d.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef ADVEC_1D_H_
#define ADVEC_1D_H_

#include <valarray>
#include <vector>

#include "../model.h"

class Advection_1D : public Model {

  public:

  Advection_1D(double advection_velocity): advection_velocity_(advection_velocity) {};
  ~Advection_1D();

  int dimen() const {
    return dimen_;
  }

  int fields() const {
    return fields_;
  }

  bool local_model() const {
    return local_;
  }

  std::vector<std::valarray<double>> flux(double t, std::valarray<double> state) const {
    return std::vector<std::valarray<double>> (dimen_, advection_velocity_ * state );             
  }
  std::valarray<double> source(double t, std::valarray<double> state) const {
    return std::valarray<double> (dimen_);                        
  }


  private:
  // Space dimension
  static const int dimen_ = 1;
  // density only
  static const int fields_ = 1;
  // Local flux, source
  static const bool local_ = true;

  const double advection_velocity_;
};




#endif // ADVEC_1D_H_