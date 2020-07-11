#include "output.h"
#include "sat.h"

void output_max(
	DATA_T (&outputs)[FC2_NB_OUTPUTS],
	uint32_t (&outputEstimated)[OUTPUTS_HEIGHT][OUTPUTS_WIDTH])
{
    if (FC2_NB_OUTPUTS > 1) {
        DATA_T maxVal = outputs[0];
        unsigned int outputMax = 0;

        for (unsigned int output = 1; output < FC2_NB_OUTPUTS; ++output) {
            if (outputs[output] > maxVal) {
                maxVal = outputs[output];
                outputMax = output;
            }
        }

        outputEstimated[0][0] = outputMax;
    }
    else
        outputEstimated[0][0] = (outputs[0] > (BINARY_THRESHOLD * DATA_T_MAX));
}


