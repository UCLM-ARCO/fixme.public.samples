CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(libshared)
set(libshared_BINARY_DIR bin)
set(libshared_SOURCE_DIR .)

include_directories(.)

add_library(dummy SHARED dummy.cpp)
set_property(TARGET dummy PROPERTY SOVERSION 1.0)

# Si se instala, es necesario configurar
# LD_LIBRARY_PATH=/usr/local/lib
install (TARGETS dummy DESTINATION lib)
