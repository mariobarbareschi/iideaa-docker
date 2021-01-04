#include <string.h>
#include "network.h"
#include "math.h"
#include "trunc.h"

int nab_0 = 0;
SUM_T neuron_conv1
(
  DATA_T (&inputs)[CONV1_NB_CHANNELS][CONV1_CHANNELS_HEIGHT][CONV1_CHANNELS_WIDTH],
  const BDATA_T (&bias)[CONV1_NB_OUTPUTS],
  const WDATA_T (*weights[CONV1_NB_OUTPUTS][CONV1_NB_CHANNELS])[CONV1_KERNEL_HEIGHT][CONV1_KERNEL_WIDTH],
  unsigned int output,
  unsigned int sxMin,
  unsigned int syMin,
  unsigned int sxMax,
  unsigned int syMax,
  int ix,
  int iy
)
{
  SUM_T weightedSum = bias[output];
  for (unsigned int channel = 0; channel < CONV1_NB_CHANNELS; ++channel)
  {
    if (weights[output][channel] == NULL) continue;
    for (unsigned int sy = syMin; sy < syMax; ++sy)
      for (unsigned int sx = sxMin; sx < sxMax; ++sx)
      {
        SUM_T prod = truncate::ax_integer(nab_0, (*weights[output][channel])[sy][sx]) * truncate::ax_integer(nab_0, ((UDATA_T) inputs[channel][iy + sy][ix + sx]));
        weightedSum += prod;
      }
  }
  return weightedSum;
}

void convcell_upropagate_conv1(
  DATA_T (&inputs)[CONV1_NB_CHANNELS][CONV1_CHANNELS_HEIGHT][CONV1_CHANNELS_WIDTH],
  DATA_T (&outputs)[CONV1_NB_OUTPUTS][CONV1_OUTPUTS_HEIGHT][CONV1_OUTPUTS_WIDTH],
  const BDATA_T (&bias)[CONV1_NB_OUTPUTS],
  const WDATA_T (*weights[CONV1_NB_OUTPUTS][CONV1_NB_CHANNELS])[CONV1_KERNEL_HEIGHT][CONV1_KERNEL_WIDTH])
{
  #pragma omp parallel for
  for (unsigned int output = 0; output < CONV1_NB_OUTPUTS; ++output)
    for (unsigned int oy = 0; oy < CONV1_OY_SIZE; ++oy)
      for (unsigned int ox = 0; ox < CONV1_OX_SIZE; ++ox)
      {
        const unsigned int sxMin = (unsigned int) int_max((int) CONV1_PADDING_X - (int) (ox * CONV1_STRIDE_X), 0);
        const unsigned int syMin = (unsigned int) int_max((int) CONV1_PADDING_Y - (int) (oy * CONV1_STRIDE_Y), 0);
        const unsigned int sxMax = (unsigned int) int_max(int_min((int) CONV1_CHANNELS_WIDTH + CONV1_PADDING_X - (int) (ox * CONV1_STRIDE_X),(int) CONV1_KERNEL_WIDTH),0);
        const unsigned int syMax = (unsigned int) int_max(int_min((int) CONV1_CHANNELS_HEIGHT + CONV1_PADDING_Y - (int) (oy * CONV1_STRIDE_Y),(int) CONV1_KERNEL_HEIGHT),0);
        const int ix = (int) (ox * CONV1_STRIDE_X) - (int) CONV1_PADDING_X;
        const int iy = (int) (oy * CONV1_STRIDE_Y) - (int) CONV1_PADDING_Y;
        outputs[CONV1_OUTPUT_OFFSET + output][oy][ox] = usat(neuron_conv1(inputs, bias, weights, output, sxMin, syMin, sxMax, syMax, ix, iy), CONV1_ACTIVATION, CONV1_SHIFT);
      }
}

