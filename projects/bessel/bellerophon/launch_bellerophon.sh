#!/bin/bash
set -x

echo "Launcing bellerophon"

bellerophon -v -objs fap.o -cd-dir ./ -r ../chimera/output/mutants/bessel.cpp/1/flap_float_report.csv -t FLAPAprx -P gaconfig.param 1e-7

