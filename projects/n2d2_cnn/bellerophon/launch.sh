#!/bin/bash
set -x

bellerophon -v -objs vpa_n.o -libdb ../code/build/ -cd-dir ./ -r /root/projects/n2d2_cnn/clang-chimera/output/mutants/n2d2.cc/6/vpa_n_float_report.csv -t VpanAprx -P gaconfig.param 10000

