#!/bin/bash
set -x
bellerophon -v -libdb /root/projects/LeNet5/float/code/build/ -cd-dir $PWD -r /root/projects/LeNet5/float/clang-chimera/LOOP1/outer/output/mutants/network.cc/4/loop_report.csv -t LoopAprx -P gaconfig.param 0.9



