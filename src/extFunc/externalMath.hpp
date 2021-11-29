/**
 * @file externalMath.hpp
 * External useful math functions
 * 
 * \copyright Copyright (c) 2021 Tal Rubin Distributed under MIT License.
*/


#ifndef EXMATH_HPP_
#define EXMATH_HPP_

#include <cmath>
#include <stdexcept>
#include <iostream>

/**
 * @brief Namespace for math functions that don't belong in any specific project. 
 */
namespace ExtaMath{
  /**
   * @brief Newton-Rhapson root-finding iterator for function f
   * 
   * @tparam F type of f
   * @tparam T data type. double was tested
   * @param f returns an array / vecotr / pair / tuple of {f(x), f'(x)}
   * @param guess initial guess
   * @param min range minimum
   * @param max range maximum
   * @param tol solution tolerance
   * @param max_iteration maximal number of iterations
   * @return T value of root of f
   */


  template <class F,class T>
  T newton (F f, T guess, T min, T max, T tol, int max_iteration) {
    if (max < min) throw std::range_error( "max < min" ); 
    if (guess < min || guess > max) throw std::out_of_range( "guess out of range" );
    
    T val = guess;
    auto f_ = f(guess);
    T delta;
    for (int i =0; i < max_iteration; i++){
      delta = f_[0]/f_[1];
      val -= delta;

      if (val < min || val > max) throw std::out_of_range( "iteration left range" );
      if (std::abs(delta) <tol) {
        return val;      
      }
      f_ = f(val);
    }
    throw std::length_error("not converged after max_iteration");
  }

  /**
   * @brief Halley root-finding iterator for function f
   * 
   * @tparam F type of f
   * @tparam T data type. double was tested
   * @param f returns an array / vecotr / pair / tuple of {f(x), f'(x), f''(x)}
   * @param guess initial guess
   * @param min range minimum
   * @param max range maximum
   * @param tol solution tolerance
   * @param max_iteration maximal number of iterations
   * @return T value of root of f
   */

  template <class F,class T>
  T halley (F f, T guess, T min, T max, T tol, int max_iteration) {
    if (max < min) throw std::range_error( "max < min" ); 
    if (guess < min || guess > max) throw std::out_of_range( "guess out of range" );
    
    T val = guess;
    auto f_ = f(guess);
    T delta;
    for (int i =0; i < max_iteration; i++){
      delta = 2*f_[0]*f_[1]/(2*f_[1]*f_[1]-f_[0]*f_[2]);
      val -= delta;

      if (val < min || val > max) throw std::out_of_range( "iteration left range" );
      if (std::abs(2*delta/(2*val)) <tol) {
     //   std::cout<<i<<std::endl; //number of iterations
        return val;      
      }
      f_ = f(val);
    }
    throw std::length_error("not converged after max_iteration");
  }

}

#endif // EXMATH_HPP_
