#include "evoapproxlib.h"
#include "evoapprox-lite_8bit.h"
#include <stdint.h>
#include <stdlib.h>
#include <limits>

typedef int16_t(*mul8s_fptr)(int8_t, int8_t);
typedef struct {
   mul8s_fptr fptr;
   double power;
   double area;
} mult_8s_t;
const int mult_8s_N = 13;
mult_8s_t mult_8s_array[mult_8s_N] = {
   {.fptr = mul8s_1KV8, .power = 0.425, .area = 729.800},
   {.fptr = mul8s_1KVA, .power = 0.422, .area = 711.000},
   {.fptr = mul8s_1KVB, .power = 0.41,  .area = 685.200},
   {.fptr = mul8s_1KR6, .power = 0.363, .area = 635.000},
   {.fptr = mul8s_1L2H, .power = 0.301, .area = 558.900},
   {.fptr = mul8s_1L2D, .power = 0.2,   .area = 411.600},
   {.fptr = mul8s_1L1G, .power = 0.126, .area = 284.900},
   {.fptr = mul8s_1KR3, .power = 0.052, .area = 172.200},
   {.fptr = mul8s_1KX2, .power = 0.391, .area = 641.1},
   {.fptr = mul8s_1KRC, .power = 0.351, .area = 599.8},
   {.fptr = mul8s_1KVL, .power = 0.289, .area = 543},
   {.fptr = mul8s_1KR8, .power = 0.369, .area = 652.8},
   {.fptr = mul8s_1KTY, .power = 0.237, .area = 482.4},
};

int16_t evoapproxlib::evoapprox_s8_t::mul8s (int8_t multiplicand, int8_t multiplier, uint32_t approx_component)
{
   if (approx_component < mult_8s_N)
      return mult_8s_array[approx_component].fptr(multiplicand, multiplier);
   else
      return multiplicand * multiplier;
}

double evoapproxlib::evoapprox_s8_t::mul8s_power(uint32_t approx_component)
{
   if (approx_component < mult_8s_N)
      return mult_8s_array[approx_component].power;
   else
      return std::numeric_limits<double>::infinity();
}

double evoapproxlib::evoapprox_s8_t::mul8s_area(uint32_t approx_component)
{
   if (approx_component < mult_8s_N)
      return mult_8s_array[approx_component].area;
   else
      return std::numeric_limits<double>::infinity();
}

typedef uint64_t(*mul8u_fptr)(uint64_t, uint64_t);
typedef struct {
   mul8u_fptr fptr;
   float power;
   float area;
} mult_8u_t;

const int mult_8u_N = 36;
mult_8u_t mult_8u_array[mult_8u_N]= {
   {.fptr = mul8u_1JFF, .power = 0.391 , .area = 709.6 },
   {.fptr = mul8u_2P7 , .power = 0.386 , .area = 676.3 },
   {.fptr = mul8u_KEM , .power = 0.370 , .area = 637.8 },
   {.fptr = mul8u_CK5 , .power = 0.345 , .area = 604.5 },
   {.fptr = mul8u_2HH , .power = 0.302 , .area = 542.5 },
   {.fptr = mul8u_19DB, .power = 0.206 , .area = 395.6 },
   {.fptr = mul8u_17KS, .power = 0.104 , .area = 239.3 },
   {.fptr = mul8u_JV3 , .power = 0.034 , .area = 110.8 },
   {.fptr = mul8u_17QU, .power = 0.0017, .area = 13.1 },
   {.fptr = mul8u_E9R , .power = 0.000 , .area = 0.0},
   {.fptr = mul8u_Y48 , .power = 0.390 , .area = 682.8 },
   {.fptr = mul8u_LM7 , .power = 0.380 , .area = 663.6 },
   {.fptr = mul8u_150Q, .power = 0.360 , .area = 660.3 },
   {.fptr = mul8u_2AC , .power = 0.311 , .area = 508.3 },
   {.fptr = mul8u_185Q, .power = 0.206 , .area = 427.5 },
   {.fptr = mul8u_FTA , .power = 0.084 , .area = 214.5 },
   {.fptr = mul8u_13QR, .power = 0.0085, .area =  41.3 },
   {.fptr = mul8u_125K, .power = 0.384 , .area = 674.9 },
   {.fptr = mul8u_14VP, .power = 0.364 , .area = 654.2 },
   {.fptr = mul8u_ZFB , .power = 0.304 , .area = 590.4 },
   {.fptr = mul8u_12N4, .power = 0.142 , .area = 390.5 },
   {.fptr = mul8u_QKX , .power = 0.029 , .area = 112.2 },
   {.fptr = mul8u_1446, .power = 0.388 , .area = 683.3 },
   {.fptr = mul8u_JQQ , .power = 0.371 , .area = 661.2 },
   {.fptr = mul8u_GS2 , .power = 0.356 , .area = 632.6 },
   {.fptr = mul8u_7C1 , .power = 0.329 , .area = 606.8 },
   {.fptr = mul8u_RCG , .power = 0.309 , .area = 561.8 },
   {.fptr = mul8u_1CMB, .power = 0.237 , .area = 479.2 },
   {.fptr = mul8u_L40 , .power = 0.189 , .area = 437.4 },
   {.fptr = mul8u_YX7 , .power = 0.061 , .area = 220.6 },
   {.fptr = mul8u_QJD , .power = 0.344 , .area = 624.2 },
   {.fptr = mul8u_NGR , .power = 0.276 , .area = 511.5 },
   {.fptr = mul8u_DM1 , .power = 0.195 , .area = 401.7 },
   {.fptr = mul8u_1AGV, .power = 0.095 , .area = 228.5 },
   {.fptr = mul8u_18DU, .power = 0.031 , .area = 96.7 },
   {.fptr = mul8u_17C8, .power = 0.0019, .area =  15.5 },
};

