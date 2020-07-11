// N2D2 auto-generated file.
// @ Mon Sep 16 12:33:02 2019

#ifndef N2D2_EXPORTC_NETWORK_H
#define N2D2_EXPORTC_NETWORK_H

#include "sat.h"
#include "env.h"
#include "conv1.h"
#include "pool1.h"
#include "conv2.h"
#include "pool2.h"
#include "conv3.h"
#include "fc1.h"
#include "fc2.h"
#include "output.h"
void network(
		DATA_T (&in_data)[CONV1_NB_CHANNELS][CONV1_CHANNELS_HEIGHT][CONV1_CHANNELS_WIDTH],
		uint32_t (&out_data)[OUTPUTS_HEIGHT][OUTPUTS_WIDTH]);

#endif
