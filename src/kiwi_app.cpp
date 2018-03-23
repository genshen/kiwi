//
// Created by genshen(genshenchu@gmail.com) on 2018-03-21.
//

#include "kiwi_app.h"
#include "utils/mpi_utils.h"

void kiwi::kiwiApp::run(int argc, char **argv) {
// app's lifecycle here.
//    auto *app = new crystalMD(argc, argv);
    if (this->beforeCreate()) {
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

bool kiwi::kiwiApp::beforeCreate() {
    return true;
}

bool kiwi::kiwiApp::create(int argc, char *argv[]) {
    mpiUtils::initialMPI(argc, argv);
    return true;
}

void kiwi::kiwiApp::onCreate() {

}

bool kiwi::kiwiApp::prepare() {
    return true;
}

void kiwi::kiwiApp::start() {
    this->onStart();
    this->onFinish();
}

void kiwi::kiwiApp::onStart() {

}

void kiwi::kiwiApp::onFinish() {

}

void kiwi::kiwiApp::beforeDestroy() {

}

void kiwi::kiwiApp::destroy() {
    mpiUtils::finishMPI();
}

void kiwi::kiwiApp::onDestroy() {

}

void kiwi::kiwiApp::abort(int code) {
    MPI_Abort(MPI_COMM_WORLD, code);
}
