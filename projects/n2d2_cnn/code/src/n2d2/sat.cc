#include "sat.h"
#include <string.h>
#include <stdio.h> // printf()
#include <math.h>


DATA_T sat(SUM_T weightedSum, ActivationFunction_T func)
{
    switch (func) {
    case Tanh:
    case TanhLeCun:
        return tanh(weightedSum);
    case Rectifier:
        return MAX((SUM_T)0, weightedSum);
    case Linear:
        return weightedSum;
    default:
        fprintf(stderr, "Unsupported activation function in sat()\n");
        return 0;
    }
}


