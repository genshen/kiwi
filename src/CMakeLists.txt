include(platform_check.cmake) # platform check

include_directories(${KIWI_VENDOR_INCLUDE_PATH})

set(KIWI_HEADER_FILES
        kiwi_app.h
        config/config.h
        event/message_looper.h
        event/message_runner.h
        io/local_storage.h
        io/io_writer.h
        logs/colors.h
        logs/logs.h
        utils/data_def.h
        utils/bundle.h
        utils/mpi_utils.h
        )

set(KIWI_SOURCE_FILES
        kiwi_app.cpp
        config/config.cpp
        event/message_looper.cpp
        io/local_storage.cpp
        io/io_utils.hpp
        io/io_writer.cpp
        logs/logs.cpp
        utils/bundle.cpp
        utils/mpi_utils.cpp
        )


# set binary path and lib storage path for compiling process.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_library(${KIWI_LIB_NAME} ${KIWI_SOURCE_FILES} ${KIWI_HEADER_FILES})

target_include_directories(
        ${KIWI_LIB_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(
        ${KIWI_LIB_NAME}
        PUBLIC
        fmt::fmt
        )

##########################
##### install files
##########################
# install libs
install(TARGETS ${KIWI_LIB_NAME}
        EXPORT ${KIWI_LIB_NAME}-targets
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )

install(EXPORT ${KIWI_LIB_NAME}-targets DESTINATION lib/cmake)

# install header.
install(DIRECTORY "./"
        DESTINATION "include"
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hpp"
        )
