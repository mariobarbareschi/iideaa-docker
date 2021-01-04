#!/bin/bash
set -x

rm -rf output
clang-chimera -v -debug -fun-op conf.csv -generate-mutants /root/projects/LeNet5/int8_depth/code/src/n2d2/network.cc -cd-dir /root/projects/LeNet5/int8_depth/code/build -o output -- -std=c++11 -I/root/projects/LeNet5/int8_depth/code/include -I/root/projects/LeNet5/int8_depth/code/include/iideaa -I/root/projects/LeNet5/int8_depth/code/include/n2d2

