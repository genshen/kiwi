//
// Created by genshen on 5/29/18.
//

#include "local_storage.h"

kiwi::LocalStorage::LocalStorage(const std::string &filename)
        : _local_header_size(DEFAULT_LOCAL_STORAGE_SIZE), IOWriter(filename) {}

kiwi::LocalStorage::LocalStorage(size_t global_header_size, size_t local_header_size, size_t block_size,
                                 const std::string &filename)
        : _local_header_size(local_header_size), IOWriter(filename, global_header_size, block_size) {

//    _writer->getMPIFile();
}

kiwi::LocalStorage::~LocalStorage() { // todo call ~IOWriter()
}

bool kiwi::LocalStorage::make() {
    if (!IOWriter::make()) {
        return false;
    }
    MPI_File_seek(pFile, _local_header_size, MPI_SEEK_SET); // todo type long and MPI_Offset
}

void kiwi::LocalStorage::writeHeader(kiwi::byte *data, size_t size) {
    MPI_Offset current_offset;
    MPI_File_get_position(pFile, &current_offset);
    size = size > _local_header_size ? _local_header_size : size; // cut off size.

    MPI_File_seek(pFile, 0, MPI_SEEK_SET);
    write(data, size);
    MPI_File_seek(pFile, current_offset, MPI_SEEK_SET);
}
