#include "fc2.h"
#include "sat.h"
#include <omp.h>

void fccell_propagate(
	DATA_T (&inputs)[FC2_NB_CHANNELS],
	DATA_T (&outputs)[OUTPUTS_SIZE*NB_OUTPUTS],
	BDATA_T (&bias)[FC2_NB_OUTPUTS],
	WDATA_T (&weights)[FC2_NB_OUTPUTS][FC2_NB_CHANNELS])
{
	#pragma omp parallel for if (FC2_NB_OUTPUTS > 32)
    for (unsigned int output = 0; output < FC2_NB_OUTPUTS; ++output) {
        SUM_T weightedSum = bias[output];

        for (unsigned int channel = 0; channel < FC2_NB_CHANNELS; ++channel)
            weightedSum += weights[output][channel] * inputs[channel];

        outputs[FC2_OUTPUT_OFFSET + output] = sat(weightedSum, FC2_ACTIVATION);
    }
}

