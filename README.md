# Memcachex - Memcached Client for C++

Memcachex is a simple C++ project that demonstrates how to interact with a memcached server using the libmemcached library. It encapsulates memcached client functionality into a class and provides basic error handling.

## Getting Started

### Prerequisites

Before using Memcachex, you need to have the libmemcached library installed on your system. Make sure you have the following prerequisites:

- CMake (Version 3.10 or higher)
- C++ compiler (supporting C++11 or above)

### Installing libmemcached

Please follow the official libmemcached documentation to install the library on your system: [libmemcached Installation Guide](https://libmemcached.org)

### Building Memcachex

1. Setup

   ```bash
   git clone https://github.com/malwarebo/memcachex.git
   cd memcachex
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

2. Usage
After building the project, you can run the memcachex executable:

```bash
./memcachex

```
