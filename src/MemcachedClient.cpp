#include "MemcachedClient.h"

MemcachedClient::MemcachedClient() {
    memc = memcached_create(nullptr);
    memcached_server_list_st servers = memcached_server_list_append(nullptr, "localhost", 11211, nullptr);
    memcached_server_push(memc, servers);
    memcached_server_list_free(servers);
}

MemcachedClient::~MemcachedClient() {
    memcached_free(memc);
}

bool MemcachedClient::set(const std::string &key, const std::string &value, time_t expiration) {
    memcached_return_t rc = memcached_set(memc, key.c_str(), key.length(), value.c_str(), value.length(), expiration, 0);
    return rc == MEMCACHED_SUCCESS;
}

std::string MemcachedClient::get(const std::string &key) {
    char *retrieved_value;
    size_t retrieved_length;
    uint32_t flags;

    retrieved_value = memcached_get(memc, key.c_str(), key.length(), &retrieved_length, &flags, nullptr);

    std::string result;
    if (retrieved_value) {
        result = std::string(retrieved_value, retrieved_length);
        free(retrieved_value);
    }
    return result;
}