int nab_6 = 0;
int nab_5 = 0;
int nab_4 = 0;
int nab_3 = 0;
int nab_2 = 0;
int nab_1 = 0;
SUM_T neuron_conv2
(
  DATA_T (&inputs)[CONV2_NB_CHANNELS][CONV2_CHANNELS_HEIGHT][CONV2_CHANNELS_WIDTH],
  const BDATA_T (&bias)[CONV2_NB_OUTPUTS],
  const WDATA_T (*weights[CONV2_NB_OUTPUTS][CONV2_NB_CHANNELS])[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH],
  unsigned int output,
  unsigned int sxMin,
  unsigned int syMin,
  unsigned int sxMax,
  unsigned int syMax,
  int ix,
  int iy
)
{
  SUM_T weightedSum = bias[output];

//  for (unsigned int channel = 0; channel < CONV2_NB_CHANNELS; ++channel)
//  {
//    if (weights[output][channel] == NULL) continue;
//    for (unsigned int sy = syMin; sy < syMax; ++sy)
//      for (unsigned int sx = sxMin; sx < sxMax; ++sx)
//      {
//        SUM_T prod = (SUM_T) (*weights[output][channel])[sy][sx] * (SUM_T) ((UDATA_T) inputs[channel][iy + sy][ix + sx]);
//        weightedSum += prod;
//      }
//  }

  // channel 0
  if (weights[output][0] != NULL)
  for (unsigned int sy = syMin; sy < syMax; ++sy)
    for (unsigned int sx = sxMin; sx < sxMax; ++sx)
    {
      SUM_T prod = truncate::ax_integer(nab_1, (*weights[output][0])[sy][sx]) * truncate::ax_integer(nab_1, ((UDATA_T) inputs[0][iy + sy][ix + sx]));
      weightedSum += prod;
    }

  // channel 1
  if (weights[output][1] != NULL)
  for (unsigned int sy = syMin; sy < syMax; ++sy)
    for (unsigned int sx = sxMin; sx < sxMax; ++sx)
    {
      SUM_T prod = truncate::ax_integer(nab_2, (*weights[output][1])[sy][sx]) * truncate::ax_integer(nab_2, ((UDATA_T) inputs[1][iy + sy][ix + sx]));
      weightedSum += prod;
    }

  // channel 2
  if (weights[output][2] != NULL)
  for (unsigned int sy = syMin; sy < syMax; ++sy)
    for (unsigned int sx = sxMin; sx < sxMax; ++sx)
    {
      SUM_T prod = truncate::ax_integer(nab_3, (*weights[output][2])[sy][sx]) * truncate::ax_integer(nab_3, ((UDATA_T) inputs[2][iy + sy][ix + sx]));
      weightedSum += prod;
    }

  // channel 3
  if (weights[output][3] != NULL)
  for (unsigned int sy = syMin; sy < syMax; ++sy)
    for (unsigned int sx = sxMin; sx < sxMax; ++sx)
    {
      SUM_T prod = truncate::ax_integer(nab_4, (*weights[output][3])[sy][sx]) * truncate::ax_integer(nab_4, ((UDATA_T) inputs[3][iy + sy][ix + sx]));
      weightedSum += prod;
    }

  // channel 4
  if (weights[output][4] != NULL)
  for (unsigned int sy = syMin; sy < syMax; ++sy)
    for (unsigned int sx = sxMin; sx < sxMax; ++sx)
    {
      SUM_T prod = truncate::ax_integer(nab_5, (*weights[output][4])[sy][sx]) * truncate::ax_integer(nab_5, ((UDATA_T) inputs[4][iy + sy][ix + sx]));
      weightedSum += prod;
    }

  // channel 5
  if (weights[output][5] != NULL)
  for (unsigned int sy = syMin; sy < syMax; ++sy)
    for (unsigned int sx = sxMin; sx < sxMax; ++sx)
    {
      SUM_T prod = truncate::ax_integer(nab_6, (*weights[output][5])[sy][sx]) * truncate::ax_integer(nab_6, ((UDATA_T) inputs[5][iy + sy][ix + sx]));
      weightedSum += prod;
    }
  return weightedSum;
}

