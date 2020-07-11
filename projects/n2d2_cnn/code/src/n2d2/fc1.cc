#include "fc1.h"
#include "sat.h"
#include <omp.h>

void fccell_propagate_2d(
                    DATA_T (&inputs)[CONV3_NB_OUTPUTS][CONV3_OUTPUTS_HEIGHT][CONV3_OUTPUTS_WIDTH],
                    DATA_T (&outputs)[FC1_NB_OUTPUTS],
                    BDATA_T (&bias)[FC1_NB_OUTPUTS],
                    WDATA_T (&weights)[FC1_NB_OUTPUTS][FC1_NB_CHANNELS])
{

	#pragma omp parallel for if (FC1_NB_OUTPUTS > 32)
    for (unsigned int output = 0; output < FC1_NB_OUTPUTS; ++output) {
        SUM_T weightedSum = bias[output];
        unsigned int c = 0;

        for (unsigned int channel = 0; channel < CONV3_NB_OUTPUTS; ++channel) {
            for (unsigned int iy = 0; iy < CONV3_OUTPUTS_HEIGHT; ++iy) {
				for (unsigned int ix = 0; ix < CONV3_OUTPUTS_WIDTH; ++ix)
                    weightedSum += weights[output][c++] * inputs[channel][iy][ix];
            }
        }

        outputs[FC1_OUTPUT_OFFSET + output] = sat(weightedSum, FC1_ACTIVATION);
    }
}


