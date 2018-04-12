//
// Created by genshen(genshenchu@gmail.com) on 2018-03-09.
//

#ifndef KIWI_DATA_PACK_H
#define KIWI_DATA_PACK_H

#include <mpi.h>
#include <string>
#include "data_def.h"

/**
 * a util for mpi data pack(including packing std::string),
 * if you know data size approximately before constructing DataPack class.
 *
 * usage:
 * dataPack *pack = new dataPack();
 * pack-> newPackBuffer(128); // initialize buffer,the buffer cap is 128.
 * pack->append(0x12); // pack int
 * pack->append("hello"); // pack string
 * pack->releasePackBuffer(); // release buffer.
 *
 */
namespace kiwi {
    class Bundle {
    public:

        // new bundle and new buffer with cap length
        Bundle(const unsigned int cap);

        // if need to pack data, do call newPackBuffer(cap) before packing.
        Bundle();

        ~Bundle(); // release buffer here (you can also release buffer by calling releasePackBuffer().

        // Initialize pack buffer, cap is the capacity of packBuffer.
        void newPackBuffer(const unsigned int cap);

        // clean pack buffer after we won't use the buffer any more.
        void releasePackBuffer();

        byte *getPackedData();

        // returns capacity of buffer.
        unsigned int getPackedDataCap();

        // pack T into packBuffer. notice: if T is the type like sts::string, it is not allowed to be packed (may cause segment fault).
        // make sure buffer is not null before calling this function.
        template<typename T>
        void put(MPI_Comm comm, const T &data);

        // append an array (1d array) into buffer.
        template<typename T>
        void put(MPI_Comm comm, int size, const T *data);

        // make sure buffer is not null before calling this methods.
        void put(MPI_Comm comm, const std::string &t); // todo safe put with cap.

        // recover data from buffer.
        template<typename T>
        void get(MPI_Comm comm, int &cursor, T &data);

        // recover an array (1d array) from buffer.
        template<typename T>
        void get(MPI_Comm comm, int &cursor, int size, T data[]);

        // recover string from buffer.
        void get(MPI_Comm comm, int &cursor, std::string &t);

    private:
        unsigned int cap; // capacity of buffer.
        int length; // length of buffer, its smaller than capacity of buffer. //todo int -> usigned int. // todo move length to above level.
        byte *buffer = nullptr;
    };
}

// methods implementation.
// Templated code implementation should never be in a .cpp file.
template<typename T>
void kiwi::Bundle::put(MPI_Comm comm, const T &data) {
    MPI_Pack(&data, sizeof(T), MPI_BYTE, buffer, cap, &length, comm);
}

template<typename T>
void kiwi::Bundle::put(MPI_Comm comm, int size, const T *data) {
    MPI_Pack(data, size * sizeof(T), MPI_BYTE, buffer, cap, &length, comm);
}

template<typename T>
void kiwi::Bundle::get(MPI_Comm comm, int &cursor, T &data) {
    MPI_Unpack(buffer, cap, &cursor, &data, sizeof(T), MPI_BYTE, comm);
}

template<typename T>
void kiwi::Bundle::get(MPI_Comm comm, int &cursor, int size, T *data) {
    MPI_Unpack(buffer, cap, &cursor, data, size * sizeof(T), MPI_BYTE, comm);
}

#endif //KIWI_DATA_PACK_H
