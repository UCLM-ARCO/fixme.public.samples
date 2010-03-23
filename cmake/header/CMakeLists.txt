CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(hello)
include_directories(.)

ADD_EXECUTABLE(hello dummy.cpp hello.cpp)

# set (CMAKE_INSTALL_PREFIX /tmp)

install (TARGETS hello DESTINATION bin)
