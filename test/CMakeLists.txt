enable_testing()

if (NOT (KIWI_MPI_ENABLE))
    set(KIWI_TEST_MPI_ENABLE OFF)  # if we disabled MPI_ENABLE_FLAG,we cann't also use TEST_MPI_ENABLE_FLAG.
endif ()
MESSAGE(STATUS "MPI in test: ${KIWI_TEST_MPI_ENABLE}")

MESSAGE(STATUS "Set googletest as test library.")


add_subdirectory(unit)
