//
// Created by genshen on 3/24/18.
//

#include <gtest/gtest.h>
#include <utils/bundle.h>
#include <utils/mpi_utils.h>

TEST(bundle_test_1, bundle_test) {
    kiwi::Bundle bundle = kiwi::Bundle();
    bundle.newPackBuffer(1024);
    if (kiwi::mpiUtils::own_rank == MASTER_PROCESSOR) { // pack data.
        bundle.put(MPI_COMM_WORLD, 1024);
        std::string s = "hello";
        bundle.put(MPI_COMM_WORLD, s);
        bundle.put(MPI_COMM_WORLD, 'c');
    }

    MPI_Bcast(bundle.getPackedData(), bundle.getPackedDataCap(),
              MPI_BYTE, MASTER_PROCESSOR, MPI_COMM_WORLD); // synchronize config information

    if (kiwi::mpiUtils::own_rank != MASTER_PROCESSOR) { // unpack data.
        int i, cursor = 0;
        char ch;
        std::string hello;
        bundle.get(MPI_COMM_WORLD, cursor, i);
        bundle.get(MPI_COMM_WORLD, cursor, hello);
        bundle.get(MPI_COMM_WORLD, cursor, ch);
        EXPECT_EQ(i, 1024);
        EXPECT_EQ(hello, "hello");
        EXPECT_EQ(ch, 'c');
    }
    bundle.releasePackBuffer();
}
