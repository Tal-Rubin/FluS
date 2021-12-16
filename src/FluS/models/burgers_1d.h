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
#include "../mesh1d.h"

class Burgers_1d : public Model {
public:
  // Custom constuctor
  Burgers_1d(const Mesh1D& mesh) : mesh_(mesh) {};
  // Destructor
  ~Burgers_1d() {};   

  int dimen() const {
    return dimen_;
  }

  unsigned int fields() const {
    return fields_;
  }

  unsigned int parameters() const {
    return params_;
  }

  unsigned int local_model() const {
    return local_;
  }

  double flux(const double t, const Dynamic_Variable& state, Dynamic_Variable& ddt) const {
    (void) t;

    for (auto ed : mesh_.edge_vect) {
      std::valarray<double> el_flux(state.element_size());
      std::valarray<double> left = state.get_element(ed.neighbor_elements.first);
      std::valarray<double> right = state.get_element(ed.neighbor_elements.second);

      el_flux = std::signbit(ed.unit_vector[0]) *  0.5 * std::pow(right, 2.0) + \
	(1-std::signbit(ed.unit_vector[0])) * 0.5 * std::pow(left, 2.0);
	
      ddt.element(ed.neighbor_elements.first) -= el_flux;
      ddt.element(ed.neighbor_elements.second) += el_flux;
    }

    ddt.data_ /= mesh_.el_volume;
    return mesh_.el_volume;
  }

private:
  // Space dimension: 1D
  static const int dimen_ = 1;       
  // Fields: density only
  static const int fields_ = 1;
  // Finit volume method
  static const int params_ = 1;
  // Local flux, source
  static const bool local_ = true;
  // Apply 1D mesh
  const Mesh1D& mesh_;
}

#endif   //BURGERS_1D_H
  