void convcell_upropagate_conv2(
  DATA_T (&inputs)[CONV2_NB_CHANNELS][CONV2_CHANNELS_HEIGHT][CONV2_CHANNELS_WIDTH],
  DATA_T (&outputs)[CONV2_NB_OUTPUTS][CONV2_OUTPUTS_HEIGHT][CONV2_OUTPUTS_WIDTH],
  const BDATA_T (&bias)[CONV2_NB_OUTPUTS],
  const WDATA_T (*weights[CONV2_NB_OUTPUTS][CONV2_NB_CHANNELS])[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH])
{
  #pragma omp parallel for
  for (unsigned int output = 0; output < CONV2_NB_OUTPUTS; ++output)
    for (unsigned int oy = 0; oy < CONV2_OY_SIZE; ++oy)
      for (unsigned int ox = 0; ox < CONV2_OX_SIZE; ++ox)
      {
        const unsigned int sxMin = (unsigned int) int_max((int) CONV2_PADDING_X - (int) (ox * CONV2_STRIDE_X), 0);
        const unsigned int syMin = (unsigned int) int_max((int) CONV2_PADDING_Y - (int) (oy * CONV2_STRIDE_Y), 0);
        const unsigned int sxMax = (unsigned int) int_max(int_min((int) CONV2_CHANNELS_WIDTH + CONV2_PADDING_X - (int) (ox * CONV2_STRIDE_X),(int) CONV2_KERNEL_WIDTH), 0);
        const unsigned int syMax = (unsigned int) int_max(int_min((int) CONV2_CHANNELS_HEIGHT + CONV2_PADDING_Y - (int) (oy * CONV2_STRIDE_Y),(int) CONV2_KERNEL_HEIGHT),0);
        const int ix = (int) (ox * CONV2_STRIDE_X) - (int) CONV2_PADDING_X;
        const int iy = (int) (oy * CONV2_STRIDE_Y) - (int) CONV2_PADDING_Y;
        outputs[CONV2_OUTPUT_OFFSET + output][oy][ox] = usat(neuron_conv2(inputs, bias, weights, output, sxMin, syMin, sxMax, syMax, ix, iy), CONV2_ACTIVATION, CONV2_SHIFT);
      }
}

