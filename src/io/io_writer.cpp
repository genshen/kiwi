//
// Created by genshen(genshenchu@gmail.com) on 2018-3-13.
//

#include <iostream>
#include "io_writer.h"

kiwi::IOWriter::IOWriter(const std::string &filename) :
        IOWriter(filename, DEFAULT_IO_HEADER_SIZE, DEFAULT_IO_BLOCK_SIZE) {
}

kiwi::IOWriter::IOWriter(const std::string &filename, size_t header_size, size_t block_size) :
        _filename(filename), _header_size(header_size), _block_size(block_size) {}

kiwi::IOWriter::~IOWriter() {
    if (pFile != nullptr) {
        MPI_File_close(&pFile);
        pFile = nullptr;
    }
}

bool kiwi::IOWriter::make() {
    int status = MPI_File_open(mpiUtils::global_comm, _filename.c_str(), // todo comm.
                               MPI_MODE_CREATE | MPI_MODE_WRONLY,
                               MPI_INFO_NULL, &pFile);
    if (status == -1) {
        return false;
    }

    MPI_Aint lb, extent;
    MPI_Datatype etype, contig, filetype;

    etype = MPI_BYTE;
    lb = 0; // DEFAULT_IO_BLOCK_SIZE * mpiUtils::ownRank;
    extent = _block_size * mpiUtils::all_ranks;

    MPI_Type_contiguous(_block_size, MPI_BYTE, &contig);
    MPI_Type_create_resized(contig, lb, extent, &filetype);
    MPI_Type_commit(&filetype);
    MPI_File_set_view(pFile, _header_size + _block_size * mpiUtils::own_rank,
                      etype, filetype, "native", MPI_INFO_NULL);
    return true;
}
