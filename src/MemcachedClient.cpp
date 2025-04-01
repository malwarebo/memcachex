#include "MemcachedClient.h"

namespace memcachex {

MemcachedClient::MemcachedClient() {
    initialize();
}

MemcachedClient::MemcachedClient(const ServerConfig& config) {
    initialize();
    addServer(config);
}

MemcachedClient::MemcachedClient(const std::vector<ServerConfig>& configs) {
    initialize();
    for (const auto& config : configs) {
        addServer(config);
    }
}

MemcachedClient::~MemcachedClient() {
    if (memc) {
        memcached_free(memc);
        memc = nullptr;
    }
}

void MemcachedClient::initialize() {
    memc = memcached_create(nullptr);
    if (!memc) {
        throw std::runtime_error("Failed to create memcached instance");
    }
}

bool MemcachedClient::set(const std::string& key, const std::string& value, time_t expiration) {
    auto rc = memcached_set(memc, key.c_str(), key.length(), value.c_str(), value.length(), expiration, 0);
    last_error_ = rc;
    return rc == MEMCACHED_SUCCESS;
}

std::string MemcachedClient::get(const std::string& key) {
    size_t value_length;
    uint32_t flags;
    memcached_return_t rc;
    
    char* result = memcached_get(memc, key.c_str(), key.length(), &value_length, &flags, &rc);
    last_error_ = rc;
    
    if (rc != MEMCACHED_SUCCESS || !result) {
        return "";
    }
    
    std::string value(result, value_length);
    free(result);
    return value;
}

bool MemcachedClient::remove(const std::string& key, time_t expiration) {
    auto rc = memcached_delete(memc, key.c_str(), key.length(), expiration);
    last_error_ = rc;
    return rc == MEMCACHED_SUCCESS;
}

// Implement other methods here...

memcached_return_t MemcachedClient::addServer(const ServerConfig& config) {
    auto rc = memcached_server_add(memc, config.host.c_str(), config.port);
    last_error_ = rc;
    return rc;
}

std::string MemcachedClient::getLastErrorMessage() const {
    return memcached_strerror(memc, last_error_);
}

memcached_return_t MemcachedClient::getLastReturnCode() const {
    return last_error_;
}

void MemcachedClient::throwIfError(memcached_return_t rc, const std::string& operation) const {
    if (rc != MEMCACHED_SUCCESS) {
        throw MemcachedError(operation + " failed: " + memcached_strerror(memc, rc), rc);
    }
}

} // namespace memcachex
