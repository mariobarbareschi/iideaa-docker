/*
 * kmeans.c
 *
 * Created on: Sep 9, 2013
 * 			Author: Amir Yazdanbakhsh <a.yazdanbakhsh@gatech.edu>
 */


/*#include <stdio.h>*/
/*#include <math.h>*/
/*#include "rgbimage.h"*/
#include "segmentation.h"
/*#include "distance.h"*/

/*extern "C" double BELLERO_getError();*/

int main (int argc, const char* argv[]) {
  //void main
  return 0;
}

// BELLEROPHON FUNCTION

/*char golden_image_path[] = "/home/ntonjeta/Approximate/examples/kmeans/images/original.rgb";*/
/*char noaprx_image_path[] = "/home/ntonjeta/Approximate/examples/kmeans/images/noaprx.rgb";*/

/*//char approx_image_path[] = "/home/ntonjeta/Approximate/examples/jpeg/iideaa/outputs/output_large_decode.ppm";*/


/*double eDistance(RgbPixel p, RgbPixel q) {*/
  /*float r;*/

  /*r = 0;*/
  /*double r_tmp;*/

  /*[>double dataIn[6];<]*/
  /*[>dataIn[0] = p->r;<]*/
  /*[>dataIn[1] = p->g;<]*/
  /*[>dataIn[2] = p->b;<]*/
  /*[>dataIn[3] = c1->r;<]*/
  /*[>dataIn[4] = c1->g;<]*/
  /*[>dataIn[5] = c1->b;<]*/

  /*r += (p.r - q.r) * (p.r - q.r);*/
  /*r += (p.g - q.g) * (p.g - q.g);*/
  /*r += (p.b - q.b) * (p.b - q.b);*/

  /*r_tmp = sqrt(r);*/

  /*return r_tmp;*/
/*}*/


/*extern "C" double BELLERO_getError() {*/
   /*double error = 0;*/
  /*RgbImage noaprx;*/
  /*RgbImage srcImage;*/
  /*Clusters clusters;*/
  /*// Read no approximated image*/
  /*initRgbImage(&noaprx);*/
  /*loadRgbImage(noaprx_image_path, &noaprx,256);*/
  /*// Read Golden image */
  /*initRgbImage(&srcImage);*/
  /*loadRgbImage(golden_image_path, &srcImage,256);*/
  /*// Apply kmeans with aprx code*/
  /*initClusters(&clusters, 6, 1);*/
  /*segmentImage(&srcImage, &clusters, 1);*/

  /*// Calculate MSE */
  /*int i,j;*/
  /*double d = 0;*/

  /*int w = srcImage.w;*/
  /*int h = srcImage.h;*/

  /*for(i = 0; i<w; i++) {*/
    /*for( j = 0; j<h; j++){*/
      /*d += eDistance(srcImage.pixels[i][j],noaprx.pixels[i][j]);*/
    /*}*/
  /*}*/

  /*return d/(h*w);*/
/*}*/
