#ifndef ENV_READ_H
#define ENV_READ_H

#include "typedefs.h"
#include "env.h"

#define ENV_NB_CHANNELS 1
#define ENV_NB_HEIGHT 32
#define ENV_NB_WIDTH 32
#define ENV_NB_OUTPUTS_HEIGHT 1
#define ENV_NB_OUTPUTS_WIDTH 1

void env_read(char* fileName,
              DATA_T (&inputs)[ENV_NB_OUTPUTS][ENV_SIZE_Y][ENV_SIZE_X],
              int32_t (&outputTargets)[ENV_NB_OUTPUTS_HEIGHT][ENV_NB_OUTPUTS_WIDTH]);

#endif

