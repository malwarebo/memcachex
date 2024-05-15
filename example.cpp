/**
 * Example usage of MemcachedClient class.
 * Author: Irfan Hamid
 */

#include "MemcachedClient.h"
#include <iostream>
#include <stdexcept>

int main() {
  try {
    MemcachedClient memcached;

    // Attempt to store a value
    const std::string key = "my_key";
    const std::string value = "my_value";

    if (memcached.set(key, value)) {
      std::cout << "Value stored successfully for key: " << key << std::endl;
    } else {
      std::cerr << "Failed to store value for key: " << key << std::endl;
      return 1; // Exit with error code
    }

    // Attempt to retrieve the stored value
    std::string retrievedValue = memcached.get(key);
    if (!retrievedValue.empty()) {
      std::cout << "Retrieved value for key '" << key << "': " << retrievedValue
                << std::endl;
    } else {
      std::cerr << "Failed to retrieve value for key: " << key << std::endl;
      return 1; // Exit with error code
    }
  } catch (const std::exception &ex) {
    std::cerr << "An error occurred: " << ex.what() << std::endl;
    return 1; // Exit with error code
  } catch (...) {
    std::cerr << "An unknown error occurred." << std::endl;
    return 1; // Exit with error code
  }

  return 0; // Exit successfully
}
