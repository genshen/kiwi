//
// Created by genshen on 2018/03/20.
//

#ifndef KIWI_GTEST_ENV_H
#define KIWI_GTEST_ENV_H

#include <gtest/gtest.h>
#include "test_config.h"

#ifdef KIWI_TEST_MPI_ENABLE_FLAG

#include "utils/mpi_utils.h"

class MPIEnvironment : public ::testing::Environment {
public:
    void SetUp() override {
        char **argv = NULL;
        int argc = 0;
        kiwi::mpiUtils::initialMPI(argc, argv);
//        int mpiError = MPI_Init(&argc, &argv);
//        ASSERT_FALSE(mpiError);
    }

    void TearDown() override {
        kiwi::mpiUtils::finishMPI();
//        int mpiError = MPI_Finalize();
//        ASSERT_FALSE(mpiError);
    }

    ~MPIEnvironment() override = default;
};

#  endif  // end KIWI_TEST_MPI_ENABLE_FLAG

// see https://github.com/google/googletest/issues/822 for more information.
// main function for adapt mpi environment
int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
#ifdef KIWI_TEST_MPI_ENABLE_FLAG
    ::testing::AddGlobalTestEnvironment(new MPIEnvironment);
#endif  // end KIWI_TEST_MPI_ENABLE_FLAG
    return RUN_ALL_TESTS();
}

#endif // KIWI_GTEST_ENV_H