uint16_t evoapproxlib::evoapprox_u8_t::mul8u (uint8_t multiplicand, uint8_t multiplier, uint32_t approx_component)
{
   if (approx_component < mult_8u_N)
      return mult_8u_array[approx_component].fptr(multiplicand, multiplier);
   else
      return multiplicand * multiplier;
}

double evoapproxlib::evoapprox_u8_t::mul8u_power(uint32_t approx_component)
{
   if (approx_component < mult_8u_N)
      return mult_8u_array[approx_component].power;
   else
      return std::numeric_limits<double>::infinity();
}

double evoapproxlib::evoapprox_u8_t::mul8u_area(uint32_t approx_component)
{
   if (approx_component < mult_8u_N)
      return mult_8u_array[approx_component].area;
   else
      return std::numeric_limits<double>::infinity();
}

typedef uint64_t(*add8s_fptr)(uint64_t, uint64_t);
typedef struct {
   add8s_fptr fptr;
   float power;
   float area;
} add_8s_t;
const int add_8s_N = 56;
add_8s_t add_8s_array[add_8s_N]= {
   {add8s_83C, 0.034, 70.4},
   {add8s_83N, 0.033, 74.1},
   {add8s_6FR, 0.032, 67.1},
   {add8s_6TR, 0.03, 67.6},
   {add8s_6UN, 0.025, 57.3},
   {add8s_6PM, 0.021, 48.3},
   {add8s_6H2, 0.017, 44.6},
   {add8s_6J2, 0.012, 32.9},
   {add8s_701, 0.0054, 21.6},
   {add8s_6HF, 0, 0},
   {add8s_6X7, 0.033, 64.8},
   {add8s_6SN, 0.032, 71.8},
   {add8s_6FC, 0.027, 55.8},
   {add8s_6ZP, 0.025, 57.3},
   {add8s_6X9, 0.016, 39.4},
   {add8s_6T8, 0.0063, 26.8},
   {add8s_6XL, 0.03, 63.8},
   {add8s_704, 0.024, 54.4},
   {add8s_6UC, 0.02, 51.2},
   {add8s_6PA, 0.017, 40.8},
   {add8s_6YG, 0.031, 75.6},
   {add8s_7YK, 0.03, 71.8},
   {add8s_6S5, 0.028, 63.4},
   {add8s_70Z, 0.02, 57.7},
   {add8s_6QJ, 0.029, 60.5},
   {add8s_6TN, 0.022, 56.8},
   {add8s_6YE, 0.017, 38},
   {add8s_70S, 0.013, 31.4},
   {add8s_70F, 0.0099, 35.7},
   {add8s_6R6, 0.0039, 18.8},
   {add8se_7A2, 0.035, 74.6},
   {add8se_8YC, 0.034, 70.4},
   {add8se_72D, 0.03, 65.7},
   {add8se_7LN, 0.026, 59.1},
   {add8se_7J7, 0.021, 52.6},
   {add8se_91D, 0.019, 39.9},
   {add8se_92J, 0.014, 31},
   {add8se_90Z, 0.0093, 22.1},
   {add8se_8UN, 0.0042, 11.7},
   {add8se_8XS, 0, 0},
   {add8se_91X, 0.032, 70.4},
   {add8se_76P, 0.016, 41.3},
   {add8se_8UF, 0.0094, 23.5},
   {add8se_7N1, 0.002, 10.8},
   {add8se_90X, 0.000065, 1.4},
   {add8se_7C9, 0.034, 78.4},
   {add8se_78P, 0.03, 65.2},
   {add8se_90J, 0.024, 54.9},
   {add8se_8VV, 0.019, 41.3},
   {add8se_8V4, 0.033, 66.6},
   {add8se_91Y, 0.028, 57.7},
   {add8se_90R, 0.023, 48.8},
   {add8se_8UT, 0.019, 41.3},
   {add8se_8ZX, 0.014, 32.4},
   {add8se_8TX, 0.0094, 23.5},
   {add8se_91V, 0.0042, 11.7}
};

