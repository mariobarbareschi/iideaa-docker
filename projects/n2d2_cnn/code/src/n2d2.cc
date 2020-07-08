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

#include "n2d2.h"
#include "c99_vla_cast_for_cpp.h"
#include "vpa_n.h"
#include "fap.h"
#include <string.h>

int compare(void const* a, void const* b)
{
    char const* const* pa = (char const * const*) a;
    char const* const* pb = (char const * const*) b;
    return strcmp(*pa, *pb);
}

int sortedFileList(const char* const dirName,
                   char*** fileList,
                   unsigned int nbMax)
{
	unsigned int count = 0;

    DIR* pDir = opendir(dirName);

    if (pDir == NULL)
        fprintf(stderr, "Couldn't open the directory for input patterns: %s\n", dirName);
    struct dirent* pFile;

    // Count the number of files
    while ((pFile = readdir(pDir))) {
        if (pFile->d_name[0] == '.')
            continue;

        ++count;
    }
	//
    // Allocate enough space
    (*fileList) = (char**) malloc(count * sizeof(*(*fileList)));

    if ((*fileList) == NULL) {
        closedir(pDir);
        fprintf(stderr, "sortedFileList(): 'list' memory allocation failed\n");
        return -1;
    }

    count = 0;

    rewinddir(pDir); /* reset position */

    while ((pFile = readdir(pDir)) && (nbMax == 0 || count < nbMax)) {
        if (pFile->d_name[0] == '.')
            continue;

        /* + 2 because of the '/' and the terminating 0 */
        (*fileList)[count] = (char*)malloc((strlen(dirName) + strlen(pFile->d_name)
                                     + 2) * sizeof(*(*fileList)[count]));

        if ((*fileList)[count] == NULL) {
            closedir(pDir);
            fprintf(stderr, "sortedFileList(): 'fileName' memory allocation failed\n");
            return -1;
        }

        sprintf((*fileList)[count], "%s/%s", dirName, pFile->d_name);
        ++count;
    }

    closedir(pDir);

    if (nbMax > 0) {
        printf("sortedFileList(): warning: nbMax > 0 may lead to globally unsorted stimuli!\n");
    }

    qsort((*fileList), count, sizeof(*(*fileList)), compare);
    return count;
}

void env_read(char* fileName,
              unsigned int nbChannels,
              unsigned int channelsHeight,
              unsigned int channelsWidth,
              DATA_T * inputs_to_be_cast,
              unsigned int outputsHeight,
              unsigned int outputsWidth,
              int32_t * outputTargets_to_be_cast)
{
	DECLARE_3D_VLA_ARRAY_AND_CAST(DATA_T, inputs_vla_array_t, nbChannels, channelsHeight, channelsWidth, inputs, inputs_to_be_cast);
	DECLARE_2D_VLA_ARRAY_AND_CAST(int32_t, outputTargets_vla_array_t, outputsHeight, outputsWidth, outputTargets, outputTargets_to_be_cast);


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

    if (pixelWidth != (int)channelsWidth || pixelHeight != (int)channelsHeight) {
        fprintf(stderr, "PGM image size does not match array size for file %s\n", fileName);
        fclose(filePtr);
        return;
    }

    size_t nbRead = 0;

    nbRead = fread(inputs, sizeof(inputs[0]), nbChannels, filePtr);

    if (nbRead != nbChannels)
        fprintf(stderr, "fread() number of read objects different than expected\n");

    nbRead = fread(outputTargets, sizeof(outputTargets[0]), outputsHeight, filePtr);

    if (nbRead != outputsHeight)
        fprintf(stderr, "fread() number of read objects different than expected\n");

    if (feof(filePtr))
        fprintf(stderr, "End-of-file reached prematurely in data file: %s\n", fileName);
    else if (ferror(filePtr))
        fprintf(stderr, "Error while reading data file: %s\n", fileName);
    else if (fgetc(filePtr) != EOF)
        fprintf(stderr, "Data file size larger than expected: %s\n", fileName);

    fclose(filePtr);
}

