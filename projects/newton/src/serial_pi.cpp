#include<stdio.h>
#include<math.h>

float f(float x);
float df (float x);

float  newton()
{
    int itr, maxmitr;
    float h, x0, x1, allerr;
   
    
    maxmitr = 120;   
    x0 = 45.4; 
    for (itr=1; itr<=maxmitr; itr++)
    {
        h=f(x0)/df(x0);
        x1=x0-h;
        x0=x1;
    }
    return x0;
}

int  main () {


    printf(" Result = %f\n", newton() ); 
}

float f(float x)
{
    return x*log10(x) - 1.2;
}
float df (float x)
{
    return log10(x) + 0.43429;
}
