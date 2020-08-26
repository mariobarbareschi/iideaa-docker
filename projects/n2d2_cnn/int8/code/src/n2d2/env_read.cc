#include "env_read.h"
#include <stdlib.h>
#include <stdio.h>

void env_read(char* fileName,
              DATA_T (&inputs)[ENV_NB_OUTPUTS][ENV_SIZE_Y][ENV_SIZE_X],
              int32_t (&outputTargets)[ENV_NB_OUTPUTS_HEIGHT][ENV_NB_OUTPUTS_WIDTH])
{
    FILE* filePtr = fopen(fileName, "rb");

    if (filePtr == NULL) {
        fprintf(stderr, "Unable to open file \"%s\"\n", fileName);
        perror("The following error occurred");
    }

    char header[2];
    fread(&header[0], sizeof(header[0]), 2, filePtr);

    if (header[0] != 'P' || (header[1] != '5' && header[1] != '6')) {
        fprintf(stderr, "Unknown PGM file format for file %s\n", fileName);
        fclose(filePtr);
        return;
    }

    int pixelWidth;
    int pixelHeight;
    int maxValue;
    fscanf(filePtr, "%d %d %d", &pixelWidth, &pixelHeight, &maxValue);
    fgetc(filePtr);

    if (pixelWidth != (int)ENV_SIZE_X || pixelHeight
                                            != (int)ENV_SIZE_Y) {
        fprintf(stderr,
                "PGM image size does not match array size for file %s\n",
                fileName);
        fclose(filePtr);
        return;
    }

    size_t nbRead = 0;

#if NB_BITS > 0 && NB_BITS != 8 && NB_BITS != 16 && NB_BITS != 32 && NB_BITS   \
                                                                     != 64
#if NB_BITS > 0 && NB_BITS < 8
    char inputs_fixed[ENV_NB_OUTPUTS][ENV_SIZE_Y][ENV_SIZE_X];
#elif NB_BITS > 8 && NB_BITS < 16
    short inputs_fixed[ENV_NB_OUTPUTS][ENV_SIZE_Y][ENV_SIZE_X];
#elif NB_BITS > 16 && NB_BITS < 32
    int inputs_fixed[ENV_NB_OUTPUTS][ENV_SIZE_Y][ENV_SIZE_X];
#elif NB_BITS > 32 && NB_BITS < 64
    long long int inputs_fixed[ENV_NB_OUTPUTS][ENV_SIZE_Y][ENV_SIZE_X];
#endif
    nbRead = fread(inputs_fixed, sizeof(inputs_fixed[0]), ENV_NB_OUTPUTS, filePtr);

    for (unsigned int channel = 0; channel < ENV_NB_OUTPUTS; ++channel) {
        for (unsigned int iy = 0; iy < ENV_SIZE_Y; ++iy) {
            for (unsigned int ix = 0; ix < ENV_SIZE_X; ++ix)
                inputs[channel][iy][ix] = (DATA_T)inputs_fixed[channel][iy][ix];
        }
    }
#else
    nbRead = fread(inputs, sizeof(inputs[0]), ENV_NB_OUTPUTS, filePtr);
#endif

    if (nbRead != ENV_NB_OUTPUTS)
        fprintf(stderr,
                "fread() number of read objects different than expected\n");

    /*
        for (unsigned int channel = 0; channel < ENV_NB_OUTPUTS; ++channel) {
            // DEBUG
            for (unsigned int iy = 0; iy < ENV_SIZE_Y; ++iy) {
                for (unsigned int ix = 0; ix < ENV_SIZE_X; ++ix) {
                    printf("%d", inputs[channel][iy][ix]);
                }

                printf("\n");
            }
        }
    */
    nbRead = fread(
        outputTargets, sizeof(outputTargets[0]), ENV_NB_OUTPUTS_HEIGHT, filePtr);

    if (nbRead != ENV_NB_OUTPUTS_HEIGHT)
        fprintf(stderr,
                "fread() number of read objects different than expected\n");

    if (feof(filePtr))
        fprintf(stderr,
                "End-of-file reached prematurely in data file: %s\n",
                fileName);
    else if (ferror(filePtr))
        fprintf(stderr, "Error while reading data file: %s\n", fileName);
    else if (fgetc(filePtr) != EOF)
        fprintf(stderr, "Data file size larger than expected: %s\n", fileName);

    fclose(filePtr);
}
