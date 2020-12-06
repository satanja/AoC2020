cmake_minimum_required(VERSION 3.10)

project(advent)

set(CMAKE_CXX_STANDARD 20)

add_executable(advent 06/main.cpp)  

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(stefan STATIC 01/main.cpp)
