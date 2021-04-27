#ifndef SOBEL_HH
#define SOBEL_HH

#include <inttypes.h>
#include <opencv2/opencv.hpp>

void sobel(cv::Mat& orig, cv::Mat& output);
void ax_sobel(cv::Mat& orig, cv::Mat& output, uint8_t comp1, uint8_t comp2, uint8_t comp3, uint8_t comp4, uint8_t comp5);

#endif
