#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "file_list.h"
#include "env_read.h"
#include "network.h"
#include "fap.h"

#include<iostream>
#include<fstream>
#include <math.h>


const char * stimuli_directory = "/root/projects/LeNet5/float/code/stimuli";

extern "C" double BELLERO_getError() {    
	omp_set_num_threads(8);

	// Getting the success-rate of the original CNN
	FILE *oracle_file = fopen("/root/projects/LeNet5/float/bellerophon/success_rate.txt", "r");
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

extern ::fap::FloatPrecTy OP_9;
extern ::fap::FloatPrecTy OP_8;
extern ::fap::FloatPrecTy OP_7;
extern ::fap::FloatPrecTy OP_6;
extern ::fap::FloatPrecTy OP_5;
extern ::fap::FloatPrecTy OP_4;
extern ::fap::FloatPrecTy OP_3;
extern ::fap::FloatPrecTy OP_2;
extern ::fap::FloatPrecTy OP_1;
extern ::fap::FloatPrecTy OP_0;

extern "C" double BELLERO_Reward()
{
	double reward = 0.0;
	double num_genes = 10.0;
	double bits_per_gene = 23.0;
	double total_bits = num_genes * bits_per_gene;

	double used_bits = (OP_0.mant_size + OP_1.mant_size + OP_2.mant_size + OP_3.mant_size + OP_4.mant_size + OP_5.mant_size + OP_6.mant_size + OP_7.mant_size);
	double bits_saved = total_bits - (double) used_bits;

	printf("Bits saved: %lf-(%d+%d+%d+%d+%d+%d+%d+%d+%d+%d)=%lf-%lf=%lf\n", total_bits, 
							OP_0.mant_size, OP_1.mant_size, OP_2.mant_size, OP_3.mant_size, OP_4.mant_size, OP_5.mant_size, OP_6.mant_size, OP_7.mant_size, OP_8.mant_size, OP_9.mant_size,
							total_bits, used_bits,
							bits_saved);

    reward = bits_saved / total_bits;
	printf("Reward: %lf\n", reward);

	return reward;
}
