#ifndef N2D2_EXPORTC_DEEPNET_H
#define N2D2_EXPORTC_DEEPNET_H


#include "typedefs.h"
#include "env.h"
#include "utils.h"

#define ADD_SAT(x, y) ((x) + (y))

DATA_T sat(SUM_T weightedSum, ActivationFunction_T func);

#endif // N2D2_EXPORTC_DEEPNET_H
