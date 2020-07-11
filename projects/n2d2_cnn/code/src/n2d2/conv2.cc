#include "conv2.h"
#include "sat.h"
#include <omp.h>

void convcell_propagate_conv2(
    DATA_T (&inputs)[CONV2_NB_CHANNELS][CONV2_CHANNELS_HEIGHT][CONV2_CHANNELS_WIDTH],
    DATA_T (&outputs)[CONV2_NB_OUTPUTS][CONV2_OUTPUTS_HEIGHT][CONV2_OUTPUTS_WIDTH],
    BDATA_T (&bias)[CONV2_NB_OUTPUTS],
    CONV2_KERNEL_T* (&weights)[CONV2_NB_OUTPUTS][CONV2_NB_CHANNELS])
{

	#pragma omp parallel for
	for (unsigned int output = 0; output < CONV2_NB_OUTPUTS; ++output) { 
		for (unsigned int oy = 0; oy < CONV2_OY_SIZE; ++oy) { 
			for (unsigned int ox = 0; ox < CONV2_OX_SIZE; ++ox) { 
				const unsigned int sxMin = (unsigned int)int_max( (int)CONV2_PADDING_X - (int)(ox * CONV2_STRIDE_X), 0); 
				const unsigned int syMin = (unsigned int)int_max( (int)CONV2_PADDING_Y - (int)(oy * CONV2_STRIDE_Y), 0); 
				const unsigned int sxMax = (unsigned int)int_max( int_min((int)CONV2_CHANNELS_WIDTH + CONV2_PADDING_X - (int)(ox * CONV2_STRIDE_X), (int)5), 0); 
				const unsigned int syMax = (unsigned int)int_max( int_min((int)CONV2_CHANNELS_HEIGHT + CONV2_PADDING_Y - (int)(oy * CONV2_STRIDE_Y), (int)5), 0); 
				const int ix = (int)(ox * CONV2_STRIDE_X) - (int)CONV2_PADDING_X; 
				const int iy = (int)(oy * CONV2_STRIDE_Y) - (int)CONV2_PADDING_Y; 
				SUM_T weightedSum = bias[output]; 
				for (unsigned int channel = 0; channel < CONV2_NB_CHANNELS; ++channel) { 
					if (weights[output][channel] == NULL) continue;
					#pragma unroll 5
					for (unsigned int sy = 0; sy < 5; ++sy) {
						#pragma unroll 5
						for (unsigned int sx = 0; sx < 5; ++sx) { 
							if (sx >= sxMin && sx < sxMax && sy >= syMin && sy < syMax) { 
								weightedSum = ((weightedSum) + ((SUM_T)( *weights[output][channel])[sy][sx] * (SUM_T)( (DATA_T) inputs[channel][iy + sy][ix + sx]))); 
							} 
						} 
					} 
				} 
				outputs[CONV2_OUTPUT_OFFSET + output][oy][ox] = sat(weightedSum, CONV2_ACTIVATION); 
			} 
		} 
	} 
}