int nab_22 = 0;
int nab_21 = 0;
int nab_20 = 0;
int nab_19 = 0;
int nab_18 = 0;
int nab_17 = 0;
int nab_16 = 0;
int nab_15 = 0;
int nab_14 = 0;
int nab_13 = 0;
int nab_12 = 0;
int nab_11 = 0;
int nab_10 = 0;
int nab_9 = 0;
int nab_8 = 0;
int nab_7 = 0;
SUM_T neuron_conv3
(
  DATA_T (&inputs)[CONV3_NB_CHANNELS][CONV3_CHANNELS_HEIGHT][CONV3_CHANNELS_WIDTH],
  const BDATA_T (&bias)[CONV3_NB_OUTPUTS],
  const WDATA_T (*weights[CONV3_NB_OUTPUTS][CONV3_NB_CHANNELS])[CONV3_KERNEL_HEIGHT][CONV3_KERNEL_WIDTH],
  unsigned int output,
  unsigned int sxMin,
  unsigned int syMin,
  unsigned int sxMax,
  unsigned int syMax,
  int ix,
  int iy
)
{
  SUM_T weightedSum = bias[output];
//  for (unsigned int channel = 0; channel < CONV3_NB_CHANNELS; ++channel)
//  {
//    if (weights[output][channel] == NULL) continue;
//    for (unsigned int sy = syMin; sy < syMax; ++sy)
//      for (unsigned int sx = sxMin; sx < sxMax; ++sx)
//      {
//        SUM_T prod = (SUM_T) (*weights[output][channel])[sy][sx] * (SUM_T) ((UDATA_T) inputs[channel][iy + sy][ix + sx]);
//        weightedSum += prod;
//      }
//  }
  
  // channel 0
  if (weights[output][0] != NULL)
    for (unsigned int sy = syMin; sy < syMax; ++sy)
      for (unsigned int sx = sxMin; sx < sxMax; ++sx)
      {
        SUM_T prod = truncate::ax_integer(nab_7, (*weights[output][0])[sy][sx]) * truncate::ax_integer(nab_7, ((UDATA_T) inputs[0][iy + sy][ix + sx]));
        weightedSum += prod;
      }

  // channel 1
  if (weights[output][1] != NULL)
    for (unsigned int sy = syMin; sy < syMax; ++sy)
      for (unsigned int sx = sxMin; sx < sxMax; ++sx)
      {
        SUM_T prod = truncate::ax_integer(nab_8, (*weights[output][1])[sy][sx]) * truncate::ax_integer(nab_8, ((UDATA_T) inputs[1][iy + sy][ix + sx]));
        weightedSum += prod;
      }

  // channel 2
  if (weights[output][2] != NULL)
    for (unsigned int sy = syMin; sy < syMax; ++sy)
      for (unsigned int sx = sxMin; sx < sxMax; ++sx)
      {
        SUM_T prod = truncate::ax_integer(nab_9, (*weights[output][2])[sy][sx]) * truncate::ax_integer(nab_9, ((UDATA_T) inputs[2][iy + sy][ix + sx]));
        weightedSum += prod;
      }

  // channel 3
  if (weights[output][3] != NULL)
    for (unsigned int sy = syMin; sy < syMax; ++sy)
      for (unsigned int sx = sxMin; sx < sxMax; ++sx)
      {
        SUM_T prod = truncate::ax_integer(nab_10, (*weights[output][3])[sy][sx]) * truncate::ax_integer(nab_10, ((UDATA_T) inputs[3][iy + sy][ix + sx]));
        weightedSum += prod;
      }

  // channel 4
  if (weights[output][4] != NULL)
    for (unsigned int sy = syMin; sy < syMax; ++sy)
      for (unsigned int sx = sxMin; sx < sxMax; ++sx)
      {
        SUM_T prod = truncate::ax_integer(nab_11, (*weights[output][4])[sy][sx]) * truncate::ax_integer(nab_11, ((UDATA_T) inputs[4][iy + sy][ix + sx]));
        weightedSum += prod;
      }

  // channel 5
  if (weights[output][5] != NULL)
    for (unsigned int sy = syMin; sy < syMax; ++sy)
      for (unsigned int sx = sxMin; sx < sxMax; ++sx)
      {
        SUM_T prod = truncate::ax_integer(nab_12, (*weights[output][5])[sy][sx]) * truncate::ax_integer(nab_12, ((UDATA_T) inputs[5][iy + sy][ix + sx]));
        weightedSum += prod;
      }

  // channel 6
  if (weights[output][6] != NULL)
    for (unsigned int sy = syMin; sy < syMax; ++sy)
      for (unsigned int sx = sxMin; sx < sxMax; ++sx)
      {
        SUM_T prod = truncate::ax_integer(nab_13, (*weights[output][6])[sy][sx]) * truncate::ax_integer(nab_13, ((UDATA_T) inputs[6][iy + sy][ix + sx]));
        weightedSum += prod;
      }

  // channel 7
  if (weights[output][7] != NULL)
    for (unsigned int sy = syMin; sy < syMax; ++sy)
      for (unsigned int sx = sxMin; sx < sxMax; ++sx)
      {
        SUM_T prod = truncate::ax_integer(nab_14, (*weights[output][7])[sy][sx]) * truncate::ax_integer(nab_14, ((UDATA_T) inputs[7][iy + sy][ix + sx]));
        weightedSum += prod;
      }

  // channel 8
  if (weights[output][8] != NULL)
    for (unsigned int sy = syMin; sy < syMax; ++sy)
      for (unsigned int sx = sxMin; sx < sxMax; ++sx)
      {
        SUM_T prod = truncate::ax_integer(nab_15, (*weights[output][8])[sy][sx]) * truncate::ax_integer(nab_15, ((UDATA_T) inputs[8][iy + sy][ix + sx]));
        weightedSum += prod;
      }

  // channel 9
  if (weights[output][9] != NULL)
    for (unsigned int sy = syMin; sy < syMax; ++sy)
      for (unsigned int sx = sxMin; sx < sxMax; ++sx)
      {
        SUM_T prod = truncate::ax_integer(nab_16, (*weights[output][9])[sy][sx]) * truncate::ax_integer(nab_16, ((UDATA_T) inputs[9][iy + sy][ix + sx]));
        weightedSum += prod;
      }

  // channel 10
  if (weights[output][10] != NULL)
    for (unsigned int sy = syMin; sy < syMax; ++sy)
      for (unsigned int sx = sxMin; sx < sxMax; ++sx)
      {
        SUM_T prod = truncate::ax_integer(nab_17, (*weights[output][10])[sy][sx]) * truncate::ax_integer(nab_17, ((UDATA_T) inputs[10][iy + sy][ix + sx]));
        weightedSum += prod;
      }

  // channel 11
  if (weights[output][11] != NULL)
    for (unsigned int sy = syMin; sy < syMax; ++sy)
      for (unsigned int sx = sxMin; sx < sxMax; ++sx)
      {
        SUM_T prod = truncate::ax_integer(nab_18, (*weights[output][11])[sy][sx]) * truncate::ax_integer(nab_18, ((UDATA_T) inputs[11][iy + sy][ix + sx]));
        weightedSum += prod;
      }

  // channel 12
  if (weights[output][12] != NULL)
    for (unsigned int sy = syMin; sy < syMax; ++sy)
      for (unsigned int sx = sxMin; sx < sxMax; ++sx)
      {
        SUM_T prod = truncate::ax_integer(nab_19, (*weights[output][12])[sy][sx]) * truncate::ax_integer(nab_19, ((UDATA_T) inputs[12][iy + sy][ix + sx]));
        weightedSum += prod;
      }

  // channel 13
  if (weights[output][13] != NULL)
    for (unsigned int sy = syMin; sy < syMax; ++sy)
      for (unsigned int sx = sxMin; sx < sxMax; ++sx)
      {
        SUM_T prod = truncate::ax_integer(nab_20, (*weights[output][13])[sy][sx]) * truncate::ax_integer(nab_20, ((UDATA_T) inputs[13][iy + sy][ix + sx]));
        weightedSum += prod;
      }

  // channel 14
  if (weights[output][14] != NULL)
    for (unsigned int sy = syMin; sy < syMax; ++sy)
      for (unsigned int sx = sxMin; sx < sxMax; ++sx)
      {
        SUM_T prod = truncate::ax_integer(nab_21, (*weights[output][14])[sy][sx]) * truncate::ax_integer(nab_21, ((UDATA_T) inputs[14][iy + sy][ix + sx]));
        weightedSum += prod;
      }

  // channel 15
  if (weights[output][15] != NULL)
    for (unsigned int sy = syMin; sy < syMax; ++sy)
      for (unsigned int sx = sxMin; sx < sxMax; ++sx)
      {
        SUM_T prod = truncate::ax_integer(nab_22, (*weights[output][15])[sy][sx]) * truncate::ax_integer(nab_22, ((UDATA_T) inputs[15][iy + sy][ix + sx]));
        weightedSum += prod;
      }
  return weightedSum;
}
void convcell_upropagate_conv3(
  DATA_T (&inputs)[CONV3_NB_CHANNELS][CONV3_CHANNELS_HEIGHT][CONV3_CHANNELS_WIDTH],
  DATA_T (&outputs)[CONV3_NB_OUTPUTS][CONV3_OUTPUTS_HEIGHT][CONV3_OUTPUTS_WIDTH],
  const BDATA_T (&bias)[CONV3_NB_OUTPUTS],
  const WDATA_T (*weights[CONV3_NB_OUTPUTS][CONV3_NB_CHANNELS])[CONV3_KERNEL_HEIGHT][CONV3_KERNEL_WIDTH])
{
  #pragma omp parallel for
  for (unsigned int output = 0; output < CONV3_NB_OUTPUTS; ++output)
    for (unsigned int oy = 0; oy < CONV3_OY_SIZE; ++oy)
      for (unsigned int ox = 0; ox < CONV3_OX_SIZE; ++ox)
      {
        const unsigned int sxMin = (unsigned int) int_max((int) CONV3_PADDING_X - (int) (ox * CONV3_STRIDE_X), 0);
        const unsigned int syMin = (unsigned int) int_max((int) CONV3_PADDING_Y - (int) (oy * CONV3_STRIDE_Y), 0);
        const unsigned int sxMax = (unsigned int) int_max(int_min((int) CONV3_CHANNELS_WIDTH + CONV3_PADDING_X - (int) (ox * CONV3_STRIDE_X),(int) CONV3_KERNEL_WIDTH),0);
        const unsigned int syMax = (unsigned int) int_max(int_min((int) CONV3_CHANNELS_HEIGHT + CONV3_PADDING_Y - (int) (oy * CONV3_STRIDE_Y),(int) CONV3_KERNEL_HEIGHT),0);
        const int ix = (int) (ox * CONV3_STRIDE_X) - (int) CONV3_PADDING_X;
        const int iy = (int) (oy * CONV3_STRIDE_Y) - (int) CONV3_PADDING_Y;
        outputs[CONV3_OUTPUT_OFFSET + output][oy][ox] = usat(neuron_conv3(inputs, bias, weights, output, sxMin, syMin, sxMax, syMax, ix, iy), CONV3_ACTIVATION, CONV3_SHIFT);
      }
}


