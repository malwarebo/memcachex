#include "MemcachedClient.h"
#include <iostream>

int main() {
    MemcachedClient memcached;

    if (memcached.set("my_key", "my_value")) {
        std::cout << "Value stored successfully!" << std::endl;
    } else {
        std::cout << "Failed to store value." << std::endl;
    }

    std::string retrievedValue = memcached.get("my_key");
    if (!retrievedValue.empty()) {
        std::cout << "Retrieved value: " << retrievedValue << std::endl;
    } else {
        std::cout << "Key not found." << std::endl;
    }

    return 0;
}
