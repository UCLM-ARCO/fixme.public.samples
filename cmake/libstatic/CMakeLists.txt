CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(libstatic)
ADD_EXECUTABLE(hello hello.cpp)

include_directories(.)

add_library(dummy STATIC dummy.cpp)

target_link_libraries(hello dummy)

install (TARGETS hello DESTINATION bin)
