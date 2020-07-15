#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "network.h"
#include "c99_vla_cast_for_cpp.h"
#include "file_list.h"
#include "env_read.h"
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

	printf("Success-rate: %f, error: %lf (%lf)\n", success_rate, error, success_rate + error);

	return error;
}

extern int stride9;
extern int stride8;
extern int stride7;
extern int stride6;
extern int stride5;
extern int stride4;
extern int stride3;
extern int stride2;
extern int stride1;

#define max(actual, absolute_max) (((actual) > (absolute_max)) ? absolute_max : actual)

extern "C" double BELLERO_Reward()
{
	double reward = 0.0;

	double conv1_inner_loops = CONV1_NB_CHANNELS * 5 * 5;
	double conv2_inner_loops = CONV2_NB_CHANNELS * 5 * 5;
	double conv3_inner_loops = CONV3_NB_CHANNELS * 5 * 5;
	double conv1_outer_loops = CONV1_NB_OUTPUTS * CONV1_OY_SIZE * CONV1_OX_SIZE;
	double conv2_outer_loops = CONV2_NB_OUTPUTS * CONV2_OY_SIZE * CONV2_OX_SIZE;
	double conv3_outer_loops = CONV3_NB_OUTPUTS * CONV3_OY_SIZE * CONV3_OX_SIZE;

	int stride9_norm = max(stride9, CONV3_OX_SIZE);
	int stride8_norm = max(stride8, CONV3_OY_SIZE);
	int stride7_norm = max(stride7, CONV3_NB_OUTPUTS);
	int stride6_norm = max(stride6, CONV2_OX_SIZE);
	int stride5_norm = max(stride5, CONV2_OY_SIZE);
	int stride4_norm = max(stride4, CONV2_NB_OUTPUTS);
	int stride3_norm = max(stride3, CONV1_OX_SIZE);
	int stride2_norm = max(stride2, CONV1_OY_SIZE);
	int stride1_norm = max(stride1, CONV1_NB_OUTPUTS);

	double conv1_skipped_loops = stride1_norm * stride2_norm * stride3_norm;
	double conv2_skipped_loops = stride4_norm * stride5_norm * stride6_norm;
	double conv3_skipped_loops = stride7_norm * stride8_norm * stride9_norm;

	double total_loops = conv1_inner_loops * conv1_outer_loops + 
						 conv2_inner_loops * conv2_outer_loops + 
						 conv3_inner_loops * conv3_outer_loops;

	double skipped_loops =  conv1_skipped_loops * conv1_inner_loops + 
						 	conv2_skipped_loops * conv2_inner_loops + 
						 	conv3_skipped_loops * conv3_inner_loops;

	reward = skipped_loops / total_loops;

	printf("Strides: [%d, %d, %d, %d, %d, %d %d, %d, %d]\n", stride1_norm, stride2_norm, stride3_norm, stride4_norm, stride5_norm, stride6_norm, stride7_norm, stride8_norm, stride9_norm);
	printf("Conv1 (total, skipped): %lf, %lf\n",  conv1_inner_loops * conv1_outer_loops, conv1_skipped_loops * conv1_outer_loops);
	printf("Conv2 (total, skipped): %lf, %lf\n",  conv2_inner_loops * conv2_outer_loops, conv2_skipped_loops * conv2_outer_loops);
	printf("Conv3 (total, skipped): %lf, %lf\n",  conv3_inner_loops * conv3_outer_loops, conv3_skipped_loops * conv3_outer_loops);
	printf("Total loops: %lf\n", total_loops);
	printf("Skipped loops: %lf\n", skipped_loops);
	printf("Reward: %lf\n", reward);

	return reward;
}
