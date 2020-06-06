project (N2D2_export_C LANGUAGES CXX)
cmake_minimum_required (VERSION 3.10)

SET (CMAKE_C_COMPILER	"/usr/bin/clang")
SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")
SET (CMAKE_AR      		"/usr/bin/llvm-ar")
SET (CMAKE_LINKER  		"/usr/bin/llvm-ld")
SET (CMAKE_NM      		"/usr/bin/llvm-nm")
SET (CMAKE_OBJDUMP 		"/usr/bin/llvm-objdump")
SET (CMAKE_RANLIB  		"/usr/bin/llvm-ranlib")
set (CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -Wall -Wextra -Wno-unused-label -pedantic -Wconversion -fsigned-char -march=native ")

set (CMAKE_CXX_STANDARD 11)
set (CXX_STANDARD_REQUIRED ON)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

FIND_PACKAGE(OpenMP)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (NOT CMAKE_BUILD_TYPE)
    MESSAGE(STATUS "No build type selected, default to Release")
    SET(CMAKE_BUILD_TYPE "Release")
endif()

set_source_files_properties(
	n2d2_test.c 
	##	src/getline.c
	src/n2d2.c
	src/network.c  
	PROPERTIES LANGUAGE CXX)

add_executable(
	n2d2_test
	n2d2_test.c
	src/getline.c
	src/n2d2.c
	src/network.c)

target_include_directories(
	n2d2_test
	PRIVATE include
)

target_link_libraries(
	n2d2_test
	PRIVATE m
)
