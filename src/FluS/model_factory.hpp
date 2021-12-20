/**
 * @file model_factory.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef FLUS_MODEL_F_HPP_
#define FLUS_MODEL_F_HPP_

#include <string>
#include <stdexcept>
#include <memory>

#include "model.h"

#include "mesh.h"

#include "models/advection_1d.h"
#include "models/euler_1d.h"
#include "../FluS/models/euler_1d.h"

namespace Model_factory {
  
  std::unique_ptr<Model> get_model(std::string model_name, std::vector<double> model_parameters, Mesh & mesh) {
    if (model_parameters.size() != 1) {
      throw std::invalid_argument("Wrong number of model parameters.");
    }
    if (model_name == "Euler"){
      return std::make_unique<Euler_1d_Godunov>(model_parameters[0], mesh);
    } else if (model_name == "Advection") {
      return std::make_unique<Advection_1d_Upwind>(model_parameters[0], mesh);
    } else throw std::invalid_argument("No such model.");
    // returns pointer
    return nullptr;
  }

  unsigned int num_model_params(std::string model_name) {
    if (model_name == "Euler"){
      return 1;
    } else if (model_name == "Advection") {
      return 1;
    } else throw std::invalid_argument("No such model.");
    return 0;
  }



}




#endif // FLUS_MODEL_F_HPP_