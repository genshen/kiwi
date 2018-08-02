## Test Utils for parallel program.
# in this directory, google-test for MPI has provided.

include_directories(${PROJECT_SOURCE_DIR}/src)

set(KIWI_TEST_UTILS_HEADER_FILES
        gtest_env.h
        )

# install header.
install(DIRECTORY "./"
        DESTINATION "include/test"
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hpp"
        )