void poolcell_upropagate_unitmap_pool1(
  DATA_T (&inputs)[POOL1_NB_CHANNELS][POOL1_CHANNELS_HEIGHT][POOL1_CHANNELS_WIDTH],
  DATA_T (&outputs)[POOL1_NB_OUTPUTS][POOL1_OUTPUTS_HEIGHT][POOL1_OUTPUTS_WIDTH])
{

#pragma omp parallel for collapse(3)
  for (unsigned int output = 0; output < POOL1_NB_OUTPUTS; ++output)
  {
    for (unsigned int oy = 0; oy < POOL1_OUTPUTS_HEIGHT; ++oy)
    {
      for (unsigned int ox = 0; ox < POOL1_OUTPUTS_WIDTH; ++ox)
      {
        const unsigned int sxMax
          = uint_min(POOL1_CHANNELS_WIDTH - ox * POOL1_STRIDE_X, POOL1_POOL_WIDTH);
        const unsigned int syMax
          = uint_min(POOL1_CHANNELS_HEIGHT - oy * POOL1_STRIDE_Y, POOL1_POOL_HEIGHT);
        
        if (POOL1_POOLING == Max)
        {
          UDATA_T poolValue = 0;
          
          for (unsigned int sy = 0; sy < syMax; ++sy)
          {
            for (unsigned int sx = 0; sx < sxMax; ++sx)
            {
              const unsigned int ix = ox * POOL1_STRIDE_X + sx;
              const unsigned int iy = oy * POOL1_STRIDE_Y + sy;
              
              if (((UDATA_T) inputs[output][iy][ix]) > poolValue)
                poolValue = (UDATA_T) inputs[output][iy][ix];
            }
          }
          outputs[POOL1_OUTPUT_OFFSET + output][oy][ox] = poolValue;
        }
      }
    }
  }
}

