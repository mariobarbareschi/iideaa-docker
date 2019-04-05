#!/bin/bash
set -x

#rm -rf output
clang-chimera -v -fun-op conf.csv -generate-mutants  ../code/src/segmentation/segmentation.cpp -o output -- -std=c++11  -I../code/include -I../code/include/segmentation
cp output/mutants/segmentation.cpp/1/flap_float_report.csv ./
cp output/mutants/segmentation.cpp/1/segmentation.cpp ./
chmod 775 ./flap_float_report.csv
chmod 775 ./segmentation.cpp
