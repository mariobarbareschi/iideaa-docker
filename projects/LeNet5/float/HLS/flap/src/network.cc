#include "network.h"
#include "fap.h"
#include "env.h"
#include "utils.h"
#include <math.h>


#define ADD_SAT(x, y) ((x) + (y))

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



::fap::FloatPrecTy OP_1(8,23);
::fap::FloatPrecTy OP_0(8,23);
void convcell_propagate_conv1(
     DATA_T (&inputs)[CONV1_NB_CHANNELS][CONV1_CHANNELS_HEIGHT][CONV1_CHANNELS_WIDTH],
     DATA_T (&outputs)[CONV1_NB_OUTPUTS][CONV1_OUTPUTS_HEIGHT][CONV1_OUTPUTS_WIDTH],
     BDATA_T (&bias)[CONV1_NB_OUTPUTS],
     WDATA_T (&weights)[CONV1_NB_OUTPUTS][CONV1_NB_CHANNELS][CONV1_KERNEL_HEIGHT][CONV1_KERNEL_WIDTH])
{

	
	for (unsigned int output = 0; output < CONV1_NB_OUTPUTS; ++output) { 
		for (unsigned int oy = 0; oy < CONV1_OY_SIZE; ++oy) { 
			for (unsigned int ox = 0; ox < CONV1_OX_SIZE; ++ox) { 
				const unsigned int sxMin = (unsigned int)int_max( (int)CONV1_PADDING_X - (int)(ox * CONV1_STRIDE_X), 0); 
				const unsigned int syMin = (unsigned int)int_max( (int)CONV1_PADDING_Y - (int)(oy * CONV1_STRIDE_Y), 0); 
				const unsigned int sxMax = (unsigned int)int_max( int_min((int)CONV1_CHANNELS_WIDTH + CONV1_PADDING_X - (int)(ox * CONV1_STRIDE_X), (int)5), 0); 
				const unsigned int syMax = (unsigned int)int_max( int_min((int)CONV1_CHANNELS_HEIGHT + CONV1_PADDING_Y - (int)(oy * CONV1_STRIDE_Y), (int)5), 0); 
				const int ix = (int)(ox * CONV1_STRIDE_X) - (int)CONV1_PADDING_X; 
				const int iy = (int)(oy * CONV1_STRIDE_Y) - (int)CONV1_PADDING_Y; 
				SUM_T weightedSum = bias[output]; 
				for (unsigned int channel = 0; channel < CONV1_NB_CHANNELS; ++channel) { 
					#pragma unroll 5
					for (unsigned int sy = 0; sy < 5; ++sy) {
						#pragma unroll 5
						for (unsigned int sx = 0; sx < 5; ++sx) { 
							if (sx >= sxMin && sx < sxMax && sy >= syMin && sy < syMax) { 
								weightedSum = ((float)(::fap::FloatingPointType((float) (weightedSum), OP_0)) + ((SUM_T)(float)(::fap::FloatingPointType((float) weights[output][channel][sy][sx], OP_1)) * (SUM_T)(float)(::fap::FloatingPointType((float) ( (DATA_T) inputs[channel][iy + sy][ix + sx]), OP_1)))); 
							} 
						} 
					} 
				} 
				outputs[CONV1_OUTPUT_OFFSET + output][oy][ox] = sat(weightedSum, CONV1_ACTIVATION); 
			} 
		} 
	} 
}


void poolcell_propagate_pool1(
    DATA_T (&inputs)[POOL1_NB_CHANNELS][POOL1_CHANNELS_HEIGHT][POOL1_CHANNELS_WIDTH],
    DATA_T (&outputs)[POOL1_NB_OUTPUTS][POOL1_OUTPUTS_HEIGHT][POOL1_OUTPUTS_WIDTH])
{
	
    for (unsigned int output = 0; output < POOL1_NB_OUTPUTS; ++output) {
        for (unsigned int oy = 0; oy < POOL1_OUTPUTS_HEIGHT; ++oy) {
            for (unsigned int ox = 0; ox < POOL1_OUTPUTS_WIDTH; ++ox) {
                const unsigned int sxMax
                    = uint_min(POOL1_CHANNELS_WIDTH - ox * POOL1_STRIDE_X, POOL1_POOL_WIDTH);
                const unsigned int syMax
                    = uint_min(POOL1_CHANNELS_HEIGHT - oy * POOL1_STRIDE_Y, POOL1_POOL_HEIGHT);

                if (POOL1_POOLING == Max) {
                    DATA_T poolValue = DATA_T_MIN;

                    for (unsigned int sy = 0; sy < syMax; ++sy) {
                        for (unsigned int sx = 0; sx < sxMax; ++sx) {
                            const unsigned int ix = ox * POOL1_STRIDE_X + sx;
                            const unsigned int iy = oy * POOL1_STRIDE_Y + sy;

                            if (inputs[output][iy][ix] > poolValue)
                                poolValue = inputs[output][iy][ix];
                        }
                    }
                    outputs[POOL1_OUTPUT_OFFSET + output][oy][ox] = sat(poolValue, POOL1_ACTIVATION);
                } else if (POOL1_POOLING == Average) {
                    SUM_T sum = 0;

                    for (unsigned int sy = 0; sy < syMax; ++sy) {
                        for (unsigned int sx = 0; sx < sxMax; ++sx) {
                            const unsigned int ix = ox * POOL1_STRIDE_X + sx;
                            const unsigned int iy = oy * POOL1_STRIDE_Y + sy;
                            sum += inputs[output][iy][ix];
                        }
                    }
                    sum /= POOL1_POOL_WIDTH * POOL1_POOL_HEIGHT;
                    outputs[POOL1_OUTPUT_OFFSET + output][oy][ox] = sat(sum, POOL1_ACTIVATION);
                }
            }
        }
    }
}

