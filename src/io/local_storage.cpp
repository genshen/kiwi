//
// Created by genshen on 5/29/18.
//

#include "local_storage.h"

kiwi::LocalStorage::LocalStorage(MPI_File pFile) :
        LocalStorage(pFile, DEFAULT_IO_HEADER_SIZE, DEFAULT_LOCAL_STORAGE_SIZE, DEFAULT_IO_BLOCK_SIZE) {
}

kiwi::LocalStorage::LocalStorage(MPI_File pFile, size_t global_header_size,
                                 size_t local_header_size, size_t block_size)
        : _global_header_size(global_header_size), _local_header_size(local_header_size),
          _block_size(block_size), writer(pFile) {}

bool kiwi::LocalStorage::make(MPI_Datatype type) {
    if (!writer.make(_global_header_size + _local_header_size * kiwi::mpiUtils::all_ranks,
                     _block_size, type)) {
        return false;
    }
}

void kiwi::LocalStorage::writeHeader(kiwi::byte *data, size_t size) {
    writer.make(_global_header_size, _local_header_size, MPI_BYTE);
    writer.write(data, size);
}

