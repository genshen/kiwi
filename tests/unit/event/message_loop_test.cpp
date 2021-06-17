//
// Created by genshen on 4/7/18.
//

#include <gtest/gtest.h>
#include <logs/logs.h>

#include "event/message_looper.h"
#include "event/message_runner.h"
#include "utils/mpi_utils.h"

#define MESSAGE_LOOP_TEST_TAG 1

class MsgGet : public kiwi::MessageRunner {
public:
  long id = 1204;
  bool message_received = false;
  int message_data = 0;
  const MPI_Comm comm;

  explicit MsgGet(const MPI_Comm _comm) : comm(_comm) {}

  void onAttach() override {}

  void onDetach() override {}

  bool shouldDetach() const override { // detach this runner from message loop, if message have been received.
    return message_received;
  }

  bool filter(MPI_Status *pStatus) override {
    return pStatus->MPI_SOURCE == MASTER_PROCESSOR && pStatus->MPI_TAG == MESSAGE_LOOP_TEST_TAG;
  }

  void onMessage(MPI_Status *pStatus) override {
    MPI_Recv(&message_data, 1, MPI_INT, MASTER_PROCESSOR, MESSAGE_LOOP_TEST_TAG, comm, MPI_STATUS_IGNORE);
    message_received = true;
    std::cout << message_data << std::endl;
  }

  void onMessage(MPI_Status *pStatus, MPI_Message *pMessage) override {
    MPI_Mrecv(&message_data, 1, MPI_INT, pMessage, MPI_STATUS_IGNORE);
    message_received = true;
    std::cout << message_data << std::endl;
  }
};

// require at least 2 MPI ranks
TEST(message_loop_test, msg_loop_test_dispatch) {
  if (kiwi::mpiUtils::global_process.own_rank == MASTER_PROCESSOR) { // send message.
    int data = 1024;
    MPI_Send(&data, 1, MPI_INT, 1, MESSAGE_LOOP_TEST_TAG, MPI_COMM_WORLD);
  } else if (kiwi::mpiUtils::global_process.own_rank == 1) { // receive message.
    auto _runner = MsgGet(MPI_COMM_WORLD);
    kiwi::MessageLooper::registerRunner(&_runner);
    // a dead loop to listen and dispatch messages.
    // And runners in message loop will be unregistered automatically before loop finished.
    kiwi::MessageLooper::start(); // run start() in a new thread may be a better way.
  }
}

void NewMessageLooper();

// require at least 2 MPI ranks
TEST(message_loop_test, msg_loop_test_multiple_domain) {
  const int PROS_PER_GROUP = 2;
  int world_rank, world_size;
  // todo: to use in new thread, MPI must be initialized with thread support.
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  if (world_size % PROS_PER_GROUP != 0) {
    GTEST_FATAL_FAILURE_("You must run this with 2n processes (where n is number of simulation domains).");
  }

  // split the global domain into ${GROUPS} groups.
  int color = world_rank / PROS_PER_GROUP;
  // Split the communicator based on the color.
  MPI_Comm row_comm;
  int rank_row_comm, size_row_comm;
  MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &row_comm);
  MPI_Comm_rank(row_comm, &rank_row_comm);
  MPI_Comm_size(row_comm, &size_row_comm);

  kiwi::MessageLooper::setGlobalMessageDomain(row_comm);
  if (rank_row_comm == MASTER_PROCESSOR) { // send message.
    int data = 1024;
    MPI_Send(&data, 1, MPI_INT, 1, MESSAGE_LOOP_TEST_TAG, row_comm);
  } else if (rank_row_comm == 1) {
    auto _runner = MsgGet(row_comm);
    kiwi::MessageLooper::registerRunner(&_runner);
    // receive message in new thread.
    NewMessageLooper();
  }
  MPI_Barrier(row_comm);
  sleep(2); // wait new thread to finish
}

void *messageLoopNewThread(void *object) {
  // Start a dead loop to listen and dispatch messages.
  // And runners in message loop will be unregistered automatically before loop finished.
  kiwi::MessageLooper::start();
  return nullptr;
}

void NewMessageLooper() {
  pthread_t message_thread;
  int ret;

  ret = pthread_create(&message_thread, nullptr, messageLoopNewThread, nullptr);
  if (ret != 0) {
    return;
  }

  // Make a thread detached(by default threads are joinable).
  int err_detach = 0;
  err_detach = pthread_detach(message_thread);
  if (err_detach != 0) {
    // detach error.
    return;
  }
}
