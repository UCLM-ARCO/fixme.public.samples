CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(hello_ice)

include (CheckLibraryExists)
check_library_exists (Ice accept "" ICE_FOUND)

include_directories(.)

# set(SLICES hello.ice)
# set(SLICE_DIR slice)

# set(slices_cpp)
# set(slices_h)

# foreach(s ${SLICES})
#   string(REGEX REPLACE "(.*).ice" "\\1.cpp" cpp ${s})
#   string(REGEX REPLACE "(.*).ice" "\\1.h" h ${s})

#   list(APPEND slices_cpp ${cpp})
#   list(APPEND slices_h ${h})

#   add_custom_command (
#     OUTPUT ${cpp} ${h}
#     COMMAND slice2cpp ${SLICE_DIR}/${SLICES} -I ${SLICE_DIR}
#     DEPENDS ${S}
#     )

# endforeach(s)

add_custom_command (
  OUTPUT hello.cpp hello.h
  COMMAND slice2cpp slice/hello.ice -I slice
  DEPENDS slice/hello.ice
  )


add_executable(Client hello.cpp Client.cpp)
add_executable(Server hello.cpp helloI.cpp Server.cpp)
target_link_libraries(Server Ice)
target_link_libraries(Client Ice)

install(TARGETS Client Server DESTINATION bin)

