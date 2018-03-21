# src directory
set(UMBRELLA_SOURCE_FILES library.cpp)
set(UMBRELLA_HEADER_FILES library.h)

# todo bin lib, install
add_library(${UMBRELLA_LIB_NAME} ${UMBRELLA_SOURCE_FILES} ${UMBRELLA_HEADER_FILES})
