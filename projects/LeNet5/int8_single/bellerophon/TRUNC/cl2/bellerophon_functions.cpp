#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "file_list.h"
#include "env_read.h"
#include "network.h"
#include "trunc.h"

#include<iostream>
#include<fstream>
#include <math.h>


extern "C" double BELLERO_getError() {    
	omp_set_num_threads(8);

	// Getting the success-rate of the original CNN
	FILE *oracle_file = fopen("/root/projects/LeNet5/int8_mul/bellerophon/success_rate.txt", "r");
	if (oracle_file == NULL)
	{
		printf("Error opening success_rate.txt file!\n");
		exit(1);
	}
	float original_success_rate = 0;
	fscanf(oracle_file, "%f", &original_success_rate);

	// Getting the set of stimuli, 
	char** stimuli_list;
	unsigned int total_stimuli = sortedFileList("/root/projects/LeNet5/int8_mul/code/stimuli", &stimuli_list, 0);

	DATA_T env_data[ENV_NB_CHANNELS][ENV_NB_HEIGHT][ENV_NB_WIDTH];
	uint32_t outputEstimated[OUTPUTS_HEIGHT][OUTPUTS_WIDTH];
    int32_t outputTargets[ENV_NB_OUTPUTS_HEIGHT][ENV_NB_OUTPUTS_WIDTH];
	
	float success = 0;

	for (unsigned int n = 0; n < total_stimuli; n++) {
		env_read(stimuli_list[n], env_data, outputTargets);
		network(env_data, outputEstimated);

		unsigned int nbValidPredictions = 0;
		unsigned int nbPredictions = 0;

		for (unsigned int oy = 0; oy < OUTPUTS_HEIGHT; ++oy) {
			for (unsigned int ox = 0; ox < OUTPUTS_WIDTH; ++ox) {

				int iy = oy;
				int ix = ox;

					nbPredictions++;
					if (outputTargets[iy][ix] == (int)outputEstimated[oy][ox]) 
						nbValidPredictions++;

			}
		}

		success += (nbPredictions > 0) ? ((float) nbValidPredictions / nbPredictions) : 1.0;

		free(stimuli_list[n]);
	}

	free(stimuli_list);

	float success_rate = 100.0 * success / (float) total_stimuli;
	double error = original_success_rate - success_rate;

	printf("Success-rate: %f, error: %lf\n", success_rate, error);

	return error;
}

extern int nab_0;

extern "C" double BELLERO_Reward()
{
  const int layers = 5;
  long input_volumes[layers] = {
    CONV1_NB_CHANNELS * CONV1_KERNEL_HEIGHT * CONV1_KERNEL_WIDTH,
    CONV2_NB_CHANNELS * CONV2_KERNEL_HEIGHT * CONV2_KERNEL_WIDTH,
    CONV3_NB_CHANNELS * CONV3_KERNEL_HEIGHT * CONV3_KERNEL_WIDTH,
    CONV3_NB_OUTPUTS * CONV3_OUTPUTS_HEIGHT * CONV3_OUTPUTS_WIDTH,
    FC2_NB_CHANNELS};
  long output_volumes[layers] = {
    CONV1_OUTPUTS_WIDTH * CONV1_OUTPUTS_HEIGHT * CONV1_NB_OUTPUTS,
    CONV2_OUTPUTS_WIDTH * CONV2_OUTPUTS_HEIGHT * CONV2_NB_OUTPUTS,
    CONV3_OUTPUTS_WIDTH * CONV3_OUTPUTS_HEIGHT * CONV2_NB_OUTPUTS,
    FC1_NB_OUTPUTS,
    FC2_NB_OUTPUTS};
  long nab_mul[layers] = {nab_0, nab_0, nab_0, nab_0, nab_0};

  int i = 1; // approx. layer index

  double saved_bits = 0, total_bits = 0;
  saved_bits += nab_mul[i] * input_volumes[i] * output_volumes[i];
  total_bits += input_volumes[i] * output_volumes[i];
  total_bits *= NB_BITS;
  
  double reward = saved_bits / total_bits;
  printf("Reward %lf / %lf = %lf\n", saved_bits, total_bits, reward);
  
	return reward;
}
