#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "network.h"
#include "fap.h"
#include "c99_vla_cast_for_cpp.h"

#include<iostream>
#include<fstream>
#include <math.h>


const char * stimuli_directory = "/root/projects/n2d2_cnn/code/stimuli";

extern "C" double BELLERO_getError() {    
	omp_set_num_threads(8);

	// Getting the success-rate of the original CNN
	FILE *oracle_file = fopen("/root/projects/n2d2_cnn/bellerophon/FLAP/success_rate.txt", "r");
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
