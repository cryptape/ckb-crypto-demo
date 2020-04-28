
cmake_minimum_required(VERSION 3.5)
project(ed25519)

set(LIB_DIRC /code/botan_riscv)

INCLUDE_DIRECTORIES(${LIB_DIRC}/build/include)
LINK_DIRECTORIES(${LIB_DIRC})

add_executable(ed25519 main.cpp)
TARGET_LINK_LIBRARIES(ed25519 libbotan-2.a )