void convcell_propagate_conv1(
    unsigned int nbChannels,
    unsigned int channelsHeight,
    unsigned int channelsWidth,
    int paddingY,
    int paddingX,
    unsigned int strideY,
    unsigned int strideX,
    DATA_T * inputs_to_be_cast,
    unsigned int oySize,
    unsigned int oxSize,
    unsigned int nbOutputs_,
    unsigned int outputsHeight,
    unsigned int outputsWidth,
    unsigned int nbOutputs,
    unsigned int outputOffset,
    DATA_T * outputs_to_be_cast,
    BDATA_T * bias_to_be_cast,
    WDATA_T * weights_to_be_cast,
    ActivationFunction_T func,
    int shift)
{
	typedef DATA_T inputs_vla_array_t[nbChannels][channelsHeight][channelsWidth]; 
	inputs_vla_array_t &inputs = *reinterpret_cast<inputs_vla_array_t*>(inputs_to_be_cast); 
	typedef DATA_T outputs_vla_array_t[nbOutputs_][outputsHeight][outputsWidth]; 
	outputs_vla_array_t &outputs = *reinterpret_cast<outputs_vla_array_t*>(outputs_to_be_cast); 
	typedef BDATA_T bias_vla_array_t[nbOutputs]; 
	bias_vla_array_t &bias = *reinterpret_cast<bias_vla_array_t*>(bias_to_be_cast); 
	typedef WDATA_T internal_type_t[5][5]; 
	typedef internal_type_t* weights_vla_array_t[nbOutputs][nbChannels]; 
	weights_vla_array_t & weights = *reinterpret_cast<weights_vla_array_t*>(weights_to_be_cast);
	#pragma omp parallel for
	for (unsigned int output = 0; output < nbOutputs; ++output) { 
		for (unsigned int oy = 0; oy < oySize; ++oy) { 
			for (unsigned int ox = 0; ox < oxSize; ++ox) { 
				const unsigned int sxMin = (unsigned int)int_max( (int)paddingX - (int)(ox * strideX), 0); 
				const unsigned int syMin = (unsigned int)int_max( (int)paddingY - (int)(oy * strideY), 0); 
				const unsigned int sxMax = (unsigned int)int_max( int_min((int)channelsWidth + paddingX - (int)(ox * strideX), (int)5), 0); 
				const unsigned int syMax = (unsigned int)int_max( int_min((int)channelsHeight + paddingY - (int)(oy * strideY), (int)5), 0); 
				const int ix = (int)(ox * strideX) - (int)paddingX; 
				const int iy = (int)(oy * strideY) - (int)paddingY; 
				SUM_T weightedSum = bias[output]; 
				for (unsigned int channel = 0; channel < nbChannels; ++channel) { 
					if (weights[output][channel] == NULL) continue;
					#pragma unroll 5
					for (unsigned int sy = 0; sy < 5; ++sy) {
						#pragma unroll 5
						for (unsigned int sx = 0; sx < 5; ++sx) { 
							if (sx >= sxMin && sx < sxMax && sy >= syMin && sy < syMax) { 
								weightedSum = ((weightedSum) + ((SUM_T)( *weights[output][channel])[sy][sx] * (SUM_T)( (DATA_T) inputs[channel][iy + sy][ix + sx]))); 
							} 
						} 
					} 
				} 
				outputs[outputOffset + output][oy][ox] = sat(weightedSum, func, shift); 
			} 
		} 
	} 
}
void convcell_propagate_conv2(
    unsigned int nbChannels,
    unsigned int channelsHeight,
    unsigned int channelsWidth,
    int paddingY,
    int paddingX,
    unsigned int strideY,
    unsigned int strideX,
    DATA_T * inputs_to_be_cast,
    unsigned int oySize,
    unsigned int oxSize,
    unsigned int nbOutputs_,
    unsigned int outputsHeight,
    unsigned int outputsWidth,
    unsigned int nbOutputs,
    unsigned int outputOffset,
    DATA_T * outputs_to_be_cast,
    BDATA_T * bias_to_be_cast,
    WDATA_T * weights_to_be_cast,
    ActivationFunction_T func,
    int shift)
{
	typedef DATA_T inputs_vla_array_t[nbChannels][channelsHeight][channelsWidth]; 
	inputs_vla_array_t &inputs = *reinterpret_cast<inputs_vla_array_t*>(inputs_to_be_cast); 
	typedef DATA_T outputs_vla_array_t[nbOutputs_][outputsHeight][outputsWidth]; 
	outputs_vla_array_t &outputs = *reinterpret_cast<outputs_vla_array_t*>(outputs_to_be_cast); 
	typedef BDATA_T bias_vla_array_t[nbOutputs]; 
	bias_vla_array_t &bias = *reinterpret_cast<bias_vla_array_t*>(bias_to_be_cast); 
	typedef WDATA_T internal_type_t[5][5]; 
	typedef internal_type_t* weights_vla_array_t[nbOutputs][nbChannels]; 
	weights_vla_array_t & weights = *reinterpret_cast<weights_vla_array_t*>(weights_to_be_cast);
	#pragma omp parallel for
	for (unsigned int output = 0; output < nbOutputs; ++output) { 
		for (unsigned int oy = 0; oy < oySize; ++oy) { 
			for (unsigned int ox = 0; ox < oxSize; ++ox) { 
				const unsigned int sxMin = (unsigned int)int_max( (int)paddingX - (int)(ox * strideX), 0); 
				const unsigned int syMin = (unsigned int)int_max( (int)paddingY - (int)(oy * strideY), 0); 
				const unsigned int sxMax = (unsigned int)int_max( int_min((int)channelsWidth + paddingX - (int)(ox * strideX), (int)5), 0); 
				const unsigned int syMax = (unsigned int)int_max( int_min((int)channelsHeight + paddingY - (int)(oy * strideY), (int)5), 0); 
				const int ix = (int)(ox * strideX) - (int)paddingX; 
				const int iy = (int)(oy * strideY) - (int)paddingY; 
				SUM_T weightedSum = bias[output]; 
				for (unsigned int channel = 0; channel < nbChannels; ++channel) { 
					if (weights[output][channel] == NULL) continue;
					#pragma unroll 5
					for (unsigned int sy = 0; sy < 5; ++sy) {
						#pragma unroll 5
						for (unsigned int sx = 0; sx < 5; ++sx) { 
							if (sx >= sxMin && sx < sxMax && sy >= syMin && sy < syMax) { 
								weightedSum = ((weightedSum) + ((SUM_T)( *weights[output][channel])[sy][sx] * (SUM_T)( (DATA_T) inputs[channel][iy + sy][ix + sx]))); 
							} 
						} 
					} 
				} 
				outputs[outputOffset + output][oy][ox] = sat(weightedSum, func, shift); 
			} 
		} 
	} 
}

