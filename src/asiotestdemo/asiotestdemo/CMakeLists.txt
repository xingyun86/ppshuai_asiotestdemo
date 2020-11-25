# CMakeList.txt : CMake project for asiotestdemo, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(project_name asiotestdemo)
project(${project_name})

include(CheckIncludeFileCXX)
CHECK_INCLUDE_FILE_CXX(coroutine HAVE_COROUTINE_H)
if(HAVE_COROUTINE_H)
SET(EXPERIMENTAL_SUPPORT OFF)
else(HAVE_COROUTINE_H)
SET(EXPERIMENTAL_SUPPORT ON)
endif(HAVE_COROUTINE_H)

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
add_executable (${project_name} ${SRCS} ${ASIO_SRCS})
IF(MSVC)
	target_compile_options(${project_name} 
		PRIVATE "/std:c++latest"
		PRIVATE "/await"
	)
	list(APPEND EXT_DEF _WIN32_WINNT=0x0600)
	IF(EXPERIMENTAL_SUPPORT)
		message(STATUS "${project_name}:[EXPERIMENTAL_SUPPORT=ON]")
		list(APPEND EXT_DEF EXPERIMENTAL_SUPPORT=1)
	ELSE(EXPERIMENTAL_SUPPORT)
		message(STATUS "${project_name}:[EXPERIMENTAL_SUPPORT=OFF]")
	ENDIF(EXPERIMENTAL_SUPPORT)
ELSE(MSVC)
	IF(EXPERIMENTAL_SUPPORT)
		message(STATUS "${project_name}:[EXPERIMENTAL_SUPPORT=ON]")
		list(APPEND EXT_DEF EXPERIMENTAL_SUPPORT=1)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -stdlib=libc++")
		target_compile_options(${project_name} PRIVATE "-fcoroutines-ts")
	ELSE(EXPERIMENTAL_SUPPORT)
		message(STATUS "${project_name}:[EXPERIMENTAL_SUPPORT=OFF]")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
		target_compile_options(${project_name} PRIVATE "-fcoroutines")
	ENDIF(EXPERIMENTAL_SUPPORT)	
ENDIF(MSVC)

target_compile_definitions(${project_name}
	PRIVATE "ASIO_STANDALONE"
	PRIVATE "ASIO_SEPARATE_COMPILATION"
	PRIVATE ${EXT_DEF}
)

target_link_libraries(${project_name}	
    PRIVATE re_tls_static
    PRIVATE re_ssl_static
    PRIVATE re_crypto_static
)
# TODO: Add tests and install targets if needed.
