//
// Created by genshen on 4/17/18.
//

#ifndef KIWI_LOGS_H
#define KIWI_LOGS_H

#include <sstream>
#include <fmt/format.h>
#include <fstream>
#include "colors.h"
#include "../utils/mpi_utils.h"

namespace kiwi {


    class logs {
        struct LogOptions {
            bool async;
            bool detail;
            bool colorful;
            bool log_file;
            std::string log_format;
        };

    public:

        /**
         * set output format for logs.
         */
        static void setFormat(const std::string &format);

        /**
         * set whether the log is colorful when outputting to console or terminal.
         * (there is no color if it output into file no matter what the value of variable colorful is.)
         * @param with_color true for colorful when outputting to console/terminal.
         */
        static void setColorFul(bool with_color);

        // todo format, buffer.
        /**
         * write log into file instant of console or terminal.
         * and open file for writing.
         * @param filename file name.
         * @return if fail to open file, false will be returned, otherwise true will be returned.
         */
        static bool setLogFile(const std::string &filename);

        /**
         * this function is called before tha application is end.
         */
        static void finalize();

        // success
        template<class ... Types>
        inline static void s(const char *tag, const char *format, Types ... args) {
            out_log("[S]", COLOR_R_GREEN, tag, format, args...);
        }

        // information
        template<class ... Types>
        inline static void i(const char *tag, const char *format, Types ... args) {
            out_log("[I]", COLOR_R_BLUE, tag, format, args...);
        }

        // VERBOSE
        template<class ... Types>
        inline static void v(const char *tag, const char *format, Types ... args) {
            out_log("[V]", COLOR_CLEAR, tag, format, args...);
        }

        // warning
        template<class ... Types>
        inline static void w(const char *tag, const char *format, Types ... args) {
            out_log("[W]", COLOR_R_ORANGE, tag, format, args...);
        }

        // error
        template<class ... Types>
        inline static void e(const char *tag, const char *format, Types ... args) {
            out_log("[E]", COLOR_R_RED, tag, format, args...);
        }

        // debug
        template<class ... Types>
        inline static void d(const char *tag, const char *format, Types ... args) {
            out_log("[D]", COLOR_R_MAGENTA, tag, format, args...);
        }

        /** only show log of specific processor **/
        template<class ... Types>
        inline static void s(const kiwi::RID rank_id, const char *tag, const char *format, Types ... args) {
            if (kiwi::mpiUtils::global_process.own_rank == rank_id) {
                s(tag, format, args...);
            }
        }

        // information
        template<class ... Types>
        inline static void i(const kiwi::RID rank_id, const char *tag, const char *format, Types ... args) {
            if (kiwi::mpiUtils::global_process.own_rank == rank_id) {
                i(tag, format, args...);
            }
        }

        // VERBOSE
        template<class ... Types>
        inline static void v(const kiwi::RID rank_id, const char *tag, const char *format, Types ... args) {
            if (kiwi::mpiUtils::global_process.own_rank == rank_id) {
                v(tag, format, args...);
            }
        }

        // warning
        template<class ... Types>
        inline static void w(const kiwi::RID rank_id, const char *tag, const char *format, Types ... args) {
            if (kiwi::mpiUtils::global_process.own_rank == rank_id) {
                s(tag, format, args...);
            }
        }

        // error
        template<class ... Types>
        inline static void e(const kiwi::RID rank_id, const char *tag, const char *format, Types ... args) {
            if (kiwi::mpiUtils::global_process.own_rank == rank_id) {
                e(tag, format, args...);
            }
        }

        // debug
        template<class ... Types>
        inline static void d(const kiwi::RID rank_id, const char *tag, const char *format, Types ... args) {
            if (kiwi::mpiUtils::global_process.own_rank == rank_id) {
                d(tag, format, args...);
            }
        }

    private:
        static LogOptions options;
        static std::ofstream stream;

        template<class ... Types>
        static void out_log(const char *level, const char *level_color,
                            const char *tag, const char *format, Types ... args) {
            std::string out_header = fmt::format(options.log_format, level, mpiUtils::global_process.own_rank, tag);
            std::ostringstream o_string; // todo combine to line 1.
            if (options.colorful) {
                o_string << level_color;
            }

            o_string << out_header;
            o_string << fmt::format(format, args...);

            if (options.colorful) {
                o_string << COLOR_CLEAR;
            }

            // write data.
            if (options.log_file) {
                stream << o_string.str();
            } else {
                printf("%s", o_string.str().c_str());
            }
        }
    };
}

// kiwi::log.v("[Info]"tag":" format "n", __VA_ARGS__);
// log(__FILE__, __func__, __LINE__, tag, format, __VA_ARGS__);

#endif //KIWI_LOGS_H
