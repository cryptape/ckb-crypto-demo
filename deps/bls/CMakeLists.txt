cmake_minimum_required (VERSION 3.0)
project(bls)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)




option(
	BLS_SWAP_G
	"swap G1 and G2"
	"OFF"
)

if(BLS_SWAP_G)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBLS_SWAP_G")
endif()



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMCL_USE_VINT -DMCL_VINT_FIXED_BUFFER")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMCL_DONT_USE_OPENSSL")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMCL_DONT_USE_XBYAK")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og -g")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBLS_ETH")
# ETH2.0




#add_library(bls_c256 STATIC src/bls_c256.cpp)
#add_library(bls_c384 STATIC src/bls_c384.cpp)
add_library(bls_c384_256 STATIC src/bls_c384_256.cpp)
#add_library(bls::c256 ALIAS bls_c256)
#add_library(bls::c384 ALIAS bls_c384)
add_library(bls::c384_256 ALIAS bls_c384_256)

#target_include_directories(bls_c256 PUBLIC ${PROJECT_SOURCE_DIR}/include)
#target_include_directories(bls_c384 PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(bls_c384_256 PUBLIC ${PROJECT_SOURCE_DIR}/include)

#target_link_libraries(bls_c256 mcl::mcl)
#target_link_libraries(bls_c384 mcl::mcl)
target_link_libraries(bls_c384_256 mcl::mcl)

file(GLOB BLS_HEADERS include/bls/bls.h include/bls/bls.hpp)

#nstall(TARGETS bls_c256 DESTINATION lib)
#install(TARGETS bls_c384 DESTINATION lib)
install(TARGETS bls_c384_256 DESTINATION lib)
install(FILES ${BLS_HEADERS} DESTINATION include/bls)



#add_executable(bls_c256_test test/bls_c256_test.cpp)
#target_link_libraries(bls_c256_test bls_c256 )
#add_executable(bls_c384_test test/bls_c384_test.cpp)
#target_link_libraries(bls_c384_test bls_c384 )
#add_executable(bls_test  test/bls_test.cpp)
add_executable(bls_c384_256_test test/bls_c384_256_test.cpp)
#target_link_libraries(bls_test bls_c384_256)
target_link_libraries(bls_c384_256_test bls_c384_256 )

