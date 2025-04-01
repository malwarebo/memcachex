cmake_minimum_required(VERSION 3.10)
project(memcachex VERSION 0.1.0 LANGUAGES CXX)

# Print helpful message about build directory
message(STATUS "Configure with: mkdir -p build && cd build && cmake ..")
message(STATUS "Then build with: cmake --build .")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find libmemcached
find_path(LIBMEMCACHED_INCLUDE_DIR libmemcached/memcached.h)
find_library(LIBMEMCACHED_LIBRARY memcached)

# Check if libmemcached was found
if(NOT LIBMEMCACHED_INCLUDE_DIR OR NOT LIBMEMCACHED_LIBRARY)
    message(FATAL_ERROR "libmemcached not found. Please install libmemcached development files.")
endif()

# Library target
add_library(memcachex
    src/MemcachedClient.cpp
)

target_include_directories(memcachex 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PRIVATE
        ${LIBMEMCACHED_INCLUDE_DIR}
)

target_link_libraries(memcachex 
    PRIVATE
        ${LIBMEMCACHED_LIBRARY}
)

# Examples
add_subdirectory(examples)

# Installation
install(TARGETS memcachex
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES src/MemcachedClient.h
    DESTINATION include/memcachex
)
