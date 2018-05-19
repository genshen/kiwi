//
// Created by genshen on 3/24/18.
//

#include <gtest/gtest.h>
#include <utils/bundle.h>
#include <utils/mpi_utils.h>

TEST(bundle_test_pack, bundle_test) {
    kiwi::Bundle bundle = kiwi::Bundle();
    bundle.newPackBuffer(1024);
    if (kiwi::mpiUtils::own_rank == MASTER_PROCESSOR) { // pack data.
        bundle.pack(MPI_COMM_WORLD, 1024);
        std::string s = "hello";
        bundle.pack(MPI_COMM_WORLD, s);
        bundle.pack(MPI_COMM_WORLD, 'c');
    }

    MPI_Bcast(bundle.getPackedData(), bundle.getPackedDataCap(),
              MPI_BYTE, MASTER_PROCESSOR, MPI_COMM_WORLD); // synchronize config information

    if (kiwi::mpiUtils::own_rank != MASTER_PROCESSOR) { // unpack data.
        int i, cursor = 0;
        char ch;
        std::string hello;
        bundle.unpack(MPI_COMM_WORLD, cursor, i);
        bundle.unpack(MPI_COMM_WORLD, cursor, hello);
        bundle.unpack(MPI_COMM_WORLD, cursor, ch);
        EXPECT_EQ(i, 1024);
        EXPECT_EQ(hello, "hello");
        EXPECT_EQ(ch, 'c');
    }
    bundle.releasePackBuffer();
}

TEST(bundle_test_put, bundle_test) {
    kiwi::Bundle bundle = kiwi::Bundle();
    bundle.newPackBuffer(1024);
    if (kiwi::mpiUtils::own_rank == MASTER_PROCESSOR) { // pack data.
        bundle.put(1024);
        std::string s = "hello";
        bundle.put(s);
        bundle.put('c');
    }

    MPI_Bcast(bundle.getPackedData(), bundle.getPackedDataCap(),
              MPI_BYTE, MASTER_PROCESSOR, MPI_COMM_WORLD); // synchronize config information

    if (kiwi::mpiUtils::own_rank != MASTER_PROCESSOR) { // unpack data.
        int i, cursor = 0;
        char ch;
        std::string hello;
        bundle.get(cursor, i);
        bundle.get(cursor, hello);
        bundle.get(cursor, ch);
        EXPECT_EQ(i, 1024);
        EXPECT_EQ(hello, "hello");
        EXPECT_EQ(ch, 'c');
    }
    bundle.releasePackBuffer();
}

TEST(bundle_test_mixed, bundle_test) {
    kiwi::Bundle bundle = kiwi::Bundle();
    bundle.newPackBuffer(1024);
    if (kiwi::mpiUtils::own_rank == MASTER_PROCESSOR) { // pack data.
        bundle.pack(MPI_COMM_WORLD, 1024);
        std::string s = "hello";
        bundle.put(s);
        bundle.pack(MPI_COMM_WORLD, 'c');
    }

    MPI_Bcast(bundle.getPackedData(), bundle.getPackedDataCap(),
              MPI_BYTE, MASTER_PROCESSOR, MPI_COMM_WORLD); // synchronize config information

    if (kiwi::mpiUtils::own_rank != MASTER_PROCESSOR) { // unpack data.
        int i, cursor = 0;
        char ch;
        std::string hello;
        bundle.unpack(MPI_COMM_WORLD, cursor, i);
        bundle.get(cursor, hello);
        bundle.unpack(MPI_COMM_WORLD, cursor, ch);
        EXPECT_EQ(i, 1024);
        EXPECT_EQ(hello, "hello");
        EXPECT_EQ(ch, 'c');
    }
    bundle.releasePackBuffer();
}
