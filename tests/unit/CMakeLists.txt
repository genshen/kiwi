# store temp file, e.g. files for IO test.
set(KIWI_TEST_TEMP_STORAGE_PATH ${CMAKE_CURRENT_BINARY_DIR})

# configure a header file to pass some of the CMake settings to the source code
configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/test_config.h.in"
        "${CMAKE_CURRENT_SOURCE_DIR}/test_config.h"
)

set(KIWI_TEST_HEADER_FILES
        test_config.h
        gtest_env.h
        )

set(KIWI_TEST_SOURCE_FILES
        main.cpp
        config/config.cpp
        event/message_loop_test.cpp
        io/io_utils_test.cpp
        io/io_writer_test.cpp
        utils/bundle_test.cpp
        utils/mpi_utils_test.cpp
        logs/logs_test.cpp
        io/local_storage_test.cpp
        )

# set binary path and lib storage path wile compiling process.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_executable(${KIWI_UINT_TEST_NAME} ${KIWI_TEST_SOURCE_FILES} ${KIWI_TEST_HEADER_FILES})

# Extra linking for the project.
if (TARGET GTest::gtest AND TARGET GTest::gtest_main)
    # googletest is added by `find_package(GTest)`
    target_link_libraries(${KIWI_UINT_TEST_NAME}
            PRIVATE GTest::gtest GTest::gtest_main ${KIWI_EXTRA_LIBS} ${KIWI_LIB_NAME}
            )
else ()
    # googletest is added by `add_subdirectory`
    target_link_libraries(${KIWI_UINT_TEST_NAME}
            PRIVATE gtest gtest_main ${KIWI_EXTRA_LIBS} ${KIWI_LIB_NAME}
            )
endif ()


# This is so you can do 'make test' to see all your tests run, instead of
# manually running the executable runUnitTests to see those specific tests.
add_test(NAME ${KIWI_UINT_TEST_NAME} COMMAND ${KIWI_UINT_TEST_NAME})


##########################
##### install files
##########################
if (${KIWI_INSTALL})
    install(TARGETS ${KIWI_UINT_TEST_NAME}
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            )
endif ()
