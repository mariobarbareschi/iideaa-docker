#include <string>
#include <iostream>
#include "evoapproxlib.h"

using namespace evoapproxlib;


int main(int argc, char **argv)
{
    uint8_t add1_axc = atoi(argv[1]);
    uint8_t add2_axc = atoi(argv[2]);
    uint8_t add3_axc = atoi(argv[3]);
    uint8_t add4_axc = atoi(argv[4]);
    uint8_t add5_axc = atoi(argv[5]);

    double area =  evoapprox_t((int16_t)0, add1_axc).getAddArea() + 
                    evoapprox_t((int16_t)0, add2_axc).getAddArea() + 
                    evoapprox_t((int16_t)0, add3_axc).getAddArea() + 
                    evoapprox_t((int16_t)0, add4_axc).getAddArea() + 
                    evoapprox_t((int16_t)0, add5_axc).getAddArea();
    std::cout << area << std::endl;
}

