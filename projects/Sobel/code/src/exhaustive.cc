#include <string>
#include <iostream>
#include <filesystem>
#include <list>
#include <omp.h>
#include <opencv2/opencv.hpp>
#include "metrics.h"
#include "sobel.h"
#include "evoapproxlib.h"

namespace fs = std::filesystem;
using namespace evoapproxlib;


int main(int argc, char **argv)
{
    const int add_16s_N = 19;
    std::cout <<"ConfID\t\tPSNR\tArea\tPower" << std::endl;

    int num_threads = omp_get_max_threads();
    #pragma omp parallel for num_threads(num_threads)
    for (uint8_t add1_axc = 1; add1_axc < add_16s_N; add1_axc++)
        for (uint8_t add2_axc = 1; add2_axc < add_16s_N; add2_axc++)
            for (uint8_t add3_axc = 1; add3_axc < add_16s_N; add3_axc++)
                for (uint8_t add4_axc = 1; add4_axc < add_16s_N; add4_axc++)
                    for (uint8_t add5_axc = 1; add5_axc < add_16s_N; add5_axc++)
                    {
                        int num_images = 0;
                        double mpsnr = 0;
                        for (const auto & entry : fs::directory_iterator(argv[1]))
                        {
                            //std::cout << "Processing image " << entry.path() << std::endl;
                            cv::Mat orig = imread(entry.path().c_str(), cv::IMREAD_GRAYSCALE);
                            assert( orig.data && "No image data");
                            cv::Mat reference, ax_image;
                            sobel(orig, reference);
                            ax_sobel(orig, ax_image, add1_axc, add2_axc, add3_axc, add4_axc, add5_axc);
                            mpsnr += compute_psnr(reference, ax_image);
                            num_images++;
                        }
                        mpsnr /= num_images;
                        double area = evoapprox_t::add16s_area(add1_axc) + evoapprox_t::add16s_area(add2_axc) + evoapprox_t::add16s_area(add3_axc) + evoapprox_t::add16s_area(add4_axc) + evoapprox_t::add16s_area(add5_axc);
                        double power = evoapprox_t::add16s_power(add1_axc) + evoapprox_t::add16s_power(add2_axc) + evoapprox_t::add16s_power(add3_axc) + evoapprox_t::add16s_power(add4_axc) + evoapprox_t::add16s_power(add5_axc);
                        
                        #pragma omp critical
                        std::cout << (int)add1_axc <<"_" << (int)add2_axc <<"_" << (int)add3_axc <<"_" << (int)add4_axc <<"_" << (int)add5_axc <<"\t" << mpsnr << "\t" << area << "\t" << power << std::endl;
                    }
}

