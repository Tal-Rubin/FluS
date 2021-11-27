cmake_minimum_required(VERSION 3.10)

# set the project name
project(ExactReimannSolver CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
set(SOURCE_FILES testErs.cpp ers.cpp)
add_executable(testErs ${SOURCE_FILES})

