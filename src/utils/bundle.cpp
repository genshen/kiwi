//
// Created by genshen(genshenchu@gmail.com) on 2018-03-09.
//

#include <mpi.h>
#include "bundle.h"

kiwi::Bundle::Bundle() {
}

kiwi::Bundle::Bundle(const unsigned int cap){
    newPackBuffer(cap);
}

kiwi::Bundle::~Bundle() {
    releasePackBuffer(); // make sure memory cleaned.
}

void kiwi::Bundle::newPackBuffer(const unsigned int cap) {
    this->cap = cap;
    if (buffer == nullptr && cap != 0) {
        buffer = new byte[cap];
        length = 0;
    }
}

void kiwi::Bundle::releasePackBuffer() {
    if (buffer != nullptr) {
        delete buffer;
        buffer = nullptr;
        length = 0;
    }
}

// pack string.
void kiwi::Bundle::put(MPI_Comm comm, const std::string &str) {
    long strlen = str.length(); // long type and int param in MPI api may not match.
    MPI_Pack(&strlen, 1, MPI_LONG, buffer, cap, &length, comm); // pack string length.
    if (strlen > 0) { // only pack data when there is data in str.
        MPI_Pack(str.c_str(), strlen, MPI_BYTE, buffer, cap, &length, comm); // with null-terminated char.
    }
}

// recover string.
void kiwi::Bundle::get(MPI_Comm comm, int &cursor, std::string &t) {
    long strlen;
    MPI_Unpack(buffer, cap, &cursor, &strlen, 1, MPI_LONG, comm); //unpack string length first.
    if (strlen > 0) {
        char *b = new char[strlen]; // todo '\0'
        MPI_Unpack(buffer, cap, &cursor, b, strlen, MPI_BYTE, comm);
//        b[strlen] = '\0';
        t = std::string(b);
        delete[]b;
    }
}

kiwi::byte *kiwi::Bundle::getPackedData() {
    return buffer;
}

unsigned int kiwi::Bundle::getPackedDataCap() {
    return cap;
}
