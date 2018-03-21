# src directory
include_directories(${PROJECT_SOURCE_DIR}/vendor/include)

set(KIWI_SOURCE_FILES library.cpp)
set(KIWI_HEADER_FILES library.h)

# todo bin lib, install
# set binary path and lib storage path for compiling process.
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_library(${KIWI_LIB_NAME} ${KIWI_SOURCE_FILES} ${KIWI_HEADER_FILES})


##########################
##### install files
##########################
install(TARGETS ${KIWI_LIB_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )

install(FILES ${HEADER_FILES} DESTINATION include) # todo head file

