#pragma once

#include <libmemcached/memcached.h>
#include <memory>
#include <string>
#include <vector>
#include <utility>
#include <stdexcept>
#include <functional>

namespace memcachex {

class MemcachedError : public std::runtime_error {
public:
    explicit MemcachedError(const std::string& message, memcached_return_t code)
        : std::runtime_error(message), return_code_(code) {}

    memcached_return_t getReturnCode() const { return return_code_; }

private:
    memcached_return_t return_code_;
};

struct ServerConfig {
    std::string host = "localhost";
    uint16_t port = 11211;
    uint32_t weight = 1;
};

class MemcachedClient {
public:
    MemcachedClient();
    
    explicit MemcachedClient(const ServerConfig& config);
    
    explicit MemcachedClient(const std::vector<ServerConfig>& configs);
    
    ~MemcachedClient();

    bool set(const std::string& key, const std::string& value, time_t expiration = 0);
    std::string get(const std::string& key);
    bool remove(const std::string& key, time_t expiration = 0);
    
    bool add(const std::string& key, const std::string& value, time_t expiration = 0);
    bool replace(const std::string& key, const std::string& value, time_t expiration = 0);
    bool append(const std::string& key, const std::string& value);
    bool prepend(const std::string& key, const std::string& value);
    
    uint64_t increment(const std::string& key, uint32_t offset = 1);
    uint64_t decrement(const std::string& key, uint32_t offset = 1);
    
    bool setMulti(const std::vector<std::pair<std::string, std::string>>& keyValues, time_t expiration = 0);
    std::vector<std::pair<std::string, std::string>> getMulti(const std::vector<std::string>& keys);
    
    bool flush(time_t expiration = 0);
    memcached_return_t addServer(const ServerConfig& config);
    
    std::string getLastErrorMessage() const;
    memcached_return_t getLastReturnCode() const;
    uint64_t getVersion() const;

private:
    MemcachedClient(const MemcachedClient&) = delete;
    MemcachedClient& operator=(const MemcachedClient&) = delete;
    
    void throwIfError(memcached_return_t rc, const std::string& operation) const;
    void initialize();
    
    memcached_st* memc;
    memcached_return_t last_error_ = MEMCACHED_SUCCESS;
};

} // namespace memcachex
