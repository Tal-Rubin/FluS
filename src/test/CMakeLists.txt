cmake_minimum_required(VERSION 3.10)

# set the project name
project(tests CXX)

# add the executable

add_executable(test_catch test_catch.cpp test_dynamic_variable.cpp ../FluS/dynamic_variable.cpp)


add_test(test_catch test_catch)