//
// Created by genshen on 4/7/18.
//

#include <gtest/gtest.h>
#include "utils/mpi_utils.h"
#include "event/message_runner.h"
#include "event/message_looper.h"
#include "../test_config.h"

#define MESSAGE_LOOP_TEST_TAG 1

class MsgGet : public kiwi::MessageRunner {
public:
    long id = 1204;
    bool message_received = false;
    int message_data = 0;

    bool shouldDetach() const override { // detach this runner from message loop, if message have been received.
        return message_received;
    }

    bool filter(MPI_Status *pStatus) override {
        return pStatus->MPI_SOURCE == MASTER_PROCESSOR && pStatus->MPI_TAG == MESSAGE_LOOP_TEST_TAG;
    }

    void onMessage(MPI_Status *pStatus) override {
        MPI_Recv(&message_data, 1, MPI_INT, MASTER_PROCESSOR, MESSAGE_LOOP_TEST_TAG,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        message_received = true;
        std::cout << message_data << std::endl;
    }
};

TEST(msg_loop_test_dispatch, message_loop_test) {
    if (kiwi::mpiUtils::ownRank == MASTER_PROCESSOR) { // send message.
        int data = 1024;
        MPI_Send(&data, 1, MPI_INT, 1, MESSAGE_LOOP_TEST_TAG, MPI_COMM_WORLD);
    } else if (kiwi::mpiUtils::ownRank == 1) { // receive message.
        kiwi::MessageLooper::registerRunner(new MsgGet());
        // a dead loop to listen and dispatch messages.
        // And runners in message loop will be unregistered automatically before loop finished.
        kiwi::MessageLooper::start(); // run start() in a new thread may be a better way.
    }
}
