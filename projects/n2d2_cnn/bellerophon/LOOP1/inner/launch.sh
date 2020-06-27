#!/bin/bash
set -x
bellerophon -v -libdb /root/projects/n2d2_cnn/code/build/ -cd-dir $PWD -r /root/projects/n2d2_cnn/clang-chimera/LOOP1/inner/output/mutants/n2d2.cc/4/loop_report.csv -t LoopAprx -P gaconfig.param 0.5



