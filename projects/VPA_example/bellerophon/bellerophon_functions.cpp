#include<iostream>
#include<fstream>
#include <math.h>

#include "vpa.h"
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

extern vpa::FloatingPointPrecision OP_0, OP_1, OP_2;

extern "C" double BELLERO_Reward()
{
  double rew = 0;

//  MantType mant;
  int gradeMant[3];
  int gradeExp[3];

  gradeMant[0] = 54 - OP_0.mant_size;
  gradeMant[1] = 54 - OP_1.mant_size;
  gradeMant[2] = 54 - OP_2.mant_size;

    
  gradeExp[0] = 11 - OP_0.exp_size;
  gradeExp[1] = 11 - OP_1.exp_size;
  gradeExp[2] = 11 - OP_2.exp_size;

    for(int i=0; i<3; i++)
        rew+=gradeMant[i]*gradeMant[i]+gradeExp[i];
//printf("Reward: %g\n\n", rew);
  return rew;
}
