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
        virtual void onAttach() {};

        /**
         * In each message loop, if shouldDetach returns true, this runner will be detached immediately.
         * onDetach will be called after this runner is detached.
         * Detach means the runner is removed from message looper (messages will not be received), and this runner object will be destroyed.
         */
        virtual void onDetach() {};

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
         * This method check which message should be dispatch to this runner.
         * @param pStatus MPI message status.
         */
        virtual bool filter(MPI_Status *pStatus) = 0;

        /**
         * If matched probe api MPI_Mprobe is not support by MPI,
         * the message loop will use MPI_PROBE to checks for incoming messages without receiving them.
         *
         * Then this method will be called to process the message if @filter() returns true in runner.
         *
         * @param pStatus MPI_Status returned by MPI_PROBE.
         */
        virtual void onMessage(MPI_Status *pStatus) {};

        /**
         * If matched probe api MPI_Mprobe is not support by MPI,
         * the message loop will usr MPI_Mprobe to check for incoming messages.
         *
         * And this method will then be called to process the message if @filter() returns true.
         * Use MPI_MRECV or MPI_IMRECV to receive message.
         * @param pStatus MPI_Status returned by MPI_Mprobe
         * @param pMessage MPI_Message set by MPI_Mprobe
         */
        virtual void onMessage(MPI_Status *pStatus, MPI_Message *pMessage) {};

    };
}
#endif //KIWI_MESSAGE_RUNNER_H
