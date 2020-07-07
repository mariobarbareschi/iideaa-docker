project (N2D2_export_C LANGUAGES CXX)
cmake_minimum_required (VERSION 3.10)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set (CMAKE_C_COMPILER	"/usr/bin/clang")
set (CMAKE_CXX_COMPILER "/usr/bin/clang++")
set (CMAKE_AR      		"/usr/bin/llvm-ar")
set (CMAKE_LINKER  		"/usr/bin/llvm-ld")
set (CMAKE_NM      		"/usr/bin/llvm-nm")
set (CMAKE_OBJDUMP 		"/usr/bin/llvm-objdump")
set (CMAKE_RANLIB  		"/usr/bin/llvm-ranlib")
set (CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -fsigned-char -march=native -fPIC")

set (CMAKE_CXX_STANDARD 11)
set (CXX_STANDARD_REQUIRED ON)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

if (CMAKE_BUILD_TYPE STREQUAL "DEBUG")
	message(STATUS "Debug configuration")
	enable_testing()
	set (CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -O0 -ggdb3 -Wall -Wextra -Wconversion")
	include(cmake/CodeCoverage.cmake)
	APPEND_COVERAGE_COMPILER_FLAGS()
elseif (CMAKE_BUILD_TYPE STREQUAL "RELEASE")
	message(STATUS "Release configuration")
	set (CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -O3")
elseif (NOT CMAKE_BUILD_TYPE)
	MESSAGE(FATAL_ERROR "No build type selected. Please select DEBUG or RELEASE. Aborting...")
endif()



#We are going to collect all the target modules in libs folders
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs.o)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs.o)

#Then we list all of them into a the library_database file; this target must be set as dependency of the ${CMAKE_PROJECT_NAME}
add_custom_target(library_database
  COMMAND ${CMAKE_COMMAND} -E echo adding compile modules to the library_database.csv file
  COMMAND echo "\\\\\\\\list of all objects which must be loaded to run the software as JIT" >> ${PROJECT_BINARY_DIR}/library_database.csv
  COMMAND echo "\\\\\\\\dynamic and shared libraries" >> ${PROJECT_BINARY_DIR}/library_database.csv
  COMMAND if [ -d ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ]; then ls ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} | grep 'o\\|so' >> ${PROJECT_BINARY_DIR}/library_database.csv\; fi
  COMMAND echo "\\\\\\\\static libraries" >> ${PROJECT_BINARY_DIR}/library_database.csv
  COMMAND if [ -d ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ]; then ls ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} | grep 'a' >> ${PROJECT_BINARY_DIR}/library_database.csv\; fi
)


add_library(n2d2cnn SHARED src/n2d2.cc src/network.cc)
target_include_directories(n2d2cnn PRIVATE include)

add_executable(n2d2_test n2d2_test.cc)
target_include_directories(n2d2_test PRIVATE include)
target_link_libraries(n2d2_test m n2d2cnn)

add_dependencies(library_database n2d2cnn)

if (CMAKE_BUILD_TYPE STREQUAL "DEBUG")
	add_test(NAME n2d2_test COMMAND n2d2_test /root/projects/n2d2_cnn/code/stimuli)
	SETUP_TARGET_FOR_COVERAGE_LCOV(NAME coverage EXECUTABLE ctest --output-on-failure -C ${ROOT_DIR}/CTestTestfile.cmake DEPENDENCIES n2d2_test)
endif()
