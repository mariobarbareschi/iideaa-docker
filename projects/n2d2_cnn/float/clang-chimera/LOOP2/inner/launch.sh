#!/bin/bash
set -x

rm -rf output
clang-chimera -v -debug -fun-op conf.csv -generate-mutants /root/projects/n2d2_cnn/float/code/src/n2d2/network.cc -cd-dir /root/projects/n2d2_cnn/float/code/build -o output -- -std=c++11  -I/root/projects/n2d2_cnn/float/code/include -I/root/projects/n2d2_cnn/float/code/include/iideaa  -I/root/projects/n2d2_cnn/float/code/include/n2d2

