cmake_minimum_required(VERSION 3.10)

# set the project name
project(dev CXX)

# add the executable
add_executable(echo_mesh echo_mesh.cpp)
add_executable(echo_mesh2 echo_mesh2.cpp ../mocks/mesh.cpp)


add_executable(echo_advection echo_advection.cpp ../FluS/dynamic_variable.cpp ../FluS/forward_euler.cpp ../FluS/preproc.cpp ../mocks/mesh.cpp)
add_executable(echo_euler echo_euler.cpp ../FluS/dynamic_variable.cpp ../FluS/forward_euler.cpp ../FluS/preproc.cpp ../exactRS/ers.cpp ../mocks/mesh.cpp)




add_executable(echo_libco echo_libco.cpp)
target_link_libraries(echo_libco -lconfig++)
