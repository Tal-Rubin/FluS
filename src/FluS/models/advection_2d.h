/**
 * @file advection_2d.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef ADVEC_2D_H_
#define ADVEC_2D_H_

#include <valarray>
#include <vector>
#include <math.h>

#include "../model.h"
#include "../dynamic_variable.h"
#include "../mesh2d.h"

class Advection_2d_Upwind : public Model {

  public:

 Advection_2d_Upwind(std::valarray<double> advection_velocity, const Mesh2D& mesh) : advection_velocity_(advection_velocity), mesh_(mesh) {};
  
  ~Advection_2d_Upwind() {};

  int dimen() const {
    return dimen_;
  }

  int fields() const {
    return fields_;
  }

  int parameters() const {
    return params_;
  }

  bool local_model() const {
    return local_;
  }

  double flux(const double t, const Dynamic_Variable& state, Dynamic_Variable& ddt)const {
    (void) t;

    // Flux in the x direction
    for (auto ed: mesh_.vert_edge_vect)  {
      std::valarray<double> el_flux (state.element_size());
      std::valarray<double> left = state.get_element(ed.neighbor_elements.first);
      std::valarray<double> right = state.get_element(ed.neighbor_elements.second);
      
      el_flux = std::signbit(advection_velocity_[0] * ed.unit_vector[0])*advection_velocity_[0] * right + \
	(1-std::signbit(advection_velocity_[0] * ed.unit_vector[0]))*advection_velocity_[0] * left;
      
      ddt.element(ed.neighbor_elements.first) -=el_flux;
      ddt.element(ed.neighbor_elements.second) +=el_flux;
    }

    // Flux in the y direction
    for (auto ed: mesh_.hori_edge_vect)  {
      std::valarray<double> el_flux (state.element_size());
      std::valarray<double> upp = state.get_element(ed.neighbor_elements.first);
      std::valarray<double> low = state.get_element(ed.neighbor_elements.second);
      
      el_flux = std::signbit(advection_velocity_[1] * ed.unit_vector[1])*advection_velocity_[1] * low + \
                  (1-std::signbit(advection_velocity_[1] * ed.unit_vector[1]))*advection_velocity_[1] * upp;
      
      ddt.element(ed.neighbor_elements.first) +=el_flux;
      ddt.element(ed.neighbor_elements.second) -=el_flux;
    }

    ddt.data_ /= mesh_.element_volume;
    
    return mesh_.min_elem_vol / sqrt(pow(advection_velocity_, 2.0) + pow(advection_velocity_, 2.0));
  }
  
  private:
  // Space dimension
  static const int dimen_ = 2;
  // density only
  static const int fields_ = 1;
  // finite volume
  static const int params_ = 1;
  // Local flux, source
  static const bool local_ = true;

  const std::valarray<double> advection_velocity_;

  const Mesh2D& mesh_;

};




#endif // ADVEC_2D_H_