::fap::FloatPrecTy OP_3(8,23);
::fap::FloatPrecTy OP_2(8,23);
void convcell_propagate_conv2(
    DATA_T (&inputs)[CONV2_NB_CHANNELS][CONV2_CHANNELS_HEIGHT][CONV2_CHANNELS_WIDTH],
    DATA_T (&outputs)[CONV2_NB_OUTPUTS][CONV2_OUTPUTS_HEIGHT][CONV2_OUTPUTS_WIDTH],
    BDATA_T (&bias)[CONV2_NB_OUTPUTS],
    WDATA_T (&weights)[CONV2_NB_OUTPUTS][CONV2_NB_CHANNELS][CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH])
{

	
	for (unsigned int output = 0; output < CONV2_NB_OUTPUTS; ++output) { 
		for (unsigned int oy = 0; oy < CONV2_OY_SIZE; ++oy) { 
			for (unsigned int ox = 0; ox < CONV2_OX_SIZE; ++ox) { 
				const unsigned int sxMin = (unsigned int)int_max( (int)CONV2_PADDING_X - (int)(ox * CONV2_STRIDE_X), 0); 
				const unsigned int syMin = (unsigned int)int_max( (int)CONV2_PADDING_Y - (int)(oy * CONV2_STRIDE_Y), 0); 
				const unsigned int sxMax = (unsigned int)int_max( int_min((int)CONV2_CHANNELS_WIDTH + CONV2_PADDING_X - (int)(ox * CONV2_STRIDE_X), (int)5), 0); 
				const unsigned int syMax = (unsigned int)int_max( int_min((int)CONV2_CHANNELS_HEIGHT + CONV2_PADDING_Y - (int)(oy * CONV2_STRIDE_Y), (int)5), 0); 
				const int ix = (int)(ox * CONV2_STRIDE_X) - (int)CONV2_PADDING_X; 
				const int iy = (int)(oy * CONV2_STRIDE_Y) - (int)CONV2_PADDING_Y; 
				SUM_T weightedSum = bias[output]; 
				for (unsigned int channel = 0; channel < CONV2_NB_CHANNELS; ++channel) { 
					#pragma unroll 5
					for (unsigned int sy = 0; sy < 5; ++sy) {
						#pragma unroll 5
						for (unsigned int sx = 0; sx < 5; ++sx) { 
							if (sx >= sxMin && sx < sxMax && sy >= syMin && sy < syMax) { 
								weightedSum = ((float)(::fap::FloatingPointType((float) (weightedSum), OP_2)) + ((SUM_T)(float)(::fap::FloatingPointType((float) weights[output][channel][sy][sx], OP_3)) * (SUM_T)(float)(::fap::FloatingPointType((float) ( (DATA_T) inputs[channel][iy + sy][ix + sx]), OP_3)))); 
							} 
						} 
					} 
				} 
				outputs[CONV2_OUTPUT_OFFSET + output][oy][ox] = sat(weightedSum, CONV2_ACTIVATION); 
			} 
		} 
	} 
}