void poolcell_upropagate_unitmap_pool2(
  DATA_T (&inputs)[POOL2_NB_CHANNELS][POOL2_CHANNELS_HEIGHT][POOL2_CHANNELS_WIDTH],
  DATA_T (&outputs)[POOL2_NB_OUTPUTS][POOL2_OUTPUTS_HEIGHT][POOL2_OUTPUTS_WIDTH])
{

#pragma omp parallel for collapse(3)
  for (unsigned int output = 0; output < POOL2_NB_OUTPUTS; ++output)
  {
    for (unsigned int oy = 0; oy < POOL2_OUTPUTS_HEIGHT; ++oy)
    {
      for (unsigned int ox = 0; ox < POOL2_OUTPUTS_WIDTH; ++ox)
      {
        const unsigned int sxMax
          = uint_min(POOL2_CHANNELS_WIDTH - ox * POOL2_STRIDE_X, POOL2_POOL_WIDTH);
        const unsigned int syMax
          = uint_min(POOL2_CHANNELS_HEIGHT - oy * POOL2_STRIDE_Y, POOL2_POOL_HEIGHT);
        
        if (POOL2_POOLING == Max)
        {
          UDATA_T poolValue = 0;
          
          for (unsigned int sy = 0; sy < syMax; ++sy)
          {
            for (unsigned int sx = 0; sx < sxMax; ++sx)
            {
              const unsigned int ix = ox * POOL2_STRIDE_X + sx;
              const unsigned int iy = oy * POOL2_STRIDE_Y + sy;
              
              if (((UDATA_T) inputs[output][iy][ix]) > poolValue)
                poolValue = (UDATA_T) inputs[output][iy][ix];
            }
          }
          outputs[POOL2_OUTPUT_OFFSET + output][oy][ox] = poolValue;
        }
      }
    }
  }
}

