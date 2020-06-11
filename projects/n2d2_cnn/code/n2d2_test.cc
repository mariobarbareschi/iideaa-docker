#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>
#include "network.h"
#include "c99_vla_cast_for_cpp.h"

static const size_t CONFUSION_MATRIX_PRINT_MAX_TARGETS = 16;

DATA_T env_data[ENV_NB_OUTPUTS][ENV_SIZE_Y][ENV_SIZE_X];
uint32_t outputEstimated[OUTPUTS_HEIGHT][OUTPUTS_WIDTH];

void write_confusion_matrix(
		const char * const absolute_cm_file_name,
		const char * const percentage_cm_file_name,
		unsigned int nbOutputs,
        unsigned int * confusion_to_be_cast);

void write_success_rate(const char* const file_name, float rate);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s path_to_stimuli\n", argv[0]);
		exit(1);
	}

	unsigned int confusion[NB_TARGETS][NB_TARGETS] = {{0}};

    unsigned int dimX = 1;
    unsigned int dimY = 1;
    if (OUTPUTS_WIDTH > 1 || OUTPUTS_HEIGHT > 1) {
        dimX = ENV_SIZE_X;
        dimY = ENV_SIZE_Y;
    }

    int32_t outputTargets[dimY][dimX];
    double yRatio = ENV_SIZE_Y / OUTPUTS_HEIGHT;
    double xRatio = ENV_SIZE_X / OUTPUTS_WIDTH;
    float successRate = 0.0;

        double success = 0;
        struct timeval start, end;
        double elapsed = 0.0;

        char** fileList;
        // unsigned int total = sortedFileList("stimuli", &fileList, 0);
		 unsigned int total = sortedFileList(argv[1], &fileList, 0);

        omp_set_num_threads(8);

		FILE *oracle_file = fopen("oracle.txt", "w");
        if (oracle_file == NULL)
        {
            printf("Error opening outputs.txt file!\n");
            exit(1);
        }

        for (unsigned int n = 0; n < total;) {
            env_read(fileList[n],
                     ENV_NB_OUTPUTS,
                     ENV_SIZE_Y,
                     ENV_SIZE_X,
                     reinterpret_cast<DATA_T*>(env_data),
                     dimY,
                     dimX,
                     reinterpret_cast<int32_t*>(outputTargets));
			
			char resolved_path[PATH_MAX + 1];
			realpath(fileList[n], resolved_path);
			fprintf(oracle_file, "%s;", resolved_path);

			for (int dimY_c = 0; dimY_c < dimY; dimY_c++)
				for (int dimX_c = 0; dimX_c < dimX; dimX_c++)
					fprintf(oracle_file, "%d;", outputTargets[dimY_c][dimX_c]);

            free(fileList[n]);

            gettimeofday(&start, NULL);

            network(reinterpret_cast<DATA_T*>(env_data), reinterpret_cast<uint32_t*>(outputEstimated));


            gettimeofday(&end, NULL);


            const double duration = 1.0e6 * (double)(end.tv_sec - start.tv_sec)
                                    + (double)(end.tv_usec - start.tv_usec);
            elapsed += duration;

            unsigned int nbValidPredictions = 0;
            unsigned int nbPredictions = 0;

            for (unsigned int oy = 0; oy < OUTPUTS_HEIGHT; ++oy) {
                for (unsigned int ox = 0; ox < OUTPUTS_WIDTH; ++ox) {
					fprintf(oracle_file, "%d;", outputEstimated[oy][ox]);

                    int iy = oy;
                    int ix = ox;
                    if (dimX > 1 || dimY > 1) {
                        iy = (int)floor((oy + 0.5) * yRatio);
                        ix = (int)floor((ox + 0.5) * xRatio);
                    }

                    if (outputTargets[iy][ix] >= 0) {
                        confusion[outputTargets[iy][ix]]
                                 [outputEstimated[oy][ox]] += 1;
                            
                        nbPredictions++;
                        if (outputTargets[iy][ix] == (int)outputEstimated[oy][ox]) {
                            nbValidPredictions++;
							fprintf(oracle_file, "+\n", outputEstimated[oy][ox]);

                        }
						else
							fprintf(oracle_file, "-\n", outputEstimated[oy][ox]);

                    }
                }
            }


            success += (nbPredictions > 0) ? ((float) nbValidPredictions / nbPredictions) : 1.0;

            ++n;
            printf("%.02f/%d    (avg = %02f%%)  @  %.02f us\n", success, n, 100.0 * success / (float)n, duration);
        }

        free(fileList);
		fclose(oracle_file);

        printf("%sTested %d stimuli%s\n", ESC_BOLD, total, ESC_ALL_OFF);
        printf("Success rate = %02f%%\n", 100.0 * success / (float)total);

        successRate = 100.0 * success / (float)total;

        printf("Process time per stimulus = %f us (%d threads)\n",
               elapsed / (double)total,
               omp_get_max_threads());
    

        write_confusion_matrix(
				"confusion.txt",
				"confusion_perc.txt",
				NB_TARGETS, 
				reinterpret_cast<unsigned int *>(confusion));

		write_success_rate(
				"success_rate.txt",
				successRate);

}


void write_confusion_matrix(
		const char * const absolute_cm_file_name,
		const char * const percentage_cm_file_name,
		unsigned int nbOutputs,
        unsigned int * confusion_to_be_cast)
{
	DECLARE_2D_VLA_ARRAY_AND_CAST(int, vla_array_t, nbOutputs, nbOutputs, confusion, confusion_to_be_cast);

	FILE * abs_file = fopen(absolute_cm_file_name, "w");
	if (abs_file == NULL)
    {
        printf("Error opening %s file!\n", absolute_cm_file_name);
        return;
    }

	FILE * perc_file = fopen(percentage_cm_file_name, "w");
	if (perc_file == NULL)
    {
        printf("Error opening %s file!\n", percentage_cm_file_name);
        return;
    }

    unsigned int total = 0;
    unsigned int totalCorrect = 0;

    for (unsigned int target = 0; target < nbOutputs; ++target) {
        unsigned int targetCount = 0;

        for (unsigned int estimated = 0; estimated < nbOutputs; ++estimated)
            targetCount += confusion[target][estimated];

        total += targetCount;
        totalCorrect += confusion[target][target];


        for (unsigned int estimated = 0; estimated < nbOutputs; ++estimated)
            fprintf(abs_file, "%d;", confusion[target][estimated]);


        for (unsigned int estimated = 0; estimated < nbOutputs; ++estimated) {
            fprintf(perc_file, "%f;", 100.0 * ((targetCount > 0) ? (confusion[target][estimated] / (double)targetCount) : 0.0));
        }

        fprintf(abs_file, "\n");
        fprintf(perc_file, "\n");
    }

	fclose(abs_file);
	fclose(perc_file);
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
