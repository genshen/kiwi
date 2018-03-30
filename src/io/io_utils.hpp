//
// Created by genshen on 2018-02-30.
//

#ifndef KIWI_IO_UTILS_HPP
#define KIWI_IO_UTILS_HPP

#include <fstream>
#include "../utils/data_def.h"

namespace kiwi {
    /**
     * seek and read bytes to variable b.
     * read data into array/vector.
     * @tparam T type of target.
     * @param fs file stream.
     * @param b target receiving read result.
     * @param offset io offset for seek (locate to target position).
     * @param _dir the same as _dir in std seekg(ff_type __off, ios_base::seekdir __dir)
     * @param _size size needing to read (how many T need to read).
     * @return _size in T have read.
     */
    template<typename T>
    long seekRead(std::fstream &fs, T *b, _type_io_offset offset,
                  std::ios_base::seekdir _dir, unsigned long _size) {
        fs.seekg(offset, _dir);
        fs.read((char *) b, sizeof(T) * _size);
        return _size;
    }


    /**
    * calculate relative offset by the offset to data position of this processor.
    * @param offset
    * @return
    */
    inline long relOffset(std::ifstream &fs, long base_offset, long offset) {
        return base_offset + offset - fs.tellg();
    }

}

#endif //KIWI_IO_UTILS_HPP
