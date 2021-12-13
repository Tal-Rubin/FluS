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



#include <iostream>
#include <stdio.h>

#include <libconfig.h++>

int loadSolverParameters(double &t, int & grid);

int main(){
  double t;

  int grid;

  if (loadSolverParameters(t, grid) ==0){
    std::cout<<"success "<< t<< " "<< grid<< " \n";
  }
}

int loadSolverParameters(double &t, int & grid) {

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
            if (int(FluS_version[0]) !=0 || int(FluS_version[1]) !=0 || int(FluS_version[2]) !=0) {
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
        t = root["general_settings"]["solver"]["time_final"];
    } catch(const libconfig::SettingTypeException &tex) {
        int tempint = root["general_settings"]["solver"]["time_final"];
        t = double(tempint);        
    }
    
    try {
        grid = root["general_settings"]["solver"]["N_grid"];
    } catch(const libconfig::SettingTypeException &tex) {
        fprintf(stderr, "N_grid has to be an integer.\n" );
        return -1;        
    }
    
    return 0;
}