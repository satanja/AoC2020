cmake_minimum_required(VERSION 3.10)

project(advent)

set(CMAKE_CXX_STANDARD 20)

add_executable(advent 09/main.cpp)  

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES 
    01/main.cpp
)

add_library(stefan STATIC ${SOURCES})
install(TARGETS stefan DESTINATION ${CMAKE_INSTALL_PREFIX})
