#warning "Compiling network.cc"
#include "network.h"

static DATA_T conv1_data[CONV1_NB_OUTPUTS][CONV1_OUTPUTS_HEIGHT][CONV1_OUTPUTS_WIDTH];
static DATA_T pool1_data[POOL1_NB_OUTPUTS][POOL1_OUTPUTS_HEIGHT][POOL1_OUTPUTS_WIDTH];
static DATA_T conv2_data[CONV2_NB_OUTPUTS][CONV2_OUTPUTS_HEIGHT][CONV2_OUTPUTS_WIDTH];
static DATA_T pool2_data[POOL2_NB_OUTPUTS][POOL2_OUTPUTS_HEIGHT][POOL2_OUTPUTS_WIDTH];
static DATA_T conv3_data[CONV3_NB_OUTPUTS][CONV3_OUTPUTS_HEIGHT][CONV3_OUTPUTS_WIDTH];
static DATA_T fc1_data[FC1_NB_OUTPUTS];
DATA_T output_data[NB_OUTPUTS*OUTPUTS_HEIGHT*OUTPUTS_WIDTH]; 
static DATA_T output_spatial_data[NB_OUTPUTS][OUTPUTS_HEIGHT][OUTPUTS_WIDTH]; 

void network(DATA_T * in_data, uint32_t * out_data) 
{
    convcell_propagate_conv1(CONV1_NB_CHANNELS, CONV1_CHANNELS_HEIGHT, CONV1_CHANNELS_WIDTH, CONV1_PADDING_Y, CONV1_PADDING_X, CONV1_STRIDE_Y, CONV1_STRIDE_X, in_data, CONV1_OY_SIZE, CONV1_OX_SIZE, CONV1_NB_OUTPUTS, CONV1_OUTPUTS_HEIGHT, CONV1_OUTPUTS_WIDTH, CONV1_NB_OUTPUTS, CONV1_OUTPUT_OFFSET, reinterpret_cast<DATA_T*>(conv1_data), reinterpret_cast<BDATA_T*>(conv1_biases), reinterpret_cast<WDATA_T*>(conv1_weights), CONV1_ACTIVATION, CONV1_SHIFT);
    poolcell_propagate_unitmap(POOL1_NB_CHANNELS, POOL1_CHANNELS_HEIGHT, POOL1_CHANNELS_WIDTH, POOL1_STRIDE_Y, POOL1_STRIDE_X, reinterpret_cast<DATA_T*>(conv1_data), POOL1_NB_OUTPUTS, POOL1_OUTPUTS_HEIGHT, POOL1_OUTPUTS_WIDTH, POOL1_NB_OUTPUTS, POOL1_OUTPUT_OFFSET, reinterpret_cast<DATA_T*>(pool1_data), POOL1_POOL_HEIGHT, POOL1_POOL_WIDTH, POOL1_POOLING, POOL1_ACTIVATION, POOL1_SHIFT);
    convcell_propagate_conv2(CONV2_NB_CHANNELS, CONV2_CHANNELS_HEIGHT, CONV2_CHANNELS_WIDTH, CONV2_PADDING_Y, CONV2_PADDING_X, CONV2_STRIDE_Y, CONV2_STRIDE_X, reinterpret_cast<DATA_T*>(pool1_data), CONV2_OY_SIZE, CONV2_OX_SIZE, CONV2_NB_OUTPUTS, CONV2_OUTPUTS_HEIGHT, CONV2_OUTPUTS_WIDTH, CONV2_NB_OUTPUTS, CONV2_OUTPUT_OFFSET, reinterpret_cast<DATA_T*>(conv2_data), reinterpret_cast<BDATA_T*>(conv2_biases), reinterpret_cast<WDATA_T*>(conv2_weights), CONV2_ACTIVATION, CONV2_SHIFT);
    poolcell_propagate_unitmap(POOL2_NB_CHANNELS, POOL2_CHANNELS_HEIGHT, POOL2_CHANNELS_WIDTH, POOL2_STRIDE_Y, POOL2_STRIDE_X, reinterpret_cast<DATA_T*>(conv2_data), POOL2_NB_OUTPUTS, POOL2_OUTPUTS_HEIGHT, POOL2_OUTPUTS_WIDTH, POOL2_NB_OUTPUTS, POOL2_OUTPUT_OFFSET, reinterpret_cast<DATA_T*>(pool2_data), POOL2_POOL_HEIGHT, POOL2_POOL_WIDTH, POOL2_POOLING, POOL2_ACTIVATION, POOL2_SHIFT);
    convcell_propagate_conv3(CONV3_NB_CHANNELS, CONV3_CHANNELS_HEIGHT, CONV3_CHANNELS_WIDTH, CONV3_PADDING_Y, CONV3_PADDING_X, CONV3_STRIDE_Y, CONV3_STRIDE_X, reinterpret_cast<DATA_T*>(pool2_data), CONV3_OY_SIZE, CONV3_OX_SIZE, CONV3_NB_OUTPUTS, CONV3_OUTPUTS_HEIGHT, CONV3_OUTPUTS_WIDTH, CONV3_NB_OUTPUTS, CONV3_OUTPUT_OFFSET, reinterpret_cast<DATA_T*>(conv3_data), reinterpret_cast<BDATA_T*>(conv3_biases), reinterpret_cast<WDATA_T*>(conv3_weights), CONV3_ACTIVATION, CONV3_SHIFT);
    fccell_propagate_2d(CONV3_NB_OUTPUTS, CONV3_OUTPUTS_HEIGHT, CONV3_OUTPUTS_WIDTH, reinterpret_cast<DATA_T*>(conv3_data), FC1_NB_OUTPUTS, FC1_NB_OUTPUTS, FC1_OUTPUT_OFFSET, reinterpret_cast<DATA_T*>(fc1_data), FC1_NB_CHANNELS, reinterpret_cast<WDATA_T*>(fc1_biases), reinterpret_cast<WDATA_T*>(fc1_weights), FC1_ACTIVATION, FC1_SHIFT);
    fccell_propagate(FC2_NB_CHANNELS, reinterpret_cast<DATA_T*>(fc1_data), OUTPUTS_SIZE*NB_OUTPUTS, FC2_NB_OUTPUTS, FC2_OUTPUT_OFFSET, reinterpret_cast<DATA_T*>(output_data), reinterpret_cast<BDATA_T*>(fc2_biases), reinterpret_cast<WDATA_T*>(fc2_weights), FC2_ACTIVATION, FC2_SHIFT);
    output_max(FC2_NB_OUTPUTS, output_data, out_data);
}
