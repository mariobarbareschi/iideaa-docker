project (N2D2_export_C LANGUAGES CXX)
cmake_minimum_required (VERSION 3.10)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsigned-char -march=native -fPIC")
set (CMAKE_CXX_STANDARD 11)
set (CXX_STANDARD_REQUIRED ON)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs.o)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs.o)

add_custom_target(library_database
  COMMAND ${CMAKE_COMMAND} -E echo adding compile modules to the library_database.csv file
  COMMAND echo "\\\\\\\\list of all objects which must be loaded to run the software as JIT" >> ${PROJECT_BINARY_DIR}/library_database.csv
  COMMAND echo "\\\\\\\\dynamic and shared libraries" >> ${PROJECT_BINARY_DIR}/library_database.csv
  COMMAND if [ -d ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ]; then ls ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} | grep 'o\\|so' >> ${PROJECT_BINARY_DIR}/library_database.csv\; fi
  COMMAND echo "\\\\\\\\static libraries" >> ${PROJECT_BINARY_DIR}/library_database.csv
  COMMAND if [ -d ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ]; then ls ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} | grep 'a' >> ${PROJECT_BINARY_DIR}/library_database.csv\; fi
)

add_library(
	n2d2cnn SHARED 
	src/n2d2/file_list.cc
	src/n2d2/env_read.cc
	src/n2d2/network.cc
)

target_include_directories(
	n2d2cnn 
	PRIVATE include
	PRIVATE include/iideaa
	PRIVATE include/n2d2
)

add_dependencies(library_database n2d2cnn)

add_executable(
	n2d2_test 
	src/n2d2_test.cc
)

target_include_directories(
	n2d2_test 
	PRIVATE include
	PRIVATE include/iideaa
	PRIVATE include/n2d2
)

target_link_libraries(n2d2_test m n2d2cnn)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	message(STATUS "Debug configuration")
  include(cmake-scripts/code-coverage.cmake)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -O0")
	add_code_coverage()

  add_executable(n2d2_coverage 
    src/n2d2/file_list.cc
    src/n2d2/env_read.cc
    src/n2d2/network.cc
    src/n2d2_coverage.cc
  )

  target_include_directories(
    n2d2_coverage 
    PRIVATE include
    PRIVATE include/iideaa
    PRIVATE include/n2d2
  )

  target_link_libraries(n2d2_coverage m)

	target_code_coverage(n2d2_coverage)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
	message(STATUS "Release configuration")
	set (CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -O3")
elseif (NOT CMAKE_BUILD_TYPE)
	MESSAGE(FATAL_ERROR "No build type selected. Please select Debug or Release. Aborting...")
endif()
