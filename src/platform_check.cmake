include(CheckFunctionExists)
include(CheckCXXSourceCompiles)

set(CMAKE_REQUIRED_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES};${KIWI_EXTRA_LIBS})
set(CMAKE_REQUIRED_INCLUDES ${CMAKE_REQUIRED_INCLUDES};${MPI_INCLUDE_PATH})

check_function_exists(MPI_Mprobe FUNC_MPI_MPROBE_SUPPORTED)

configure_file(
        "${PROJECT_SOURCE_DIR}/src/platform/mpi_support.h.in"
        "${PROJECT_SOURCE_DIR}/src/platform/mpi_support.h"
)

# proper version check
#check_cxx_source_compiles("
##include <mpi.h>
#int main(int argc, char** argv){
#    MPI_Init(&argc,&argv);
#    MPI_Status status;
#    MPI_Message msg;
#    MPI_Mprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &msg, &status);
#    MPI_Finalize();
#}
#" FUNC_MPI_MPROBE_SUPPORTED)

#if (NOT FUNC_MPI_MPROBE_SUPPORTED)
#    message(FATAL_ERROR "ERROR: required MPI_Mprobe function not found")
#endif ()