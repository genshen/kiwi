//
// Created by genshen(genshenchu@gmail.com) on 2017/5/7.
//

#include "mpi.h"
#include "data_def.h"

#ifndef KIWI_MPI_UTILS_H
#define KIWI_MPI_UTILS_H

namespace kiwi {
#define MASTER_PROCESSOR 0

    namespace mpiUtils {
        // you can use ownRank and allRanks after called function initialMPI in tiny_fmm.h
        extern RID ownRank;
        extern RID allRanks;

        void initialMPI(int argc, char *argv[]);

        void finishMPI();

    };
}
#endif // KIWI_MPI_UTILS_H
