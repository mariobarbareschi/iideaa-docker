/*
 * segmentation.h
 * 
 * Created on: Sep 9, 2013
 * 			Author: Amir Yazdanbakhsh <a.yazdanbakhsh@gatech.edu>
 */


#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

//#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
//#include <stdlib.h>
//#include "rgbimage.h"
//#include "segmentation.h"

typedef struct {
   float r;
   float g;
   float b;
   int cluster;
   float distance;
} RgbPixel;

typedef struct {
   int w;
   int h;
   RgbPixel** pixels;
   char* meta;
} RgbImage;

typedef struct {
   float r;
   float g;
   float b;
   int n;
} Centroid;

typedef struct {
   int k;
   Centroid* centroids;
} Clusters;


void initRgbImage(RgbImage* image);
int readCell(FILE *fp, char* w);
int loadRgbImage(const char* fileName, RgbImage* image, float scale);
int saveRgbImage(RgbImage* image, const char* fileName, float scale);
void freeRgbImage(RgbImage* image);
void makeGrayscale(RgbImage* image);
extern "C"  double BELLERO_getError();

int initClusters(Clusters* clusters, int k, float scale);
void segmentImage(RgbImage* image, Clusters* clusters, int n);
void freeClusters(Clusters* clusters);

#endif /* SEGMENTATION_H_ */
