#!/bin/bash
set -x

#rm -rf output
clang-chimera -v -fun-op conf.csv -generate-mutants  ../code/src/segmentation/segmentation.cpp -o output -- -std=c++11  -I../code/include -I../code/include/segmentation
