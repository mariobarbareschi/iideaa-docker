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

int evoApprox8u_component_4 = 0;
int evoApprox8u_component_3 = 0;
int evoApprox8u_component_2 = 0;
int evoApprox8u_component_1 = 0;
int evoApprox8u_component_0 = 0;
void ax_sobel(cv::Mat& orig, cv::Mat& output)
{
    output = cv::Mat::zeros(orig.rows, orig.cols, CV_8U);
    for (int row = 1; row < orig.rows - 1; row++) {
        for (int col = 1; col < orig.cols - 1; col++) {
            int16_t mul1 = (orig.at<int16_t>(row, col-1) << 1);
            int16_t mul2 = (orig.at<int16_t>(row, col+1) << 1); 
            
            int16_t add1 = evoapproxlib::evoapprox_t(orig.at<int16_t>(row-1, col-1), evoApprox8u_component_0) + evoapproxlib::evoapprox_t(orig.at<int16_t>(row+1, col-1), evoApprox8u_component_0);
            int16_t add2 = evoapproxlib::evoapprox_t(add1, evoApprox8u_component_1) + evoapproxlib::evoapprox_t(mul1, evoApprox8u_component_1);
            int16_t add3 = evoapproxlib::evoapprox_t(orig.at<int16_t>(row-1, col+1), evoApprox8u_component_2) + evoapproxlib::evoapprox_t(orig.at<int16_t>(row+1, col+1), evoApprox8u_component_2);
            int16_t add4 = evoapproxlib::evoapprox_t(add3, evoApprox8u_component_3) + evoapproxlib::evoapprox_t(mul2, evoApprox8u_component_3);
            int16_t add4n = -add4;
            int16_t pixel = evoapproxlib::evoapprox_t(add2, evoApprox8u_component_4) + evoapproxlib::evoapprox_t(add4n, evoApprox8u_component_4);
              
            output.at<int16_t>(row, col) = pixel;
        }
    }
}
