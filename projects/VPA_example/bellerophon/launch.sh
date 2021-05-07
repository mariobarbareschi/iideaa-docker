#!/bin/bash
set -x

bellerophon -v -objs vpa.o -libdb ../src/build/ -cd-dir ./ -r /root/projects/VPA_example/clang-chimera/output/mutants/taylor.cpp/7/vpa_float_report.csv -t VpaAprx -P gaconfig.param 10000