int nab_23 = 0;
void fccell_upropagate_2d(
  DATA_T (&inputs)[CONV3_NB_OUTPUTS][CONV3_OUTPUTS_HEIGHT][CONV3_OUTPUTS_WIDTH],
  DATA_T (&outputs)[FC1_NB_OUTPUTS],
  const BDATA_T (&bias)[FC1_NB_OUTPUTS],
  const WDATA_T (&weights)[FC1_NB_OUTPUTS][FC1_NB_CHANNELS])
{
  for (unsigned int output = 0; output < FC1_NB_OUTPUTS; ++output)
  {
    SUM_T weightedSum = bias[output];
    unsigned int c = 0;
    for (unsigned int channel = 0; channel < CONV3_NB_OUTPUTS; ++channel)
      for (unsigned int iy = 0; iy < CONV3_OUTPUTS_HEIGHT; ++iy)
        for (unsigned int ix = 0; ix < CONV3_OUTPUTS_WIDTH; ++ix)
        {
          SUM_T prod = truncate::ax_integer(nab_23, weights[output][c++]) * truncate::ax_integer(nab_23, ((UDATA_T) inputs[channel][iy][ix]));
          weightedSum += prod;
        }
    outputs[FC1_OUTPUT_OFFSET + output] = usat(weightedSum, FC1_ACTIVATION, FC1_SHIFT);
  }
}

