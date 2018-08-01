cmake_minimum_required(VERSION 3.8)
project(kiwi)

set(CMAKE_CXX_STANDARD 11)

include(config.cmake)

###################
# MPI dependency #
###################
if (KIWI_MPI_ENABLE)
    find_package(MPI REQUIRED)
    MESSAGE(STATUS "MPI_INCLUDE dir:" ${MPI_INCLUDE_PATH})
    MESSAGE(STATUS "MPI_LIBRARIES dir:" ${MPI_LIBRARIES})

    if (MPI_COMPILE_FLAGS)
        set(COMPILE_FLAGS "${COMPILE_FLAGS} ${MPI_COMPILE_FLAGS}")
    endif ()

    if (MPI_LINK_FLAGS)
        set(LINK_FLAGS "${LINK_FLAGS} ${MPI_LINK_FLAGS}")
    endif ()

    include_directories(${MPI_INCLUDE_PATH})

    set(KIWI_EXTRA_LIBS ${KIWI_EXTRA_LIBS} ${MPI_LIBRARIES}) #add mpi lib
endif ()
#### end MPI

include(pkg.dep.cmake)

add_subdirectory(src)
# utils for building parallel test.
add_subdirectory(test/utils)

#if (KIWI_BUILD_DOCS)
#    add_subdirectory(docs)
#endif ()

### build test
if (KIWI_BUILD_TESTS)
    add_subdirectory(test)
endif ()
