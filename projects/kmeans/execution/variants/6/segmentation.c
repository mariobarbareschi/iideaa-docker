/*
 * segmentation.c
 *
 * Created on: Sep 9, 2013
 * 			Author: Amir Yazdanbakhsh <a.yazdanbakhsh@gatech.edu>
 */


#include <segmentation.h>
//#include <stdio.h>
//#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <fap.h>

using namespace std;

int count = 0;
#define MAX_COUNT 1200000

void initRgbImage(RgbImage* image) {
  image->w = 0;
  image->h = 0;
  image->pixels = NULL;
  image->meta = NULL;
}

int readCell(FILE *fp, char* w) {
  int c;
  int i;

  w[0] = 0;
  for (c = fgetc(fp), i = 0; c != EOF; c = fgetc(fp)) {
    if (c == ' ' || c == '\t') {
      if (w[0] != '\"')
              continue;
    }

    if (c == ',' || c == '\n') {
      if (w[0] != '\"')
        break;
      else if (c == '\"') {
        w[i] = c;
        i++;
        break;
      }
    }

    w[i] = c;
    i++;
  }
  w[i] = 0;

  return c;
}

int loadRgbImage(const char* fileName, RgbImage* image, float scale) {
  int c;
  int i;
  int j;
  char w[256];
  RgbPixel** pixels;
  FILE *fp;

  //printf("Loading %s ...\n", fileName);

  fp = fopen(fileName, "r");
  if (!fp) {
    printf("Warning: Oops! Cannot open %s!\n", fileName);
    return 0;
  }

  c = readCell(fp, w);
  image->w = atoi(w);
  c = readCell(fp, w);
  image->h = atoi(w);

  //printf("%d x %d\n", image->w, image->h);

  pixels = (RgbPixel**)malloc(image->h * sizeof(RgbPixel*));

  if (pixels == NULL) {
    printf("Warning: Oops! Cannot allocate memory for the pixels!\n");

    fclose(fp);

    return 0;
  }

  c = 0;
  for(i = 0; i < image->h; i++) {
    pixels[i] = (RgbPixel*)malloc(image->w * sizeof(RgbPixel));
    if (pixels[i] == NULL) {
      c = 1;
      break;
    }
  }

  if (c == 1) {
    printf("Warning: Oops! Cannot allocate memory for the pixels!\n");

    for (i--; i >= 0; i--)
      free(pixels[i]);
    free(pixels);

    fclose(fp);

    return 0;
  }

  for(i = 0; i < image->h; i++) {
    for(j = 0; j < image->w; j++) {
      c = readCell(fp, w);
      pixels[i][j].r = atoi(w) / scale;

      c = readCell(fp, w);
      pixels[i][j].g = atoi(w) / scale;

      c = readCell(fp, w);
      pixels[i][j].b = atoi(w) / scale;

      pixels[i][j].cluster = 0;
      pixels[i][j].distance = 0.;
    }
  }
  image->pixels = pixels;

  c = readCell(fp, w);
  image->meta = (char*)malloc(strlen(w) * sizeof(char));
  if(image->meta == NULL) {
    printf("Warning: Oops! Cannot allocate memory for the pixels!\n");

    for (i = 0; i < image->h; i++)
            free(pixels[i]);
    free(pixels);

    fclose(fp);

    return 0;

  }
  strcpy(image->meta, w);

  //printf("%s\n", image->meta);

  //printf("w=%d x h=%d\n", image->w, image->h);

  return 1;
}

int saveRgbImage(RgbImage* image, const char* fileName, float scale) {
  int i;
  int j;
  FILE *fp;

  //printf("Saving %s ...\n", fileName);

  fp = fopen(fileName, "w");
  if (!fp) {
    printf("Warning: Oops! Cannot open %s!\n", fileName);
    return 0;
  }

  fprintf(fp, "%d,%d\n", image->w, image->h);
  //printf("%d,%d\n", image->w, image->h);

  for(i = 0; i < image->h; i++) {
    for(j = 0; j < (image->w - 1); j++) {
      //cout<<"r:"<<image->pixels[i][j].r<<"; g: "<<image->pixels[i][j].g<<"; b:"<<image->pixels[i][j].b<<endl;
      fprintf(fp, "%d,%d,%d,", (int)(image->pixels[i][j].r * scale) , (int)(image->pixels[i][j].g * scale) , (int)(image->pixels[i][j].b * scale) );
      //cout<<"r:"<<image->pixels[i][j].r * scale <<"; g: "<< image->pixels[i][j].g * scale <<"; b:"<<image->pixels[i][j].b * scale<<endl<<endl;
    }
    fprintf(fp, "%d,%d,%d\n", (int)(image->pixels[i][j].r * scale), (int)(image->pixels[i][j].g * scale), (int)(image->pixels[i][j].b * scale) );
  }

  fprintf(fp, "%s", image->meta);
  //printf("%s\n", image->meta);

  fclose(fp);

  return 1;
}

void freeRgbImage(RgbImage* image) {
  int i;

  if (image->meta != NULL)
          free(image->meta);

  if (image->pixels == NULL)
          return;

  for (i = 0; i < image->h; i++)
          if (image->pixels != NULL)
                  free(image->pixels[i]);

  free(image->pixels);
}

void makeGrayscale(RgbImage* image) {
  int i;
  int j;
  float luminance;

  float rC = 0.30;
  float gC = 0.59;
  float bC = 0.11;

  for(i = 0; i < image->h; i++) {
    for(j = 0; j < image->w; j++) {
      luminance =
              rC * image->pixels[i][j].r +
              gC * image->pixels[i][j].g +
              bC * image->pixels[i][j].b;

      image->pixels[i][j].r = (unsigned char)luminance;
      image->pixels[i][j].g = (unsigned char)luminance;
      image->pixels[i][j].b = (unsigned char)luminance;
    }
  }
}

