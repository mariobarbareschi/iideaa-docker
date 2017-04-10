#!/bin/bash
set -x

#bellerophon -libdb ../code/build/ -objs fap.o -p ./ -r ../chimera/output/mutants/segmentation.cpp/1/flap_float_report.csv -t FLAPAprx -P gaconfig.param 10000
bellerophon -objs fap.o -p ./ -r ../chimera/output/mutants/segmentation.cpp/1/flap_float_report.csv -t FLAPAprx -P gaconfig.param 10000
