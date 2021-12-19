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
#include "../mesh.h"
#include "../../exactRS/ers.h"


class Euler_2d_Godunov : public Model {

  public:

  Euler_2d_Godunov(double gamma, Mesh& mesh): gamma_(gamma), mesh_(mesh) {};
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

  double flux(const double t, const Dynamic_Variable& state, Dynamic_Variable& ddt, const int dim) const {
    /**
     * Apply the second order time step to model 2D Euler equation
     * The parameter dim: 0 refers to x direction; 1 refers to y direction
     */
    (void) t;
    double min_timestep = 10000.;
    
    /**
     * This for loop should be adaptable to both x and y directions
     * In edge_vector, row1 - horizontal edges; row2 - vertical edges
     * In 2D case, there is flow in both x and y directions
     */
    for (auto ed : mesh_.edge_vect[1-dim]){
      std::valarray<double> first = state.get_element(ed.neighbor_elements.first);
      std::valarray<double> second = state.get_element(ed.neighbor_elements.second);

      first[1] /=  first[0];
      first[2] /=  first[0];
      first[3] /=  first[0];
      first[4] =  (gamma_-1)*(first[4] - 0.5*first[0]*(first[1]*first[1]+first[2]*first[2]+first[3]*first[3]));

      second[1] /=  second[0];
      second[2] /=  second[0];
      second[3] /=  second[0];
      second[4] =  (gamma_-1)*(second[4] - 0.5*second[0]*(second[1]*second[1]+second[2]*second[2]+second[3]*second[3]));
      
      Ers ers(first, second, gamma_);
      std::valarray<double> W = ers.W(0);
      std::valarray<double> el_flux (state.element_size());
      el_flux[0] = W[0]*W[dim+1];
      el_flux[1] = W[0]*W[dim+1]*W[1] + std::signbit(dim-1) * W[4];
      el_flux[2] = W[0]*W[dim+1]*W[2] + std::signbit((-1) * dim) * W[4];
      el_flux[3] = W[0]*W[dim+1]*W[3];
      el_flux[4] = W[0]*W[dim+1]*(0.5*(W[1]*W[1]+W[2]*W[2]+W[3]*W[3])) + W[4]*W[dim+1]/(gamma_-1);
      
      ddt.element(ed.neighbor_elements.first) -= std::signbit(ed.unit_vector[dim]) * el_flux;
      ddt.element(ed.neighbor_elements.second) += std::singbit(ed.unit_vector[dim]) * el_flux;

      
      min_timestep = 2 * std::min(min_timestep, \
				  std::min(mesh_.elem_vect[ed.neighbor_elements.first].volume, \
					   mesh_.elem_vect[ed.neighbor_elements.second].volume) / ers.max_speed());
    }

    return min_timestep;
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
  static const int fields_ = 5;
  // finite volume
  static const int params_ = 1;
  // Local flux, source
  static const bool local_ = true;
  double gamma_;
  const Meshd& mesh_;

};

#endif // FLUS_EULER_2D_H_
