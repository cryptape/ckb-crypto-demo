cmake_minimum_required(VERSION 3.5)
project(test)

set(CMAKE_CXX_STANDARD 14)


INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/include")

set(PROJECT_TEST_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/test/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_TEST_BINARY_DIR})

add_executable(test_sha256 sha256_test.cpp ../src/hash/sha256.cpp)