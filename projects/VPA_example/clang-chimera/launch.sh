#!/bin/bash
set -x

#rm -rf output
clang-chimera -v -debug -fun-op conf.csv -generate-mutants  ../src/taylor/taylor.cpp -cd-dir ../src/build/ -o output -- -std=c++11  -I../code/include -I../code/include/segmentation
