#!/bin/bash
set -x
bellerophon -v -objs fap.o -libdb /root/projects/n2d2_cnn/code/build/ -cd-dir ./ -r /root/projects/n2d2_cnn/clang-chimera/FLAP/output/mutants/n2d2.cc/3/flap_float_report.csv -t FLAPAprx -P gaconfig.param 10000 

