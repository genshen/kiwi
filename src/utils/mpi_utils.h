//
// Created by genshen(genshenchu@gmail.com) on 2017/5/7.
//

#include <mpi.h>

#include "data_def.h"

#ifndef KIWI_MPI_UTILS_H
#define KIWI_MPI_UTILS_H

namespace kiwi {
#define MASTER_PROCESSOR 0
  struct mpi_process {
    RID own_rank, all_ranks;
    MPI_Comm comm;
  };

  class mpiUtils {
  public:
    // you can use global_own_rank and global_all_ranks after called function initialMPI in tiny_fmm.h
    static mpi_process global_process;
    static mpi_process local_process;

    /**
     * initialize mpi
     */
    static void initialMPI(int argc, char *argv[]);

    /**
     * initialize mpi environments with multiple thread support.
     */
    static void initMPIWithThread(int argc, char *argv[], short type);

    static void finishMPI();

    // if the global communicator has changed(default is {MPI_COMM_WORLD}),
    // this method can be called the re-set the global communicator.
    static void onGlobalCommChanged(MPI_Comm comm);

    // if the local mpi communicator has set or changed (e.g. calling MPI_Comm_group),
    // this method can be called to change local ranks and local mpi communicator.
    static void onLocalCommChanged(MPI_Comm comm);

  private:
    /**
     * initialize mpi variable @var ownRank and allRanks.
     */
    static void initMPIRank();
  };
} // namespace kiwi
#endif // KIWI_MPI_UTILS_H
