cmake_minimum_required(VERSION 3.10)

project(memcachex)

set(CMAKE_CXX_STANDARD 11)

add_executable(memcachex example.cpp src/MemcachedClient.cpp)

find_package(libmemcached REQUIRED)
target_link_libraries(memcachex libmemcached::libmemcached)