void poolcell_propagate_pool2(
    DATA_T (&inputs)[POOL2_NB_CHANNELS][POOL2_CHANNELS_HEIGHT][POOL2_CHANNELS_WIDTH],
    DATA_T (&outputs)[POOL2_NB_OUTPUTS][POOL2_OUTPUTS_HEIGHT][POOL2_OUTPUTS_WIDTH])
{
	
    for (unsigned int output = 0; output < POOL2_NB_OUTPUTS; ++output) {
        for (unsigned int oy = 0; oy < POOL2_OUTPUTS_HEIGHT; ++oy) {
            for (unsigned int ox = 0; ox < POOL2_OUTPUTS_WIDTH; ++ox) {
                const unsigned int sxMax
                    = uint_min(POOL2_CHANNELS_WIDTH - ox * POOL2_STRIDE_X, POOL2_POOL_WIDTH);
                const unsigned int syMax
                    = uint_min(POOL2_CHANNELS_HEIGHT - oy * POOL2_STRIDE_Y, POOL2_POOL_HEIGHT);

                if (POOL2_POOLING == Max) {
                    DATA_T poolValue = DATA_T_MIN;

                    for (unsigned int sy = 0; sy < syMax; ++sy) {
                        for (unsigned int sx = 0; sx < sxMax; ++sx) {
                            const unsigned int ix = ox * POOL2_STRIDE_X + sx;
                            const unsigned int iy = oy * POOL2_STRIDE_Y + sy;

                            if (inputs[output][iy][ix] > poolValue)
                                poolValue = inputs[output][iy][ix];
                        }
                    }
                    outputs[POOL2_OUTPUT_OFFSET + output][oy][ox] = sat(poolValue, POOL2_ACTIVATION);
                } else if (POOL2_POOLING == Average) {
                    SUM_T sum = 0;

                    for (unsigned int sy = 0; sy < syMax; ++sy) {
                        for (unsigned int sx = 0; sx < sxMax; ++sx) {
                            const unsigned int ix = ox * POOL2_STRIDE_X + sx;
                            const unsigned int iy = oy * POOL2_STRIDE_Y + sy;
                            sum += inputs[output][iy][ix];
                        }
                    }
                    sum /= POOL2_POOL_WIDTH * POOL2_POOL_HEIGHT;
                    outputs[POOL2_OUTPUT_OFFSET + output][oy][ox] = sat(sum, POOL2_ACTIVATION);
                }
            }
        }
    }
}



::fap::FloatPrecTy OP_5(8,23);
::fap::FloatPrecTy OP_4(8,23);
void convcell_propagate_conv3(
    DATA_T (&inputs)[CONV3_NB_CHANNELS][CONV3_CHANNELS_HEIGHT][CONV3_CHANNELS_WIDTH],
    DATA_T (&outputs)[CONV3_NB_OUTPUTS][CONV3_OUTPUTS_HEIGHT][CONV3_OUTPUTS_WIDTH],
    BDATA_T (&bias)[CONV3_NB_OUTPUTS],
    WDATA_T (&weights)[CONV3_NB_OUTPUTS][CONV3_NB_CHANNELS][CONV3_KERNEL_HEIGHT][CONV3_KERNEL_WIDTH])
{

	
	for (unsigned int output = 0; output < CONV3_NB_OUTPUTS; ++output) { 
		for (unsigned int oy = 0; oy < CONV3_OY_SIZE; ++oy) { 
			for (unsigned int ox = 0; ox < CONV3_OX_SIZE; ++ox) { 
				const unsigned int sxMin = (unsigned int)int_max( (int)CONV3_PADDING_X - (int)(ox * CONV3_STRIDE_X), 0); 
				const unsigned int syMin = (unsigned int)int_max( (int)CONV3_PADDING_Y - (int)(oy * CONV3_STRIDE_Y), 0); 
				const unsigned int sxMax = (unsigned int)int_max( int_min((int)CONV3_CHANNELS_WIDTH + CONV3_PADDING_X - (int)(ox * CONV3_STRIDE_X), (int)5), 0); 
				const unsigned int syMax = (unsigned int)int_max( int_min((int)CONV3_CHANNELS_HEIGHT + CONV3_PADDING_Y - (int)(oy * CONV3_STRIDE_Y), (int)5), 0); 
				const int ix = (int)(ox * CONV3_STRIDE_X) - (int)CONV3_PADDING_X; 
				const int iy = (int)(oy * CONV3_STRIDE_Y) - (int)CONV3_PADDING_Y; 
				SUM_T weightedSum = bias[output]; 
				for (unsigned int channel = 0; channel < CONV3_NB_CHANNELS; ++channel) { 
					#pragma unroll 5
					for (unsigned int sy = 0; sy < 5; ++sy) {
						#pragma unroll 5
						for (unsigned int sx = 0; sx < 5; ++sx) { 
							if (sx >= sxMin && sx < sxMax && sy >= syMin && sy < syMax) { 
								weightedSum = ((float)(::fap::FloatingPointType((float) (weightedSum), OP_4)) + ((SUM_T)(float)(::fap::FloatingPointType((float) weights[output][channel][sy][sx], OP_5)) * (SUM_T)(float)(::fap::FloatingPointType((float) ( (DATA_T) inputs[channel][iy + sy][ix + sx]), OP_5)))); 
							} 
						} 
					} 
				} 
				outputs[CONV3_OUTPUT_OFFSET + output][oy][ox] = sat(weightedSum, CONV3_ACTIVATION); 
			} 
		} 
	} 
}




