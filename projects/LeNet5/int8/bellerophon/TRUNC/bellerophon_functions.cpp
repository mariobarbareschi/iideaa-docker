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
	FILE *oracle_file = fopen("/root/projects/LeNet5/int8/bellerophon/success_rate.txt", "r");
	if (oracle_file == NULL)
	{
		printf("Error opening success_rate.txt file!\n");
		exit(1);
	}
	float original_success_rate = 0;
	fscanf(oracle_file, "%f", &original_success_rate);

	// Getting the set of stimuli, 
	char** stimuli_list;
	unsigned int total_stimuli = sortedFileList("/root/projects/LeNet5/int8/code/stimuli", &stimuli_list, 0);

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

extern int nab_9;
extern int nab_8;
extern int nab_7;
extern int nab_6;
extern int nab_5;
extern int nab_4;
extern int nab_3;
extern int nab_2;
extern int nab_1;
extern int nab_0;

extern "C" double BELLERO_Reward()
{
  long int conv1_num_neurons = CONV1_OUTPUTS_WIDTH * CONV1_OUTPUTS_HEIGHT * CONV1_NB_OUTPUTS;
  long int conv2_num_neurons = CONV2_OUTPUTS_WIDTH * CONV2_OUTPUTS_HEIGHT * CONV2_NB_OUTPUTS;
  long int conv3_num_neurons = CONV3_OUTPUTS_WIDTH * CONV3_OUTPUTS_HEIGHT * CONV2_NB_OUTPUTS;
  long int full1_num_neurons = FC1_NB_OUTPUTS;
  long int full2_num_neurons = FC2_NB_OUTPUTS;
  long int conv1_num_operations = CONV1_KERNEL_HEIGHT * CONV1_KERNEL_WIDTH * conv1_num_neurons;
  long int conv2_num_operations = CONV2_KERNEL_HEIGHT * CONV2_KERNEL_WIDTH * conv2_num_neurons;
  long int conv3_num_operations = CONV3_KERNEL_HEIGHT * CONV3_KERNEL_WIDTH * conv3_num_neurons;
  long int full1_num_operations = FC1_NB_CHANNELS * full1_num_neurons;
  long int full2_num_operations = FC2_NB_OUTPUTS * full2_num_neurons;
  
  long int data_length = 64;
  double total_bits =  2 * data_length * (  conv1_num_operations +
                                            conv2_num_operations +
                                            conv3_num_operations +
                                            full1_num_operations +
                                            full2_num_operations);
  
  double saved_bits =  // prod                         sum
                       nab_0 * conv1_num_operations  + nab_1 * conv1_num_operations +
                       nab_2 * conv2_num_operations  + nab_3 * conv2_num_operations +
                       nab_4 * conv3_num_operations  + nab_5 * conv3_num_operations +
                       nab_6 * full1_num_operations  + nab_7 * full1_num_operations +
                       nab_8 * full2_num_operations  + nab_9 * full2_num_operations;
  
  double reward = saved_bits / total_bits;
  printf("Reward %lf / %lf = %lf\n", saved_bits, total_bits, reward);
  
	return reward;
}
