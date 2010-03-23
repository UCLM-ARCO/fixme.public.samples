CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(hello_shared)
set(hello_shared_BINARY_DIR bin)
set(hello_shared_SOURCE_DIR .)

include_directories(../libshared)

# El segundo argumento es necesario al tratarse de un directorio
# que no es subdirectorio de éste.

add_subdirectory(../libshared libshared_bin)

add_executable(hello hello.cpp)

# Todas las reglas definidas en la librería se heredan. Por eso
# no hace falta definir el target dummy
target_link_libraries(hello dummy)

install (TARGETS hello DESTINATION bin)
