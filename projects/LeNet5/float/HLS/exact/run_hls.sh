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
mkdir -p src
cp ../../code/src/n2d2/network.cc ./src

# OMP is not sintesizable
sed "s/#include <omp.h>//g" -i src/network.cc
sed "s/#include \"fap.h\"//g" -i src/network.cc
sed "s/#pragma omp parallel for if (FC1_NB_OUTPUTS > 32)//g" -i src/network.cc
sed "s/#pragma omp parallel for collapse(3)//g" -i src/network.cc
sed "s/#pragma omp parallel for//g" -i src/network.cc

$xilinx_vivado/vivado_hls -f run_hls.tcl

