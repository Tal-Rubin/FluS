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

  Advection_2d_Upwind(std::valarray<double> advection_velocity, const Mesh& mesh) : advection_velocity_(advection_velocity), mesh_(mesh) {};
  
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

  double flux(const double t, const Dynamic_Variable& state, Dynamic_Variable& ddt, const int dim) const {
    (void) t;
    num_row_ = mesh_.num_ele[0];
    num_col_ = mesh_.num_ele[1];

    /**
     * This for loop should be adaptable to both x and y directions
     * In edge_vector, row1 - horizontal edges; row2 - vertical edges
     * Conservation: \f$\dot U + \sum Flux * area / volume  = 0 \f$
     */
    for (int i = 0; i < 2; i++) {
      for (auto ed: mesh_.edge_vect[dim-i]) {
	std::valarray<double> el_flux (state.element_size());
        std::valarray<double> first = state.get_element(ed.neighbor_elements.first);
        std::valarray<double> second = state.get_element(ed.neighbor_elements.second);
      
        el_flux = std::signbit(advection_velocity_[i] * ed.unit_vector[i])*advection_velocity_[i] * second + \
	  (1-std::signbit(advection_velocity_[i] * ed.unit_vector[i]))*advection_velocity_[i] * first;

        ddt.element(ed.neighbor_elements.first) -= ed.unit_vector[i] * el_flux;
        ddt.element(ed.neighbor_elements.first) *= ed.edge_area;
        ddt.element(ed.neighbor_elements.second) += ed.unit_vector[i] * el_flux;
	ddt.element(ed.neighbor_elements.second) *= ed.edge_area;
	
      }
      ddt.data_ /= mesh_.element_volume[i];
    }
    
    return mesh_.min_elem_vol / sqrt(pow(advection_velocity_[0], 2.0) + pow(advection_velocity_[1], 2.0));
  }

  int BC(Dynamic_variable& state, const double t, std::valarray<double> (*f_pr)(double, int)) {
    /* @brief Member function to set up boundary conditions for s specific model
     *        Impose the fields on 4 boundaries respectively
     * 
     * @param state A set of Dynamic_Variable
     * @param f_pr pointer to a field function
     */
    num_ele_ = mesh_.num_elements();
    num_row_ = mesh_.num_ele[0];
    num_col_ = mesh_.num_ele[1];
   
    // For non-circular boundaries, impose the fields on the ghost cells after each step
    if (mesh_.circular[0] == false) {
      for (int j = 1; j < num_row_ -1; j++) {
	  state.element(j) = f_pr(t, j);
	  state.element(num_ele_ - 1 - j) = f_pr(t, num_ele_ - 1 - j);
      }
    }
    
    if (mesh_.circular[1] == false) {
      for (int i = 1; i < num_col_ -1; i++) {
	state.element(num_row_ * i) = f_pr(t, num_row_ * i);
	state.element(num_row_ * (i+1) - 1) = f_pr(t, num_row_ * (i+1) - 1);
      }  
    }

    return 0;   
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

  const Mesh& mesh_;

};




#endif // ADVEC_2D_H_
