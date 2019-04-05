#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "segmentation.h"
#include "csv.h"
#include "fap.h"
//paths to the input image and output of approximate version

// BELLEROPHON FUNCTION

char golden_image_path[] = "../images/original.rgb";
char noaprx_image_path[] = "../images/noaprx.rgb";

char report_path[] = "../chimera/output/mutants/segmentation.cpp/1/flap_float_report.csv";

double eDistance(RgbPixel p, RgbPixel q) {
  float r;

  r = 0;
  double r_tmp;
 /* cout<<"r:"<<p.r<<endl;
  cout<<"g:"<<p.g<<endl;
  cout<<"b:"<<p.b<<endl;

  cout<<endl;*/

  r += (p.r - q.r) * (p.r - q.r);
  r += (p.g - q.g) * (p.g - q.g);
  r += (p.b - q.b) * (p.b - q.b);

  r_tmp = sqrt(r);

  return r_tmp;
}


extern "C" double BELLERO_getError() {
   
  RgbImage noaprx;
  RgbImage srcImage;
  Clusters clusters1, clusters2;
  // Read no approximated image
  initRgbImage(&noaprx);
  loadRgbImage(noaprx_image_path, &noaprx,256);
  // Read Golden image
  initRgbImage(&srcImage);
  loadRgbImage(golden_image_path, &srcImage,256);
  // Apply kmeans with aprx code
  initClusters(&clusters1, 6, 1);
  segmentImage(&srcImage, &clusters1, 1);

  initClusters(&clusters2, 6, 1);
  segmentImage(&noaprx, &clusters2, 1);

  // Calculate MSE
  int i,j;
  double d = 0;

  int w = srcImage.w;
  int h = srcImage.h;

  for(i = 0; i<w; i++) {
    for( j = 0; j<h; j++){
      d += eDistance(srcImage.pixels[i][j],noaprx.pixels[i][j]);
    }
  }

  freeRgbImage(&srcImage);
  freeRgbImage(&noaprx);
  freeClusters(&clusters1);
  freeClusters(&clusters2);

  //cout<<"error: "<<d/(h*w)<<endl;
  /*cout<<"distance: "<<d<<endl;
  
  cout<<"error*3: "<<d/(3*h*w)<<endl;*/
  return d/(h*w);
}

extern fap::FloatPrecTy OP_0, OP_1, OP_2, OP_3, OP_4, OP_5;

extern "C" double BELLERO_Reward()
{
  double rew = 0;

//  MantType mant;
  int grade[6];

  grade[0] = 23 - OP_0.mant_size;
  grade[1] = 23 - OP_1.mant_size;
  grade[2] = 23 - OP_2.mant_size;
  grade[3] = 23 - OP_3.mant_size;
  grade[4] = 23 - OP_4.mant_size;
  grade[5] = 23 - OP_5.mant_size;


  rew = (double)grade[0] + (double)grade[1] + (double)grade[2] + (double)pow(grade[3],2) + (double)pow(grade[4],2) + (double)pow(grade[5],2);
  //rew = (double)2*grade[0] + 2*pow(grade[1],2) + 2*pow(grade[3],2) + 2*pow(grade[4],2) + 2*pow(grade[5],2);
//  FloatPrecTy prec = OP_1.getPrec();

//  cout << prec.mant_size;

  return rew;
}
