#!/bin/bash
set -x

bellerophon -cd-dir . -objs vpa.o -r ../chimera/output/mutants/BlackScholes.cpp/4/vpa_float_report.csv -t VpaAprx -P gaconfig.param 100