void convcell_propagate_conv3(
    unsigned int nbChannels,
    unsigned int channelsHeight,
    unsigned int channelsWidth,
    int paddingY,
    int paddingX,
    unsigned int strideY,
    unsigned int strideX,
    DATA_T * inputs_to_be_cast,
    unsigned int oySize,
    unsigned int oxSize,
    unsigned int nbOutputs_,
    unsigned int outputsHeight,
    unsigned int outputsWidth,
    unsigned int nbOutputs,
    unsigned int outputOffset,
    DATA_T * outputs_to_be_cast,
    BDATA_T * bias_to_be_cast,
    WDATA_T * weights_to_be_cast,
    ActivationFunction_T func,
    int shift)
{
	typedef DATA_T inputs_vla_array_t[nbChannels][channelsHeight][channelsWidth]; 
	inputs_vla_array_t &inputs = *reinterpret_cast<inputs_vla_array_t*>(inputs_to_be_cast); 
	typedef DATA_T outputs_vla_array_t[nbOutputs_][outputsHeight][outputsWidth]; 
	outputs_vla_array_t &outputs = *reinterpret_cast<outputs_vla_array_t*>(outputs_to_be_cast); 
	typedef BDATA_T bias_vla_array_t[nbOutputs]; 
	bias_vla_array_t &bias = *reinterpret_cast<bias_vla_array_t*>(bias_to_be_cast); 
	typedef WDATA_T internal_type_t[5][5]; 
	typedef internal_type_t* weights_vla_array_t[nbOutputs][nbChannels]; 
	weights_vla_array_t & weights = *reinterpret_cast<weights_vla_array_t*>(weights_to_be_cast);
	#pragma omp parallel for
	for (unsigned int output = 0; output < nbOutputs; ++output) { 
		for (unsigned int oy = 0; oy < oySize; ++oy) { 
			for (unsigned int ox = 0; ox < oxSize; ++ox) { 
				const unsigned int sxMin = (unsigned int)int_max( (int)paddingX - (int)(ox * strideX), 0); 
				const unsigned int syMin = (unsigned int)int_max( (int)paddingY - (int)(oy * strideY), 0); 
				const unsigned int sxMax = (unsigned int)int_max( int_min((int)channelsWidth + paddingX - (int)(ox * strideX), (int)5), 0); 
				const unsigned int syMax = (unsigned int)int_max( int_min((int)channelsHeight + paddingY - (int)(oy * strideY), (int)5), 0); 
				const int ix = (int)(ox * strideX) - (int)paddingX; 
				const int iy = (int)(oy * strideY) - (int)paddingY; 
				SUM_T weightedSum = bias[output]; 
				for (unsigned int channel = 0; channel < nbChannels; ++channel) { 
					if (weights[output][channel] == NULL) continue;
					#pragma unroll 5
					for (unsigned int sy = 0; sy < 5; ++sy) {
						#pragma unroll 5
						for (unsigned int sx = 0; sx < 5; ++sx) { 
							if (sx >= sxMin && sx < sxMax && sy >= syMin && sy < syMax) { 
								weightedSum = ((weightedSum) + ((SUM_T)( *weights[output][channel])[sy][sx] * (SUM_T)( (DATA_T) inputs[channel][iy + sy][ix + sx]))); 
							} 
						} 
					} 
				} 
				outputs[outputOffset + output][oy][ox] = sat(weightedSum, func, shift); 
			} 
		} 
	} 
}

