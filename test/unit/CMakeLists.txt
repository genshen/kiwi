
# configure a header file to pass some of the CMake settings to the source code
configure_file(
        "${PROJECT_SOURCE_DIR}/test/unit/test_config.h.in"
        "${PROJECT_SOURCE_DIR}/test/unit/test_config.h"
)

include_directories(${PROJECT_SOURCE_DIR}/vendor/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

set(TEST_HEADER_FILES
        test_config.h
        gtest_env.h
        )

set(TEST_SOURCE_FILES
        main.cpp
        app_test.cpp
        config/config.cpp
        io/io_writer_test.cpp
        utils/bundle_test.cpp utils/mpi_utils_test.cpp)

# set binary path and lib storage path wile compiling process.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_executable(${KIWI_UINT_TEST_NAME} ${TEST_SOURCE_FILES} ${TEST_HEADER_FILES})

# Extra linking for the project.
set(KIWI_EXTRA_LIBS ${KIWI_EXTRA_LIBS} ${KIWI_LIB_NAME})
# Extra linking for the project.
target_link_libraries(${KIWI_UINT_TEST_NAME} ${KIWI_EXTRA_LIBS})

# This is so you can do 'make test' to see all your tests run, instead of
# manually running the executable runUnitTests to see those specific tests.
add_test(NAME exampleTests COMMAND ${KIWI_UINT_TEST_NAME})


##########################
##### install files
##########################
install(TARGETS ${KIWI_UINT_TEST_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )
