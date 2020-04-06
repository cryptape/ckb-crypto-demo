cmake_minimum_required (VERSION 3.0)
project(try)

include_directories("/home/ubuntu/crypto/deps/mcl/include")
link_directories("/home/ubuntu/crypto/deps/mcl/build/lib")

include_directories("/home/ubuntu/crypto/deps/bls/include")
link_directories("/home/ubuntu/crypto/deps/bls/build/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMCL_USE_VINT -DMCL_VINT_FIXED_BUFFER")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMCL_DONT_USE_OPENSSL")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMCL_DONT_USE_XBYAK -Os")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBLS_ETH")


add_executable(pairing_c pairing.cpp) 

add_executable(blssig blssig.cpp)
add_executable(blsverify bls_verify.cpp)

target_link_libraries(pairing_c   libmcl.a)

target_link_libraries(blssig bls_c384_256 mcl)
target_link_libraries(blsverify bls_c384_256 mcl)