void poolcell_propagate_unitmap(
    unsigned int nbChannels,
    unsigned int channelsHeight,
    unsigned int channelsWidth,
    unsigned int strideY,
    unsigned int strideX,
    DATA_T * inputs_to_be_cast,
    unsigned int nbOutputs_,
    unsigned int outputsHeight,
    unsigned int outputsWidth,
    unsigned int nbOutputs,
    unsigned int outputOffset,
    DATA_T * outputs_to_be_cast,
    unsigned int poolHeight,
    unsigned int poolWidth,
    Pooling_T pooling,
    ActivationFunction_T func,
    int shift)
{

	DECLARE_3D_VLA_ARRAY_AND_CAST(DATA_T, input_vla_array_t, nbChannels, channelsHeight, channelsWidth, inputs, inputs_to_be_cast); 	
	DECLARE_3D_VLA_ARRAY_AND_CAST(DATA_T, outputs_vla_array_t, nbOutputs_, outputsHeight, outputsWidth, outputs, outputs_to_be_cast); 	

	#pragma omp parallel for collapse(3)
    for (unsigned int output = 0; output < nbOutputs; ++output) {
        for (unsigned int oy = 0; oy < outputsHeight; ++oy) {
            for (unsigned int ox = 0; ox < outputsWidth; ++ox) {
                const unsigned int sxMax
                    = uint_min(channelsWidth - ox * strideX, poolWidth);
                const unsigned int syMax
                    = uint_min(channelsHeight - oy * strideY, poolHeight);

                if (pooling == Max) {
                    DATA_T poolValue = DATA_T_MIN;

                    for (unsigned int sy = 0; sy < syMax; ++sy) {
                        for (unsigned int sx = 0; sx < sxMax; ++sx) {
                            const unsigned int ix = ox * strideX + sx;
                            const unsigned int iy = oy * strideY + sy;

                            if (inputs[output][iy][ix] > poolValue)
                                poolValue = inputs[output][iy][ix];
                        }
                    }
                    outputs[outputOffset + output][oy][ox] = sat(poolValue, func, shift);
                } else if (pooling == Average) {
                    SUM_T sum = 0;

                    for (unsigned int sy = 0; sy < syMax; ++sy) {
                        for (unsigned int sx = 0; sx < sxMax; ++sx) {
                            const unsigned int ix = ox * strideX + sx;
                            const unsigned int iy = oy * strideY + sy;
                            sum += inputs[output][iy][ix];
                        }
                    }
                    sum /= poolWidth * poolHeight;
                    outputs[outputOffset + output][oy][ox] = sat(sum, func, shift);
                }
            }
        }
    }
}

