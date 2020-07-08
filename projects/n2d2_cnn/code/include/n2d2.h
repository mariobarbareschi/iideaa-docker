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

#ifndef NO_DIRENT
#include <dirent.h>
#else
//#include "getline.h"
#endif

#include <stddef.h> // NULL def
#include <stdint.h> // (u)intx_t typedef
#include <stdio.h> // printf()
#include <sys/time.h>

#include <math.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#include "typedefs.h"
#include "env.h"
#include "utils.h"

#ifdef ACC_NB_BITS
    #define ACC_MAX ((1LL << (ACC_NB_BITS - 1)) - 1)
    #define ACC_MIN (-(1LL << (ACC_NB_BITS - 1)))
    #define ADD_SAT(x, y) MAX(ACC_MIN, MIN(ACC_MAX, ((x) + (y))))
#else
    #define ADD_SAT(x, y) ((x) + (y))
#endif

typedef struct RUNNING_MEAN {
    double mean;
    unsigned long long int count;
} RUNNING_MEAN_T;

typedef enum ACCS_REPORT { CHW, HWC } ACCS_REPORT_T;

int compare(void const* a, void const* b);
int sortedFileList(const char* const dirName,
                   char*** fileList,
                   unsigned int nbMax);
void swapEndian(char* str);

void env_read(char* fileName,
              unsigned int nbChannels,
              unsigned int channelsHeight,
              unsigned int channelsWidth,
              // DATA_T inputs[nbChannels][channelsHeight][channelsWidth],
              DATA_T * inputs,
              unsigned int outputsHeight,
              unsigned int outputsWidth,
              //int32_t outputTargets[outputsHeight][outputsWidth]);
              int32_t * outputTargets);

static inline DATA_T
sat(SUM_T weightedSum, ActivationFunction_T func, int shift)
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

void convcell_propagate_conv1(
    unsigned int nbChannels,
    unsigned int channelsHeight,
    unsigned int channelsWidth,
    int paddingY,
    int paddingX,
    unsigned int strideY,
    unsigned int strideX,
    DATA_T * inputs,
    unsigned int oySize,
    unsigned int oxSize,
    unsigned int nbOutputs_,
    unsigned int outputsHeight,
    unsigned int outputsWidth,
    unsigned int nbOutputs,
    unsigned int outputOffset,
    DATA_T * outputs,
    BDATA_T * bias,
    WDATA_T * weights,
    ActivationFunction_T func,
    int shift);

void convcell_propagate_conv2(
    unsigned int nbChannels,
    unsigned int channelsHeight,
    unsigned int channelsWidth,
    int paddingY,
    int paddingX,
    unsigned int strideY,
    unsigned int strideX,
    DATA_T * inputs,
    unsigned int oySize,
    unsigned int oxSize,
    unsigned int nbOutputs_,
    unsigned int outputsHeight,
    unsigned int outputsWidth,
    unsigned int nbOutputs,
    unsigned int outputOffset,
    DATA_T * outputs,
    BDATA_T * bias,
    WDATA_T * weights,
    ActivationFunction_T func,
    int shift);

void convcell_propagate_conv3(
    unsigned int nbChannels,
    unsigned int channelsHeight,
    unsigned int channelsWidth,
    int paddingY,
    int paddingX,
    unsigned int strideY,
    unsigned int strideX,
    DATA_T * inputs,
    unsigned int oySize,
    unsigned int oxSize,
    unsigned int nbOutputs_,
    unsigned int outputsHeight,
    unsigned int outputsWidth,
    unsigned int nbOutputs,
    unsigned int outputOffset,
    DATA_T * outputs,
    BDATA_T * bias,
    WDATA_T * weights,
    ActivationFunction_T func,
    int shift);

void poolcell_propagate_unitmap(
    unsigned int nbChannels,
    unsigned int channelsHeight,
    unsigned int channelsWidth,
    unsigned int strideY,
    unsigned int strideX,
    DATA_T * inputs,
    unsigned int nbOutputs_,
    unsigned int outputsHeight,
    unsigned int outputsWidth,
    unsigned int nbOutputs,
    unsigned int outputOffset,
    DATA_T * outputs,
    unsigned int poolHeight,
    unsigned int poolWidth,
    Pooling_T pooling,
    ActivationFunction_T func,
    int shift);

void
fccell_propagate_2d(unsigned int nbChannels,
                    unsigned int channelsHeight,
                    unsigned int channelsWidth,
                    DATA_T * inputs,
                    unsigned int nbOutputs_,
                    unsigned int nbOutputs,
                    unsigned int outputOffset,
                    DATA_T * outputs,
                    unsigned int nbChannels_,
                    BDATA_T * bias,
                    WDATA_T * weights,
                    ActivationFunction_T func,
                    int shift);

void fccell_propagate(unsigned int nbChannels,
                      DATA_T * inputs,
                      unsigned int nbOutputs_,
                      unsigned int nbOutputs,
                      unsigned int outputOffset,
                      DATA_T * outputs,
                      BDATA_T * bias,
                      WDATA_T * weights,
                      ActivationFunction_T func,
                      int shift);

void output_max(unsigned int nbOutputs,
                DATA_T * outputs,
                uint32_t * outputEstimated);

#endif // N2D2_EXPORTC_DEEPNET_H
