## Test Utils for parallel program.
# in this directory, google-test for MPI has provided.


set(KIWI_TEST_HEADER_FILES

        )

# install header.
install(DIRECTORY "./"
        DESTINATION "include/test"
        FILES_MATCHING PATTERN "*.h")