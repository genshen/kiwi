//
// Created by genshen on 3/24/18.
//

#include <gtest/gtest.h>
#include <utils/mpi_utils.h>

// test allRanks in mpi_utils.cpp/.h
TEST(mpi_utils_test_size, mpi_utils_test) {
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    EXPECT_EQ(size, kiwi::mpiUtils::global_process.all_ranks);
}

// test ownRanks in mpi_utils.cpp/.h
TEST(mpi_utils_test_rank, mpi_utils_test) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    EXPECT_EQ(rank, kiwi::mpiUtils::global_process.own_rank);
}