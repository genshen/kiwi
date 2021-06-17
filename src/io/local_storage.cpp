//
// Created by genshen on 5/29/18.
//

#include "local_storage.h"

kiwi::LocalStorage::LocalStorage(MPI_File pFile)
    : LocalStorage(pFile, DEFAULT_IO_HEADER_SIZE, DEFAULT_LOCAL_STORAGE_SIZE, DEFAULT_IO_BLOCK_SIZE) {}

kiwi::LocalStorage::LocalStorage(MPI_File pFile, size_t global_header_size, size_t local_header_size, size_t block_size)
    : writer(pFile), _global_header_size(global_header_size), _local_header_size(local_header_size),
      _block_size(block_size) {}

bool kiwi::LocalStorage::make(MPI_Datatype type, mpi_process mpi_p) {
  return writer.make(_global_header_size + _local_header_size * mpi_p.all_ranks, _block_size, type, mpi_p);
}

void kiwi::LocalStorage::writeHeader(MPI_Datatype data_type, void *data, size_t size, kiwi::mpi_process mpi_p) {
  writer.make(_global_header_size, _local_header_size, data_type, mpi_p);
  writer.writeAll(data, size);
}

void kiwi::LocalStorage::writeHeader(kiwi::byte *data, size_t size, mpi_process mpi_p) {
  writer.make(_global_header_size, _local_header_size, MPI_BYTE, mpi_p);
  writer.writeAll(data, size);
}
