cmake_minimum_required(VERSION 3.2)
project(SimpleLogger VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(SimpleLogger SHARED ${CMAKE_CURRENT_SOURCE_DIR}/simpleLogger.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})