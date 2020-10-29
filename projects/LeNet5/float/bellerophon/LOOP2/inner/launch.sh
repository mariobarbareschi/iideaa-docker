#!/bin/bash
set -x
bellerophon -v -libdb /root/projects/LeNet5/float/code/build/ -cd-dir $PWD -r /root/projects/LeNet5/float/clang-chimera/LOOP2/inner/output/mutants/network.cc/5/loop_report.csv -t LoopAprx -P gaconfig.param 0.8



