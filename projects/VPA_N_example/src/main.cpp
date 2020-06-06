#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>

#include "taylor.h"

double factorial(int n){
    double ret = n;
    while(--n > 1)
        ret*=n;
    return ret;
}

int main(){
    ::std::ofstream oracle ( "taylor_oracle", ::std::ofstream::out );
    double val;
    for(int t = 0; t < 1000; t++){
        val = (double) 2-((double)rand()/(double)(RAND_MAX));
        oracle << ::std::setprecision ( ::std::numeric_limits<double>::digits10 + 1 ) << val << " "
               << ::std::setprecision ( ::std::numeric_limits<double>::digits10 + 1 )
               << taylor::taylorSin(val, 100) << "\n";

    }
    return 0;
}