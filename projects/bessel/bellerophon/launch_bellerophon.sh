#!/bin/bash
set -x

echo "Launcing bellerophon"

bellerophon -objs fap.o -p ./ -r ../chimera/output/mutants/bessel.cpp/1/flap_float_report.csv -t FLAPAprx -P gaconfig.param 1e-7

