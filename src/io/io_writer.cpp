//
// Created by genshen(genshenchu@gmail.com) on 2018-3-13.
//

#include <iostream>
#include "io_writer.h"

kiwi::IOWriter::IOWriter(MPI_File pFile) : pFile(pFile) {
}

bool kiwi::IOWriter::make(MPI_Datatype etype) {
    return make(DEFAULT_IO_HEADER_SIZE, DEFAULT_IO_BLOCK_SIZE, etype);
}

bool kiwi::IOWriter::make(size_t _skip_size, size_t _block_size, MPI_Datatype etype) {
    this->_etype = etype;

    MPI_Aint lb, extent;
    MPI_Datatype contig, filetype;

    lb = 0; // DEFAULT_IO_BLOCK_SIZE * mpiUtils::ownRank;
    extent = _block_size * mpiUtils::all_ranks;

    MPI_Type_contiguous(_block_size, etype, &contig);
    MPI_Type_create_resized(contig, lb, extent, &filetype);
    MPI_Type_commit(&filetype);
    MPI_File_set_view(pFile, _skip_size + _block_size * mpiUtils::own_rank,
                      etype, filetype, "native", MPI_INFO_NULL);
    return true;
}
