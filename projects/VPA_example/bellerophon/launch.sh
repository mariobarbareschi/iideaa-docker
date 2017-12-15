#!/bin/bash
set -x

bellerophon -v -objs vpa.o -libdb ../src/build/ -cd-dir ./ -r ../clang-chimera/output/mutants/taylor.cpp/5/vpa_float_report.csv -t VpaAprx -P gaconfig.param 10000
