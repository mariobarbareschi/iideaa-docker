#ifndef ENV_READ_H
#define ENV_READ_H

#include "typedefs.h"

void env_read(char* fileName,
              unsigned int nbChannels,
              unsigned int channelsHeight,
              unsigned int channelsWidth,
              DATA_T inputs[nbChannels][channelsHeight][channelsWidth],
              unsigned int outputsHeight,
              unsigned int outputsWidth,
              int32_t outputTargets[outputsHeight][outputsWidth]);

#endif
