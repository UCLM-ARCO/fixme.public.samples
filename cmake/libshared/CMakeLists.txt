CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(libshared)

include_directories(.)

add_library(dummy SHARED dummy.cpp)
set_property(TARGET dummy PROPERTY SOVERSION 1.0)
# Si se instala, es necesario configurar
# LD_LIBRARY_PATH=/usr/local/lib
install (TARGETS dummy DESTINATION lib)
