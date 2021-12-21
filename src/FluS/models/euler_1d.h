/**
 * @file euler_1d.h
 * @author Tal Rubin (trubin@princeton.edu)
 * @brief 
 * @version 0.1
 * @date 2021-12-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef FLUS_EULER_1D_H_
#define FLUS_EULER_1D_H_

#include <valarray>
#include <vector>

#include "../model.h"
#include "../dynamic_variable.h"

#include "../mesh.h"
#include "../../exactRS/ers.h"


class Euler_1d_Godunov : public Model {

  public:

  Euler_1d_Godunov(double gamma, Mesh& mesh): gamma_(gamma), mesh_(mesh) {};
  ~Euler_1d_Godunov() {};

  int dimen() const {
    return dimen_;
  }

  unsigned int fields() const {
    return fields_;
  }

  unsigned int parameters() const {
    return params_;
  }

  bool local_model() const {
    return local_;
  }

  double flux(const double t, const Dynamic_Variable& state, Dynamic_Variable& ddt)const {
    (void) t;
    double min_timestep = 10000.;
    for (auto edges:mesh_.edge_vect){
    for (auto ed:edges){
      std::valarray<double> left = state.get_element(ed.neighbor_elements.first);
      std::valarray<double> right = state.get_element(ed.neighbor_elements.second);

      left[1] /=  left[0];
      left[2] /=  left[0];
      left[3] /=  left[0];
      left[4] =  (gamma_-1)*(left[4]-0.5*left[0]*(left[1]*left[1]+ left[2]*left[2]+left[3]*left[3]));

      right[1] /=  right[0];
      right[2] /=  right[0];
      right[3] /=  right[0];
      right[4] =  (gamma_-1)*(right[4]-0.5*right[0]*(right[1]*right[1]+ right[2]*right[2]+right[3]*right[3]));


      
      Ers ers(left,right,gamma_);
      std::valarray<double> W = ers.W(0);
      std::valarray<double> el_flux (state.element_size());
      el_flux[0] = W[0]*W[1];
      el_flux[1] = W[0]*W[1]*W[1] + W[4];
      el_flux[2] = W[0]*W[1]*W[2];
      el_flux[3] = W[0]*W[1]*W[3];
      el_flux[4] = W[0]*W[1]*(0.5*(W[1]*W[1]+ W[2]*W[2]+W[3]*W[3])) + W[4]*W[1]/(gamma_-1);
      
      ddt.element(ed.neighbor_elements.first) -=  (!mesh_.elem_vect[ed.neighbor_elements.first].ghost)* el_flux;
      ddt.element(ed.neighbor_elements.second) += (!mesh_.elem_vect[ed.neighbor_elements.second].ghost)* el_flux;


      min_timestep = std::min(min_timestep, std::min(mesh_.elem_vect[ed.neighbor_elements.first].volume,mesh_.elem_vect[ed.neighbor_elements.second].volume)/ers.max_speed());
    }
    }
    return min_timestep;
  }
/*  Dynamic_Variable source(const double t, const Dynamic_Variable& state) const {
    (void) t;
    return (state.dim_);
  }*/


  private:
  // Space dimension
  static const int dimen_ = 1;
  // density only
  static const int fields_ = 5;
  // finite volume
  static const int params_ = 1;
  // Local flux, source
  static const bool local_ = true;
  double gamma_;
  Mesh& mesh_;

};




#endif // FLUS_EULER_1D_H_