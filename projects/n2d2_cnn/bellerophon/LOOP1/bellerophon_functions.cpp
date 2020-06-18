#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "network.h"
#include "c99_vla_cast_for_cpp.h"

#include<iostream>
#include<fstream>
#include <math.h>


const char * stimuli_directory = "/root/projects/n2d2_cnn/code/stimuli";

extern "C" double BELLERO_getError() {    
	omp_set_num_threads(8);

	// Getting the success-rate of the original CNN
	FILE *oracle_file = fopen("/root/projects/n2d2_cnn/bellerophon/VPA/success_rate.txt", "r");
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

    unsigned int dimX = 1;
    unsigned int dimY = 1;
    if (OUTPUTS_WIDTH > 1 || OUTPUTS_HEIGHT > 1) {
        dimX = ENV_SIZE_X;
        dimY = ENV_SIZE_Y;
    }
    double yRatio = ENV_SIZE_Y / OUTPUTS_HEIGHT;
    double xRatio = ENV_SIZE_X / OUTPUTS_WIDTH;

	DATA_T env_data[ENV_NB_OUTPUTS][ENV_SIZE_Y][ENV_SIZE_X];
	uint32_t outputEstimated[OUTPUTS_HEIGHT][OUTPUTS_WIDTH];
    int32_t outputTargets[dimY][dimX];
	
	float success = 0;

	for (unsigned int n = 0; n < total_stimuli; n++) {
		env_read(stimuli_list[n], ENV_NB_OUTPUTS, ENV_SIZE_Y, ENV_SIZE_X, reinterpret_cast<DATA_T*>(env_data),  dimY,  dimX, reinterpret_cast<int32_t*>(outputTargets));
		network(reinterpret_cast<DATA_T*>(env_data), reinterpret_cast<uint32_t*>(outputEstimated));

		unsigned int nbValidPredictions = 0;
		unsigned int nbPredictions = 0;

		for (unsigned int oy = 0; oy < OUTPUTS_HEIGHT; ++oy) {
			for (unsigned int ox = 0; ox < OUTPUTS_WIDTH; ++ox) {

				int iy = oy;
				int ix = ox;
				if (dimX > 1 || dimY > 1) {
					iy = (int)floor((oy + 0.5) * yRatio);
					ix = (int)floor((ox + 0.5) * xRatio);
				}

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

extern int stride8;
extern int stride7;
extern int stride6;
extern int stride5;
extern int stride4;
extern int stride3;
extern int stride2;
extern int stride1;

extern "C" double BELLERO_Reward()
{
	double reward = 0.0;

	int stride8_norm = (stride8 % 5);
	int stride7_norm = (stride7 % 5);
	int stride6_norm = (stride6 % 5);
	int stride5_norm = (stride5 % 5);
	int stride4_norm = (stride4 % 5);
	int stride3_norm = (stride3 % 5);
	int stride2_norm = (stride2 % 5);
	int stride1_norm = (stride1 % 5);


	double conv1_kern_loops = CONV1_NB_CHANNELS * CONV1_NB_OUTPUTS * CONV1_OY_SIZE * CONV1_OX_SIZE;
	double conv2_kern_loops = CONV2_NB_CHANNELS * CONV2_NB_OUTPUTS * CONV2_OY_SIZE * CONV2_OX_SIZE;
	double conv3_kern_loops = CONV3_NB_CHANNELS * CONV3_NB_OUTPUTS * CONV3_OY_SIZE * CONV3_OX_SIZE;
	double fc_2d_kern_loops = CONV3_NB_OUTPUTS * FC1_NB_OUTPUTS;


	double conv1_skipped_loops = stride1_norm * stride2_norm * conv1_kern_loops;
	double conv2_skipped_loops = stride3_norm * stride3_norm * conv2_kern_loops;
	double conv3_skipped_loops = stride5_norm * stride6_norm * conv3_kern_loops;
	double fc_2d_skipped_loops = stride7_norm * stride8_norm * fc_2d_kern_loops;

	reward = (conv1_skipped_loops + conv2_skipped_loops + conv3_skipped_loops + fc_2d_skipped_loops) / (25 * (conv1_kern_loops + conv2_kern_loops + conv3_kern_loops + fc_2d_kern_loops));



	return reward;
}
