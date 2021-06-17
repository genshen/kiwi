//
// Created by genshen(genshenchu@gmail.com) on 2018-3-13.
//

#include <cassert>
#include <iostream>

#include "io_writer.h"

kiwi::IOWriter::IOWriter(MPI_File pFile) : pFile(pFile) {}

bool kiwi::IOWriter::make(MPI_Datatype etype, mpi_process mpi_p) {
  return make(DEFAULT_IO_HEADER_SIZE, DEFAULT_IO_BLOCK_SIZE, etype, mpi_p);
}

bool kiwi::IOWriter::make(size_t _skip_size, size_t _block_size, MPI_Datatype etype, mpi_process mpi_p) {
  this->_etype = etype;

  // calculation size of element type
  int etype_size = 0; // todo
  MPI_Type_size(etype, &etype_size);
  assert(etype_size != 0);

  MPI_Aint lb, extent;
  MPI_Datatype contig, filetype;

  lb = 0; // DEFAULT_IO_BLOCK_SIZE * mpiUtils::ownRank;
  extent = etype_size * _block_size * mpi_p.all_ranks;

  MPI_Type_contiguous(_block_size, etype, &contig);
  // note unit of extent is bytes.
  MPI_Type_create_resized(contig, lb, extent, &filetype);
  MPI_Type_commit(&filetype);

  // note: the second argument disp is absolute offset in bytes from the beginning of the file.
  MPI_File_set_view(pFile, _skip_size + _block_size * etype_size * mpi_p.own_rank, etype, filetype, "native",
                    MPI_INFO_NULL);
  return true;
}
