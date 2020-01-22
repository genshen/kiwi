include(platform_check.cmake) # platform check

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

add_library(${KIWI_LIB_NAME} STATIC ${KIWI_SOURCE_FILES} ${KIWI_HEADER_FILES})

target_include_directories(
        ${KIWI_LIB_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

set(IMP OFF)
get_target_property(IMP fmt::fmt IMPORTED)
if (NOT ${IMP})
    # if fmt is added by add_subdirectory
    target_link_libraries(
            ${KIWI_LIB_NAME}
            PUBLIC
            $<BUILD_INTERFACE:fmt::fmt>)
else ()
    target_link_libraries(
            ${KIWI_LIB_NAME}
            PUBLIC
            fmt::fmt)
endif ()


##########################
##### install files
##########################
set(TARGETS_EXPORT_NAME ${KIWI_LIB_NAME}-targets)
set(KIWI_LIB_CMAKE_DIR lib/cmake/${KIWI_LIB_NAME})
set(KIWI_LIB_CMAKE_NAMESPACE ${KIWI_LIB_NAME}::)
set(KIWI_LIB_CMAKE_CONFIG_IN "${KIWI_LIB_NAME}-config.cmake.in")
set(KIWI_LIB_CMAKE_CONFIG_OUT "${CMAKE_CURRENT_BINARY_DIR}/${KIWI_LIB_NAME}-config.cmake")

# lib alias to makes it possible to always use the namespace version consistently
add_library(${KIWI_LIB_CMAKE_NAMESPACE}${KIWI_LIB_NAME} ALIAS ${KIWI_LIB_NAME})

if (${KIWI_INSTALL})
    # install libs
    install(TARGETS ${KIWI_LIB_NAME}
            EXPORT ${KIWI_LIB_NAME}-targets
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            )

    # install header.
    install(DIRECTORY "./"
            DESTINATION "include"
            FILES_MATCHING
            PATTERN "*.h"
            PATTERN "*.hpp"
            )

    # install export target and config for find_package
    install(EXPORT ${TARGETS_EXPORT_NAME} DESTINATION ${KIWI_LIB_CMAKE_DIR} NAMESPACE ${KIWI_LIB_CMAKE_NAMESPACE}) # todo
    include(CMakePackageConfigHelpers)
    configure_package_config_file(
            ${KIWI_LIB_CMAKE_CONFIG_IN} ${KIWI_LIB_CMAKE_CONFIG_OUT}
            INSTALL_DESTINATION ${KIWI_LIB_CMAKE_DIR}
    )
    install(FILES ${KIWI_LIB_CMAKE_CONFIG_OUT} DESTINATION ${KIWI_LIB_CMAKE_DIR})

endif ()
