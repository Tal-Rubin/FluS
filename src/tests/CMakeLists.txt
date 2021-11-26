cmake_minimum_required(VERSION 3.10)

# set the project name
project(tests CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(test_NewtonHalley test_NewtonHalley.cpp)
add_executable(test_DynamicVar test_DynamicVar.cpp ../FluS/dynamic_variable.cpp ../FluS/forward_euler.cpp)
add_executable(test_valarray test_valarray.cpp)
