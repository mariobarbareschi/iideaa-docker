project (Sobel LANGUAGES CXX)
cmake_minimum_required(VERSION 3.10)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -O3 -std=c++11")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs.so)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs.a)

find_package( OpenCV REQUIRED )
set(OpenCV_STATIC ON)

# find_package(OpenMP REQUIRED)
# if (OPENMP_FOUND)
#     set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#     set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#     set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
# endif()

include_directories( ${OpenCV_INCLUDE_DIRS} include)

add_executable(get_area src/get_area.cc src/evoapproxlib.cc)
add_executable(get_power src/get_power.cc src/evoapproxlib.cc)
add_executable(get_psnr src/get_psnr.cc src/sobel.cc src/metrics.cc src/evoapproxlib.cc)
target_link_libraries(get_psnr ${OpenCV_LIBS})

add_custom_target(library_database
  COMMAND ${CMAKE_COMMAND} -E echo adding compile modules to the library_database.csv file
  COMMAND echo "\\\\\\\\list of all objects which must be loaded to run the software as JIT" >> ${PROJECT_BINARY_DIR}/library_database.csv
  COMMAND echo "\\\\\\\\dynamic and shared libraries" >> ${PROJECT_BINARY_DIR}/library_database.csv
  COMMAND if [ -d ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ]; then ls ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} | grep 'o\\|so' >> ${PROJECT_BINARY_DIR}/library_database.csv\; fi
  COMMAND echo "\\\\\\\\static libraries" >> ${PROJECT_BINARY_DIR}/library_database.csv
  COMMAND if [ -d ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ]; then ls ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} | grep 'a' >> ${PROJECT_BINARY_DIR}/library_database.csv\; fi
)
