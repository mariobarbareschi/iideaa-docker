#include "pool2.h"
#include "sat.h"
#include <omp.h>

void poolcell_propagate_pool2(
    DATA_T (&inputs)[POOL2_NB_CHANNELS][POOL2_CHANNELS_HEIGHT][POOL2_CHANNELS_WIDTH],
    DATA_T (&outputs)[POOL2_NB_OUTPUTS][POOL2_OUTPUTS_HEIGHT][POOL2_OUTPUTS_WIDTH])
{
	#pragma omp parallel for collapse(3)
    for (unsigned int output = 0; output < POOL2_NB_OUTPUTS; ++output) {
        for (unsigned int oy = 0; oy < POOL2_OUTPUTS_HEIGHT; ++oy) {
            for (unsigned int ox = 0; ox < POOL2_OUTPUTS_WIDTH; ++ox) {
                const unsigned int sxMax
                    = uint_min(POOL2_CHANNELS_WIDTH - ox * POOL2_STRIDE_X, POOL2_POOL_WIDTH);
                const unsigned int syMax
                    = uint_min(POOL2_CHANNELS_HEIGHT - oy * POOL2_STRIDE_Y, POOL2_POOL_HEIGHT);

                if (POOL2_POOLING == Max) {
                    DATA_T poolValue = DATA_T_MIN;

                    for (unsigned int sy = 0; sy < syMax; ++sy) {
                        for (unsigned int sx = 0; sx < sxMax; ++sx) {
                            const unsigned int ix = ox * POOL2_STRIDE_X + sx;
                            const unsigned int iy = oy * POOL2_STRIDE_Y + sy;

                            if (inputs[output][iy][ix] > poolValue)
                                poolValue = inputs[output][iy][ix];
                        }
                    }
                    outputs[POOL2_OUTPUT_OFFSET + output][oy][ox] = sat(poolValue, POOL2_ACTIVATION);
                } else if (POOL2_POOLING == Average) {
                    SUM_T sum = 0;

                    for (unsigned int sy = 0; sy < syMax; ++sy) {
                        for (unsigned int sx = 0; sx < sxMax; ++sx) {
                            const unsigned int ix = ox * POOL2_STRIDE_X + sx;
                            const unsigned int iy = oy * POOL2_STRIDE_Y + sy;
                            sum += inputs[output][iy][ix];
                        }
                    }
                    sum /= POOL2_POOL_WIDTH * POOL2_POOL_HEIGHT;
                    outputs[POOL2_OUTPUT_OFFSET + output][oy][ox] = sat(sum, POOL2_ACTIVATION);
                }
            }
        }
    }
}


