
project(rsa)

set(LIB_DIRC ../botan_riscv)

INCLUDE_DIRECTORIES(${LIB_DIRC}/build/include)
LINK_DIRECTORIES(${LIB_DIRC})

add_executable(rsa rsa.cpp)
TARGET_LINK_LIBRARIES(rsa libverify.a)
