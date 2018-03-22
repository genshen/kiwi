//
// Created by genshen(genshenchu@gmail.com) on 2018-03-21.
//

#include "base_app.h"
#include "utils/mpi_utils.h"

void kiwi::baseApp::run(int argc, char **argv) {
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

//bool kiwi::kiwi::beforeCreate() {
//    return true;
//}

bool kiwi::baseApp::create(int argc, char *argv[]) {
    mpiUtils::initialMPI(argc,argv);
    return true;
}

void kiwi::baseApp::start() {
    this->onStart();
    this->onFinish();
}

void kiwi::baseApp::destroy() {
    mpiUtils::finishMPI();
}
