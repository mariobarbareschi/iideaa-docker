#include "env_read.h"
#include <stdlib.h>
#include <stdio.h>

void env_read(char* fileName,
              unsigned int nbChannels,
              unsigned int channelsHeight,
              unsigned int channelsWidth,
              DATA_T inputs[nbChannels][channelsHeight][channelsWidth],
              unsigned int outputsHeight,
              unsigned int outputsWidth,
              int32_t outputTargets[outputsHeight][outputsWidth])
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

    if (pixelWidth != (int)channelsWidth || pixelHeight
                                            != (int)channelsHeight) {
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
    char inputs_fixed[nbChannels][channelsHeight][channelsWidth];
#elif NB_BITS > 8 && NB_BITS < 16
    short inputs_fixed[nbChannels][channelsHeight][channelsWidth];
#elif NB_BITS > 16 && NB_BITS < 32
    int inputs_fixed[nbChannels][channelsHeight][channelsWidth];
#elif NB_BITS > 32 && NB_BITS < 64
    long long int inputs_fixed[nbChannels][channelsHeight][channelsWidth];
#endif
    nbRead = fread(inputs_fixed, sizeof(inputs_fixed[0]), nbChannels, filePtr);

    for (unsigned int channel = 0; channel < nbChannels; ++channel) {
        for (unsigned int iy = 0; iy < channelsHeight; ++iy) {
            for (unsigned int ix = 0; ix < channelsWidth; ++ix)
                inputs[channel][iy][ix] = (DATA_T)inputs_fixed[channel][iy][ix];
        }
    }
#else
    nbRead = fread(inputs, sizeof(inputs[0]), nbChannels, filePtr);
#endif

    if (nbRead != nbChannels)
        fprintf(stderr,
                "fread() number of read objects different than expected\n");

    /*
        for (unsigned int channel = 0; channel < nbChannels; ++channel) {
            // DEBUG
            for (unsigned int iy = 0; iy < channelsHeight; ++iy) {
                for (unsigned int ix = 0; ix < channelsWidth; ++ix) {
                    printf("%d", inputs[channel][iy][ix]);
                }

                printf("\n");
            }
        }
    */
    nbRead = fread(
        outputTargets, sizeof(outputTargets[0]), outputsHeight, filePtr);

    if (nbRead != outputsHeight)
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
