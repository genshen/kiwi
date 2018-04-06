//
// Created by genshen on 4/6/18.
//

#include "../utils/mpi_utils.h"
#include "message_looper.h"

void kiwi::MessageLooper::start() {
    while (shouldExistLoop()) {
        MPI_Status status;
        // Probe for an incoming message from any process with and tag.
        MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD,
                  &status); // probe but not receive. Get blocked if there is no message.
        for (MessageRunner &runner : _runners) { // check each runners's filter, dispatch message to one runner.
            if (runner.filter(&status)) {
                runner.onMessage(&status);
            }
        }

    }
}

void kiwi::MessageLooper::registerRunner(MessageRunner &runner) {
    runner.id = 0; // todo runner id.
    _runners.push_back(runner); // just add it to the list _runners.
}

bool kiwi::MessageLooper::shouldExistLoop() {
    bool flag = true;
    for (MessageRunner &runner : _runners) {
        if (runner.shouldDetach()) { // check each runner.
            unRegisterRunner(runner); // if reaches to the end, just unregister it.
        } else {
            flag = false; // If at least one runner not end, the message loop will continue.
        }
    }
    return flag;
}

void kiwi::MessageLooper::unRegisterRunner(MessageRunner &runner) {
    // todo
}
