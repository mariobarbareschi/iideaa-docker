#!/bin/bash
rm -rf build
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
rm -rf build
mkdir build
cd build
cmake .. -DCMAKE_USER_MAKE_RULES_OVERRIDE=/root/projects/n2d2_cnn/code/ClangOverrides.txt -D_CMAKE_TOOLCHAIN_PREFIX=llvm- -DCODE_COVERAGE=ON $1
make VERBOSE=1 -j `nproc`
cd ..
