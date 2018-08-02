//
// Created by genshen on 4/6/18.
//

#include <iostream>
#include "../platform/mpi_support.h"
#include "../utils/mpi_utils.h"
#include "message_looper.h"

std::list<kiwi::MessageRunner *> kiwi::MessageLooper::_runners; // define of _runners.
MPI_Comm kiwi::MessageLooper::global_comm_domain = MPI_COMM_WORLD;

void kiwi::MessageLooper::start() {
    while (!shouldExistLoop()) {
        MPI_Status status;
        // checkout income message but not receive it.
#ifdef FUNC_MPI_MPROBE_SUPPORTED
        MPI_Message msg;
        MPI_Mprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, global_comm_domain, &msg, &status);
#else
        // Probe for an incoming message from any process with and tag.
        MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, global_comm_domain,
                  &status); // probe but not receive. Get blocked if there is no message.
#endif

        // check each runners's filter, dispatch message to one runner.
        for (MessageRunner *runner : _runners) {
            if (runner->filter(&status)) {
#ifdef FUNC_MPI_MPROBE_SUPPORTED
                runner->onMessage(&status, &msg);
#else
                runner->onMessage(&status);
#endif
                break;
            }
        }
    }
    // todo clean list.
}

void kiwi::MessageLooper::setGlobalMessageDomain(MPI_Comm comm) {
    global_comm_domain = comm;
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
    runner->onAttach();
}

void kiwi::MessageLooper::unRegisterRunner(MessageRunner *mr) {
    for (auto iter = _runners.begin(); iter != _runners.end();) {
        MessageRunner *pItem = *iter;
        if (pItem == mr) {
            pItem->onDetach(); // call onDetach of this runner before destroying it.
            delete pItem;
            iter = _runners.erase(iter);
        } else {
            iter++;
        }
    }
}
