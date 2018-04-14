//
// Created by genshen(genshenchu@gmail.com) on 2018-03-21.
//

#include "kiwi_app.h"

void kiwi::kiwiApp::setMPIThreadSupport(short type) {
    _mpi_thread_type = type;
}

void kiwi::kiwiApp::run(int argc, char *argv[]) {
    // app's lifecycle here.
    if (this->beforeCreate(argc, argv)) {
        if (this->create(argc, argv)) {
            this->onCreate();
            if (this->prepare()) {
                this->start();
            } else {
                // prepare failed
            }
            this->beforeDestroy();
        } else { // create else
            // on create failed
        }
        this->destroy();
        this->onDestroy();
    }
}

bool kiwi::kiwiApp::beforeCreate(int argc, char *argv[]) {
    return true;
}

bool kiwi::kiwiApp::create(int argc, char *argv[]) {
    if (_mpi_thread_type == MPI_THREAD_SINGLE) {
        mpiUtils::initialMPI(argc, argv);
    } else {
        mpiUtils::initMPIWithThread(argc, argv, _mpi_thread_type);
    }
    return true;
}

bool kiwi::kiwiApp::prepare() {
    return true;
}

void kiwi::kiwiApp::start() {
    this->onStart();
    this->onFinish();
}

void kiwi::kiwiApp::destroy() {
    mpiUtils::finishMPI();
}

void kiwi::kiwiApp::abort(int code) {
    MPI_Abort(MPI_COMM_WORLD, code);
}
