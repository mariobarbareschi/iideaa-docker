#!/bin/bash
set -x

rm -rf output
clang-chimera -v -debug -fun-op conf.csv -generate-mutants /root/projects/LeNet5/int8_single/code/src/n2d2/network.cc -cd-dir /root/projects/LeNet5/int8_single/code/build -o output -- -std=c++11 -I/root/projects/LeNet5/int8_single/code/include -I/root/projects/LeNet5/int8_single/code/include/iideaa -I/root/projects/LeNet5/int8_single/code/include/n2d2

