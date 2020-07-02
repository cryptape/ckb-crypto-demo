
project(ed25519)

set(LIB_DIRC ../botan_riscv)

INCLUDE_DIRECTORIES(${LIB_DIRC}/build/include)
LINK_DIRECTORIES(${LIB_DIRC})

add_executable(ed25519 ed25519.cpp)
TARGET_LINK_LIBRARIES(ed25519 libverify.a)
