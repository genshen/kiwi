set(KIWI_VERSION "0.2.0-beta")
set(KIWI_NAME ${PROJECT_NAME}) # project name

#############
## options ##
#############
option(KIWI_OpenMP_ENABLE_FLAG "Use OpenMP" OFF) #change this flag to OFF to disable OpenMP
option(KIWI_MPI_ENABLE_FLAG "Use MPI library" ON) #change this flag to false to disable mpi
option(KIWI_BUILD_TESTS_ENABLE_FLAG "Enable building test" ON) # enable test
option(KIWI_TEST_MPI_ENABLE_FLAG "Enable MPI in test" ON) # enable mpi in test, its value depends on option MPI_ENABLE_FLAG.
option(KIWI_BUILD_DOCS "Build docs" ON)

set(MASTER_PROJECT OFF)
if (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    set(MASTER_PROJECT ON)
endif ()

option(KIWI_INSTALL "Generate the install target." ${MASTER_PROJECT})

## architecture ralated values.
# option(ARCH_SW "Enable sunway athread" OFF) # enable sunway athread if its running on sunway system.

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

if (CMAKE_BUILD_TYPE MATCHES "^(Debug|DEBUG|debug)$")
    set(KIWI_DEBUG_ENABLE_FLAG ON)
endif ()

#############
## const ##
#############
set(KIWI_LIB_NAME ${KIWI_NAME}) # todo use PARENT_SCOPE to modify globle variable.

# test
set(KIWI_UINT_TEST_NAME "kiwi-unit-test")
