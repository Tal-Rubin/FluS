cmake_minimum_required(VERSION 3.10)

# set the project name
project(tests CXX)

# add the executable
add_executable(test_dynamic_variable test_catch.cpp test_dynamic_variable.cpp ../FluS/dynamic_variable.cpp)
add_executable(test_mesh1d test_catch.cpp test_mesh1d.cpp ../FluS/mesh.cpp)

add_test(test_dynamic_variable test_dynamic_variable)
add_test(test_mesh1d test_mesh1d)


#add_executable(test_mesh1d test_mesh1d.cpp)