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
#include "../dynamic_variable.h"

#include "../../mocks/mesh_mock.h"

class Advection_1D : public Model {

  public:

  Advection_1D(double advection_velocity, const Mesh_1d_mock& mesh): advection_velocity_(advection_velocity), mesh_(mesh) {};
  ~Advection_1D() {};

  int dimen() const {
    return dimen_;
  }

  int fields() const {
    return fields_;
  }

  bool local_model() const {
    return local_;
  }

  double flux(const double t, const Dynamic_Variable& state, Dynamic_Variable& ddt)const {
    (void) t;

    for (auto ed: mesh_.edge_vect)  {
      std::valarray<double> el_flux (state.dim_[1]*state.dim_[2]);
      el_flux = std::signbit(advection_velocity_ * ed.unit_vector[0])*advection_velocity_ * state.get_element(ed.neighbor_elements.second) + \
                  (1-std::signbit(advection_velocity_ * ed.unit_vector[0]))*advection_velocity_ * state.get_element(ed.neighbor_elements.first);
      ddt.element(ed.neighbor_elements.first) -=el_flux;
      ddt.element(ed.neighbor_elements.second) +=el_flux;
    }

    ddt.data_ /= mesh_.element_volume;
    return mesh_.min_elem_vol/std::abs(advection_velocity_);
  }
/*  Dynamic_Variable source(const double t, const Dynamic_Variable& state) const {
    (void) t;
    return (state.dim_);
  }*/


  private:
  // Space dimension
  static const int dimen_ = 1;
  // density only
  static const int fields_ = 1;
  // Local flux, source
  static const bool local_ = true;

  const double advection_velocity_;

  const Mesh_1d_mock& mesh_;

};




#endif // ADVEC_1D_H_