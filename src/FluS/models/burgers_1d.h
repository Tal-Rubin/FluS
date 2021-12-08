/*
 * @file burgers_1d.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-12-03
 *
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef BURGERS_1D_H_
#define BURGERS_1D_H_

#include <valarray>
#include <vector>

#include "../model.h"
#include "../dynamic_variable.h"

#include "../../mocks/mesh_mock.h"

class Burgers_1d : public Model {
public:
  Burgers_1d(const Mesh_1d_mock& mesh) : mesh_(mesh) {};   // Custom constructor
  ~Burgers_1d()  {};   // Destructor

  int dimen() const {
    return dimen_;
  }

  int fields() const {
    return fields_;
  }

  int parameters() const {
    return params_;
  }

  int local_model() const {
    return local_;
  }

  double flux(const double t, const Dynamic_Variable& state, Dynamic_Variable& ddt) const {
    (void) t;

    for (auto ed : mesh_.edge_vect) {
      std::valarray<double> left = state.get_element(ed.neighbor_elements.first);
      std::valarray<double> right = state.get_element(ed.neighbor_elements.second);
      std::valarray<double> el_flux (state.element_size());

      el_flux = std::signbit(ed.unit_vector[0]) * 0.5 * right * right + \
	(1-std::signbit(ed.unit_vector[0])) * 0.5 * left * left;
	
      ddt.element(ed.neighbor_elements.first) -= el_flux;
      ddt.element(ed.neighbor_elements.second) += el_flux;
    }

    ddt.data_ /= mesh_.element_volume;
    return mesh_.min_elem_vol
  }

private:
  static const int dimen_ = 1;       // 1D
  static const int fields_ = 1;      // Density only 
  static const int params_ = 1;      // Finite volume method
  static const bool local_ = true;   // Local flux, source
  const Mesh_1d_mock& mesh_;
}

#endif   //BURGERS_1D_H
  
