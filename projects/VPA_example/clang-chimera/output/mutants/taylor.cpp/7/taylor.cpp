#include "taylor.h"
#include "vpa.h"
#include "stirling.h"

::vpa::FloatingPointPrecision OP_1 = ::vpa::double_prec;
::vpa::FloatingPointPrecision OP_0 = ::vpa::double_prec;
double taylor::factorSin(double x0, int index){
    double ret;
    ret =(double)( ::vpa::VPA(::vpa::VPA(std::pow(-1, index), OP_1)/::vpa::VPA(stirling::Stirling(2*index+1), OP_1), OP_0) *::vpa::VPA(std::pow(x0,2*index+1), OP_0)/*II OP_0*/ );
    return ret;
}

::vpa::FloatingPointPrecision OP_2 = ::vpa::double_prec;
double taylor::taylorSin(double x0, int degree){
    int i;
    double acc = 0.0;
    for(i=0; i < degree; i++){
        acc = (double)(::vpa::VPA(acc, OP_2) + ::vpa::VPA(taylor::factorSin(x0, i), OP_2));
    }
    return acc;
}