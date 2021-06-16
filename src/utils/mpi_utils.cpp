//
// Created by genshen(genshenchu@gmail.com) on 2017/5/7.
//

#include <iostream>

#include "mpi_utils.h"
//#include "../pre_config.h" // todo just use  DEV_MODE

namespace kiwi {
  mpi_process mpiUtils::global_process;
  mpi_process mpiUtils::local_process;

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
    global_process.comm = MPI_COMM_WORLD;
    MPI_Comm_size(MPI_COMM_WORLD, &global_process.all_ranks);
    MPI_Comm_rank(MPI_COMM_WORLD, &global_process.own_rank);

    // set local ranks the same as global ranks as default.
    local_process = global_process;
#ifdef DEV_MODE
    if (global_process.own_rank == MASTER_PROCESSOR) {
      std::cout << "[DEV] running with " << global_process.all_ranks << " processors" << endl;
    }
#endif
  }

  void mpiUtils::finishMPI() { MPI_Finalize(); }

  void mpiUtils::onGlobalCommChanged(MPI_Comm comm) {
    global_process.comm = comm;
    MPI_Comm_size(comm, &global_process.all_ranks);
    MPI_Comm_rank(comm, &global_process.own_rank); // get new rank in comm _comm.
  }

  void mpiUtils::onLocalCommChanged(MPI_Comm comm) {
    local_process.comm = comm;
    MPI_Comm_size(comm, &local_process.all_ranks);
    MPI_Comm_rank(comm, &local_process.own_rank); // get new rank in comm _comm.
  }
} // namespace kiwi
