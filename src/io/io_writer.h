//
// Created by genshen(genshenchu@gmail.com) on 2018-3-13.
//

#ifndef KIWI_IO_WRITER_H
#define KIWI_IO_WRITER_H

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
         * Initialize variable pFile.
         */
        IOWriter(MPI_File pFile);

        /**
        * create file view with configured file pointer, data type, header size, etc.
        * @return true for success, false for creating failed.
        */
        virtual bool make(size_t _skip_size, size_t _block_size, MPI_Datatype etype, mpi_process mpi_p);

        /**
         *
         * make using default values.
         */
        virtual bool make(MPI_Datatype etype, mpi_process mpi_p);

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
        MPI_Datatype _etype;
//        const size_t _header_size;
//        const size_t _block_size;
        const std::string _filename;
    };


// methods implements.
    // notice: ths params size should match the give element type: @var _etype.
    template<typename T>
    size_t IOWriter::write(T *b, size_t start, size_t size) {
        MPI_File_write_all(pFile, b + start, size, _etype, MPI_STATUS_IGNORE);
        return size;
    }

    template<typename T>
    size_t IOWriter::write(T *b, size_t size) {
        MPI_File_write_all(pFile, b, size, _etype, MPI_STATUS_IGNORE);
        return size;
    }
}

#endif //KIWI_IO_WRITER_H
