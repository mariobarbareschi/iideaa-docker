#include "taylor.h"
#include "vpa.h"
#include "stirling.h"

double taylor::factorSin(double x0, int index){
    double ret;
    ret = std::pow(-1, index)/stirling::Stirling(2*index+1)*std::pow(x0,2*index+1);
    return ret;
}

double taylor::taylorSin(double x0, int degree){
    int i;
    double acc = 0.0;
    for(i=0; i < degree; i++){
        acc += taylor::factorSin(x0, i);
    }
    return acc;
}