::fap::FloatPrecTy OP_7(8,23);
::fap::FloatPrecTy OP_6(8,23);
void fccell_propagate_2d(
                    DATA_T (&inputs)[CONV3_NB_OUTPUTS][CONV3_OUTPUTS_HEIGHT][CONV3_OUTPUTS_WIDTH],
                    DATA_T (&outputs)[FC1_NB_OUTPUTS],
                    BDATA_T (&bias)[FC1_NB_OUTPUTS],
                    WDATA_T (&weights)[FC1_NB_OUTPUTS][FC1_NB_CHANNELS])
{

	
    for (unsigned int output = 0; output < FC1_NB_OUTPUTS; ++output) {
        SUM_T weightedSum = bias[output];
        unsigned int c = 0;

        for (unsigned int channel = 0; channel < CONV3_NB_OUTPUTS; ++channel) {
            for (unsigned int iy = 0; iy < CONV3_OUTPUTS_HEIGHT; ++iy) {
				for (unsigned int ix = 0; ix < CONV3_OUTPUTS_WIDTH; ++ix)
                    weightedSum = (float)(::fap::FloatingPointType((float) weightedSum, OP_6)) + (float)(::fap::FloatingPointType((float) weights[output][c++], OP_7)) * (float)(::fap::FloatingPointType((float) inputs[channel][iy][ix], OP_7));
            }
        }

        outputs[FC1_OUTPUT_OFFSET + output] = sat(weightedSum, FC1_ACTIVATION);
    }
}

::fap::FloatPrecTy OP_9(8,23);
::fap::FloatPrecTy OP_8(8,23);
void fccell_propagate(
	DATA_T (&inputs)[FC2_NB_CHANNELS],
	DATA_T (&outputs)[OUTPUTS_SIZE*NB_OUTPUTS],
	BDATA_T (&bias)[FC2_NB_OUTPUTS],
	WDATA_T (&weights)[FC2_NB_OUTPUTS][FC2_NB_CHANNELS])
{
	 if (FC2_NB_OUTPUTS > 32)
    for (unsigned int output = 0; output < FC2_NB_OUTPUTS; ++output) {
        SUM_T weightedSum = bias[output];

        for (unsigned int channel = 0; channel < FC2_NB_CHANNELS; ++channel)
            weightedSum = (float)(::fap::FloatingPointType((float) weightedSum, OP_8)) + (float)(::fap::FloatingPointType((float) weights[output][channel], OP_9)) * (float)(::fap::FloatingPointType((float) inputs[channel], OP_9));

        outputs[FC2_OUTPUT_OFFSET + output] = sat(weightedSum, FC2_ACTIVATION);
    }
}

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



void network(
		DATA_T (&in_data)[CONV1_NB_CHANNELS][CONV1_CHANNELS_HEIGHT][CONV1_CHANNELS_WIDTH],
		uint32_t (&out_data)[OUTPUTS_HEIGHT][OUTPUTS_WIDTH])
{
	DATA_T conv1_data[CONV1_NB_OUTPUTS][CONV1_OUTPUTS_HEIGHT][CONV1_OUTPUTS_WIDTH];
	DATA_T pool1_data[POOL1_NB_OUTPUTS][POOL1_OUTPUTS_HEIGHT][POOL1_OUTPUTS_WIDTH];
	DATA_T conv2_data[CONV2_NB_OUTPUTS][CONV2_OUTPUTS_HEIGHT][CONV2_OUTPUTS_WIDTH];
	DATA_T pool2_data[POOL2_NB_OUTPUTS][POOL2_OUTPUTS_HEIGHT][POOL2_OUTPUTS_WIDTH];
	DATA_T conv3_data[CONV3_NB_OUTPUTS][CONV3_OUTPUTS_HEIGHT][CONV3_OUTPUTS_WIDTH];
	DATA_T fc1_data[FC1_NB_OUTPUTS];
	DATA_T output_data[NB_OUTPUTS*OUTPUTS_HEIGHT*OUTPUTS_WIDTH]; 

    convcell_propagate_conv1(in_data, conv1_data, conv1_biases, conv1_weights);
    poolcell_propagate_pool1(conv1_data, pool1_data);
    convcell_propagate_conv2(pool1_data, conv2_data, conv2_biases, conv2_weights);
	poolcell_propagate_pool2(conv2_data, pool2_data);
    convcell_propagate_conv3(pool2_data, conv3_data, conv3_biases, conv3_weights);
    fccell_propagate_2d(conv3_data, fc1_data, fc1_biases, fc1_weights);
    fccell_propagate(fc1_data, output_data, fc2_biases, fc2_weights);
    output_max(output_data, out_data);
}
