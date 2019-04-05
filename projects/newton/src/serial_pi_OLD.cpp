

#include <cstdio>
#include "vpa_n.h"

#define N 100000


double pi_computation () {

	int i;
	double x, sum = 0.0;
	double num_steps=N;
	double step, pi;
	
	
	step = 1.0/ num_steps;

	for (i=0; i< N; i = i+2){
		x = (i+0.5)*step;
		sum = sum + 4.0/(1.0 + x*x);
	}
	pi = step * sum;
	return pi;

}

int main()  {  

	double pi;
	pi = pi_computation ();

	printf("Pi = %f\n",pi);

	return 0;
}
