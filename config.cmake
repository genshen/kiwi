# configures
set(KIWI_NAME ${PROJECT_NAME}) # project name

# options
option(KIWI_MPI_ENABLE "Use MPI library" ON) #change this flag to false to disable mpi
option(KIWI_TEST_MPI_ENABLE "Build test" ON)
option(KIWI_BUILD_TESTS "Build test" ON)
option(KIWI_BUILD_DOCS "Build docs" ON)

# libs
set(KIWI_LIB_NAME ${KIWI_NAME})

# test
set(KIWI_UINT_TEST_NAME "kiwi-test")
