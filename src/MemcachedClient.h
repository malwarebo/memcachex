#pragma once

#include <libmemcached/memcached.h>
#include <memory>
#include <stdexcept>
#include <string>

class MemcachedClient {
public:
  MemcachedClient();
  ~MemcachedClient();

  // Sets a key-value pair in memcached with an optional expiration time.
  bool set(const std::string &key, const std::string &value,
           time_t expiration = 0);

  // Retrieves the value associated with the key from memcached.
  std::string get(const std::string &key);

private:
  // Disallow copy constructor and assignment operator
  MemcachedClient(const MemcachedClient &) = delete;
  MemcachedClient &operator=(const MemcachedClient &) = delete;

  // Memcached client handle
  memcached_st *memc;
};
