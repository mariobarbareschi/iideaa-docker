#include<iostream>
#include<fstream>
#include <math.h>

#include "vpa_n.h"
bool vpa_n::VPA::UPCASTING = false;

#include "taylor.h"

extern "C" double BELLERO_getError() {    
    double error = 0, oracle_val, taylor_val;
    int c = 0; // Counter

    ::std::string x, value;
    ::std::ifstream oracle ( "../src/build/taylor_oracle" );
    if ( !oracle.good() ) {
        ::std::cerr << "The oracle does not exist!\n";
        exit ( 1 );
    }

    // Read oracle's values
    oracle >> x >> value;
    do {
        c++;
        oracle_val = ::std::atof ( value.c_str() );
        taylor_val = taylor::taylorSin(::std::atof ( x.c_str() ), 100 );
        error += fabs ( taylor_val - oracle_val );
        oracle >> x >> value;
    } while ( !oracle.eof() );

    return (double)error/c;
}
