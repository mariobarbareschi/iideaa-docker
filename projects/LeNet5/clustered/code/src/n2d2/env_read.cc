#include "env_read.h"
#include <stdlib.h>
#include <stdio.h>

void env_read(
		char* fileName,
		DATA_T (&inputs)[ENV_NB_CHANNELS][ENV_NB_HEIGHT][ENV_NB_WIDTH],
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

    if (pixelWidth != (int)ENV_NB_WIDTH || pixelHeight != (int)ENV_NB_HEIGHT) {
        fprintf(stderr, "PGM image size does not match array size for file %s\n", fileName);
        fclose(filePtr);
        return;
    }

    size_t nbRead = 0;

    nbRead = fread(inputs, sizeof(inputs[0]), ENV_NB_CHANNELS, filePtr);

    if (nbRead != ENV_NB_CHANNELS)
        fprintf(stderr, "fread() number of read objects different than expected\n");

    nbRead = fread(outputTargets, sizeof(outputTargets[0]), ENV_NB_OUTPUTS_HEIGHT, filePtr);

    if (nbRead != ENV_NB_OUTPUTS_HEIGHT)
        fprintf(stderr, "fread() number of read objects different than expected\n");

    if (feof(filePtr))
        fprintf(stderr, "End-of-file reached prematurely in data file: %s\n", fileName);
    else if (ferror(filePtr))
        fprintf(stderr, "Error while reading data file: %s\n", fileName);
    else if (fgetc(filePtr) != EOF)
        fprintf(stderr, "Data file size larger than expected: %s\n", fileName);

    fclose(filePtr);
}
