//
// Created by genshen on 5/29/18.
//

#include <gtest/gtest.h>
#include <io/local_storage.h>
#include "../test_config.h"

TEST(local_storage_header_test, local_storage_test) {
    MPI_File pFile;
    MPI_File_open(kiwi::mpiUtils::global_comm,
                  KIWI_TEST_TEMP_STORAGE_PATH "/local_storage_test.bin",
                  MPI_MODE_CREATE | MPI_MODE_WRONLY,
                  MPI_INFO_NULL, &pFile);

    kiwi::LocalStorage storage(pFile, 128, 32, 128);
    storage.make(MPI_BYTE);
    kiwi::byte data[26];
    for (int i = 0; i < 26; i++) {
        data[i] = static_cast<kiwi::byte>('A' + i);
    }
    storage.writer.write(data, 26);

    for (int i = 0; i < 26; i++) {
        data[i] = static_cast<kiwi::byte>('a' + i);
    }
    storage.writeHeader(data, 26);
//     todo read data and compare data.
}

TEST(local_storage_cross_block_test, local_storage_test) {
    MPI_File pFile;
    MPI_File_open(kiwi::mpiUtils::global_comm,
                  KIWI_TEST_TEMP_STORAGE_PATH "/local_storage_cross_block_test.bin",
                  MPI_MODE_CREATE | MPI_MODE_WRONLY,
                  MPI_INFO_NULL, &pFile);

    kiwi::LocalStorage storage(pFile, 0, 0, 32);
    storage.make(MPI_BYTE);

    int a[32];
    for (int i = 0; i < 32; i++) {
        a[i] = 'A' + kiwi::mpiUtils::own_rank;
    }
    storage.writer.write(a, 32);
    // todo read data and compare data.
}