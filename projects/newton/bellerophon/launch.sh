

#!/bin/bash
set -x

bellerophon -v -libdb ../src/build/ -cd-dir ./ -r ../clang-chimera/output/mutants/newton.cpp/2/loop_report.csv -t LoopAprx  -P gaconfig.param  0.5 
