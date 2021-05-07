
#include "stirling.h"

double stirling::Stirling(int n){
    double ret = STIRLING_FACTOR*std::sqrt(n)*pow(n/std::exp(1.0), n);
    return ret;
}