#!/bin/bash
set -x
bellerophon -v -objs trunc.o -libdb /root/projects/LeNet5/int8_mul/code/build/ -cd-dir ./ -r /root/projects/LeNet5/int8_single/clang-chimera/TRUNC/cl3/output/mutants/network.cc/6/trunc_adder_report.csv -t TruncAprx -maxGrade 7 -P gaconfig.param 1.0 



