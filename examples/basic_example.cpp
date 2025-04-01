#include <iostream>
#include "MemcachedClient.h"

int main() {
    try {
        // Create a client connected to localhost by default
        memcachex::MemcachedClient client;
        
        // Set a value
        if (client.set("greeting", "Hello, memcached!")) {
            std::cout << "Successfully set key 'greeting'" << std::endl;
        } else {
            std::cerr << "Failed to set key: " << client.getLastErrorMessage() << std::endl;
            return 1;
        }
        
        // Get the value back
        std::string value = client.get("greeting");
        if (!value.empty()) {
            std::cout << "Retrieved: " << value << std::endl;
        } else {
            std::cerr << "Failed to get key: " << client.getLastErrorMessage() << std::endl;
            return 1;
        }
        
        // Clean up
        if (client.remove("greeting")) {
            std::cout << "Successfully removed key 'greeting'" << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
