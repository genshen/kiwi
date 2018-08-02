//
// Created by genshen on 8/2/18.
//

#ifndef KIWI_GTEST_ENV_H
#define KIWI_GTEST_ENV_H

#include <gtest/gtest.h>
#include <utils/mpi_utils.h>

namespace kiwi {
    class MPIEnvironment : public ::testing::Environment {
    public:
        void SetUp() override {
            char **argv = nullptr;
            int argc = 0;
            kiwi::mpiUtils::initialMPI(argc, argv);
        }

        void TearDown() override {
            kiwi::mpiUtils::finishMPI();
        }

        ~MPIEnvironment() override = default;
    };
}

#endif //KIWI_GTEST_ENV_H
