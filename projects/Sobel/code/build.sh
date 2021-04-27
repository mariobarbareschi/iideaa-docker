#!/bin/bash
rm -rf build-clang
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
mkdir build-clang
cd build-clang
cmake .. -DCMAKE_USER_MAKE_RULES_OVERRIDE=$(realpath ../ClangOverrides.txt) -D_CMAKE_TOOLCHAIN_PREFIX=llvm- -DCMAKE_BUILD_TYPE=Release -G Ninja
ninja -v -j `nproc`
ninja library_database
cd ..
