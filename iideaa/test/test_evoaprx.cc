#include "evoapproxlib.h"
#include <iostream>

int main()
{
    for (int i = 0; i < 5; i++)
    {
        evoapproxlib::evoapprox_t a((int16_t)10, i);
        evoapproxlib::evoapprox_t b((int16_t)10, i);
        int16_t c = a * b;
        std::cout << c << std::endl;
    }
}
