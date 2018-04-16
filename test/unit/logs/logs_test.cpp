//
// Created by genshen on 4/16/18.
//

#include <gtest/gtest.h>
#include "logs/logs.hpp"

TEST(logs_print_test, logs_test) {
//    DEBUG("hi");
//    LogE("tag", "hello%d..", 10);
    kiwi::log::i("tag", "%s-%d", "hee", 100);
}
