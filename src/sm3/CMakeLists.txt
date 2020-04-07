cmake_minimum_required(VERSION 3.10)
project(SM3)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_LINKER_FLAGS -fstack-protector  )

set(LIB_DIRC ../../deps)

set( CMAKE_VERBOSE_MAKEFILE on )
INCLUDE_DIRECTORIES(${LIB_DIRC}/botan)
LINK_DIRECTORIES(${LIB_DIRC})

add_executable(sm3 main.cpp)
TARGET_LINK_LIBRARIES(sm3 libbotan-2.a )
