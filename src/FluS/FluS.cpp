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
#include <cstddef>
#include <vector>

#include <libconfig.h++>

#include "model.h"
#include "model_factory.hpp"
#include "forward_euler.h"
#include "preproc.h"
#include "dynamic_variable.h"

#define VER1 0
#define VER2 0
#define VER3 0

int read_params(std::string config_file, double &t_end, double & time_step_scaling, std::vector<unsigned int> & num_ele, std::vector<std::vector<double>> & positions, 
                  std::vector<bool> & circular, std::string & model_name, std::vector<double> & model_parameters, unsigned int & output_freq,
                  std::vector<double> & const_IC, std::vector<double> & gaussian_amplitude, std::vector<double>& low_half_amplitude);

int main(int argc, char **argv) {
  
  if (argc != 2) {
    throw std::invalid_argument("Expected a single string, for a configuration file path.");
    return 1;
  }
  std::string config_file = argv[1];


  std::vector<unsigned int> num_ele;
  std::vector<std::vector<double>> positions;
  std::vector<bool> circular;

  std::string model_name;
  std::vector<double> model_parameters;
  

  std::vector<double> const_IC;
  std::vector<double> gaussian_amplitude;
  std::vector<double> low_half_amplitude;

  
  double t_end;
  double time_step_scaling;
  unsigned int output_freq;

  double t = 0.;




  if( read_params(config_file, t_end, time_step_scaling,  num_ele, positions, circular, \
  model_name, model_parameters, output_freq, const_IC, gaussian_amplitude, low_half_amplitude)!=0) { 
    return 1;
  }



  if (!(num_ele.size() == 1 && positions.size() == 1 && circular.size() == 1)) {
    throw std::invalid_argument("Currently, only 1d mesh is implemented. Sorry.");
  }

  Mesh mesh(num_ele[0],  positions[0], circular[0]);

  std::ofstream OutputFile;
  OutputFile.open ("mesh.txt");
  OutputFile << mesh;
  OutputFile.close ();

  std::unique_ptr<Model> model = Model_factory::get_model(model_name, model_parameters, mesh);
  std::cout<<model->fields()<<" "<<model->parameters()<<"\n";

  
  Dynamic_Variable state (mesh.num_elements(), model->fields(), model->parameters()); 
  Dynamic_Variable ddt_flux(state.dim());
  Dynamic_Variable ddt_source(state.dim());

  if (const_IC.size() < model->fields()){
    throw std::invalid_argument("wrong number of initial conditions");
  }
  
  for (std::size_t i =0; i<model->fields(); i++){
    state.field_coeff(i,0) = const_IC[i];
    Preprocessor::gaussian_initial_conditions(gaussian_amplitude[i] ,state, i, mesh);
    Preprocessor::low_half_domain(low_half_amplitude[i] ,0 ,state, i, mesh);

  }

  std::cout<< t << " " << state;

  for (std::size_t steps = 0; t< t_end; steps++) {
    
    ddt_flux.data_ = 0;
    ddt_source.data_=0;
   // Boundary_conditions(BC, state, t);

    double dt = time_step_scaling * 2. *model->flux(t, state, ddt_flux);
    if (t+dt>t_end){
      dt = t_end - t;
    }
    

    state.data_= forward_euler(0.5 * dt, state, ddt_flux).data_;

    model->source(t, state, ddt_source);

    state.data_= forward_euler(dt, state, ddt_source).data_;
    
    ddt_flux.data_ = 0;
    (void) model->flux(t+0.5*dt, state, ddt_flux);
    

    state.data_= forward_euler(0.5 * dt, state, ddt_flux).data_;

    t += dt;



    if(steps % output_freq == 0) std::cout<< t << " " << state;

  }


  std::cout << "FIN"<<std::endl;
  return 0;

}



int read_params(std::string config_file, double &t_end, double & time_step_scaling, std::vector<unsigned int> & num_ele, std::vector<std::vector<double>> & positions, 
                  std::vector<bool> & circular, std::string & model_name, std::vector<double> & model_parameters, unsigned int & output_freq,
                  std::vector<double> & const_IC, std::vector<double> & gaussian_amplitude, std::vector<double>& low_half_amplitude) {

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
      time_step_scaling = root["general_settings"]["solver"]["time_step_scaling"];
    } catch(const libconfig::SettingTypeException &tex) {
      int tempint = root["general_settings"]["solver"]["time_step_scaling"];
      time_step_scaling = (double)tempint;        
    }

    try {
      std::string tmp_str = root["general_settings"]["solver"]["model_name"];  
      model_name = tmp_str;
    } catch (const libconfig::SettingNotFoundException &nfex) {
        fprintf(stderr, "No 'model_name' setting in configuration file.\n" );
        return -1;
    }

    try {
      const libconfig::Setting& mod_par = root["general_settings"]["solver"]["model_parameters"];

      for (int i = 0; i < mod_par.getLength(); i++) {
        model_parameters.push_back(mod_par[i]);
      }
    }  catch(const libconfig::SettingTypeException &tex) {
      const libconfig::Setting& mod_par = root["general_settings"]["solver"]["model_parameters"];

      for (int i = 0; i < mod_par.getLength(); i++) {
        int  tempint = mod_par[i];
        model_parameters.push_back((double) tempint);
      }      
    }
  

    try {
      const libconfig::Setting& positions_axes = root["general_settings"]["solver"]["position_axes"];
      positions.resize(positions_axes.getLength());
      num_ele.resize(positions_axes.getLength());
      circular.resize(positions_axes.getLength());

      for (std::size_t i = 0; i < positions.size(); i++){
        const libconfig::Setting& positions_axis = positions_axes[i];
        num_ele[i] = positions_axis["num_ele"];
        circular[i]= positions_axis["circular"];
        const libconfig::Setting& pos = positions_axis.lookup("positions");
        for (int j = 0; j< pos.getLength(); j++) {
          positions[i].push_back(pos[j]);
        }
      }
    } catch (const libconfig::SettingNotFoundException &nfex) {
        fprintf(stderr, "No 'position_axes' setting in configuration file.\n" );
        return -1;
    } 

    try {
      output_freq = root["general_settings"]["output"]["output_freq"];
    } catch (const libconfig::SettingNotFoundException &nfex) {
        fprintf(stderr, "No 'output_freq' setting in configuration file.\n" );
        return -1;
    } 

    
    try {
      const libconfig::Setting& ICs = root["general_settings"]["IC"]["fields"];
      const_IC.resize(ICs.getLength());
      gaussian_amplitude.resize(ICs.getLength());
      low_half_amplitude.resize(ICs.getLength());
      for (std::size_t i = 0; i < const_IC.size(); i++){
        const libconfig::Setting& IC = ICs[i];
        const_IC[i] = IC["const"];
        gaussian_amplitude[i] = IC["gaussian"][0];
        low_half_amplitude[i] = IC["const_half_domain"];
      }
    } catch (const libconfig::SettingNotFoundException &nfex) {
        fprintf(stderr, "No 'IC' setting in configuration file.\n" );
        return -1;
    } 


    return 0;
}