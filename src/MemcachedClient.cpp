#include "MemcachedClient.h"
#include <stdexcept>

MemcachedClient::MemcachedClient() {
  memc = memcached_create(nullptr);
  if (!memc) {
    throw std::runtime_error("Failed to create memcached structure");
  }

  memcached_server_st *servers =
      memcached_server_list_append(nullptr, "localhost", 11211, nullptr);
  if (!servers) {
    memcached_free(memc);
    throw std::runtime_error("Failed to append server to memcached structure");
  }

  memcached_return_t rc = memcached_server_push(memc, servers);
  memcached_server_list_free(servers);

  if (rc != MEMCACHED_SUCCESS) {
    memcached_free(memc);
    throw std::runtime_error("Failed to add server to memcached pool");
  }
}

MemcachedClient::~MemcachedClient() {
  if (memc) {
    memcached_free(memc);
  }
}

bool MemcachedClient::set(const std::string &key, const std::string &value,
                          time_t expiration) {
  memcached_return_t rc =
      memcached_set(memc, key.c_str(), key.length(), value.c_str(),
                    value.length(), expiration, 0);
  if (rc != MEMCACHED_SUCCESS) {
    // Optional: Log the error or handle it as needed
    return false;
  }
  return true;
}

std::string MemcachedClient::get(const std::string &key) {
  size_t retrieved_length;
  uint32_t flags;
  memcached_return_t rc;

  char *retrieved_value = memcached_get(memc, key.c_str(), key.length(),
                                        &retrieved_length, &flags, &rc);

  std::string result;
  if (rc == MEMCACHED_SUCCESS && retrieved_value) {
    result.assign(retrieved_value, retrieved_length);
    free(retrieved_value);
  } else {
    // Optional: Log the error or handle it as needed
  }
  return result;
}
