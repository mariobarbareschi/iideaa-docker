#ifndef OUTPUT_MAX_H
#define OUTPUT_MAX_H

#include "env.h"
#include "typedefs.h"
#include "fc2.h"

#define BINARY_THRESHOLD 0

void output_max(
	DATA_T (&outputs)[FC2_NB_OUTPUTS],
	uint32_t (&outputEstimated)[OUTPUTS_HEIGHT][OUTPUTS_WIDTH]);

#endif

