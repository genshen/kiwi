//
// Created by genshen(genshenchu@gmail.com) on 2017/5/7.
//

#include <iostream>
#include "mpi_utils.h"
//#include "../pre_config.h" // todo just use  DEV_MODE

using namespace std;

namespace kiwi {
    RID mpiUtils::own_rank;
    RID mpiUtils::all_ranks;
    MPI_Comm mpiUtils::global_comm;

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
        global_comm = MPI_COMM_WORLD;
        MPI_Comm_size(MPI_COMM_WORLD, &all_ranks);
        MPI_Comm_rank(MPI_COMM_WORLD, &own_rank);

#ifdef DEV_MODE
        if (own_rank == MASTER_PROCESSOR) {
            cout << "[DEV] running with " << all_ranks << " processors" << endl;
        }
#endif
    }

    void mpiUtils::finishMPI() {
        MPI_Finalize();
    }

    void mpiUtils::onGlobalCommChanged(MPI_Comm comm) {
        global_comm = comm;
        MPI_Comm_size(comm, &all_ranks);
        MPI_Comm_rank(comm, &own_rank); // get new rank in comm _comm.
    }
}
