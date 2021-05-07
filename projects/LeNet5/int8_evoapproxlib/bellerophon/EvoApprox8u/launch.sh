#!/bin/bash
set -x
bellerophon -v -objs evoapproxlib.o -libdb /root/projects/LeNet5/int8_evoapproxlib/code/build/ -cd-dir ./ -r /root/projects/LeNet5/int8_evoapproxlib/clang-chimera/EvoApprox8u/output/mutants/network.cc/3/evoapprox8u.csv -t EvoAprx  -maxGrade 10 -P gaconfig.param 0.5 