int8_t evoapproxlib::evoapprox_s8_t::add8s (int8_t addendum1, int8_t addendum2, uint32_t approx_component) {
   if (approx_component < add_8s_N)
      return add_8s_array[approx_component].fptr(addendum1, addendum2);
   else
      return addendum1 * addendum2;
}

double evoapproxlib::evoapprox_s8_t::add8s_power(uint32_t approx_component) {
   if (approx_component < add_8s_N)
      return add_8s_array[approx_component].power;
   else
      return std::numeric_limits<double>::infinity();
}

double evoapproxlib::evoapprox_s8_t::add8s_area(uint32_t approx_component) {
   if (approx_component < add_8s_N)
      return add_8s_array[approx_component].area;
   else
      return std::numeric_limits<double>::infinity();
}

typedef uint64_t(*add8u_fptr)(uint64_t, uint64_t);
typedef struct {
   add8u_fptr fptr;
   float power;
   float area;
} add_8u_t;
const int add_8u_N = 31;
add_8u_t add_8u_array[add_8u_N]= {
   {add8u_0FP, 0.033, 70.400},
   {add8u_5R3, 0.029, 63.800},
   {add8u_5QL, 0.024, 57.300},
   {add8u_5LT, 0.021, 56.300},
   {add8u_5HQ, 0.017, 53.000},
   {add8u_5SY, 0.012, 28.200},
   {add8u_8LL, 0.0095, 25.800},
   {add8u_006, 0.0046, 15.000},
   {add8u_8ES, 0.0015, 8},
   {add8u_88L, 0, 0},
   {add8u_4T8, 0.028, 61.5},
   {add8u_01R, 0.023, 52.6},
   {add8u_5EZ, 0.019, 43.6},
   {add8u_1DK, 0.016, 53},
   {add8u_2XT, 0.012, 26.8},
   {add8u_0H4, 0.0075, 17.8},
   {add8u_8AS, 0.0032, 8.9},
   {add8u_04A, 0, 0},
   {add8u_5ME, 0.019, 48.3},
   {add8u_5G5, 0.014, 37.1},
   {add8u_8KZ, 0.011, 32.9},
   {add8u_8GM, 0.0015, 8},
   {add8u_5NQ, 0.026, 63.8},
   {add8u_8MK, 0.023, 65.7},
   {add8u_8FF, 0.019, 56.8},
   {add8u_8FD, 0.018, 65.2},
   {add8u_8KJ, 0.014, 45.5},
   {add8u_8BB, 0.0092, 35.2},
   {add8u_5M7, 0.023, 50.7},
   {add8u_5NH, 0.014, 34.7},
   {add8u_0CA, 0.0032, 8.9},
};

uint8_t evoapproxlib::evoapprox_u8_t::add8u (uint8_t addendum1, uint8_t addendum2, uint32_t approx_component) {
   if (approx_component < add_8u_N)
      return add_8u_array[approx_component].fptr(addendum1, addendum2);
   else
      return addendum1 * addendum2;
}
double evoapproxlib::evoapprox_u8_t::add8u_power(uint32_t approx_component) {
   if (approx_component < add_8u_N)
      return add_8u_array[approx_component].power;
   else
      return std::numeric_limits<double>::infinity();
}

double evoapproxlib::evoapprox_u8_t::add8u_area(uint32_t approx_component) {
   if (approx_component < add_8u_N)
      return add_8u_array[approx_component].area;
   else
      return std::numeric_limits<double>::infinity();
}