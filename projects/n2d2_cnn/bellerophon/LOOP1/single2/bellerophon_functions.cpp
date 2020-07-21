#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "file_list.h"
#include "env_read.h"
#include "network.h"
#include "c99_vla_cast_for_cpp.h"

#include<iostream>
#include<fstream>
#include <math.h>


const char * stimuli_directory = "/root/projects/n2d2_cnn/code/stimuli";

extern "C" double BELLERO_getError() {    
	omp_set_num_threads(8);

	// Getting the success-rate of the original CNN
	FILE *oracle_file = fopen("/root/projects/n2d2_cnn/bellerophon/success_rate.txt", "r");
	if (oracle_file == NULL)
	{
		printf("Error opening success_rate.txt file!\n");
		exit(1);
	}
	float original_success_rate = 0;
	fscanf(oracle_file, "%f", &original_success_rate);

	// Getting the set of stimuli, 
	char** stimuli_list;
	unsigned int total_stimuli = sortedFileList(stimuli_directory, &stimuli_list, 0);

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

extern int stride3;
extern int stride2;
extern int stride1;

#define max(actual, absolute_max) (((actual) > (absolute_max)) ? absolute_max : actual)
#define min(actual, absolute_min) (((actual) < (absolute_min)) ? absolute_min : actual)


extern "C" double BELLERO_Reward()
{
	double reward = 0.0;
	int stride3_norm = max(stride3, 5);
	int stride2_norm = max(stride2, 5);
	int stride1_norm = max(stride1, 5);
  stride1_norm = min(stride1_norm, 1);
  stride2_norm = min(stride2_norm, 1);
  stride3_norm = min(stride3_norm, 1);

	double conv1_inner_loops = CONV1_NB_CHANNELS * 5 * 5;
	double conv2_inner_loops = CONV2_NB_CHANNELS * 5 * 5;
	double conv3_inner_loops = CONV3_NB_CHANNELS * 5 * 5;
	double conv1_outer_loops = CONV1_NB_OUTPUTS * CONV1_OY_SIZE * CONV1_OX_SIZE;
	double conv2_outer_loops = CONV2_NB_OUTPUTS * CONV2_OY_SIZE * CONV2_OX_SIZE;
	double conv3_outer_loops = CONV3_NB_OUTPUTS * CONV3_OY_SIZE * CONV3_OX_SIZE;
	double total_loops = conv1_inner_loops * conv1_outer_loops + conv2_inner_loops * conv2_outer_loops + conv3_inner_loops * conv3_outer_loops;
  
  double conv1_skipped_loops = 5 * (stride1_norm - 1) / stride1_norm;
  double conv2_skipped_loops = 5 * (stride2_norm - 1) / stride2_norm;
  double conv3_skipped_loops = 5 * (stride3_norm - 1) / stride3_norm;
  double skipped_loops = conv1_skipped_loops + conv2_skipped_loops + conv3_skipped_loops;

	reward = skipped_loops / total_loops;

	printf("Strides: [%d, %d, %d]\n", stride1_norm, stride2_norm, stride3_norm);
	printf("Reward: %lf\n", reward);

	return reward;
}
