//
// Created by genshen(genshenchu@gmail.com) on 2018-3-13.
//

#ifndef KIWI_SYS_DUMP_H
#define KIWI_SYS_DUMP_H

#include <string>
#include "../utils/mpi_utils.h"
#include "../utils/data_def.h"


/*
 * This file is basically for writing atom information and system information to file, a shared file.
 * Each processor handle some blocks, which are located by processors rank_id order.
 * Each block have DEFAULT_IO_BLOCK_SIZE bytes. it has a head with DEFAULT_IO_HEADER_SIZE byte data in that file.
 * example: space divide for 4 processors.
 * ---------------------------------------------------
 *|      |    |    |    |    |    |    |    |    |    |
 *| head | p1 | p2 | p3 | p4 | p1 | p2 | p3 | p4 | ...|
 *|      |    |    |    |    |    |    |    |    |    |
 * ---------------------------------------------------
 */
namespace kiwi {
#define DEFAULT_IO_HEADER_SIZE (128) // todo
#define DEFAULT_IO_BLOCK_SIZE (1024*1024) // 1MiB

    class IOWriter {
    public:

        /**
         * Initialize variable pDumpFile, and set MPI_IO file view.
         */
        IOWriter(const std::string &filename);

        IOWriter(const std::string &filename, size_t header_size, size_t block_size);

        /**
         * close file, release unnecessary variable.
         */
        ~IOWriter();

        /**
        * create file with configured file name, header size, etc.
        * @return true for success, false for creating failed.
        */
        virtual bool make();

        /**
          *  write data indicated by b to file pDumpFile.
          * @param b  data to be writen.
          * @param start start position of array b.
          * @param size length of array b.
          * @return size that has been writen.
          */// start from 0.
        template<typename T>
        size_t write(T *b, size_t start, size_t size);

        // write from index 0 of array b.
        template<typename T>
        size_t write(T *b, size_t size);

        /**
         * get pointer of MPI FILE.
         * @return MPI_File
         */
        inline MPI_File getMPIFile() {
            return pFile;
        }

    protected:
        MPI_File pFile;
        const size_t _header_size;
        const size_t _block_size;
        const std::string _filename;
    };


// methods implements.
    template<typename T>
    size_t IOWriter::write(T *b, size_t start, size_t size) {
        MPI_File_write(pFile, b + start, size * sizeof(T), MPI_BYTE, MPI_STATUS_IGNORE);
        return size;
    }

    template<typename T>
    size_t IOWriter::write(T *b, size_t size) {
        MPI_File_write(pFile, b, size * sizeof(T), MPI_BYTE, MPI_STATUS_IGNORE);
        return size;
    }
}

#endif //KIWI_SYS_DUMP_H
