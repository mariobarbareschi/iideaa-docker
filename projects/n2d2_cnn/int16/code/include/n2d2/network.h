// N2D2 auto-generated file.
// @ Mon Sep 16 12:44:48 2019

#ifndef N2D2_EXPORTC_NETWORK_H
#define N2D2_EXPORTC_NETWORK_H

#include "n2d2.h"
#include "env.h"
#include "conv1.h"
#include "pool1.h"
#include "conv2.h"
#include "pool2.h"
#include "conv3.h"
#include "fc1.h"
#include "fc2.h"
#define CONV1_OUTPUT_OFFSET 0
#define POOL1_OUTPUT_OFFSET 0
#define CONV2_OUTPUT_OFFSET 0
#define POOL2_OUTPUT_OFFSET 0
#define CONV3_OUTPUT_OFFSET 0
#define FC1_OUTPUT_OFFSET 0
#define FC2_OUTPUT_OFFSET 0
extern DATA_T output_data[NB_OUTPUTS*OUTPUTS_HEIGHT*OUTPUTS_WIDTH]; 

void network(DATA_T in_data[ENV_NB_OUTPUTS][ENV_SIZE_Y][ENV_SIZE_X], uint32_t out_data[OUTPUTS_HEIGHT][OUTPUTS_WIDTH]);

#endif
