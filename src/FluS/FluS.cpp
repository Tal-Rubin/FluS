/**
 * @file FluS.cpp 
 * @author Tal Rubin (trubin@princeton.edu)
 * @brief Main driver code for the FluS Fluid Solver
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>


#include <libconfig.h++>

#include "model.h"
#include "model_factory.hpp"
#include "forward_euler.h"
#include "dynamic_variable.h"

#define VER1 0
#define VER2 0
#define VER3 0

int read_params(std::string config_file, double &t_end, unsigned int & Ngrid);

int main(int argc, char **argv) {
  
  if (argc != 2) {
    throw std::invalid_argument("Expected a single string, for a configuration file path.");
    return 1;
  }
  std::string config_file = argv[1];
  
  double t_end;
  unsigned int Ngrid;
  read_params(config_file, t_end, Ngrid);
  //get data from user

  //init mesh, model, state

  //Mesh mesh(mesh_parameters);
  /*
  std::ofstream OutputFile;
  OutputFile.open ("mesh.txt");
  OutputFile << mesh;
  OutputFile.close ();*/

  //std::unique_ptr<Model> model = Model_factory::get_model(model_name, model_parameters, mesh);

  
  Dynamic_Variable state (5,1,1);//mesh.n_elements(), model->fields(), model->parameters()); 
  Dynamic_Variable ddt(state.dim());


  //Preprocessor::initial_conditions(initial_condition_string, state);


  //Boundary_conditions(BC, state, 0.);
  double CFL_frac = 0.9;
  std::cout<<state;
  double t = 0;
  while (t< t_end) {
    
    ddt.data_ = 0;
   // Boundary_conditions(BC, state, t);

    double dt = CFL_frac;// * model->flux(0, state, ddt);
    if (t+dt>t_end){
      dt = t_end - t;
    }

    state.data_= forward_euler(dt, state, ddt).data_;
    t += dt;

  }



  std::cout<<state;

  return 0;

}



int read_params(std::string config_file, double &t_end, unsigned int & Ngrid) {

    libconfig::Config FluSConfig;
    
    try {
        FluSConfig.readFile(config_file.c_str());
    } catch(const libconfig::FileIOException &fioex) {
        fprintf(stderr, "I/O error while reading file.\n");
        return -1;
    } catch(const libconfig::ParseException &pex) {
        fprintf(stderr, "Parse error at %s: Line %d - %s \n", pex.getFile(), pex.getLine()-1, pex.getError());
        return -1;
    }


    try {        
        const libconfig::Setting &FluS_version = FluSConfig.lookup("FluS_version");
        if (FluS_version.getLength() == 3)  {
            if (int(FluS_version[0]) !=VER1 || int(FluS_version[1]) !=VER2 || int(FluS_version[2]) !=VER3) {
            fprintf(stderr, "Configuration file format mismatch.\n"); }
        } else {
            fprintf(stderr, "'FluS_version' not in the correct format.\n");
        }
    } catch(const libconfig::SettingNotFoundException &nfex) {
        fprintf(stderr, "No 'FluS_version' setting in configuration file.\n" );
        return -1;
    }

    const libconfig::Setting& root = FluSConfig.getRoot();

    try {
      t_end = root["general_settings"]["solver"]["time_final"];
    } catch(const libconfig::SettingTypeException &tex) {
      int tempint = root["general_settings"]["solver"]["time_final"];
      t_end = (double)tempint;        
    }
    
    try {
      Ngrid = root["general_settings"]["solver"]["N_grid"];
    } catch(const libconfig::SettingTypeException &tex) {
      fprintf(stderr, "N_grid has to be an integer.\n" );
      return -1;        
    }
    
    return 0;
}