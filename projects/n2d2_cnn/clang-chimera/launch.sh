#!/bin/bash
set -x

#rm -rf output
clang-chimera -v -debug -fun-op conf.csv -generate-mutants ../code/src/n2d2.cc -cd-dir ../code/build/ -o output -- -std=c++11  -I../code/include 

