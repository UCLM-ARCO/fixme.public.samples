CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(hello_ice)

FIND_LIBRARY(ice_lib Ice)
FIND_PATH(ice_path Ice)

IF(NOT ice_path)
  MESSAGE(FATAL_ERROR "** Librería de Ice no encontrada")
ENDIF()

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${ice_path}
  )

SET(SLICES ${CMAKE_CURRENT_SOURCE_DIR}/slice/hello.ice)

ADD_CUSTOM_COMMAND (
  OUTPUT hello.cpp hello.h
  COMMAND slice2cpp ${SLICES}
  )


ADD_EXECUTABLE(Client hello.cpp Client.cpp)
ADD_EXECUTABLE(Server hello.cpp helloI.cpp Server.cpp)
TARGET_LINK_LIBRARIES(Server ${ice_lib})
TARGET_LINK_LIBRARIES(Client ${ice_lib})
