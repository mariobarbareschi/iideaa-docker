

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

float  newton ();
using namespace std;

extern "C" double BELLERO_getError() {    
	
	float golden_res = 2.740646;
	float axc_res;
	float error;

	axc_res = newton ();
	error = abs(axc_res - golden_res);
	
	return (error);

}

