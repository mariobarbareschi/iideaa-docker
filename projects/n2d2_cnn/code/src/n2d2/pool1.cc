#include "pool1.h"
#include "sat.h"
#include <omp.h>

void poolcell_propagate_pool1(
    DATA_T (&inputs)[POOL1_NB_CHANNELS][POOL1_CHANNELS_HEIGHT][POOL1_CHANNELS_WIDTH],
    DATA_T (&outputs)[POOL1_NB_OUTPUTS][POOL1_OUTPUTS_HEIGHT][POOL1_OUTPUTS_WIDTH])
{
	#pragma omp parallel for collapse(3)
    for (unsigned int output = 0; output < POOL1_NB_OUTPUTS; ++output) {
        for (unsigned int oy = 0; oy < POOL1_OUTPUTS_HEIGHT; ++oy) {
            for (unsigned int ox = 0; ox < POOL1_OUTPUTS_WIDTH; ++ox) {
                const unsigned int sxMax
                    = uint_min(POOL1_CHANNELS_WIDTH - ox * POOL1_STRIDE_X, POOL1_POOL_WIDTH);
                const unsigned int syMax
                    = uint_min(POOL1_CHANNELS_HEIGHT - oy * POOL1_STRIDE_Y, POOL1_POOL_HEIGHT);

                if (POOL1_POOLING == Max) {
                    DATA_T poolValue = DATA_T_MIN;

                    for (unsigned int sy = 0; sy < syMax; ++sy) {
                        for (unsigned int sx = 0; sx < sxMax; ++sx) {
                            const unsigned int ix = ox * POOL1_STRIDE_X + sx;
                            const unsigned int iy = oy * POOL1_STRIDE_Y + sy;

                            if (inputs[output][iy][ix] > poolValue)
                                poolValue = inputs[output][iy][ix];
                        }
                    }
                    outputs[POOL1_OUTPUT_OFFSET + output][oy][ox] = sat(poolValue, POOL1_ACTIVATION);
                } else if (POOL1_POOLING == Average) {
                    SUM_T sum = 0;

                    for (unsigned int sy = 0; sy < syMax; ++sy) {
                        for (unsigned int sx = 0; sx < sxMax; ++sx) {
                            const unsigned int ix = ox * POOL1_STRIDE_X + sx;
                            const unsigned int iy = oy * POOL1_STRIDE_Y + sy;
                            sum += inputs[output][iy][ix];
                        }
                    }
                    sum /= POOL1_POOL_WIDTH * POOL1_POOL_HEIGHT;
                    outputs[POOL1_OUTPUT_OFFSET + output][oy][ox] = sat(sum, POOL1_ACTIVATION);
                }
            }
        }
    }
}

