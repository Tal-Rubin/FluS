cmake_minimum_required(VERSION 3.10)

# set the project name
project(FluS)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
set(SOURCE_FILES src/exactRS/testErs.cpp src/exactRS/ers.h src/exactRS/ers.cpp src/extFunc/externalMath.hpp)
add_executable(testErs ${SOURCE_FILES})



