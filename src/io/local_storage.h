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
    class LocalStorage {
    public:

        IOWriter writer;

        /**
         * initialize using default header size and local header size.
         * @param pFile pointer of MPI file.
         */
        LocalStorage(MPI_File pFile);

        /**
         * config local storage with default values.
         * @param pFile pointer of MPI file.
         */
        LocalStorage(MPI_File pFile, size_t global_header_size,
                     size_t local_header_size, size_t block_size);

        /**
         * config local storage whit user specified values.
         * this method should be called once.
         * @param global_header_size header size used to initialize IOWriter in bytes
         * @param local_header_size the header size for each MPI rank in bytes.
         * @param block_size block size used to initialize IOWriter.
         * @param type basic data type(element type).
         */
        bool make(MPI_Datatype type, mpi_process mpi_p);

        void writeHeader(byte *data, size_t size, mpi_process mpi_p);

    private:
        size_t _global_header_size;
        size_t _local_header_size;
        size_t _block_size;
    };

}
#endif //KIWI_LOCAL_STORAGE_H
