/******************************************************************************
 * @file   fap.h
 * @author Mario Barbareschi
 * @date   April 6th 2017
 * @brief  Bellerophon functions for the Bessel Algorithm Approximated through
 *         clang-chimera and FLAP mutator operator
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <math.h>


#include "bessel.h"


char oracle_path[]= "./bessel_oracle.txt";


extern "C" double BELLERO_getError()
{
    // Local vars
    double error = 0, oracle_val, b_val;
    int c = 0; // Counter

    ::std::string x, value;
    ::std::ifstream oracle ( oracle_path );
    if ( !oracle.good() ) {
        ::std::cerr << "The oracle does not exist!\n";
        exit ( 1 );
    }

    // Read oracle's values
    oracle >> x >> value;
    do {
        c++;
        oracle_val = ::std::atof ( value.c_str() );
        b_val = BESSJ ( 0, ::std::atof ( x.c_str() ) );
        error += fabs ( b_val - oracle_val ) < 10e-16 ? 0 : fabs ( b_val - oracle_val );
        oracle >> x >> value;
    } while ( !oracle.eof() );

    return (double)error/c;
}
