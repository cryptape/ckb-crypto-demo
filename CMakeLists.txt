cmake_minimum_required(VERSION 3.5)
project(crytolib_demo)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/bin/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/include")

add_executable(sha256 examples/main.cpp src/hash/sha256.cpp)




add_subdirectory(test)

enable_testing()
add_test(test_sha256 ${CMAKE_SOURCE_DIR}/build/test/test_sha256)

