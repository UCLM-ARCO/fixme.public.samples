CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(libstatic)
include_directories(.)

add_library(dummy STATIC dummy.cpp)
