//
// Created by genshen on 2018-04-06.
//

#ifndef KIWI_MESSAGE_LOOPER_H
#define KIWI_MESSAGE_LOOPER_H

#include <list>

#include "message_runner.h"

/**
 * This class implement a message loop.
 * In this loop, MessageRunner can be registered {@note before starting loop}.
 * Then, the loop start to listen message (e.g. MPI message),
 * and dispatch different message to different runner.
 * Usage:
 *  1. register runner first, the runner must inherit from class {@see MessageRunner}.
 *  2. then, call kiwi::MessageLooper::start();
 * Note, run start method in {@note: a new thread} is a recommended,
 * because loop will not exist until all runner's shouldDetach method returns true.
 * And runners in message loop will be unregistered automatically before loop finished.
 */
namespace kiwi {
  class MessageLooper {
  public:
    /**
     * Start message looper.
     * This method will run message listening in a nearly dead loop.
     * When a message reaches, the looper dispatcher will dispatch the message to corresponding runner.
     * Then the runner will handle the message (processor the message).
     */
    static void start();

    /**
     * Register a runner. The runner specified by {@var runner} will be added to the list.
     * The runner must inherit from class {@see MessageRunner} and implement its abstract methods.
     *
     * The memory of this runner will be released in unRegisterRunner method automatically
     * if this runner's shouldDetach method returns true.
     * @param runner the new runner.
     */
    static void registerRunner(MessageRunner *runner);

    /**
     * unregister a runner.
     * Then the runner will be detached form message loop.
     * @param runner the message runner to be unregistered.
     * @deprecated
     */
    static void unRegisterRunner(MessageRunner *runner);

    /**
     * set message listener communication domain.
     * MessageLooper on this processor will listen mpi message in this domain.
     * default value is MPI_COMM_WORLD.
     * @param comm
     */
    static void setGlobalMessageDomain(MPI_Comm comm);

    /**
     * \return return number of runners
     */
    inline static size_t countRunners() { return _runners.size(); }

  private:
    /**
     * Travel all runners in {@var _runners}, check each runner should be detached.
     * And clean up all detached runners.
     * @return True: all runner's shouldDetach method returns true or {@var _runners is empty}, then the message loop
     * will exits. False for otherwise, the message loop will continue run.
     */
    static bool shouldExistLoop();

    // message listen communication domain, default value is MPI_COMM_WORLD.
    static MPI_Comm global_comm_domain;

    // collection of all message runners. todo read-write lock.
    static std::list<MessageRunner *> _runners;
  };
} // namespace kiwi

#endif // KIWI_MESSAGE_LOOPER_H
