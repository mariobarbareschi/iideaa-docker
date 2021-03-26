cmake_minimum_required(VERSION 3.3)
project("iidea-axlib" VERSION 0.1 LANGUAGES CXX)

SET (CMAKE_C_FLAGS_INIT                                        "-Wall -std=c99")
SET (CMAKE_C_FLAGS_DEBUG_INIT                                              "-g")
SET (CMAKE_C_FLAGS_MINSIZEREL_INIT                               "-Os -DNDEBUG")
SET (CMAKE_C_FLAGS_RELEASE_INIT                                  "-O3 -DNDEBUG")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO_INIT                                 "-O2 -g")
SET (CMAKE_CXX_FLAGS_INIT                                               "-Wall")
SET (CMAKE_CXX_FLAGS_DEBUG_INIT                                            "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL_INIT                             "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE_INIT                                "-O3 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT                               "-O2 -g")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY                     ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY                    ${CMAKE_BINARY_DIR}/libs)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY                    ${CMAKE_BINARY_DIR}/libs)
set (CMAKE_CXX_FLAGS     "${CMAKE_CXX_FLAGS} -fsigned-char -march=native -fPIC")
set (CMAKE_CXX_STANDARD                                                      11)
set (CXX_STANDARD_REQUIRED                                                   ON)
set (CMAKE_EXPORT_COMPILE_COMMANDS                                           ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Wno-format-truncation")
else()
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_BUILD_TYPE Debug)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wextra -ggdb3 -O0 --coverage")
    endif()
endif()
set (INCLUDE_DIR                              ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(
    iideaa STATIC
    src/fap.cc
    src/trunc.cc
    src/vpa.cc
    src/vpa_n.cc
    src/evoapproxlib.cc)

target_include_directories(iideaa PRIVATE include)

add_subdirectory(test)