int nab_24 = 0;
void fccell_upropagate(
  DATA_T (&inputs)[FC2_NB_CHANNELS],
  DATA_T (&outputs)[FC2_NB_OUTPUTS],
  const BDATA_T (&bias)[OUTPUTS_SIZE * NB_OUTPUTS],
  const WDATA_T (&weights)[OUTPUTS_SIZE * NB_OUTPUTS][FC2_NB_CHANNELS])
{
  for (unsigned int output = 0; output < OUTPUTS_SIZE * NB_OUTPUTS; ++output)
  {
    SUM_T weightedSum = bias[output];
    for (unsigned int channel = 0; channel < FC2_NB_CHANNELS; ++channel)
    {
      SUM_T prod = truncate::ax_integer(nab_24, weights[output][channel]) * truncate::ax_integer(nab_24, ((UDATA_T) inputs[channel]));
      weightedSum += prod;
    }
    outputs[FC2_OUTPUT_OFFSET + output] = usat(weightedSum, FC2_ACTIVATION, FC2_SHIFT);
  }
}


void output_max(DATA_T outputs[FC2_NB_OUTPUTS],
                uint32_t outputEstimated[1][1])
{
  if (FC2_NB_OUTPUTS > 1)
  {
    DATA_T maxVal = outputs[0];
    unsigned int outputMax = 0;
    
    for (unsigned int output = 1; output < FC2_NB_OUTPUTS; ++output)
    {
      if (outputs[output] > maxVal)
      {
        maxVal = outputs[output];
        outputMax = output;
      }
    }
    
    outputEstimated[0][0] = outputMax;
  } else
    outputEstimated[0][0] = (outputs[0] > (BINARY_THRESHOLD * DATA_T_MAX));
}

#define RESET_MEM(data)  memset(data, 0, sizeof(data))

void network(DATA_T (&in_data)[ENV_NB_OUTPUTS][ENV_SIZE_Y][ENV_SIZE_X], uint32_t (&out_data)[OUTPUTS_HEIGHT][OUTPUTS_WIDTH])
{
  DATA_T conv1_data[CONV1_NB_OUTPUTS][CONV1_OUTPUTS_HEIGHT][CONV1_OUTPUTS_WIDTH];
  DATA_T pool1_data[POOL1_NB_OUTPUTS][POOL1_OUTPUTS_HEIGHT][POOL1_OUTPUTS_WIDTH];
  DATA_T conv2_data[CONV2_NB_OUTPUTS][CONV2_OUTPUTS_HEIGHT][CONV2_OUTPUTS_WIDTH];
  DATA_T pool2_data[POOL2_NB_OUTPUTS][POOL2_OUTPUTS_HEIGHT][POOL2_OUTPUTS_WIDTH];
  DATA_T conv3_data[CONV3_NB_OUTPUTS][CONV3_OUTPUTS_HEIGHT][CONV3_OUTPUTS_WIDTH];
  DATA_T fc1_data[FC1_NB_OUTPUTS];
  DATA_T output_data[NB_OUTPUTS * OUTPUTS_HEIGHT * OUTPUTS_WIDTH];
  
  RESET_MEM(conv1_data);
  RESET_MEM(pool1_data);
  RESET_MEM(conv2_data);
  RESET_MEM(pool2_data);
  RESET_MEM(conv3_data);
  RESET_MEM(fc1_data);
  RESET_MEM(output_data);


/************************************LAYER (1)***/
  convcell_upropagate_conv1(in_data, conv1_data, conv1_biases, conv1_weights);
/************************************LAYER (2)***/
  poolcell_upropagate_unitmap_pool1(conv1_data, pool1_data);
/************************************LAYER (3)***/
  convcell_upropagate_conv2(pool1_data, conv2_data, conv2_biases, conv2_weights);
/************************************LAYER (4)***/
  poolcell_upropagate_unitmap_pool2(conv2_data, pool2_data);
/************************************LAYER (5)***/
  convcell_upropagate_conv3(pool2_data, conv3_data, conv3_biases, conv3_weights);
/************************************LAYER (6)***/
  fccell_upropagate_2d(conv3_data, fc1_data, fc1_biases, fc1_weights);
/************************************LAYER (7)***/
  fccell_upropagate(fc1_data, output_data, fc2_biases, fc2_weights);
  output_max(output_data, out_data);
}
