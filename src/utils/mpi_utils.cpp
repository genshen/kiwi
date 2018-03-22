//
// Created by genshen(genshenchu@gmail.com) on 2017/5/7.
//

#include <iostream>
#include "mpi_utils.h"
//#include "../pre_config.h" // todo just use  DEV_MODE

using namespace std;

namespace kiwi {
    namespace mpiUtils {

        int ownRank;
        int allRanks;

        void initialMPI(int argc, char *argv[]) {
            MPI_Init(&argc, &argv);
            MPI_Comm_size(MPI_COMM_WORLD, &allRanks);
            MPI_Comm_rank(MPI_COMM_WORLD, &ownRank);

#ifdef DEV_MODE
            if (ownRank == MASTER_PROCESSOR) {
                cout << "[DEV] running with " << allRanks << " processors" << endl;
            }
#endif
        }

        void finishMPI() {
            MPI_Finalize();
        }
    }
}