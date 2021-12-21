cmake_minimum_required(VERSION 3.10)

# set the project name
project(FluS CXX)

# add the executable
add_executable(FluS FluS.cpp forward_euler.cpp dynamic_variable.cpp ../exactRS/ers.cpp mesh.cpp preproc.cpp)
target_link_libraries(FluS -lconfig++)
