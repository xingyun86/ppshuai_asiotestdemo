# CMakeList.txt : CMake project for asiotestdemo, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(project_name asiotestdemo)
project(${project_name})

SET(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/vendor/libressl-3.1.1/include
	${CMAKE_SOURCE_DIR}/vendor/asio-1.18.0/include
)
link_directories(
	${CMAKE_BINARY_DIR}/vendor/libressl-3.1.1/ssl 
	${CMAKE_BINARY_DIR}/vendor/libressl-3.1.1/tls 
	${CMAKE_BINARY_DIR}/vendor/libressl-3.1.1/crypto
)
# Add source to this project's executable.
FILE(GLOB SRCS "*.cpp" "*.c")
FILE(GLOB ASIO_SRCS "${CMAKE_SOURCE_DIR}/vendor/asio-1.18.0/src/*.cpp")
add_executable (asiotestdemo ${SRCS} ${ASIO_SRCS})
IF(MSVC)
target_compile_options(asiotestdemo 
PRIVATE "/std:c++latest"
PRIVATE "/await"
)
target_compile_definitions(asiotestdemo
PRIVATE "_WIN32_WINNT=0x0601"
PRIVATE "ASIO_STANDALONE"
PRIVATE "ASIO_SEPARATE_COMPILATION"
)
ELSE(MSVC)
set(CMAKE_CXX_STANDARD 20)
#target_compile_options(asiotestdemo 
#PRIVATE "/std:c++latest"
#PRIVATE "/await"
#)
target_compile_definitions(asiotestdemo
PRIVATE "_WIN32_WINNT=0x0601"
PRIVATE "ASIO_STANDALONE"
PRIVATE "ASIO_SEPARATE_COMPILATION"
)
ENDIF(MSVC)
target_link_libraries(asiotestdemo	
        PRIVATE re_tls_static
        PRIVATE re_ssl_static
        PRIVATE re_crypto_static
)
# TODO: Add tests and install targets if needed.
