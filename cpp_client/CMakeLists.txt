cmake_minimum_required(VERSION 3.5)

project(cpp_client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(lib_interface_src cpp_client_interface.cpp)

add_executable(cpp_client cpp_client.cpp main.cpp)
add_library(interface SHARED ${lib_interface_src})
