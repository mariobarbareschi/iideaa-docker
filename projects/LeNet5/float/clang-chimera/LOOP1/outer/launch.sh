#!/bin/bash
set -x

rm -rf output
clang-chimera -v -debug -fun-op conf.csv -generate-mutants /root/projects/LeNet5/float/code/src/n2d2/network.cc -cd-dir /root/projects/LeNet5/float/code/build -o output -- -std=c++11  -I/root/projects/LeNet5/float/code/include -I/root/projects/LeNet5/float/code/include/iideaa -I/root/projects/LeNet5/float/code/include/n2d2



