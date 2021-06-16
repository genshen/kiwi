//
// Created by genshen on 4/17/18.
//

#include "logs.h"

kiwi::logs::LogOptions kiwi::logs::
options{async : false, detail : true, colorful : false, log_file : false, log_format : "{0} P{1}:{2}:"};

std::ofstream kiwi::logs::stream;

void kiwi::logs::setFormat(const std::string &format) { options.log_format = format; }

bool kiwi::logs::setLogFile(const std::string &filename) {
  options.colorful = false;
  options.log_file = true;
  // open file.
  stream.open(filename, std::ios::out | std::ios::app);
  return stream.good();
}

void kiwi::logs::setColorFul(bool with_color) {
  if (!options.log_file) {
    options.colorful = with_color;
  }
}

void kiwi::logs::finalize() {
  if (options.log_file && stream.is_open()) { // close file.
    stream.close();
  }
}

/**
template<class ... Types>
void kiwi::logs::out_log(const char *tag, const char *level, const char *format, Types ... args) {
}

template<class... Types>
void kiwi::logs::i(const char *tag, const char *format, Types... args) {
    out_log(tag, "[Info]", format, args...);
}
**/