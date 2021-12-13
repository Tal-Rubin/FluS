cmake_minimum_required(VERSION 3.10)

# set the project name
project(tests CXX)

# add the executable
add_executable(test_NewtonHalley test_NewtonHalley.cpp)
add_executable(test_mesh test_mesh.cpp)

add_executable(test_advection test_advection.cpp ../FluS/dynamic_variable.cpp ../FluS/forward_euler.cpp ../mocks/preproc_mock.cpp)
add_executable(test_euler test_euler.cpp ../FluS/dynamic_variable.cpp ../FluS/forward_euler.cpp ../mocks/preproc_mock.cpp ../exactRS/ers.cpp)



add_executable(test_catch test_catch.cpp test_dynamic_variable.cpp ../FluS/dynamic_variable.cpp)


add_test(test_catch test_catch)