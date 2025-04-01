# memcachex

A C++ wrapper library for memcached using the libmemcached library.

## Overview

memcachex provides a simple, modern C++ interface to interact with memcached servers. It uses libmemcached under the hood and offers a cleanerAPI for common memcached operations.

## Requirements

- C++11 compatible compiler
- CMake 3.29.3 or higher
- libmemcached 1.0.18 or higher
- macOS (tested on arm64 architecture) or Linux

## Building

### macOS (with Homebrew)

1. Install the dependencies:

```bash
brew install cmake libmemcached
```

2. Create a build directory, configure the project, and compile:

```bash
mkdir -p build && cd build
cmake ..
make
```

## Example Usage

```cpp
#include "MemcachedClient.h"
#include <iostream>

int main() {
   // Initialize client with default server (localhost:11211)
   memcachex::MemcachedClient client;
   
   // Or with specific server config
   memcachex::ServerConfig config;
   config.host = "localhost";
   config.port = 11211;
   memcachex::MemcachedClient client2(config);
   
   // Set a value
   if (client.set("my_key", "my_value")) {
      std::cout << "Successfully set key" << std::endl;
   }
   
   // Get a value
   std::string value = client.get("my_key");
   if (!value.empty()) {
      std::cout << "Retrieved value: " << value << std::endl;
   }
   
   // Delete a key
   if (client.remove("my_key")) {
      std::cout << "Successfully deleted key" << std::endl;
   }
   
   return 0;
}
```

## Constructor Options

The `MemcachedClient` class provides the following constructors:

```cpp
// Default constructor - no servers configured
MemcachedClient();

// Constructor with a single server config
MemcachedClient(const ServerConfig& config);

// Constructor with multiple server configs
MemcachedClient(const std::vector<ServerConfig>& configs);
```

The `ServerConfig` struct allows you to specify server details:

```cpp
struct ServerConfig {
    std::string host = "localhost";
    uint16_t port = 11211;
    uint32_t weight = 1;
};
```

## Methods

### Basic Operations

- `bool set(const std::string& key, const std::string& value, time_t expiration = 0)`: Store a value with the given key
- `std::string get(const std::string& key)`: Retrieve a value for the given key
- `bool remove(const std::string& key, time_t expiration = 0)`: Delete a key-value pair

### Additional Operations

- `bool add(const std::string& key, const std::string& value, time_t expiration = 0)`: Add a new key-value only if it doesn't exist
- `bool replace(const std::string& key, const std::string& value, time_t expiration = 0)`: Replace existing key-value
- `bool append(const std::string& key, const std::string& value)`: Append to an existing value
- `bool prepend(const std::string& key, const std::string& value)`: Prepend to an existing value
- `uint64_t increment(const std::string& key, uint32_t offset = 1)`: Increment numeric value

### Error Handling

- `std::string getLastErrorMessage() const`: Get the last error message
- `memcached_return_t getLastReturnCode() const`: Get the last return code
- `void throwIfError(memcached_return_t rc, const std::string& operation) const`: Throw a MemcachedError exception if operation failed

## Exception Handling

The library provides a `MemcachedError` exception class that can be caught to handle errors:

```cpp
try {
    client.throwIfError(rc, "operation");
} catch (const memcachex::MemcachedError& e) {
    std::cerr << e.what() << std::endl;
    auto code = e.getReturnCode(); // Get the return code
}
```
