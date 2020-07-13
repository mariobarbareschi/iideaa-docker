#!/bin/bash
usage() { 
        echo "Usage: $0 -x /xilinx_vivado_bin"; 
        exit 1; 
}

while getopts "x:" o; do
    case "${o}" in
        x)
            xilinx_vivado=${OPTARG}
            ;;
        *)
            usage
            ;;
    esac
done
shift $((OPTIND-1))

if [ -z "${xilinx_vivado}" ]; then
    usage
fi

xilinx_vivado=$(realpath $xilinx_vivado)
echo $xilinx_vivado

# Making a copy of the original source-files
rm -rf src
mkdir src
cp ../../code/src/n2d2/*.cc ./src

# OMP is not sintesizable
sed "s/#include <omp.h>//g" -i src/conv1.cc
sed "s/#pragma omp parallel for//g" -i src/conv1.cc
sed "s/#pragma unrol 5//g" -i src/conv1.cc
sed "s/#include <omp.h>//g" -i src/conv2.cc
sed "s/#pragma omp parallel for//g" -i src/conv2.cc
sed "s/#pragma unrol 5//g" -i src/conv2.cc
sed "s/#include <omp.h>//g" -i src/conv3.cc
sed "s/#pragma omp parallel for//g" -i src/conv3.cc
sed "s/#pragma unrol 5//g" -i src/conv3.cc
sed "s/#include <omp.h>//g" -i src/fc1.cc
sed "s/#pragma omp parallel for if (FC1_NB_OUTPUTS > 32)//g" -i src/fc1.cc
sed "s/#include <omp.h>//g" -i src/fc2.cc
sed "s/#pragma omp parallel for if (FC1_NB_OUTPUTS > 32)//g" -i src/fc2.cc
sed "s/#include <omp.h>//g" -i src/pool1.cc
sed "s/#pragma omp parallel for collapse(3)//g" -i src/pool1.cc
sed "s/#include <omp.h>//g" -i src/pool2.cc
sed "s/#pragma omp parallel for collapse(3)//g" -i src/pool2.cc

$xilinx_vivado/vivado_hls -f run_hls.tcl

