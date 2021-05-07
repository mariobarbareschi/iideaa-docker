#!/bin/bash
rm -rf build
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
mkdir build
cd build
cmake .. -DCMAKE_USER_MAKE_RULES_OVERRIDE=$(realpath ../ClangOverrides.txt) -D_CMAKE_TOOLCHAIN_PREFIX=llvm- -DCODE_COVERAGE=ON -DCMAKE_BUILD_TYPE=Release -G Ninja
ninja -v -j `nproc`
ninja library_database
cd ..
