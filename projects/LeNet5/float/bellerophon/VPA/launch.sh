#!/bin/bash
set -x

bellerophon -v -objs vpa_n.o -libdb /root/projects/LeNet5/float/code/build/ -cd-dir ./ -r /root/projects/LeNet5/float/clang-chimera/VPA/output/mutants/n2d2.cc/6/vpa_n_float_report.csv -t VpanAprx -P gaconfig.param 10000

