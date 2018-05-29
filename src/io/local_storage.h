//
// Created by genshen on 2018-05-29.
//

#ifndef KIWI_LOCAL_STORAGE_H
#define KIWI_LOCAL_STORAGE_H

/**
 * a file format named local storage using MPI_IO.
 */
#include "io_writer.h"

#define DEFAULT_LOCAL_STORAGE_SIZE 1024
namespace kiwi {
    class LocalStorage : public IOWriter {
    public:
        /**
         * config local storage with default values.
         */
        LocalStorage(const std::string &filename);

        /**
         * config local storage whit user specified values.
         * @param global_header_size header size used to initialize IOWriter
         * @param local_header_size the header size for each MPI rank.
         * @param block_size block size used to initialize IOWriter.
         */
        LocalStorage(size_t global_header_size, size_t local_header_size, size_t block_size,
                     const std::string &filename);

        ~LocalStorage();

        bool make();

        void writeHeader(byte *data, size_t size);

    private:
        size_t _local_header_size;
    };

}
#endif //KIWI_LOCAL_STORAGE_H
