/**
 * @file model.h
 * @author your name (you@domain.com)
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

  // Calculates d/dt of the state
  // variables `x` at `t` (using f(t,x) ), returns result in `fx[]`.
  //
  // Should return 0 if successful, nonzero if error.
  virtual double flux(const double t, const Dynamic_Variable& state, Dynamic_Variable& ddt) const = 0 ;
 // virtual Dynamic_Variable source(double t, const Dynamic_Variable& state) const = 0;


  virtual int dimen() const = 0;
  // "getter" method for number of state variables associated with the
  // system of ODEs (i.e. the size of x)
  virtual int fields() const = 0;


  /**
   * @brief Is the model local (depend on the state vector) or non-local (depend also on gradients of the state vector)
   * 
   * @return true Model is local
   * @return false Model depend on gradients
   */


   virtual bool local_model() const = 0;

};

#endif  // FLUS_MODEL_H_