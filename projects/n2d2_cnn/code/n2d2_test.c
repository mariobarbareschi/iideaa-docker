/*
    (C) Copyright 2015 CEA LIST. All Rights Reserved.
    Contributor(s): Olivier BICHLER (olivier.bichler@cea.fr)

    This software is governed by the CeCILL-C license under French law and
    abiding by the rules of distribution of free software.  You can  use,
    modify and/ or redistribute the software under the terms of the CeCILL-C
    license as circulated by CEA, CNRS and INRIA at the following URL
    "http://www.cecill.info".

    As a counterpart to the access to the source code and  rights to copy,
    modify and redistribute granted by the license, users are provided only
    with a limited warranty  and the software's author,  the holder of the
    economic rights,  and the successive licensors  have only  limited
    liability.

    The fact that you are presently reading this means that you have had
    knowledge of the CeCILL-C license and that you accept its terms.
*/

//#define SAVE_OUTPUTS

#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
// For the Windows version of dirent.h (http://www.softagalleria.net/dirent.php)
#undef min
#undef max

#ifdef _OPENMP
#include <omp.h>
#endif

#ifdef __STXP70__
#include <measure.h>
#endif

#include "network.h"

static const size_t CONFUSION_MATRIX_PRINT_MAX_TARGETS = 16;

DATA_T env_data[ENV_NB_OUTPUTS][ENV_SIZE_Y][ENV_SIZE_X];
uint32_t outputEstimated[OUTPUTS_HEIGHT][OUTPUTS_WIDTH];

int main(int argc, char* argv[])
{
    unsigned int confusion[NB_TARGETS][NB_TARGETS] = {{0}};

    printf("Binary automatically generated by the N2D2 platform\n "
           "-Description: C OMP inference binary export for Deep Neural "
           "Network.\n"
           " -Command list:\n"
           "    Stimulus selection: Use the 'path/to/the/stimulus' command to "
           "select a specific input stimulus (default value: none)\n"
           "This binary  is the exclusive property of the CEA. (C) Copyright "
           "2016 CEA LIST\n\n");

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
    if (argc > 1) {
        // printf("Reading env input %s\n", argv[1]);
        env_read(argv[1],
                 ENV_NB_OUTPUTS,
                 ENV_SIZE_Y,
                 ENV_SIZE_X,
                 env_data,
                 dimY,
                 dimX,
                 outputTargets);
        network(env_data, outputEstimated);

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

                if (outputTargets[iy][ix] >= 0) {
                    confusion[outputTargets[iy][ix]]
                             [outputEstimated[oy][ox]] += 1;

                    nbPredictions++;
                    if (outputTargets[iy][ix] == (int)outputEstimated[oy][ox]) {
                        nbValidPredictions++;
                    }
                }
            }
        }

        const double success = (nbPredictions > 0) ? ((float) nbValidPredictions / nbPredictions) : 1.0;
        printf("Success rate = %02f%%\n", 100.0 * success);
    } else {
        double success = 0;
        struct timeval start, end;
        double elapsed = 0.0;

        char** fileList;
        unsigned int total = sortedFileList("stimuli", &fileList, 0);

#ifdef _OPENMP
        omp_set_num_threads(8);
#endif

#ifdef SAVE_OUTPUTS
        FILE *fOuts = fopen("outputs.txt", "w");
        if (fOuts == NULL)
        {
            printf("Error opening outputs.txt file!\n");
            exit(1);
        }
#endif

        for (unsigned int n = 0; n < total;) {
            env_read(fileList[n],
                     ENV_NB_OUTPUTS,
                     ENV_SIZE_Y,
                     ENV_SIZE_X,
                     env_data,
                     dimY,
                     dimX,
                     outputTargets);
            free(fileList[n]);

            gettimeofday(&start, NULL);
#ifdef __STXP70__
            clrcc1();
#endif
            network(env_data, outputEstimated);
#ifdef __STXP70__
            const int cycleCount = stopcc1();
#endif
            gettimeofday(&end, NULL);

#ifdef SAVE_OUTPUTS
            char bufOuts[8];
            int k = 0;

            for (unsigned int o = 0; o < NB_OUTPUTS; ++o) {
                for (unsigned int oy = 0; oy < OUTPUTS_HEIGHT; ++oy) {
                    for (unsigned int ox = 0; ox < OUTPUTS_WIDTH; ++ox) {
                        sprintf(&bufOuts[k], "%02X",
                            (int)(unsigned char)output_data[ox
                            + OUTPUTS_WIDTH * (oy + OUTPUTS_HEIGHT * o)]);
                        k+= 2;

                        if (k == 8) {
                            swapEndian(bufOuts);
                            fprintf(fOuts, bufOuts);
                            fprintf(fOuts, "\n");
                            k = 0;
                        }
                    }
                }
            }

            if (k > 0) {
                while (k < 8) {
                    bufOuts[k] = '0';
                    ++k;
                }

                swapEndian(bufOuts);
                fprintf(fOuts, bufOuts);
                fprintf(fOuts, "\n");
            }
#endif

#ifdef __STXP70__
            const double duration = cycleCount / 100.0; // 100 MHz, unit = us
#else
            const double duration = 1.0e6 * (double)(end.tv_sec - start.tv_sec)
                                    + (double)(end.tv_usec - start.tv_usec);
#endif
            elapsed += duration;

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

                    if (outputTargets[iy][ix] >= 0) {
                        confusion[outputTargets[iy][ix]]
                                 [outputEstimated[oy][ox]] += 1;
                            
                        nbPredictions++;
                        if (outputTargets[iy][ix] == (int)outputEstimated[oy][ox]) {
                            nbValidPredictions++;
                        }
                    }
                }
            }


            success += (nbPredictions > 0) ? ((float) nbValidPredictions / nbPredictions) : 1.0;

            ++n;
#ifndef NRET
            printf("%.02f/%d    (avg = %02f%%)  @  %.02f us\n",
                   success,
                   n,
                   100.0 * success / (float)n,
                   duration);
#endif
        }

        free(fileList);
#ifdef SAVE_OUTPUTS
        fclose(fOuts);
#endif

        printf("%sTested %d stimuli%s\n", ESC_BOLD, total, ESC_ALL_OFF);
        printf("Success rate = %02f%%\n", 100.0 * success / (float)total);

        successRate = 100.0 * success / (float)total;

#ifdef _OPENMP
        printf("Process time per stimulus = %f us (%d threads)\n",
               elapsed / (double)total,
               omp_get_max_threads());
#else
        printf("Process time per stimulus = %f us\n", elapsed / (double)total);
#endif
    }

    if(NB_TARGETS <= CONFUSION_MATRIX_PRINT_MAX_TARGETS) {
        confusion_print(NB_TARGETS, confusion);
    }

#ifdef OUTXT
    FILE *f = fopen("success_rate.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f,"%f",successRate);
    fclose(f);
#endif

}
