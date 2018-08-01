# configures
set(KIWI_NAME ${PROJECT_NAME}) # project name

# options
option(KIWI_MPI_ENABLE "Use MPI library" ON) #change this flag to false to disable mpi
option(KIWI_TEST_MPI_ENABLE "Build test" ON)
option(KIWI_BUILD_TESTS "Build test" ON)
option(KIWI_BUILD_DOCS "Build docs" ON)

# libs
set(KIWI_LIB_NAME ${KIWI_NAME})

# vendor
include(pkg.dep.cmake)
set(KIWI_VENDOR_PATH ${VENDOR_PATH})
set(KIWI_VENDOR_SRC_PATH ${KIWI_VENDOR_PATH}/src)
set(KIWI_VENDOR_INCLUDE_PATH ${KIWI_VENDOR_PATH}/include)
set(KIWI_VENDOR_PKG_PATH ${KIWI_VENDOR_PATH}/pkg)

# test
set(KIWI_UINT_TEST_NAME "kiwi-test")
