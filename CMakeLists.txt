cmake_minimum_required(VERSION 3.10)

project(advent)

set(CMAKE_CXX_STANDARD 20)

add_executable(advent 10/main.cpp)  

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES 
    01/main.cpp
    02/main.cpp
    03/main.cpp
    04/main.cpp
    05/main.cpp
    06/main.cpp
    07/main.cpp
    08/main.cpp
    09/main.cpp
    11/main.cpp
)

add_library(stefan STATIC ${SOURCES})
install(TARGETS stefan DESTINATION ${CMAKE_INSTALL_PREFIX})
