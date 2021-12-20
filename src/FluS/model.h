/**
 * @file model.h
 * @author Tal Rubin (trubin@princeton.edu)
 * @brief 
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef FLUS_MODEL_H_
#define FLUS_MODEL_H_

#include "dynamic_variable.h"

class Model
{
public:
  virtual ~Model() {}

  /**
   * @brief Calculates the flux, \f$F\f$,for conservative PDEs, \f$\dot U + \nabla \cdot F = 0 \f$ .
   * 
   * @param t time
   * @param state state vector
   * @param ddt the flux funciton, return value.
   * @return double Maximal time-step, based on CFL-like criterion
   */
  virtual double flux(const double t, const Dynamic_Variable& state, Dynamic_Variable& ddt) const = 0 ;
  void source(const double t, const Dynamic_Variable& state, Dynamic_Variable& ddt) const {
    (void) t;
    (void) state;
    ddt.data_ =0;
  };


  virtual int dimen() const = 0;
  //! "getter" method for number of state variables associated with the system of ODEs (i.e. the size of x) 
  virtual unsigned int fields() const = 0;

  //! Getter method for number of parameters to desctibe each field. Default is 1 (finite volume), more would correspond to discontinuous Galerkin.
  unsigned int parameters() const {return 1;};


  /**
   * @brief Is the model local (depend on the state vector) or non-local (depend also on gradients of the state vector)
   * 
   * @return true Model is local
   * @return false Model depend on gradients
   */
   virtual bool local_model() const = 0;

};

#endif  // FLUS_MODEL_H_