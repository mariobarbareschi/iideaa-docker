#!/bin/bash
set -x
bellerophon -v -objs fap.o -libdb /root/projects/LeNet5/float/code/build/ -cd-dir ./ -r /root/projects/LeNet5/float/clang-chimera/FLAP/output/mutants/network.cc/3/flap_float_report.csv -t FLAPAprx -P gaconfig.param 0.5 

