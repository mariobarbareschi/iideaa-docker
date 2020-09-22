#!/bin/bash
rm -rf build-local
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
mkdir build-local
cd build-local
cmake .. -DCMAKE_USER_MAKE_RULES_OVERRIDE=$(realpath ../ClangOverrides.txt) -D_CMAKE_TOOLCHAIN_PREFIX=llvm- -DCODE_COVERAGE=ON -DCMAKE_BUILD_TYPE="Debug"
make VERBOSE=1 -j `nproc`
cd ..
