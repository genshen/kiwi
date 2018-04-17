//
// Created by genshen on 4/16/18.
//

#include <gtest/gtest.h>
#include "logs/logs.h"

TEST(logs_print_test, logs_test) {
    kiwi::logs::s("tag", "{0}s-{1}\n", "hee", 100);
    kiwi::logs::v("tag", "{0}s-{1}\n", "hee", 100);
    kiwi::logs::i("tag", "{0}s-{1}\n", "hee", 100);
    kiwi::logs::w("tag", "{0}s-{1}\n", "hee", 100);
    kiwi::logs::e("tag", "{0}s-{1}\n", "hee", 100);
    kiwi::logs::d("tag", "{0}s-{1}\n", "hee", 100);
}
