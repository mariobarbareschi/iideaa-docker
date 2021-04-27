#ifndef _METRICS_H_
#define _METRICS_H_

#include <opencv2/opencv.hpp>

double compute_mse(const cv::Mat& I1, const cv::Mat& I2);
double compute_psnr(const cv::Mat& orig, const cv::Mat& target);
double compute_mssim(const cv::Mat& orig, const cv::Mat& target);
double compute_dssim(const cv::Mat& orig, const cv::Mat& target);

#endif