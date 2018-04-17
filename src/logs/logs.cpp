//
// Created by genshen on 4/17/18.
//

#include "logs.h"


bool kiwi::logs::async = false;
bool kiwi::logs::detail = true;
bool kiwi::logs::colorful = true;

//template<class ... Types>
//void kiwi::logs::out_log(const char *tag, const char *level, const char *format, Types ... args) {
//}

//template<class... Types>
//void kiwi::logs::i(const char *tag, const char *format, Types... args) {
//    out_log(tag, "[Info]", format, args...);
//}
