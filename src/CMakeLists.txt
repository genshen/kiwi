# src directory
include_directories(${PROJECT_SOURCE_DIR}/vendor/include)
set(KIWI_EXPORT_INCLUDE_PATH ${KIWI_EXPORT_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/vendor/include" "${PROJECT_SOURCE_DIR}/src" CACHE STRING "kiwi_inclue_path")

set(KIWI_HEADER_FILES
        kiwi_app.h
        library.h
        config/config.h
        io/io_writer.h
        utils/data_def.h
        utils/bundle.h
        utils/mpi_utils.h
        )

set(KIWI_SOURCE_FILES
        kiwi_app.cpp
        library.cpp
        config/config.cpp
        io/io_writer.cpp
        utils/bundle.cpp
        utils/mpi_utils.cpp
        )

# todo bin lib, install
# set binary path and lib storage path for compiling process.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_library(${KIWI_LIB_NAME} ${KIWI_SOURCE_FILES} ${KIWI_HEADER_FILES})


##########################
##### install files
##########################
install(TARGETS ${KIWI_LIB_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )

install(FILES ${KIWI_HEADER_FILES} DESTINATION include) # todo head file

