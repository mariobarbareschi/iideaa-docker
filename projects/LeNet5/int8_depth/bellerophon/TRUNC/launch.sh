#!/bin/bash
set -x
bellerophon -v -objs trunc.o -libdb /root/projects/LeNet5/int8_depth/code/build/ -cd-dir ./ -r /root/projects/LeNet5/int8_depth/clang-chimera/TRUNC/output/mutants/network.cc/6/trunc_adder_report.csv -t TruncAprx -maxGrade 7 -P gaconfig.param 1.0 



