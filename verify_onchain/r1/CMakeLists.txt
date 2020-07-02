
project(r1)

set(LIB_DIRC ../botan_riscv)

INCLUDE_DIRECTORIES(${LIB_DIRC}/build/include)
LINK_DIRECTORIES(${LIB_DIRC})

add_executable(r1 r1.cpp)
TARGET_LINK_LIBRARIES(r1 libverify.a)