void
fccell_propagate_2d(unsigned int nbChannels,
                    unsigned int channelsHeight,
                    unsigned int channelsWidth,
                    DATA_T * inputs_to_be_cast,
                    unsigned int nbOutputs_,
                    unsigned int nbOutputs,
                    unsigned int outputOffset,
                    DATA_T * outputs_to_be_cast,
                    unsigned int nbChannels_,
                    BDATA_T * bias_to_be_cast,
                    WDATA_T * weights_to_be_cast,
                    ActivationFunction_T func,
                    int shift)
{
	DECLARE_3D_VLA_ARRAY_AND_CAST(DATA_T, inputs_vla_array_t, nbChannels, channelsHeight, channelsWidth, inputs, inputs_to_be_cast);
	DECLARE_1D_VLA_ARRAY_AND_CAST(DATA_T, outputs_vla_array_t, nbOutputs_, outputs, outputs_to_be_cast);
	DECLARE_1D_VLA_ARRAY_AND_CAST(BDATA_T, bias_vla_array_t, nbOutputs, bias, bias_to_be_cast);
	DECLARE_2D_VLA_ARRAY_AND_CAST(WDATA_T, weights_vla_array_t, nbOutputs, nbChannels_, weights, weights_to_be_cast);
	#pragma omp parallel for if (nbOutputs > 32)
    for (unsigned int output = 0; output < nbOutputs; ++output) {
        SUM_T weightedSum = bias[output];
        unsigned int c = 0;

        for (unsigned int channel = 0; channel < nbChannels; ++channel) {
            for (unsigned int iy = 0; iy < channelsHeight; ++iy) {
				for (unsigned int ix = 0; ix < channelsWidth; ++ix)
                    weightedSum += weights[output][c++] * inputs[channel][iy][ix];
            }
        }

        outputs[outputOffset + output] = sat(weightedSum, func, shift);
    }
}

void fccell_propagate(unsigned int nbChannels,
                      DATA_T * inputs_to_be_cast,
                      unsigned int nbOutputs_,
                      unsigned int nbOutputs,
                      unsigned int outputOffset,
                      DATA_T * outputs_to_be_cast,
                      BDATA_T * bias_to_be_cast,
                      WDATA_T * weights_to_be_cast,
                      ActivationFunction_T func,
                      int shift)
{
	DECLARE_1D_VLA_ARRAY_AND_CAST(DATA_T, inputs_vla_array_t, nbChannels, inputs, inputs_to_be_cast);
	DECLARE_1D_VLA_ARRAY_AND_CAST(DATA_T, outputs_vla_array_t, nbOutputs_, outputs, outputs_to_be_cast);
	DECLARE_1D_VLA_ARRAY_AND_CAST(BDATA_T, bias_vla_array_t, nbOutputs, bias, bias_to_be_cast);
	DECLARE_2D_VLA_ARRAY_AND_CAST(WDATA_T, weights_vla_array_t, nbOutputs, nbChannels, weights, weights_to_be_cast);
	#pragma omp parallel for if (nbOutputs > 32)
    for (unsigned int output = 0; output < nbOutputs; ++output) {
        SUM_T weightedSum = bias[output];

        for (unsigned int channel = 0; channel < nbChannels; ++channel)
            weightedSum += weights[output][channel] * inputs[channel];

        outputs[outputOffset + output] = sat(weightedSum, func, shift);
    }
}

void output_max(unsigned int nbOutputs,
                DATA_T * outputs_to_be_cast,
                uint32_t * outputEstimated_to_be_cast)
{
	DECLARE_1D_VLA_ARRAY_AND_CAST(DATA_T, outputs_vla_array_t, nbOutputs, outputs, outputs_to_be_cast);
	DECLARE_2D_VLA_ARRAY_AND_CAST(uint32_t, outputEstimated_vla_array_t, 1, 1, outputEstimated, outputEstimated_to_be_cast);

    if (nbOutputs > 1) {
        DATA_T maxVal = outputs[0];
        unsigned int outputMax = 0;

        for (unsigned int output = 1; output < nbOutputs; ++output) {
            if (outputs[output] > maxVal) {
                maxVal = outputs[output];
                outputMax = output;
            }
        }

        outputEstimated[0][0] = outputMax;
    }
    else
        outputEstimated[0][0] = (outputs[0] > (BINARY_THRESHOLD * DATA_T_MAX));
}

