#include "conv1.h"
#include "sat.h"
#include <omp.h>

void convcell_propagate_conv1(
     DATA_T (&inputs)[CONV1_NB_CHANNELS][CONV1_CHANNELS_HEIGHT][CONV1_CHANNELS_WIDTH],
     DATA_T (&outputs)[CONV1_NB_OUTPUTS][CONV1_OUTPUTS_HEIGHT][CONV1_OUTPUTS_WIDTH],
     BDATA_T (&bias)[CONV1_NB_OUTPUTS],
     WDATA_T (&weights)[CONV1_NB_OUTPUTS][CONV1_NB_CHANNELS][CONV1_KERNEL_HEIGHT][CONV1_KERNEL_WIDTH])
{

	#pragma omp parallel for
	for (unsigned int output = 0; output < CONV1_NB_OUTPUTS; ++output) { 
		for (unsigned int oy = 0; oy < CONV1_OY_SIZE; ++oy) { 
			for (unsigned int ox = 0; ox < CONV1_OX_SIZE; ++ox) { 
				const unsigned int sxMin = (unsigned int)int_max( (int)CONV1_PADDING_X - (int)(ox * CONV1_STRIDE_X), 0); 
				const unsigned int syMin = (unsigned int)int_max( (int)CONV1_PADDING_Y - (int)(oy * CONV1_STRIDE_Y), 0); 
				const unsigned int sxMax = (unsigned int)int_max( int_min((int)CONV1_CHANNELS_WIDTH + CONV1_PADDING_X - (int)(ox * CONV1_STRIDE_X), (int)5), 0); 
				const unsigned int syMax = (unsigned int)int_max( int_min((int)CONV1_CHANNELS_HEIGHT + CONV1_PADDING_Y - (int)(oy * CONV1_STRIDE_Y), (int)5), 0); 
				const int ix = (int)(ox * CONV1_STRIDE_X) - (int)CONV1_PADDING_X; 
				const int iy = (int)(oy * CONV1_STRIDE_Y) - (int)CONV1_PADDING_Y; 
				SUM_T weightedSum = bias[output]; 
				for (unsigned int channel = 0; channel < CONV1_NB_CHANNELS; ++channel) { 
					#pragma unroll 5
					for (unsigned int sy = 0; sy < 5; ++sy) {
						#pragma unroll 5
						for (unsigned int sx = 0; sx < 5; ++sx) { 
							if (sx >= sxMin && sx < sxMax && sy >= syMin && sy < syMax) { 
								weightedSum = ((weightedSum) + ((SUM_T)weights[output][channel][sy][sx] * (SUM_T)( (DATA_T) inputs[channel][iy + sy][ix + sx]))); 
							} 
						} 
					} 
				} 
				outputs[CONV1_OUTPUT_OFFSET + output][oy][ox] = sat(weightedSum, CONV1_ACTIVATION); 
			} 
		} 
	} 
}


