#!/bin/bash
set -x
bellerophon -v -libdb /root/projects/n2d2_cnn/float/code/build/ -cd-dir $PWD -r /root/projects/n2d2_cnn/float/clang-chimera/LOOP2/outer/output/mutants/network.cc/5/loop_report.csv -t LoopAprx -P gaconfig.param 0.9



