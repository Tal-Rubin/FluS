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

#include "models/advection_1d.h"

Model * get_model(std::string model_name) {
  if (model_name == "advection") return new Advection_1D (1.);

  else throw std::invalid_argument("No such model.");
  return nullptr;
}




#endif // FLUS_MODEL_F_HPP_