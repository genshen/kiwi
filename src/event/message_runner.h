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
        // long id;

        /**
         * onAttach is called after the runner is registered to message lopper.
         */
        virtual void onAttach() = 0;

        /**
         * In each message loop, if shouldDetach returns true, this runner will be detached immediately.
         * onDetach will be called after this runner is detached.
         * Detach means the runner is removed from message looper (messages will not be received), and this runner object will be destroyed.
         */
        virtual void onDetach() = 0;

        /**
         * Checkout whether this runner should be detached form message loop.
         * This method will be called before each message loop.
         * If this method return true(the runner should be detached,),
         * the runner will be unregistered automatically in this message loop.
         *
         * By default, the runner be detached in the first message loop (return true).
         * @return True for ending of this runner, false for otherwise.
         */
        virtual bool shouldDetach() const {
            return true;
        };

        /**
         * Filter message.
         * This method indicates which message should be dispatch to this runner.
         * @param pStatus MPI message status.
         */
        virtual bool filter(MPI_Status *pStatus) = 0;

        virtual void onMessage(MPI_Status *pStatus) = 0;

    };
}
#endif //KIWI_MESSAGE_RUNNER_H
