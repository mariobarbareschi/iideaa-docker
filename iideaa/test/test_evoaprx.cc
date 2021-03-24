#include "evoapproxlib.h"
#include <iostream>

int main()
{
    for (int i = 0; i < 10; i++)
    {
        std::cout << "circuit " << i << " area " << evoapproxlib::evoapprox_u8_t::mul8u_area(i) << std::endl;
    }
}