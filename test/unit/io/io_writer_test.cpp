//
// Created by genshen on 3/24/18.
//

#include <gtest/gtest.h>
#include <io/local_storage.h>
#include "../test_config.h"

TEST(writer_block_test, io_writer_test) {
    MPI_File pFile;
    MPI_File_open(kiwi::mpiUtils::global_process.comm,
                  KIWI_TEST_TEMP_STORAGE_PATH "/io_writer_block_test.bin",
                  MPI_MODE_CREATE | MPI_MODE_WRONLY,
                  MPI_INFO_NULL, &pFile);

    kiwi::IOWriter writer(pFile);
    writer.make(0, 32, MPI_BYTE, kiwi::mpiUtils::global_process);

    int a[32];
    for (int i = 0; i < 32; i++) {
        a[i] = 'A' + kiwi::mpiUtils::global_process.own_rank;
    }
    writer.writeAll(a, 32 * sizeof(int));
    MPI_File_close(&pFile);
    // todo read data and compare data.
}
