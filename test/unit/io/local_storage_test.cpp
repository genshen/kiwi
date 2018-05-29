//
// Created by genshen on 5/29/18.
//

#include <gtest/gtest.h>
#include <io/local_storage.h>
#include "../test_config.h"

TEST(local_storage_header_test, local_storage_test) {
    kiwi::LocalStorage storage(1024, 128, 4096, KIWI_TEST_TEMP_STORAGE_PATH "/local_storage_test.bin");
    storage.make();
    kiwi::byte data[26];
    for (int i = 0; i < 26; i++) {
        data[i] = static_cast<kiwi::byte>('A' + i);
    }
    storage.write(data, 26);

    for (int i = 0; i < 26; i++) {
        data[i] = static_cast<kiwi::byte>('a' + i);
    }
    storage.writeHeader(data, 26);

    for (int i = 0; i < 10; i++) {
        data[i] = static_cast<kiwi::byte>('0' + i);
    }
    storage.write(data, 10);
    // todo read data and compare data.
}