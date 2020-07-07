

set(CMAKE_CXX_STANDARD 14)

project(cli)

set(LIB_DIRC ../botan_x86)

INCLUDE_DIRECTORIES(${LIB_DIRC}/build/include)
LINK_DIRECTORIES(${LIB_DIRC})

add_executable(cli cli.cpp)
TARGET_LINK_LIBRARIES(cli libbotan-2.a)
