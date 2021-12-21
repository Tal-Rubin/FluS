/**
 * @file preproc.h
 * @author Tal Rubin (trubin@princeton.edu)
 * @brief Pre-processing module for FluS
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef FLUS_PREP_H_
#define FLUS_PREP_H_


#include <string>

#include "dynamic_variable.h"
#include "mesh.h"

/**
 * @brief Namespace for FluS' preprocessor functionality
 * 
 */
namespace Preprocessor {

  void gaussian_initial_conditions(double amplitude,Dynamic_Variable & state, const std::size_t field, const Mesh & mesh);
  void low_half_domain(double amplitude, int dim, Dynamic_Variable & state, const std::size_t field, const Mesh & mesh);

}

#endif // FLUS_PREP_H_