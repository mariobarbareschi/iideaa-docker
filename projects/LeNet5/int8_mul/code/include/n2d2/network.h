/*
    (C) Copyright 2014 CEA LIST. All Rights Reserved.
    Contributor(s): Olivier BICHLER (olivier.bichler@cea.fr)

    This software is governed by the CeCILL-C license under French law and
    abiding by the rules of distribution of free software.  You can  use,
    modify and/ or redistribute the software under the terms of the CeCILL-C
    license as circulated by CEA, CNRS and INRIA at the following URL
    "http://www.cecill.info".

    As a counterpart to the access to the source code and  rights to copy,
    modify and redistribute granted by the license, users are provided only
    with a limited warranty  and the software's author,  the holder of the
    economic rights,  and the successive licensors  have only  limited
    liability.

    The fact that you are presently reading this means that you have had
    knowledge of the CeCILL-C license and that you accept its terms.
*/

#ifndef N2D2_EXPORTC_DEEPNET_H
#define N2D2_EXPORTC_DEEPNET_H

// For logistic function, should be 0.5, but 0 gives more dynamic range
#define BINARY_THRESHOLD 0
//#define ACC_NB_BITS 16

#include <dirent.h>
#include <stddef.h> // NULL def
#include <stdint.h> // (u)intx_t typedef
#include <stdio.h> // printf()
#include <sys/time.h>
#include <math.h>
#include <omp.h>

#include "typedefs.h"
#include "utils.h"
#include "env.h"
#include "conv1.h"
#include "conv2.h"
#include "conv3.h"
#include "pool1.h"
#include "pool2.h"
#include "fc1.h"
#include "fc2.h"


typedef struct RUNNING_MEAN {
    double mean;
    unsigned long long int count;
} RUNNING_MEAN_T;

typedef enum ACCS_REPORT { CHW, HWC } ACCS_REPORT_T;

static inline DATA_T sat32(SUM_T x, char rs)
{
#if NB_BITS < 0
    const SUM_T y = x;
#else
    const SUM_T y = (x >> rs);
#endif
    return (DATA_T)((y > DATA_T_MAX) ? DATA_T_MAX :
                    (y < DATA_T_MIN) ? DATA_T_MIN :
                                       y);
}

static inline UDATA_T usat32(SUM_T x, char rs) {
#if NB_BITS < 0
    const SUM_T y = x;
#else
    const SUM_T y = (x >> rs);
#endif
    return (UDATA_T)((y > UDATA_T_MAX) ? UDATA_T_MAX :
                     (y < 0)           ? 0 :
                                         y);
}

static inline DATA_T
usat(SUM_T weightedSum, ActivationFunction_T func, int shift)
{
#if NB_BITS >= 0
    if (shift > 0)
        weightedSum >>= shift;
    else if (shift < 0)
        weightedSum <<= (-shift);
#endif

    switch (func) {
    case Tanh:
    case TanhLeCun:
#if NB_BITS < 0
        return tanh(weightedSum);
#elif defined(NL)
        weightedSum >>= 1;
        return nl32_tanh(weightedSum);
#endif
    case Saturation:
        return sat32(weightedSum, NB_BITS);

    case Logistic:
    case LogisticWithLoss:
#if NB_BITS < 0
        return 1.0 / (1.0 + exp(-weightedSum));
#else
  #if BINARY_THRESHOLD != 0
        weightedSum >>= 3;      // divide by 4 & divide by 2 (because unsigned)
        weightedSum += (DATA_T_MAX << (NB_BITS - 1));
        return MAX((DATA_T)0, sat32(weightedSum, NB_BITS));
  #else
        return sat32(weightedSum, NB_BITS + 1);
  #endif
#endif

    case Rectifier:
#if NB_BITS < 0
        return MAX((SUM_T)0, weightedSum);
#else
  #if defined(UNSIGNED_DATA) && UNSIGNED_DATA
        // Keep one more bit because the output data is considered unsigned
        return usat32(MAX((SUM_T)0, weightedSum), NB_BITS - 1);
  #else
        return sat32(MAX((SUM_T)0, weightedSum), NB_BITS);
  #endif
#endif

    case Linear:
#if NB_BITS < 0
        return weightedSum;
#else
        // Max value is 2^NB_BITS*2^(NB_BITS-1) = 2^(2*NB_BITS-1)
        // ex. NB_BITS = 8 ==> -256*-128=32768
        // Output max value is 2^(NB_BITS-1) ==> must be shifted by NB_BITS
        // 32768>>8 = 128
        return sat32(weightedSum, NB_BITS);
#endif

    default:
        fprintf(stderr, "Unsupported activation function in usat()\n");
        return 0;
    }
}

void network(DATA_T (&in_data)[ENV_NB_OUTPUTS][ENV_SIZE_Y][ENV_SIZE_X], uint32_t (&out_data)[OUTPUTS_HEIGHT][OUTPUTS_WIDTH]);

#endif // N2D2_EXPORTC_DEEPNET_H
