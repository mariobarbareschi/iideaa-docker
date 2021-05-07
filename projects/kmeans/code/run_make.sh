#!/bin/bash
if [ -d ./build ]; then
  rm -R -f ./build;
fi
mkdir build
cd build
cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang ..
make
cp compile_commands.json ../../chimera/
#cp compile_commands.json ../../bellerophon/
