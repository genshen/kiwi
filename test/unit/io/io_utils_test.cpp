//
// Created by genshen on 4/1/18.
//

#include <io/io_utils.hpp>
#include <gtest/gtest.h>
#include "../test_config.h"

const std::string TestFilename = KIWI_TEST_TEMP_STORAGE_PATH "/test_io_utils.bin";

TEST(io_utils_write_test_char, io_utils_write_test) {
    char chA = 'A', chA_read;

    std::fstream fs(TestFilename, std::ios::out | std::ios::binary);
    kiwi::seekWrite(fs, &chA, 0, std::ios_base::beg, 1);
    fs.close();

    std::fstream ifs(TestFilename, std::ios::in | std::ios::binary);
    kiwi::seekRead(ifs, &chA_read, 0, std::ios_base::beg, 1);
    ifs.close();

    EXPECT_EQ(chA, chA_read);
}

TEST(io_utils_write_test_string, io_utils_write_test) {
    char str1[] = "ABCD", str2[5] = {0};

    std::fstream fs(TestFilename, std::ios::out | std::ios::binary);
    kiwi::seekWrite(fs, &str1, 0, std::ios_base::beg, 1);
    fs.close();

    std::fstream ifs(TestFilename, std::ios::in | std::ios::binary);
    kiwi::seekRead(ifs, &str2, 0, std::ios_base::beg, 1);
    ifs.close();

    EXPECT_EQ(std::string(str1), std::string(str2));
}

TEST(io_utils_write_test_long, io_utils_write_test) {
    long long1 = 1024, long2;

    std::fstream fs(TestFilename, std::ios::out | std::ios::binary);
    kiwi::seekWrite(fs, &long1, 0, std::ios_base::beg, 1);
    fs.close();

    std::fstream ifs(TestFilename, std::ios::in | std::ios::binary);
    kiwi::seekRead(ifs, &long2, 0, std::ios_base::beg, 1);
    ifs.close();

    EXPECT_EQ(long1, long2);
}
