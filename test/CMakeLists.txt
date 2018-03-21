enable_testing()

if (NOT (KIWI_MPI_ENABLE))
    set(KIWI_TEST_MPI_ENABLE OFF)  # if we disabled MPI_ENABLE_FLAG,we cann't also use TEST_MPI_ENABLE_FLAG.
endif ()
MESSAGE(STATUS "MPI in test: ${KIWI_TEST_MPI_ENABLE}")

################################
# googletest:gtest and mocktest
################################
# or using ExternalProject_Add, see:https://github.com/kaizouman/gtest-cmake-example

# download googletest from https://github.com/google/googletest/,and copy it to "external" directory.
# Include the gtest library. gtest_SOURCE_DIR is available due to 'project(gtest)' above.
# an issue for mingw on winodws, see: https://github.com/google/googletest/issues/606#issuecomment-234733757
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/src/googletest/googletest ${PROJECT_BINARY_DIR}/vendor/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#googlemock
#add_subdirectory("${source_dir}/googlemock")
#include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

# Standard linking to gtest stuff.
set(KIWI_EXTRA_LIBS ${KIWI_EXTRA_LIBS} gtest gtest_main)
MESSAGE(STATUS "Set googletest as test library.")


add_subdirectory(unit)