float euclideanDistance(RgbPixel* p, Centroid* c1) {
  float r;

  r = 0;
  double r_tmp;

  /*double dataIn[6];
  dataIn[0] = p->r;
  dataIn[1] = p->g;
  dataIn[2] = p->b;
  dataIn[3] = c1->r;
  dataIn[4] = c1->g;
  dataIn[5] = c1->b;*/


  r += (p->r - c1->r) * (p->r - c1->r);
  r += (p->g - c1->g) * (p->g - c1->g);
  r += (p->b - c1->b) * (p->b - c1->b);

  r_tmp = sqrt(r);


  return r_tmp;
}

int pickCluster(RgbPixel* p, Centroid* c1) {
  float d1;

  d1 = euclideanDistance(p, c1);

  if (p->distance <= d1)
    return 0;

  return 1;
}

void assignCluster(RgbPixel* p, Clusters* clusters) {
  int i = 0;

  float d;
  d = euclideanDistance(p, &clusters->centroids[i]);
  p->distance = d;

  for(i = 1; i < clusters->k; ++i) {
    d = euclideanDistance(p, &clusters->centroids[i]);
    if (d < p->distance) {
      p->cluster = i;
      p->distance = d;
    }
  }
}

// TUTTO QUELLO SOPRA E' AGGIUNTO
int initClusters(Clusters* clusters, int k, float scale) {
  int i;
  float x;

  clusters->centroids = (Centroid*)malloc(k * sizeof(Centroid));

  if (clusters == NULL) {
    printf("Warning: Oops! Cannot allocate memory for the clusters!\n");

    return 0;
  }

  clusters->k = k;
  for (i = 0; i < clusters->k; i ++) {
    x = (((float)rand())/RAND_MAX) * scale;
    clusters->centroids[i].r = x;

    x = (((float)rand())/RAND_MAX) * scale;
    clusters->centroids[i].g = x;

    x = (((float)rand())/RAND_MAX) * scale;
    clusters->centroids[i].b = x;

    clusters->centroids[i].n = 0;
  }

  return 1;
}

void freeClusters(Clusters* clusters) {
  if (clusters != NULL)
    free(clusters->centroids);
}
::fap::FloatPrecTy OP_0(8,16);
::fap::FloatPrecTy OP_1(8,18);
::fap::FloatPrecTy OP_2(8,20);
::fap::FloatPrecTy OP_3(8,17);
::fap::FloatPrecTy OP_4(8,21);
::fap::FloatPrecTy OP_5(8,0);

void segmentImage(RgbImage* image, Clusters* clusters, int n) {
  int i;
  int x, y;
  int c;

  for (i = 0; i < n; ++i) {
    for (y = 0; y < image->h; y++) {
      for (x = 0; x < image->w; x++) {
              assignCluster(&image->pixels[y][x], clusters);
      }
    }

    /** Recenter */
    for (c  = 0; c < clusters->k; ++c) {
      clusters->centroids[c].r = 0.;
      clusters->centroids[c].g = 0.;
      clusters->centroids[c].b = 0.;
      clusters->centroids[c].n = 0;
    }
    for (y = 0; y < image->h; y++) {
      for (x = 0; x < image->w; x++) {
        clusters->centroids[image->pixels[y][x].cluster].r = (float)(::fap::FloatingPointType((float) clusters->centroids[image->pixels[y][x].cluster].r, OP_0)) + (float)(::fap::FloatingPointType((float) image->pixels[y][x].r, OP_0));
        clusters->centroids[image->pixels[y][x].cluster].g = (float)(::fap::FloatingPointType((float) clusters->centroids[image->pixels[y][x].cluster].g, OP_1)) + (float)(::fap::FloatingPointType((float) image->pixels[y][x].g, OP_1));
        clusters->centroids[image->pixels[y][x].cluster].b = (float)(::fap::FloatingPointType((float) clusters->centroids[image->pixels[y][x].cluster].b, OP_2)) + (float)(::fap::FloatingPointType((float) image->pixels[y][x].b, OP_2));
        clusters->centroids[image->pixels[y][x].cluster].n += 1;
      }
    }
    for (c  = 0; c < clusters->k; ++c) {
      if (clusters->centroids[c].n != 0) {
        clusters->centroids[c].r = (float)(::fap::FloatingPointType((float) clusters->centroids[c].r, OP_3)) / (float)(::fap::FloatingPointType((float) clusters->centroids[c].n, OP_3));
        clusters->centroids[c].g = (float)(::fap::FloatingPointType((float) clusters->centroids[c].g, OP_4)) / (float)(::fap::FloatingPointType((float) clusters->centroids[c].n, OP_4));
        clusters->centroids[c].b = (float)(::fap::FloatingPointType((float) clusters->centroids[c].b, OP_5)) / (float)(::fap::FloatingPointType((float) clusters->centroids[c].n, OP_5));
      }
    }
  }

  for (y = 0; y < image->h; y++) {
    for (x = 0; x < image->w; x++) {
      image->pixels[y][x].r = clusters->centroids[image->pixels[y][x].cluster].r;
      image->pixels[y][x].g = clusters->centroids[image->pixels[y][x].cluster].g;
      image->pixels[y][x].b = clusters->centroids[image->pixels[y][x].cluster].b;
    }
  }
}
