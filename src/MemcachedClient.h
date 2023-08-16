#pragma once

#include <libmemcached/memcached.h>
#include <string>
#include <memory>

class MemcachedClient {
public:
    MemcachedClient();
    ~MemcachedClient();

    bool set(const std::string &key, const std::string &value, time_t expiration = 0);
    std::string get(const std::string &key);

private:
    memcached_st *memc;
};
