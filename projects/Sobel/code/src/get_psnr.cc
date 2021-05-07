#include <string>
#include <iostream>
#include <list>
#include <assert.h>
#include <dirent.h>
#include <sys/types.h>
#include <opencv2/opencv.hpp>
#include "metrics.h"
#include "sobel.h"


int main(int argc, char **argv)
{
    uint8_t        add1_axc   = atoi(argv[2]);
    uint8_t        add2_axc   = atoi(argv[3]);
    uint8_t        add3_axc   = atoi(argv[4]);
    uint8_t        add4_axc   = atoi(argv[5]);
    uint8_t        add5_axc   = atoi(argv[6]);
    int            num_images = 0;
    double         mpsnr      = 0;
    struct dirent  *entry     = NULL;
    DIR            *dir       = opendir(argv[1]);

    assert(dir != NULL);
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
          std::string image_file = std::string(argv[1]) + "/" + std::string(entry->d_name);
          cv::Mat orig = imread(image_file.c_str(), cv::IMREAD_GRAYSCALE);
          assert( orig.data && "No image data");
          cv::Mat reference, ax_image;
          sobel(orig, reference);
          ax_sobel(orig, ax_image, add1_axc, add2_axc, add3_axc, add4_axc, add5_axc);
          mpsnr += compute_psnr(reference, ax_image);
          num_images++;
        }
    }
    closedir(dir);
    mpsnr /= num_images;
    std::cout << mpsnr << std::endl;
}

