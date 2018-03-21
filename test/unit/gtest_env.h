//
// Created by genshen on 2018/03/20.
//

#ifndef KIWI_GTEST_ENV_H
#define KIWI_GTEST_ENV_H
#include <gtest/gtest.h>
#include "test_config.h"

#  ifdef KIWI_TEST_MPI_ENABLE
#    include "mpi.h"

class MPIEnvironment : public ::testing::Environment {
public:
    virtual void SetUp() {
        char **argv;
        int argc = 0;
        int mpiError = MPI_Init(&argc, &argv);
        ASSERT_FALSE(mpiError);
    }

    virtual void TearDown() {
        int mpiError = MPI_Finalize();
        ASSERT_FALSE(mpiError);
    }

    virtual ~MPIEnvironment() {}
};
#  endif  // end KIWI_TEST_MPI_ENABLE

// see https://github.com/google/googletest/issues/822 for more information.
// main function for adapt mpi environment
int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
#ifdef KIWI_TEST_MPI_ENABLE
    ::testing::AddGlobalTestEnvironment(new MPIEnvironment);
#endif  // end KIWI_TEST_MPI_ENABLE
    return RUN_ALL_TESTS();
}
#endif // KIWI_GTEST_ENV_H
