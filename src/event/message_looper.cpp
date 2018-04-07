//
// Created by genshen on 4/6/18.
//

#include <iostream>
#include "../utils/mpi_utils.h"
#include "message_looper.h"

std::list<kiwi::MessageRunner *> kiwi::MessageLooper::_runners; // define of _runners.

void kiwi::MessageLooper::start() {
    while (!shouldExistLoop()) {
        MPI_Status status;
        // Probe for an incoming message from any process with and tag.
        MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD,
                  &status); // probe but not receive. Get blocked if there is no message.
        for (MessageRunner *runner : _runners) { // check each runners's filter, dispatch message to one runner.
            if (runner->filter(&status)) {
                runner->onMessage(&status);
                break;
            }
        }
    }
    // todo clean list.
}

bool kiwi::MessageLooper::shouldExistLoop() {
    // clean detached runner.
    _runners.remove_if([](const MessageRunner *r) {
        return r->shouldDetach();
    });

    return _runners.empty();
/*
    bool flag = true;
    for (auto &runner : _runners) {
        if (runner->shouldDetach()) { // check each runner.
            unRegisterRunner(runner); // if reaches to the end, just unregister it.
        } else {
            flag = false; // If at least one runner not end, the message loop will continue.
        }
    }
    return flag;
*/
}

void kiwi::MessageLooper::registerRunner(MessageRunner *runner) {
    _runners.push_back(runner); // just add it to the list _runners.
}

void kiwi::MessageLooper::unRegisterRunner(MessageRunner *mr) {
    for (auto iter = _runners.begin(); iter != _runners.end();) {
        MessageRunner *pItem = *iter;
        if (pItem == mr) {
            delete pItem;
            iter = _runners.erase(iter);
        } else {
            iter++;
        }
    }
}
