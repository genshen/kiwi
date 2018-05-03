//
// Created by genshen(genshenchu@gmail.com) on 2017/5/7.
//

#include "mpi.h"
#include "data_def.h"

#ifndef KIWI_MPI_UTILS_H
#define KIWI_MPI_UTILS_H

namespace kiwi {
#define MASTER_PROCESSOR 0

    class mpiUtils {
    public:
        // you can use own_rank and all_ranks after called function initialMPI in tiny_fmm.h
        static RID own_rank;
        static RID all_ranks;
        static MPI_Comm global_comm;

        /**
         * initialize mpi
         */
        static void initialMPI(int argc, char *argv[]);

        /**
         * initialize mpi environments with multiple thread support.
         */
        static void initMPIWithThread(int argc, char *argv[], short type);

        static void finishMPI();

        static void onGlobalCommChanged(MPI_Comm comm);

    private:
        /**
         * initialize mpi variable @var ownRank and allRanks.
         */
        static void initMPIRank();
    };
}
#endif // KIWI_MPI_UTILS_H
