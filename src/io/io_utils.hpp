//
// Created by genshen on 2018-02-30.
//

#ifndef KIWI_IO_UTILS_HPP
#define KIWI_IO_UTILS_HPP

#include <fstream>

#include "../utils/data_def.h"

namespace kiwi {
  /**
   * seek and read bytes to pointer b with type T.
   * read data into array/vector.
   * @tparam T type of target.
   * @param fs file input stream.
   * @param data where read result is stored.
   * @param offset io offset for seek (locate to target position).
   * @param _dir the same as _dir in std seekg(ff_type __off, ios_base::seekdir __dir)
   * @param _size size to be read (how many T need to be read).
   * @return _size in T have read.
   */
  template <typename T>
  long seekRead(std::fstream &fs, T *data, _type_io_offset offset, std::ios_base::seekdir _dir,
                const unsigned long _size) {
    fs.seekg(offset, _dir);
    fs.read((char *)data, sizeof(T) * _size);
    return _size;
  }

  /**
   * seed and write data to fstream.
   * @tparam T type of b.
   * @param fs file output stream
   * @param data data need writing to stream
   * @param offset io offset for seek
   * @param _dir the same as _dir in std seekg(ff_type __off, ios_base::seekdir __dir)
   * @param _size size in T to be write.
   * @return size in T have wrote.
   */
  template <typename T>
  long seekWrite(std::fstream &fs, T *data, _type_io_offset offset, std::ios_base::seekdir _dir,
                 const unsigned long _size) {
    fs.seekg(offset, _dir);
    fs.write((char *)data, sizeof(T) * _size);
    return _size;
  }

  /**
   * calculate relative offset by the offset to data position of this processor.
   * @param offset
   * @return
   */
  inline long relOffset(std::ifstream &fs, long base_offset, long offset) { return base_offset + offset - fs.tellg(); }

} // namespace kiwi

#endif // KIWI_IO_UTILS_HPP
