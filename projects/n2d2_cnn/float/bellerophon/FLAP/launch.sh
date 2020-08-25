#!/bin/bash
set -x
bellerophon -v -objs fap.o -libdb /root/projects/n2d2_cnn/float/code/build/ -cd-dir ./ -r /root/projects/n2d2_cnn/float/clang-chimera/FLAP/output/mutants/network.cc/3/flap_float_report.csv -t FLAPAprx -P gaconfig.param 0.5 

