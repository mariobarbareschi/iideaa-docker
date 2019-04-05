
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
