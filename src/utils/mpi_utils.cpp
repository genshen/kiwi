//
// Created by genshen(genshenchu@gmail.com) on 2017/5/7.
//

#include <iostream>
#include "mpi_utils.h"
//#include "../pre_config.h" // todo just use  DEV_MODE

using namespace std;

namespace kiwi {
    RID mpiUtils::ownRank;
    RID mpiUtils::allRanks;

    void mpiUtils::initialMPI(int argc, char *argv[]) {
        MPI_Init(&argc, &argv);
        initMPIRank();
    }

    void mpiUtils::initMPIWithThread(int argc, char **argv, short type) {
        int provided;
        MPI_Init_thread(&argc, &argv, type, &provided);
        if (provided != type) { // todo smaller then?
            std::cerr << "mpi thread not supported" << std::endl;
            exit(1);
        }
        initMPIRank();
    }

    void mpiUtils::initMPIRank() {
        MPI_Comm_size(MPI_COMM_WORLD, &allRanks);
        MPI_Comm_rank(MPI_COMM_WORLD, &ownRank);

#ifdef DEV_MODE
        if (ownRank == MASTER_PROCESSOR) {
            cout << "[DEV] running with " << allRanks << " processors" << endl;
        }
#endif
    }

    void mpiUtils::finishMPI() {
        MPI_Finalize();
    }
}
