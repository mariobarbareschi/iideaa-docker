#!/bin/bash
set -x

rm -rf output
clang-chimera -v -debug -fun-op conf.csv -generate-mutants /root/projects/Sobel/code/src/sobel.cc -cd-dir /root/projects/Sobel/code/build-clang -o output -- -std=c++11 -I/root/projects/Sobel/code/include 

