cmake_minimum_required(VERSION 3.5)
project(sm2)

set(LIB_DIRC ../)

INCLUDE_DIRECTORIES(${LIB_DIRC}/build/include)
LINK_DIRECTORIES(${LIB_DIRC})

add_executable(sm2 sm2.cpp)
TARGET_LINK_LIBRARIES(sm2 libbotan-2.a )
