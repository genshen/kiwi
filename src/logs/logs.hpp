//
// Created by genshen on 4/16/18.
//

#ifndef KIWI_LOGS_H
#define KIWI_LOGS_H


#include <fmt/format.h>
#include <utils/mpi_utils.h>

#define LOG_FORMAT "[%s] %d:%s:"
namespace kiwi {

    class log {
    public:
        bool async = false;
        bool detail = true;

        static void setFormat(std::string) {

        }

        template<class ... Types>
        static void out_log(const char *tag, const char *level, const char *format, Types ... args) {
            char *info_format = (char *) malloc(strlen(LOG_FORMAT) + strlen(format) + 1);//+1 for the null-terminator
            //in real code you would check for errors in malloc here
            strcpy(info_format, LOG_FORMAT);
            strcat(info_format, format);

            printf(info_format, "Info", mpiUtils::ownRank, tag, args...); // [Info] tag: messages
            free(info_format);
        }

        // todo format, buffer.
        template<class ... Types>
        static void i(const char *tag, const char *format, Types ... args) {
            out_log(tag, "[Info]", format, args...);
        }

        static void e(const char *filename, const char *func, const int line,
                             const char *tag, const char *format, ...) {
//            printf(strcat("[%s] %s:%s", format)); // [Info] tag:
        }
    };
}

#define LogE(tag, format, ...) { \
  /*   kiwi::log.v("[Info]"tag":" format "n", __VA_ARGS__); */ \
  kiwi::log::errorlog(__FILE__, __func__, __LINE__, tag, format, __VA_ARGS__); \
}


//#define DEBUG(message) { \
//  if(kiwi::detail){  \
//     printf("%s,%s,%d:%s\n", __FILE__, __func__, __LINE__, message);\
//  }else {   \
//     printf("%s\n", message);\
//  }  \
//}

#endif // KIWI_LOGS_H