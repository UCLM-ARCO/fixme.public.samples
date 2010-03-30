CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(libstatic)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(dummy STATIC dummy.cpp)
