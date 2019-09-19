//
// Created by genshen on 3/24/18.
//

#include <gtest/gtest.h>
#include <utils/bundle.h>
#include <utils/mpi_utils.h>

TEST(bundle_test_pack, bundle_test) {
    kiwi::Bundle bundle = kiwi::Bundle();
    bundle.newPackBuffer(1024);
    if (kiwi::mpiUtils::global_process.own_rank == MASTER_PROCESSOR) { // pack data.
        bundle.pack(MPI_COMM_WORLD, 1024);
        std::string s = "hello";
        bundle.pack(MPI_COMM_WORLD, s);
        bundle.pack(MPI_COMM_WORLD, 'c');
    }

    MPI_Bcast(bundle.getPackedData(), bundle.getPackedDataCap(),
              MPI_BYTE, MASTER_PROCESSOR, MPI_COMM_WORLD); // synchronize config information

    if (kiwi::mpiUtils::global_process.own_rank != MASTER_PROCESSOR) { // unpack data.
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
    bundle.freePackBuffer();
}

TEST(bundle_test_put, bundle_test) {
    kiwi::Bundle bundle = kiwi::Bundle();
    bundle.newPackBuffer(1024);
    if (kiwi::mpiUtils::global_process.own_rank == MASTER_PROCESSOR) { // pack data.
        bundle.put(1024);
        std::string s = "hello";
        bundle.put(s);
        bundle.put('c');
    }

    MPI_Bcast(bundle.getPackedData(), bundle.getPackedDataCap(),
              MPI_BYTE, MASTER_PROCESSOR, MPI_COMM_WORLD); // synchronize config information

    if (kiwi::mpiUtils::global_process.own_rank != MASTER_PROCESSOR) { // unpack data.
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
    bundle.freePackBuffer();
}

TEST(bundle_test_vector, bundle_test) {
    kiwi::Bundle bundle = kiwi::Bundle();
    bundle.newPackBuffer(1024);
    if (kiwi::mpiUtils::global_process.own_rank == MASTER_PROCESSOR) { // pack data.
        bundle.put(std::vector<int>{1, 2, 3, 4});
        std::string s = "hello";
        bundle.put(s);
    }

    MPI_Bcast(bundle.getPackedData(), bundle.getPackedDataCap(),
              MPI_BYTE, MASTER_PROCESSOR, MPI_COMM_WORLD); // synchronize config information

    if (kiwi::mpiUtils::global_process.own_rank != MASTER_PROCESSOR) { // unpack data.
        int cursor = 0;
        std::vector<int> vec;
        std::string hello;
        bundle.get(cursor, vec);
        bundle.get(cursor, hello);
        EXPECT_EQ(vec.size(), 4);
        EXPECT_EQ(vec[0], 1);
        EXPECT_EQ(vec[1], 2);
        EXPECT_EQ(vec[2], 3);
        EXPECT_EQ(vec[3], 4);
        EXPECT_EQ(hello, "hello");
    }
    bundle.freePackBuffer();
}

TEST(bundle_test_mixed, bundle_test) {
    kiwi::Bundle bundle = kiwi::Bundle();
    bundle.newPackBuffer(1024);
    if (kiwi::mpiUtils::global_process.own_rank == MASTER_PROCESSOR) { // pack data.
        bundle.pack(MPI_COMM_WORLD, 1024);
        std::string s = "hello";
        bundle.put(s);
        bundle.pack(MPI_COMM_WORLD, 'c');
    }

    MPI_Bcast(bundle.getPackedData(), bundle.getPackedDataCap(),
              MPI_BYTE, MASTER_PROCESSOR, MPI_COMM_WORLD); // synchronize config information

    if (kiwi::mpiUtils::global_process.own_rank != MASTER_PROCESSOR) { // unpack data.
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
    bundle.freePackBuffer();
}
