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


#ifndef FLUS_PREP_MOCK_H_
#define FLUS_PREP_MOCK_H_


#include <string>

#include "../FluS/dynamic_variable.h"
#include "../mocks/mesh_mock.h"

/**
 * @brief Namespace for FluS' preprocessor functionality
 * 
 */
namespace Preprocessor {

  void initial_conditions(std::string expression, Dynamic_Variable & state, const std::size_t field, const Mesh_1d_mock & mesh);


}

#endif // FLUS_PREP_MOCK_H_
