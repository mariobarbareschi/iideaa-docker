#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>
#include "file_list.h"
#include "env_read.h"
#include "network.h"

DATA_T env_data[ENV_NB_OUTPUTS][ENV_SIZE_Y][ENV_SIZE_X];
uint32_t outputEstimated[OUTPUTS_HEIGHT][OUTPUTS_WIDTH];



int main(int argc, char* argv[])
{
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
		total = sortedFileList("/home/ssaa/Git/iideaa-docker/projects/n2d2_cnn/int16/code/stimuli", &fileList, 0);
	else
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
	printf("Success rate = %02f%%\n", 100.0 * success / (float)total);
	printf("Process time per stimulus = %f us (%d threads)\n", elapsed / (double)total, omp_get_max_threads());


	return EXIT_SUCCESS;
}



