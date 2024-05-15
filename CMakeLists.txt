cmake_minimum_required(VERSION 3.10)

project(memcachex)

set(CMAKE_CXX_STANDARD 11)

add_executable(memcachex example.cpp src/MemcachedClient.cpp)

# Find and link libmemcached using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBMEMCACHED REQUIRED libmemcached)
include_directories(${LIBMEMCACHED_INCLUDE_DIRS})
link_directories(${LIBMEMCACHED_LIBRARY_DIRS})
target_link_libraries(memcachex ${LIBMEMCACHED_LIBRARIES})
