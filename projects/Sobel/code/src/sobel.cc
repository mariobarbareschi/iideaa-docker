#include "sobel.h"
#include "evoapproxlib.h"

using namespace evoapproxlib;

void sobel(cv::Mat& orig, cv::Mat& output)
{
    output = cv::Mat::zeros(orig.rows, orig.cols, CV_8U);
    for (int row = 1; row < orig.rows - 1; row++) {
        for (int col = 1; col < orig.cols - 1; col++) {
            int16_t mul1 = (orig.at<int16_t>(row, col-1) << 1);
            int16_t mul2 = (orig.at<int16_t>(row, col+1) << 1); 
            
            int16_t add1 = orig.at<int16_t>(row-1, col-1) + orig.at<int16_t>(row+1, col-1);
            int16_t add2 = add1 + mul1;
            int16_t add3 = orig.at<int16_t>(row-1, col+1) + orig.at<int16_t>(row+1, col+1);
            int16_t add4 = add3 + mul2;
            int16_t add4n = -add4;
            int16_t pixel = add2 + add4n;
              
            output.at<int16_t>(row, col) = pixel;
        }
    }
}

void ax_sobel(cv::Mat& orig, cv::Mat& output, uint8_t comp0, uint8_t comp1, uint8_t comp2, uint8_t comp3, uint8_t comp4)
{
    output = cv::Mat::zeros(orig.rows, orig.cols, CV_8U);
    for (int row = 1; row < orig.rows - 1; row++) {
        for (int col = 1; col < orig.cols - 1; col++) {
            int16_t mul1 = (orig.at<int16_t>(row, col-1) << 1);
            int16_t mul2 = (orig.at<int16_t>(row, col+1) << 1); 
            
            int16_t add1 = evoapproxlib::evoapprox_t(orig.at<int16_t>(row-1, col-1), comp0) + evoapproxlib::evoapprox_t(orig.at<int16_t>(row+1, col-1), comp0);
            int16_t add2 = evoapproxlib::evoapprox_t(add1, comp1) + evoapproxlib::evoapprox_t(mul1, comp1);
            int16_t add3 = evoapproxlib::evoapprox_t(orig.at<int16_t>(row-1, col+1), comp2) + evoapproxlib::evoapprox_t(orig.at<int16_t>(row+1, col+1), comp2);
            int16_t add4 = evoapproxlib::evoapprox_t(add3, comp3) + evoapproxlib::evoapprox_t(mul2, comp3);
            int16_t add4n = -add4;
            int16_t pixel = evoapproxlib::evoapprox_t(add2, comp4) + evoapproxlib::evoapprox_t(add4n, comp4);
              
            output.at<int16_t>(row, col) = pixel;
        }
    }
}
