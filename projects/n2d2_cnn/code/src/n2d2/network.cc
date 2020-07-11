#include "network.h"


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
