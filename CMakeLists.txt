cmake_minimum_required (VERSION 3.0)
project(ckb_crypto)


add_subdirectory(deps/mcl)
add_subdirectory(deps/bls)

include_directories(deps/mcl/include)
include_directories(deps/mcl/include)


#include_directories("/home/ubuntu/crypto/deps/mcl/include")
#link_directories("/home/ubuntu/crypto/deps/mcl/build/lib")

#include_directories("/home/ubuntu/crypto/deps/bls/include")
#link_directories("/home/ubuntu/crypto/deps/bls/build/lib")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMCL_USE_VINT -DMCL_VINT_FIXED_BUFFER")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMCL_DONT_USE_OPENSSL")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMCL_DONT_USE_XBYAK")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBLS_ETH")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG")


add_executable(blssig src/blssig.cpp)
add_executable(blsverify src/bls_verify.cpp)
add_executable(pairing src/pairing_c.cpp)

target_link_libraries(blssig PUBLIC bls_c384_256  mcl::mcl)
target_link_libraries(blsverify PUBLIC bls_c384_256  mcl::mcl)
target_link_libraries(pairing   mcl::mcl mcl::bn384_256)