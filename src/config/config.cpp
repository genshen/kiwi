//
// Created by genshen(genshenchu@gmail.com) on 2018-03-21.
//

#include <fstream>
#include "config.h"
#include "../utils/bundle.h"
#include "../utils/mpi_utils.h"

namespace kiwi {

    config::config() : hasError(false) {}

    // only for master.
    void config::setError(const std::string &msg) {
        errorMessage = msg;
        hasError = true;
    }

    void config::sync(const unsigned int buffer_size) {
        Bundle bundle = Bundle();
        bundle.newPackBuffer(buffer_size);
        if (mpiUtils::global_process.own_rank == MASTER_PROCESSOR) { // pack data.
            putConfigData(bundle);
        }

        MPI_Bcast(bundle.getPackedData(), bundle.getPackedDataCap(),
                  MPI_BYTE, MASTER_PROCESSOR, MPI_COMM_WORLD); // synchronize config information

        if (mpiUtils::global_process.own_rank != MASTER_PROCESSOR) { // unpack data.
            getConfigData(bundle);
        }
        bundle.freePackBuffer(); // release memory after usage.
    }

}
