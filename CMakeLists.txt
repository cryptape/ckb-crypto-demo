
cmake_minimum_required(VERSION 3.5)
project(ed25519)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdata-sections -ffunction-sections -Os")
set(BUILD_DIRC build)

INCLUDE_DIRECTORIES(${BUILD_DIRC}/include/botan-2)
include_directories(src/include)

LINK_DIRECTORIES(${BUILD_DIRC}/lib)


#add_executable(ed25519 src/ed25519/verify.cpp)
add_executable(sm2 src/sm2/verify.cpp)
#TARGET_LINK_LIBRARIES(ed25519 libbotan-2.a )
TARGET_LINK_LIBRARIES(sm2 libbotan-2.a)
