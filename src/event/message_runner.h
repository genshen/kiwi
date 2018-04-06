//
// Created by genshen on 4/6/18.
//

#ifndef KIWI_MESSAGE_RUNNER_H
#define KIWI_MESSAGE_RUNNER_H


#include "../utils/mpi_utils.h"

namespace kiwi {
    class MessageRunner {
    public:
        /**
         * the runner global unique id to identify each runner.
         * This id will be generated while this runner is registered.
         */
        long id;

        /**
         * Checkout whether this runner should be detached form message loop.
         * This method will be called before each message loop.
         * If the runner should be detached, the runner will be unregistered automatically in the this message loop.
         * By default, the runner has no end (return false,it will be be detached).
         * It will be detached/unregistered at the end of message loop lifecycle.
         * @return True for ending of this runner, false for otherwise.
         */
        virtual bool shouldDetach() {
            return false;
        };

        /**
         * Filter message.
         * This method indicates which message should be dispatch to this runner.
         *
         */
        virtual bool filter(MPI_Status *pStatus) = 0;

        virtual void onMessage(MPI_Status *pStatus) = 0;


    };
}
#endif //KIWI_MESSAGE_RUNNER_H
