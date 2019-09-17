//
// Created by genshen on 5/29/18.
//

#include <gtest/gtest.h>
#include <io/local_storage.h>
#include "../test_config.h"

TEST(local_storage_header_test, local_storage_test) {
    MPI_File pFile;
    int status = MPI_File_open(kiwi::mpiUtils::global_process.comm,
                               KIWI_TEST_TEMP_STORAGE_PATH "/local_storage_test.bin",
                               MPI_MODE_CREATE | MPI_MODE_WRONLY,
                               MPI_INFO_NULL, &pFile);
    if (status == -1) {
        GTEST_FATAL_FAILURE_("can not access file in MPI IO.");
    }

    kiwi::LocalStorage storage(pFile, 128, 32, 128);
    storage.make(MPI_BYTE, kiwi::mpiUtils::global_process);
    kiwi::byte data[26];
    for (int i = 0; i < 26; i++) {
        data[i] = static_cast<kiwi::byte>('A' + i);
    }
    storage.writer.writeAll(data, 26);

    for (int i = 0; i < 26; i++) {
        data[i] = static_cast<kiwi::byte>('a' + i);
    }
    storage.writeHeader(data, 26, kiwi::mpiUtils::global_process);
//     todo read data and compare data.
    MPI_File_close(&pFile);
}

TEST(local_storage_cross_block_test, local_storage_test) {
    MPI_File pFile;
    int status = MPI_File_open(kiwi::mpiUtils::global_process.comm,
                               KIWI_TEST_TEMP_STORAGE_PATH "/local_storage_cross_block_test.bin",
                               MPI_MODE_CREATE | MPI_MODE_WRONLY,
                               MPI_INFO_NULL, &pFile);
    if (status == -1) {
        GTEST_FATAL_FAILURE_("can not access file in MPI IO.");
    }

    kiwi::LocalStorage storage(pFile, 0, 0, 32);
    storage.make(MPI_BYTE, kiwi::mpiUtils::global_process);

    for (int loop = 0; loop < 10; loop++) {
        kiwi::byte a[32];
        for (int i = 0; i < 32; i++) {
            a[i] = 'A' + kiwi::mpiUtils::global_process.own_rank;
        }
        storage.writer.writeAll(a, 32);
    }
    // todo read data and compare data.
    MPI_File_close(&pFile);
}

// type for testing write struct to MPI-IO file.
struct IO_Test_Data_Type {
    unsigned long id;
    int type;
    unsigned long step;
};

void setType(MPI_Datatype &sendPartType) {
    int blocklengths[] = {1, 1, 1}; // 1 unsLong value (id), 1 int value (cid), 1 unsigned long values.
    MPI_Datatype types[] = {MPI_UNSIGNED_LONG, MPI_INT, MPI_UNSIGNED_LONG};

    MPI_Aint displacements[3];
    IO_Test_Data_Type pdata_dummy;

    MPI_Get_address(&pdata_dummy, displacements);
    MPI_Get_address(&pdata_dummy.type, displacements + 1);
    MPI_Get_address(&pdata_dummy.step, displacements + 2);

    MPI_Aint base = displacements[0];
    for (int i = 0; i < 3; i++) {
        displacements[i] -= base;
    }

    MPI_Type_create_struct(3, blocklengths, displacements, types, &sendPartType);
    MPI_Type_commit(&sendPartType);
}

TEST(cross_block_struct_test, local_storage_test) {
    MPI_File pFile;
    int status = MPI_File_open(kiwi::mpiUtils::global_process.comm,
                               KIWI_TEST_TEMP_STORAGE_PATH "/local_storage_cross_block_struct_test.bin",
                               MPI_MODE_CREATE | MPI_MODE_WRONLY,
                               MPI_INFO_NULL, &pFile);
    if (status == -1) {
        GTEST_FATAL_FAILURE_("can not access file in MPI IO.");
    }

    MPI_Datatype write_types;
    setType(write_types);

    const unsigned long block_size = 8;
    const unsigned long buffer_size = 2 * 8;
    kiwi::LocalStorage storage(pFile, 0, 0, block_size);
    storage.make(write_types, kiwi::mpiUtils::global_process);

    IO_Test_Data_Type buffer[buffer_size];

    memset(buffer, 'A' + kiwi::mpiUtils::global_process.own_rank, buffer_size * sizeof(IO_Test_Data_Type));

    for (int loop = 0; loop < 1; loop++) {
        storage.writer.write(buffer, buffer_size);
    }
    // todo read data and compare data.
    MPI_File_close(&pFile);
}

TEST(cross_block_struct_bytes_test, local_storage_test) {
    MPI_File pFile;
    int status = MPI_File_open(kiwi::mpiUtils::global_process.comm,
                               KIWI_TEST_TEMP_STORAGE_PATH "/cross_block_struct_bytes_test.bin",
                               MPI_MODE_CREATE | MPI_MODE_WRONLY,
                               MPI_INFO_NULL, &pFile);
    if (status == -1) {
        GTEST_FATAL_FAILURE_("can not access file in MPI IO.");
    }

    const unsigned long block_size = 1;
    const unsigned long buffer_size = 2 * 1;
    kiwi::LocalStorage storage(pFile, 0, 0, block_size * sizeof(IO_Test_Data_Type));
    storage.make(MPI_BYTE, kiwi::mpiUtils::global_process);

    IO_Test_Data_Type buffer[buffer_size];

    memset(buffer, 'A' + kiwi::mpiUtils::global_process.own_rank, buffer_size * sizeof(IO_Test_Data_Type));

    for (int loop = 0; loop < 10; loop++) {
        storage.writer.write(buffer, buffer_size * sizeof(IO_Test_Data_Type));
    }
    // todo read data and compare data.
    MPI_File_close(&pFile);
}
