/**
 * @file euler_2d.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef FLUS_EULER_2D_H_
#define FLUS_EULER_2D_H_

#include <valarray>
#include <vector>

#include "../model.h"
#include "../dynamic_variable.h"
#include "../mesh2d.h"
#include "../../exactRS/ers.h"


class Euler_2d_Godunov : public Model {

  public:

  Euler_2d_Godunov(double gamma, Mesh2D& mesh): gamma_(gamma), mesh_(mesh) {};
  ~Euler_2d_Godunov() {};

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

  double flux(const double t, const Dynamic_Variable& state, Dynamic_Variable& ddt) const {
    /**
     * Apply the second order time step to model 2D Euler equation
     */
    (void) t;
    double min_timestep = 10000.;
    
    // Push dx forward in the first half dt
    for (auto ed : mesh_.vert_edge_vect){
      std::valarray<double> left = state.get_element(ed.neighbor_elements.first);
      std::valarray<double> right = state.get_element(ed.neighbor_elements.second);

      left[1] /=  left[0];
      left[2] /=  left[0];
      left[3] /=  left[0];
      left[4] =  (gamma_-1)*(left[4] - 0.5*left[0]*(left[1]*left[1]+left[2]*left[2]+left[3]*left[3]));

      right[1] /=  right[0];
      right[2] /=  right[0];
      right[3] /=  right[0];
      right[4] =  (gamma_-1)*(right[4] - 0.5*right[0]*(right[1]*right[1]+right[2]*right[2]+right[3]*right[3]));
      
      Ers ers(left,right,gamma_);
      std::valarray<double> W = ers.W(0);
      std::valarray<double> el_flux (state.element_size());
      el_flux[0] = W[0]*W[1];
      el_flux[1] = W[0]*W[1]*W[1] + W[4];
      el_flux[2] = W[0]*W[1]*W[2];
      el_flux[3] = W[0]*W[1]*W[3];
      el_flux[4] = W[0]*W[1]*(0.5*(W[1]*W[1]+W[2]*W[2]+W[3]*W[3])) + W[4]*W[1]/(gamma_-1);
      
      ddt.element(ed.neighbor_elements.first) -=el_flux;
      ddt.element(ed.neighbor_elements.second) +=el_flux;

      /**
       * min_timestep = 2 * std::min(min_timestep, \
       *			     std::min(mesh_.elem_vect[ed.neighbor_elements.first].volume, \
       *				      mesh_.elem_vect[ed.neighbor_elements.second].volume) / ers.max_speed());
       */
    }

    // Push dy forward in dt
    for (auto ed : mesh_.hori_edge_vect){
      std::valarray<double> upp = state.get_element(ed.neighbor_elements.first);
      std::valarray<double> low = state.get_element(ed.neighbor_elements.second);

      upp[1] /=  upp[0];
      upp[2] /=  upp[0];
      upp[3] /=  upp[0];
      upp[4] =  (gamma_-1)*(upp[4] - 0.5*upp[0]*(upp[1]*upp[1]+upp[2]*upp[2]+upp[3]*upp[3]));

      low[1] /=  low[0];
      low[2] /=  low[0];
      low[3] /=  low[0];
      low[4] =  (gamma_-1)*(low[4] - 0.5*low[0]*(low[1]*low[1]+low[2]*low[2]+low[3]*low[3]));
      
      Ers ers(upp,low,gamma_);
      std::valarray<double> W = ers.W(0);
      std::valarray<double> el_flux (state.element_size());
      el_flux[0] = W[0]*W[1];
      el_flux[1] = W[0]*W[1]*W[1] + W[4];
      el_flux[2] = W[0]*W[1]*W[2];
      el_flux[3] = W[0]*W[1]*W[3];
      el_flux[4] = W[0]*W[1]*(0.5*(W[1]*W[1]+ W[2]*W[2]+W[3]*W[3])) + W[4]*W[1]/(gamma_-1);
      
      ddt.element(ed.neighbor_elements.first) -=el_flux;
      ddt.element(ed.neighbor_elements.second) +=el_flux;

      /**
       * min_timestep = std::min(min_timestep, \
       *			 std::min(mesh_.elem_vect[ed.neighbor_elements.first].volume, \
       *				  mesh_.elem_vect[ed.neighbor_elements.second].volume) / ers.max_speed());
       */
    }


    // Push dx forward in the latter half dt
    for (auto ed : mesh_.edge_vect){
      std::valarray<double> left = state.get_element(ed.neighbor_elements.first);
      std::valarray<double> right = state.get_element(ed.neighbor_elements.second);

      left[1] /=  left[0];
      left[2] /=  left[0];
      left[3] /=  left[0];
      left[4] =  (gamma_-1)*(left[4] - 0.5*left[0]*(left[1]*left[1]+left[2]*left[2]+left[3]*left[3]));

      right[1] /=  right[0];
      right[2] /=  right[0];
      right[3] /=  right[0];
      right[4] =  (gamma_-1)*(right[4] - 0.5*right[0]*(right[1]*right[1]+right[2]*right[2]+right[3]*right[3]));
      
      Ers ers(left,right,gamma_);
      std::valarray<double> W = ers.W(0);
      std::valarray<double> el_flux (state.element_size());
      el_flux[0] = W[0]*W[1];
      el_flux[1] = W[0]*W[1]*W[1] + W[4];
      el_flux[2] = W[0]*W[1]*W[2];
      el_flux[3] = W[0]*W[1]*W[3];
      el_flux[4] = W[0]*W[1]*(0.5*(W[1]*W[1]+ W[2]*W[2]+W[3]*W[3])) + W[4]*W[1]/(gamma_-1);
      
      ddt.element(ed.neighbor_elements.first) -=el_flux;
      ddt.element(ed.neighbor_elements.second) +=el_flux;

      /** 
       * min_timestep = 2 * std::min(min_timestep, \
       *			     std::min(mesh_.elem_vect[ed.neighbor_elements.first].volume, \
       *				      mesh_.elem_vect[ed.neighbor_elements.second].volume) / ers.max_speed());
       */
    }
   
    return min_timestep / 2.;
  }

  private:
  // Space dimension
  static const int dimen_ = 2;
  // density only
  static const int fields_ = 5;
  // finite volume
  static const int params_ = 1;
  // Local flux, source
  static const bool local_ = true;
  double gamma_;
  const Mesh2d& mesh_;

};

#endif // FLUS_EULER_2D_H_
