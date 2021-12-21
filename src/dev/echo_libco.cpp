/**
 * @file test_libco.cpp
 * @author Tal Rubin
 * @brief Making sure cmake links libconfig properly
 * @version 0.1
 * @date 2021-12-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#define VER1 0
#define VER2 0
#define VER3 0

#include <iostream>
#include <stdio.h>
#include <valarray>
#include <vector>

#include <libconfig.h++>

int read_params(double &t_end, double & time_step_scaling, std::vector<unsigned int> & num_ele, std::vector<std::vector<double>> & positions, 
                  std::vector<bool> & circular, std::string & model_name, std::vector<double> & model_parameters);


int main(){
  std::vector<unsigned int> num_ele;
  std::vector<std::vector<double>> positions;
  std::vector<bool> circular;

  std::string model_name;
  std::vector<double> model_parameters;
  
  
  
  double t_end;
  double time_step_scaling;

  double t = 0.;
  if (read_params(t_end, time_step_scaling,  num_ele, positions, circular, model_name, model_parameters) ==0){
    std::cout<<"success "<< t<< " \n";
  }


  for (auto a:num_ele) std::cout<<a<<" ";
  for (auto b:positions) for(auto a:b) std::cout<<a<<" ";
  for (auto a:model_parameters) std::cout<<a<<" ";

  std::cout <<"\n";


  return 0;
}



int read_params(double &t_end, double & time_step_scaling, std::vector<unsigned int> & num_ele, std::vector<std::vector<double>> & positions, 
                  std::vector<bool> & circular, std::string & model_name, std::vector<double> & model_parameters) {

    libconfig::Config FluSConfig;
    
    try {
        FluSConfig.readFile("../src/FluS/FluSConfig.cfg");
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



    
    
    return 0;
}