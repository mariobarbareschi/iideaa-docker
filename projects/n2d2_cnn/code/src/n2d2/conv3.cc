#include "conv3.h"
#include "sat.h"
#include <omp.h>

void convcell_propagate_conv3(
    DATA_T (&inputs)[CONV3_NB_CHANNELS][CONV3_CHANNELS_HEIGHT][CONV3_CHANNELS_WIDTH],
    DATA_T (&outputs)[CONV3_NB_OUTPUTS][CONV3_OUTPUTS_HEIGHT][CONV3_OUTPUTS_WIDTH],
    BDATA_T (&bias)[CONV3_NB_OUTPUTS],
    CONV3_KERNEL_T* (&weights)[CONV3_NB_OUTPUTS][CONV3_NB_CHANNELS])
{

	#pragma omp parallel for
	for (unsigned int output = 0; output < CONV3_NB_OUTPUTS; ++output) { 
		for (unsigned int oy = 0; oy < CONV3_OY_SIZE; ++oy) { 
			for (unsigned int ox = 0; ox < CONV3_OX_SIZE; ++ox) { 
				const unsigned int sxMin = (unsigned int)int_max( (int)CONV3_PADDING_X - (int)(ox * CONV3_STRIDE_X), 0); 
				const unsigned int syMin = (unsigned int)int_max( (int)CONV3_PADDING_Y - (int)(oy * CONV3_STRIDE_Y), 0); 
				const unsigned int sxMax = (unsigned int)int_max( int_min((int)CONV3_CHANNELS_WIDTH + CONV3_PADDING_X - (int)(ox * CONV3_STRIDE_X), (int)5), 0); 
				const unsigned int syMax = (unsigned int)int_max( int_min((int)CONV3_CHANNELS_HEIGHT + CONV3_PADDING_Y - (int)(oy * CONV3_STRIDE_Y), (int)5), 0); 
				const int ix = (int)(ox * CONV3_STRIDE_X) - (int)CONV3_PADDING_X; 
				const int iy = (int)(oy * CONV3_STRIDE_Y) - (int)CONV3_PADDING_Y; 
				SUM_T weightedSum = bias[output]; 
				for (unsigned int channel = 0; channel < CONV3_NB_CHANNELS; ++channel) { 
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
				outputs[CONV3_OUTPUT_OFFSET + output][oy][ox] = sat(weightedSum, CONV3_ACTIVATION); 
			} 
		} 
	} 
}



