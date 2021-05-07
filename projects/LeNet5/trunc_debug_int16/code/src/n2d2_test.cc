#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>
#include <math.h>
#include "file_list.h"
#include "env_read.h"
#include "network.h"

DATA_T env_data[ENV_NB_CHANNELS][ENV_NB_HEIGHT][ENV_NB_WIDTH];
uint32_t outputEstimated[OUTPUTS_HEIGHT][OUTPUTS_WIDTH];

void write_success_rate(const char* const file_name, float rate);

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

int main(int argc, char* argv[])
{
 // Error     Reward   Penalty #OP     OP_0    OP_1    OP_2    OP_3    OP_4    OP_5    OP_6    OP_7    OP_8    OP_9
 //-0.0373459 0.100831 0       10      8       6       7       8       3       8       9       9       7       4
 
  nab_9 = 8;
  nab_8 = 6;
  nab_7 = 7;
  nab_6 = 8;
  nab_5 = 3;
  nab_4 = 8;
  nab_3 = 9;
  nab_2 = 9;
  nab_1 = 7;
  nab_0 = 4;
  
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
  
  char** fileList;
	unsigned int total;
  int32_t outputTargets[ENV_NB_OUTPUTS_HEIGHT][ENV_NB_OUTPUTS_WIDTH];
  float successRate = 0.0;
	double success = 0;
	struct timeval start, end;
	double elapsed = 0.0;
	unsigned int nbValidPredictions = 0;
	unsigned int nbPredictions = 0;

	if (argc < 2)
	{
		printf("Usage: %s path_to_stimuli\n", argv[0]);
		return EXIT_FAILURE;
	}
		
  total = sortedFileList(argv[1], &fileList, 0);

	omp_set_num_threads(8);

	for (unsigned int n = 0; n < total;)
	{
		env_read(fileList[n], env_data, outputTargets);
		
		free(fileList[n]);

		gettimeofday(&start, NULL);
		network(env_data, outputEstimated);
		gettimeofday(&end, NULL);

		const double duration = 1.0e6 * (double)(end.tv_sec - start.tv_sec)
								+ (double)(end.tv_usec - start.tv_usec);
		elapsed += duration;


		for (unsigned int oy = 0; oy < OUTPUTS_HEIGHT; ++oy) {
			for (unsigned int ox = 0; ox < OUTPUTS_WIDTH; ++ox) {

				int iy = oy;
				int ix = ox;

				if (outputTargets[iy][ix] >= 0) {
						
					nbPredictions++;
					if (outputTargets[iy][ix] == (int)outputEstimated[oy][ox]) 
						nbValidPredictions++;
				}
			}
		}


		success += (nbPredictions > 0) ? ((float) nbValidPredictions / nbPredictions) : 1.0;

		++n;
		printf("%.02f/%d    (avg = %02f%%)  @  %.02f us\n", success, n, 100.0 * success / (float)n, duration);
	}

	free(fileList);
	successRate = 100.0 * success / (float)total;

	printf("Tested %d stimuli\n", total);
	printf("Success rate = %02f%%\n", successRate);
  printf("Reward %lf / %lf = %lf\n", saved_bits, total_bits, reward);
  printf("Process time per stimulus = %f us (%d threads)\n", elapsed / (double)total, omp_get_max_threads());

	return EXIT_SUCCESS;
}


void write_success_rate(const char* const file_name, float rate)
{
    FILE * f = fopen(file_name, "w");
    if (f == NULL)
    {
        printf("Error opening %s!\n", file_name);
        exit(1);
    }
    fprintf(f ,"%f\n", rate);
    fclose(f);
}
