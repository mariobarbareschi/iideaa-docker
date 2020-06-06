// Amir
#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>

#include "helperIntrinsics.h"

using namespace std;

#include "vpa.h"

typedef struct threadIdx_struct{int x; int y; int z;} threadIdx_t;
typedef struct blockDim_struct{int x; int y; int z;} blockDim_t;
typedef struct blockIdx_struct{int x; int y; int z;} blockIdx_t;

threadIdx_t threadIdx = {0,0,0};
blockDim_t blockDim = {0,0,0};
blockIdx_t blockIdx = {0,0,0};

float cndGPU(float d)
{
    const float       A1 = 0.31938153f;
    const float       A2 = -0.356563782f;
    const float       A3 = 1.781477937f;
    const float       A4 = -1.821255978f;
    const float       A5 = 1.330274429f;
    const float RSQRT2PI = 0.39894228040143267793994605993438f;

    float K = 1.0f / (1.0f + 0.2316419f * fabsf(d));

    float cnd = RSQRT2PI * __expf(- 0.5f * d * d) *
          (K * (A1 + K * (A2 + K * (A3 + K * (A4 + K * A5)))));

    if (d > 0)
        cnd = 1.0f - cnd;

    return cnd;
}


void BlackScholesBodyGPU(
    float &CallResult,
    float &PutResult,
    float S, //Stock price
    float X, //Option strike
    float T, //Option years
    float R, //Riskless rate
    float V  //Volatility rate
)
{
    float sqrtT, expRT;
    float d1, d2, CNDD1, CNDD2;
    
    sqrtT = sqrtf(T);
    d1 = (__logf(S / X) + (R + 0.5f * V * V) * T) / (V * sqrtT);
    d2 = d1 - V * sqrtT;

    CNDD1 = cndGPU(d1);
    CNDD2 = cndGPU(d2);

    //Calculate Call and Put simultaneously
    expRT = __expf(- R * T);
    CallResult = S * CNDD1 - X * expRT * CNDD2;
   
    PutResult  = X * expRT * (1.0f - CNDD2) - S * (1.0f - CNDD1);
}


void BlackScholesGPU(
    float *d_CallResult,
    float *d_PutResult,
    float *d_StockPrice,
    float *d_OptionStrike,
    float *d_OptionYears,
    float Riskfree,
    float Volatility,
    int optN
)
{

    const int opt = blockDim.x * blockIdx.x + threadIdx.x;
    if (opt < optN)
        BlackScholesBodyGPU(
            d_CallResult[opt],
            d_PutResult[opt],
            d_StockPrice[opt],
            d_OptionStrike[opt],
            d_OptionYears[opt],
            Riskfree,
            Volatility
        );
}

////////////////////////////////////////////////////////////////////////////////
// Helper function, returning uniformly distributed
// random float in [low, high] range
////////////////////////////////////////////////////////////////////////////////
float RandFloat(float low, float high)
{
    float t = (float)rand() / (float)RAND_MAX;
    return (1.0f - t) * low + t * high;
}

////////////////////////////////////////////////////////////////////////////////
// Data configuration
////////////////////////////////////////////////////////////////////////////////
const int OPT_N = 4000000;
const int  NUM_ITERATIONS = 1; // Amir: Change number of iteration


const int          OPT_SZ = OPT_N * sizeof(float);
const float      RISKFREE = 0.02f;
const float    VOLATILITY = 0.30f;

#define DIV_UP(a, b) ( ((a) + (b) - 1) / (b) )


int main(int argc, char* argv[]){
    if(argc < 2){
        std::cerr << "you must provide a test input file" << std::endl;
        return -1;
    }
    ::std::ofstream oracle ( "bs_oracle.txt", ::std::ofstream::out );
    ::std::ifstream dataFile ( argv[1], ::std::ofstream::out );
    int numberOptions;
    dataFile >> numberOptions;
    float h_StockPrice[1], h_OptionStrike[1], h_OptionYears[1], callResult[1], putResult[1];

    //Generate options set
    for (int i = 0; i < numberOptions; i++)
    {
        dataFile >> h_StockPrice[0] >> h_OptionStrike[0] >> h_OptionYears[0];
        BlackScholesGPU(callResult, putResult, h_StockPrice, h_OptionStrike, h_OptionYears, RISKFREE, VOLATILITY, numberOptions);
        oracle << ::std::setprecision ( ::std::numeric_limits<double>::digits10 + 1 ) << h_StockPrice[0] << " " << h_OptionStrike[0] << " " <<  h_OptionYears[0] << " "
               << ::std::setprecision ( ::std::numeric_limits<double>::digits10 + 1 )
               << callResult[0] << " " << putResult[0] << "\n";
    }
    return 0;

}
