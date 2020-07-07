
project(sm2)

set(LIB_DIRC ../botan_riscv)


INCLUDE_DIRECTORIES(${LIB_DIRC}/build/include)
LINK_DIRECTORIES(${LIB_DIRC})

add_executable(sm2 sm2.cpp)
TARGET_LINK_LIBRARIES(sm2 libverify.a)
