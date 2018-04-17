//
// Created by genshen on 4/17/18.
//

#ifndef KIWI_LOGS_H
#define KIWI_LOGS_H

#include <sstream>
#include <fmt/format.h>
#include "colors.h"
#include "../utils/mpi_utils.h"

#define LOG_FORMAT "{0} P{1}:{2}:"
namespace kiwi {
    class logs {
    public:
        static bool async;
        static bool detail;
        static bool colorful;

        static void setFormat(std::string) {}

        // todo format, buffer.
        // success
        template<class ... Types>
        static void s(const char *tag, const char *format, Types ... args) {
            out_log("[S]", COLOR_R_GREEN, tag, format, args...);
        }

        // information
        template<class ... Types>
        static void i(const char *tag, const char *format, Types ... args) {
            out_log("[I]", COLOR_R_BLUE, tag, format, args...);
        }

        // VERBOSE
        template<class ... Types>
        static void v(const char *tag, const char *format, Types ... args) {
            out_log("[V]", COLOR_CLEAR, tag, format, args...);
        }

        // warning
        template<class ... Types>
        static void w(const char *tag, const char *format, Types ... args) {
            out_log("[W]", COLOR_R_ORANGE, tag, format, args...);
        }

        // error
        template<class ... Types>
        static void e(const char *tag, const char *format, Types ... args) {
            out_log("[E]", COLOR_R_RED, tag, format, args...);
        }

        // debug
        template<class ... Types>
        static void d(const char *tag, const char *format, Types ... args) {
            out_log("[D]", COLOR_R_MAGENTA, tag, format, args...);
        }

    private:
        template<class ... Types>
        static void out_log(const char *level, const char *level_color,
                            const char *tag, const char *format, Types ... args) {
            std::string out_header = fmt::format(LOG_FORMAT, level, mpiUtils::ownRank, tag);
            std::ostringstream o_string; // todo combine to line 1.
            if (colorful) {
                o_string << level_color;
            }

            o_string << out_header;
            o_string << fmt::format(format, args...);

            if (colorful) {
                o_string << COLOR_CLEAR;
            }
            printf(o_string.str().c_str());
        }
    };
}


//#define LogE(tag, format, ...) { \
//  /*   kiwi::log.v("[Info]"tag":" format "n", __VA_ARGS__); */ \
//  kiwi::log::errorlog(__FILE__, __func__, __LINE__, tag, format, __VA_ARGS__); \
//}

//#define DEBUG(message) { \
//  if(kiwi::detail){  \
//     printf("%s,%s,%d:%s\n", __FILE__, __func__, __LINE__, message);\
//  }else {   \
//     printf("%s\n", message);\
//  }  \
//}
#endif //KIWI_LOGS_H
