# kiwi
A framework for parallel

## install kiwi
1. install dependency
```bash
$ cd kiwi
$ pkg fetch
$ pkg install # install fmt lib, google test lib(for linking test) and some header files.
```

2. build
mpi lib is required for building kiwi lib.
```bash
$ cmake -B./build/ -H./
$ cmake --build ./build -j 4
$ make install # only kiwi lib is installed, fmt lib and mpi lib should be linked in your program.
```
