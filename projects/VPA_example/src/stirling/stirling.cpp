
#include "stirling.h"

#include <iostream>

double stirling::Stirling(int n){
    double ret = stirling::STIRLING_FACTOR*std::sqrt(n)*pow(n/std::exp(1.0), n);
    std::cout << stirling::STIRLING_FACTOR << std::endl;
    return ret;
}
