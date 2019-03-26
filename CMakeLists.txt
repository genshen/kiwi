cmake_minimum_required(VERSION 3.8)

# change to mpicc and mpicxx
#set(CMAKE_C_COMPILER mpicc -cc=gcc -cxx=g++)
#set(CMAKE_CXX_COMPILER mpicxx -cc=gcc -cxx=g++)

project(kiwi)

set(CMAKE_CXX_STANDARD 11)

include(config.cmake)


include(dependency.cmake)

add_subdirectory(src)
add_subdirectory(tests/utils)


##############################
## test configure
##############################
if (KIWI_BUILD_TESTS_ENABLE_FLAG)
    MESSAGE(STATUS "TEST is enabled")
    enable_testing()
    add_subdirectory(tests)
endif ()
