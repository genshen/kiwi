# kiwi

![](https://img.shields.io/badge/all%20commits%26tags-gpg%20signed-brightgreen)

A parallel framework and tool library. It includes the following components:  
- wiki app: provide interfaces for developing parallel applications and built-in MPI wrapper.
- I/O: high level parallel I/O API based on MPI-I/O.
- logs: [fmt](https://github.com/fmtlib/fmt)-based parallel log component. It is designed for parallel applications, which can output MPI rank id and provide configurable log destination (e.g. log to console or to file). 
- bundle: pack data to a bytes buffer and unpack data from the buffer. It supports the `config` component.
- config: provide a mechanism for: packing data to a bytes buffer and BCast to all processors; unpacking and recovering the origin data after BCast.
- event: a listener to receive and process MPI messages.

## Documentation
see directory `docs`.

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
