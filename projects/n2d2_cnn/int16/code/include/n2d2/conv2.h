// N2D2 auto-generated file.
// @ Mon Sep 16 12:44:48 2019

#ifndef N2D2_EXPORTC_CONV2_LAYER_H
#define N2D2_EXPORTC_CONV2_LAYER_H

#include "typedefs.h"
#define CONV2_NB_OUTPUTS 16
#define CONV2_NB_CHANNELS 6
#define CONV2_OUTPUTS_WIDTH 10
#define CONV2_OUTPUTS_HEIGHT 10
#define CONV2_OUTPUT_OFFSET 0
#define CONV2_OX_SIZE 10
#define CONV2_OY_SIZE 10
#define CONV2_CHANNELS_WIDTH 14
#define CONV2_CHANNELS_HEIGHT 14
#define CONV2_KERNEL_WIDTH 5
#define CONV2_KERNEL_HEIGHT 5
#define CONV2_SUB_SAMPLE_X 1
#define CONV2_SUB_SAMPLE_Y 1
#define CONV2_STRIDE_X 1
#define CONV2_STRIDE_Y 1
#define CONV2_PADDING_X 0
#define CONV2_PADDING_Y 0

#define CONV2_ACTIVATION Rectifier
#define CONV2_SHIFT 2
static const BDATA_T conv2_biases[CONV2_NB_OUTPUTS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static const WDATA_T conv2_weights_0_0[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {3014, 7548, 11561, 11869, 6541},
    {1996, 5161, 6910, 2254, 1937},
    {3424, 1753, 16286, 27012, 22570},
    {21, -4496, -1617, 4843, 6852},
    {1865, 6011, 2939, 6277, 17537}};
static const WDATA_T conv2_weights_0_1[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-4002, -6515, -10997, -8690, -2421},
    {-1954, -1229, 1612, 16305, 32767},
    {-8843, -3852, -1807, -11763, -4517},
    {-5477, -3476, 19144, 29781, 786},
    {-4381, -10469, -5376, 22786, 12872}};
static const WDATA_T conv2_weights_0_2[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {1965, 6753, 4982, -949, -5237},
    {3453, 230, -197, -1657, -3140},
    {-1295, -132, -4891, -5039, -1384},
    {-5106, -325, -9034, -11825, -6001},
    {-10768, -10302, -9025, -9405, -9281}};
static const WDATA_T conv2_weights_1_1[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {12373, 9775, -5432, -9018, -4128},
    {3201, 15847, 17057, -550, -9251},
    {-2875, -2975, 16615, 18005, 1317},
    {8925, -1692, 1551, 18201, 16630},
    {9154, 1869, -7374, 79, 7505}};
static const WDATA_T conv2_weights_1_2[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-10575, -10285, -5225, 7798, 12797},
    {-9977, -12666, -14156, -958, 107},
    {-6345, -8145, -11617, -9229, -5404},
    {-91, -101, -1406, -985, 3293},
    {8017, 6075, -797, -692, 2191}};
static const WDATA_T conv2_weights_1_3[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-4838, -3285, 7178, 5482, 681},
    {3432, -9513, -2802, 5185, 4747},
    {5378, -3311, -12767, -6665, 628},
    {-3162, 2420, -5998, -13657, -11176},
    {-674, 2452, -971, -2586, -3333}};
static const WDATA_T conv2_weights_2_2[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {21022, 15481, -724, -6544, 16788},
    {14258, 10082, -6160, 1722, 20960},
    {9721, 7490, -8807, 4469, 13257},
    {4400, 2102, -6835, 4535, 7368},
    {-1565, 4543, -2838, 3255, 2061}};
static const WDATA_T conv2_weights_2_3[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-9604, -6844, -12361, -16179, -14120},
    {-5528, -5871, -9939, -14389, -13020},
    {-7480, -8252, -10209, -12095, -8443},
    {-3173, -6973, -10869, -8483, -3292},
    {402, -6552, -13774, -9804, 5202}};
static const WDATA_T conv2_weights_2_4[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {5503, 8943, 3020, -3835, -5054},
    {5903, 16169, 1461, -8726, 756},
    {2612, 12884, -4155, -11694, 2594},
    {-3133, 5624, -4982, -7876, 1736},
    {-3702, 8152, 4665, -5551, -4222}};
static const WDATA_T conv2_weights_3_3[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {20523, 27027, 25991, 18081, 4053},
    {5925, 3568, 7046, 4838, -2598},
    {4526, 374, -3899, -7737, -9939},
    {4509, 4701, -584, -2370, -5633},
    {-5, 2146, -1786, -1575, -5047}};
static const WDATA_T conv2_weights_3_4[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {3074, -4887, -418, -2040, -6084},
    {1199, -5552, -4893, -4499, -8287},
    {5333, -3466, -4387, -3961, -7508},
    {3966, -2841, -3786, -3453, -7936},
    {-119, -2381, -4484, -6167, -6430}};
static const WDATA_T conv2_weights_3_5[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {11461, 4792, -2041, 2202, 1027},
    {2387, -2748, -9040, -7167, -2284},
    {-7161, -3416, -5551, -7139, -2831},
    {-6651, 4120, -2460, -4953, -1777},
    {247, 900, -1520, -2977, -3759}};
static const WDATA_T conv2_weights_4_0[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {3229, 5684, 6090, 4926, 12489},
    {2537, 8052, 2279, 9859, 13405},
    {4893, 5068, 2751, 13935, 3844},
    {10260, 7342, 11590, 16503, 5944},
    {11493, 7919, 9100, 9158, 3541}};
static const WDATA_T conv2_weights_4_4[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-3471, -1758, -6527, 4061, -6320},
    {802, -3387, -13642, 8590, -15101},
    {3194, -8043, -12961, 12458, -18535},
    {4438, -11211, -10262, 6453, -11257},
    {-654, -12661, -9337, -1104, -1255}};
static const WDATA_T conv2_weights_4_5[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-1596, -1891, 1149, -1364, 8935},
    {-1796, 3422, 3269, -7271, 15947},
    {-7338, 7569, 49, -9264, 16940},
    {-5377, 7069, -3694, -3745, 12598},
    {-819, 7053, -3587, -1691, 2253}};
static const WDATA_T conv2_weights_5_0[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-1969, -4422, -6918, -3911, -1004},
    {-2828, -2373, -2607, -3732, -3168},
    {965, 767, -2037, -4417, -4035},
    {4152, 2885, 2378, 1331, -1263},
    {3932, 246, 259, -242, -1372}};
static const WDATA_T conv2_weights_5_1[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {13883, 5065, -3899, -3640, -1113},
    {16309, 17740, 5003, 193, -1976},
    {2467, 16343, 11838, 8579, 6084},
    {-3609, 4807, 7126, 5355, 3794},
    {-19216, -11099, -2608, -2436, -1841}};
static const WDATA_T conv2_weights_5_5[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-128, 593, -10373, -12959, -9620},
    {-1883, 4989, -7123, -10101, -8443},
    {-4935, 9078, -678, -6961, -7587},
    {-4783, 10282, 5818, -1467, -5577},
    {-2979, 3779, 3640, 447, -2271}};
static const WDATA_T conv2_weights_6_0[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {1768, 912, -2944, -3949, -3169},
    {-112, 838, -789, -1233, 1027},
    {2082, -249, -1429, -446, 9329},
    {1425, -384, 1434, 9069, 14170},
    {-1592, -2248, 3233, 4247, -2083}};
static const WDATA_T conv2_weights_6_1[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-2887, -5804, -6959, -9069, -12999},
    {-4198, -6382, -9055, -4949, 1546},
    {-2048, -3068, -692, 4617, 5783},
    {-7316, -5304, 618, -3326, -7655},
    {-3104, -3870, -3932, -6874, -4287}};
static const WDATA_T conv2_weights_6_2[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {1864, -16, -1640, -4811, -1027},
    {-727, -2167, -1572, 26, 14763},
    {-3925, -3951, 3425, 13967, 19023},
    {-2634, 3005, 17710, 15265, 9649},
    {7654, 15057, 19127, 5775, -89}};
static const WDATA_T conv2_weights_6_3[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {8281, 7491, 3520, -1073, -1363},
    {8584, 4319, -4174, -15431, -16392},
    {6307, 3748, -3264, -11028, -11014},
    {2482, -786, -7476, -11291, -5913},
    {-4612, -9928, -14467, -15627, -11581}};
static const WDATA_T conv2_weights_7_1[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-7479, -2804, -446, -2840, -4570},
    {-15549, -15544, -6499, -765, -5139},
    {-16917, -14843, -11095, -3179, -3314},
    {-13066, -12222, -11454, -4127, -4092},
    {-11391, -8321, -3612, 483, 5317}};
static const WDATA_T conv2_weights_7_2[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {728, 701, -840, -7525, 93},
    {-8498, 3513, 3686, -4130, 5935},
    {-8292, 6738, 3869, 700, 11426},
    {141, 6632, 3059, 7747, 8558},
    {585, 93, 3914, 5474, -446}};
static const WDATA_T conv2_weights_7_3[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {2836, -1537, -3899, -5276, -7897},
    {553, 1533, -5255, -7879, -9309},
    {144, 871, -10430, -9636, -10664},
    {4741, 6812, -238, -10895, -13376},
    {8381, 8885, 168, -13805, -15456}};
static const WDATA_T conv2_weights_7_4[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {18189, 9534, 9041, -75, -9219},
    {8399, 11430, 15583, -4795, -7809},
    {1852, 14445, 12809, -5125, -3320},
    {400, 11398, 4009, 778, -2397},
    {-5703, 1079, 3266, 8474, 264}};
static const WDATA_T conv2_weights_8_2[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {150, 9114, 16187, 1830, -5904},
    {-7136, -5649, -4271, 3803, 7976},
    {285, 10211, 28269, 26725, 15263},
    {15645, 18919, 16364, 3453, -2262},
    {4566, -232, -6460, -6383, 3227}};
static const WDATA_T conv2_weights_8_3[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-1801, -4778, 3432, 14035, 15898},
    {17781, 24909, 30217, 19156, 1957},
    {11568, 10089, 1356, -9844, -2467},
    {-11919, -13983, -4637, 5087, 10124},
    {-8420, -2495, 4440, 8409, 1987}};
static const WDATA_T conv2_weights_8_4[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-2713, 281, -3632, -8395, -8858},
    {-4507, -5997, -15327, -12337, -7934},
    {-9554, -8537, -12601, -7934, -9886},
    {-11058, -10349, -9385, -3582, -1685},
    {-9291, -4263, 883, 2363, -2510}};
static const WDATA_T conv2_weights_8_5[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-5252, -2026, 2764, 3717, 2060},
    {-13609, -4912, 3212, -1964, -8918},
    {-19157, -7402, -6783, -14705, -5711},
    {-15101, -7486, -3346, -1468, 3434},
    {-2791, -1458, -6028, -4591, -7186}};
static const WDATA_T conv2_weights_9_0[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-1922, 2229, 4416, -2810, -5618},
    {1635, 1053, -3098, 8402, 9720},
    {-2615, 2742, 14688, 20935, 1478},
    {7077, 18392, 13158, 4334, -3023},
    {5883, -2352, -6038, -2111, -4885}};
static const WDATA_T conv2_weights_9_3[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-2637, 106, 3859, -2144, -14329},
    {-7300, -4585, -6111, -13152, -4667},
    {-10011, -9249, -10049, 3089, 5146},
    {-7264, -1259, 11540, 12615, 1000},
    {17244, 15494, 8358, 1735, -6817}};
static const WDATA_T conv2_weights_9_4[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {3500, 2959, -3603, 98, 7935},
    {1621, 794, 2900, 6474, 6375},
    {1792, 8144, 6380, 1453, -2292},
    {4304, -2127, -2947, -4888, -9906},
    {-3857, -8284, -7549, -13131, -14106}};
static const WDATA_T conv2_weights_9_5[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-2788, -3065, -1052, -9607, -11578},
    {-3089, -820, -798, -9011, 4138},
    {462, -5232, -4239, 10231, 15043},
    {-1841, 748, 7842, 9865, 5866},
    {1765, 2139, -3581, -4201, -9684}};
static const WDATA_T conv2_weights_10_0[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-7, -105, -25, 480, 207},
    {688, -513, 708, -102, 147},
    {-222, 53, -257, -260, 36},
    {-400, -775, -159, -428, -54},
    {708, -1056, -1046, -548, 781}};
static const WDATA_T conv2_weights_10_1[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-419, -120, 731, 4, 146},
    {-465, -340, -21, 923, 956},
    {-929, 520, -335, -702, -336},
    {-273, 90, -157, -1201, -1074},
    {215, 428, 214, 1521, 1239}};
static const WDATA_T conv2_weights_10_4[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {409, -191, -949, -941, -353},
    {72, -13, 163, -234, 567},
    {-77, 415, -18, 583, -636},
    {-220, 142, 199, 386, -77},
    {-301, -660, -809, 783, 1706}};
static const WDATA_T conv2_weights_10_5[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-314, -264, -887, 230, -997},
    {129, 70, -453, -380, -865},
    {-108, 109, -35, -466, 154},
    {404, -242, -1233, 154, -121},
    {-635, -502, 52, -400, -816}};
static const WDATA_T conv2_weights_11_0[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {2170, 769, 2874, 4527, 1958},
    {429, 785, 3629, 1511, 467},
    {-1462, 21, -193, -62, -355},
    {-1082, -604, -633, -733, -1342},
    {-1240, -506, -752, -483, -507}};
static const WDATA_T conv2_weights_11_1[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {1675, 684, 937, -470, -2779},
    {-1922, -292, 154, -1583, -3542},
    {-3125, -2313, 254, 345, -664},
    {-1458, -1696, -404, 1881, 2467},
    {144, -535, -1109, -823, -1214}};
static const WDATA_T conv2_weights_11_2[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-140, 2653, 4418, 4263, 498},
    {-524, 1795, 786, 672, 25},
    {-2231, -385, -657, -1465, 410},
    {-3370, -1297, -1188, -1319, 363},
    {-1826, -559, -1002, -1876, -2443}};
static const WDATA_T conv2_weights_11_5[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {2926, 1673, 2553, 4144, 3054},
    {2984, 428, 4015, 5241, 1529},
    {-1010, -2778, 1863, 1288, -1514},
    {-3582, -4537, -2129, -2294, -2451},
    {-3735, -4443, -3802, -3546, -2338}};
static const WDATA_T conv2_weights_12_0[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-825, -1911, -4119, -6029, -6006},
    {34, -1292, -4580, -7952, -12715},
    {-2108, -36, -4911, -10015, -9607},
    {687, 1926, -2954, -5563, 12},
    {6884, 4585, 636, -502, 1076}};
static const WDATA_T conv2_weights_12_1[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {404, -3026, -10523, -12071, -5587},
    {-2305, -2186, -5847, -10443, -7470},
    {-1963, 2833, 3522, -1372, -4412},
    {7767, 11123, 12138, 6760, -5282},
    {-1936, -897, -1604, -3717, -13060}};
static const WDATA_T conv2_weights_12_3[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-2267, -8484, -10265, -12999, -18362},
    {-2521, -6884, -8007, -9652, -18691},
    {-1527, -5022, -7212, -6798, -13370},
    {753, 1498, -2810, -7068, -7264},
    {10120, 15554, 3203, -4172, 3784}};
static const WDATA_T conv2_weights_12_4[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-1936, -5269, -5974, 5982, 9516},
    {-3475, -6092, -8405, 4559, 16508},
    {-3536, -7348, -9781, 2884, 20663},
    {-1380, -4468, -4521, 7956, 19301},
    {-3663, -4740, -1569, 13331, 14137}};
static const WDATA_T conv2_weights_13_1[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-784, 2348, 1592, 2350, 3462},
    {-5379, -2555, 762, 3027, 2758},
    {2478, 1738, -2389, -4275, -5254},
    {16031, 22029, 24643, 15171, 6767},
    {8446, 15633, 22853, 26041, 15167}};
static const WDATA_T conv2_weights_13_2[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-6918, -757, 5696, 9976, 13823},
    {-7246, -2465, 7442, 8606, 8910},
    {-9828, -15839, -15531, -12750, -8168},
    {4747, -6883, -16123, -17315, -8771},
    {13423, 8331, 7377, 4545, -426}};
static const WDATA_T conv2_weights_13_4[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {2695, 3574, 3371, 8020, 7858},
    {-4736, -1547, 2449, 8600, 7408},
    {-11507, -9095, -3011, 2926, -1431},
    {-8113, -11043, -11481, -9310, -8767},
    {-1421, -1199, -1344, -6400, -6713}};
static const WDATA_T conv2_weights_13_5[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {7062, 6639, 3051, 373, 1821},
    {-4063, -6788, -3677, -956, 4174},
    {-16712, -15121, -9348, -5997, -515},
    {-16285, -12677, -13250, -14356, -14514},
    {-1530, -122, -4109, -5746, -11317}};
static const WDATA_T conv2_weights_14_0[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {1977, 7379, 9205, 9682, 6970},
    {-3706, 1775, 11273, 12576, 9875},
    {-6579, -7646, 575, 9808, 6930},
    {-4122, -3095, -2933, 4634, 8543},
    {-6184, -3170, -2300, -688, 1142}};
static const WDATA_T conv2_weights_14_2[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {3826, 8961, 5995, -1820, 322},
    {-3395, -277, -5279, -3905, -592},
    {-3657, -3282, -10088, -5099, 2437},
    {-12459, -12921, -15519, -14672, -8431},
    {-4857, -8002, -9143, -8882, -10141}};
static const WDATA_T conv2_weights_14_3[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-5749, -11127, -6769, -2376, -4713},
    {1438, -11059, -9501, -3075, 671},
    {11892, 2100, -7699, 391, 3150},
    {12699, 21691, 15307, 3636, -4590},
    {-5490, 12835, 21324, 19187, 11018}};
static const WDATA_T conv2_weights_14_5[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {6007, 10042, 6197, -1226, 2028},
    {-481, 7021, 12123, 1306, 3957},
    {-9587, -3542, 2316, -1110, -581},
    {-14500, -13969, -9404, -11184, -6603},
    {-11252, -14485, -12823, -9526, -2526}};
static const WDATA_T conv2_weights_15_0[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {534, 943, -1026, -3138, -3887},
    {9984, 11813, 1610, -2813, -998},
    {15491, 7185, 885, -505, 405},
    {5474, 1676, 168, -1085, 4413},
    {-609, 454, 128, 4426, 8467}};
static const WDATA_T conv2_weights_15_1[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-5998, -3614, -4103, -11558, -11200},
    {-3410, -5068, -11119, -11607, -8482},
    {-4766, -8313, -5855, -2678, -152},
    {-6051, -1368, 6033, 8143, 7924},
    {27, 11140, 14660, 8007, 6974}};
static const WDATA_T conv2_weights_15_2[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {103, 3984, 2864, -1239, 3601},
    {13259, 10124, 474, -1000, 2276},
    {12218, 2332, -1451, -1565, 4762},
    {-4821, -3001, 1566, 6254, 7041},
    {-4034, 4899, 7415, 6873, 3636}};
static const WDATA_T conv2_weights_15_3[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {459, -7616, -11685, -7750, -4607},
    {-5753, -5367, -2240, -7562, -11637},
    {-4088, 2659, -1000, -5049, -8734},
    {2885, -4969, -6510, -6161, -1959},
    {1589, -3910, -2890, -4132, -2793}};
static const WDATA_T conv2_weights_15_4[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {7640, 13724, 706, -5320, -9103},
    {12877, 8971, -4777, -10889, -11717},
    {3026, -4208, -11042, -10745, -8650},
    {-7602, -8487, -9225, -4459, -2484},
    {-4373, -437, -360, 675, 2677}};
static const WDATA_T conv2_weights_15_5[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH] = {
    {-2819, 6732, 16155, 6898, 255},
    {-1325, 16056, 19044, 219, -6544},
    {13264, 17886, 5424, -6065, -8892},
    {11654, -82, -7758, -8678, -6839},
    {-4491, -9121, -2806, -2753, 3259}};
typedef WDATA_T CONV2_KERNEL_T[CONV2_KERNEL_HEIGHT][CONV2_KERNEL_WIDTH];
static const CONV2_KERNEL_T* conv2_weights[CONV2_NB_OUTPUTS][CONV2_NB_CHANNELS] = {
    {&conv2_weights_0_0, &conv2_weights_0_1, &conv2_weights_0_2, NULL, NULL, NULL},
    {NULL, &conv2_weights_1_1, &conv2_weights_1_2, &conv2_weights_1_3, NULL, NULL},
    {NULL, NULL, &conv2_weights_2_2, &conv2_weights_2_3, &conv2_weights_2_4, NULL},
    {NULL, NULL, NULL, &conv2_weights_3_3, &conv2_weights_3_4, &conv2_weights_3_5},
    {&conv2_weights_4_0, NULL, NULL, NULL, &conv2_weights_4_4, &conv2_weights_4_5},
    {&conv2_weights_5_0, &conv2_weights_5_1, NULL, NULL, NULL, &conv2_weights_5_5},
    {&conv2_weights_6_0, &conv2_weights_6_1, &conv2_weights_6_2, &conv2_weights_6_3, NULL, NULL},
    {NULL, &conv2_weights_7_1, &conv2_weights_7_2, &conv2_weights_7_3, &conv2_weights_7_4, NULL},
    {NULL, NULL, &conv2_weights_8_2, &conv2_weights_8_3, &conv2_weights_8_4, &conv2_weights_8_5},
    {&conv2_weights_9_0, NULL, NULL, &conv2_weights_9_3, &conv2_weights_9_4, &conv2_weights_9_5},
    {&conv2_weights_10_0, &conv2_weights_10_1, NULL, NULL, &conv2_weights_10_4, &conv2_weights_10_5},
    {&conv2_weights_11_0, &conv2_weights_11_1, &conv2_weights_11_2, NULL, NULL, &conv2_weights_11_5},
    {&conv2_weights_12_0, &conv2_weights_12_1, NULL, &conv2_weights_12_3, &conv2_weights_12_4, NULL},
    {NULL, &conv2_weights_13_1, &conv2_weights_13_2, NULL, &conv2_weights_13_4, &conv2_weights_13_5},
    {&conv2_weights_14_0, NULL, &conv2_weights_14_2, &conv2_weights_14_3, NULL, &conv2_weights_14_5},
    {&conv2_weights_15_0, &conv2_weights_15_1, &conv2_weights_15_2, &conv2_weights_15_3, &conv2_weights_15_4, &conv2_weights_15_5}};

#endif // N2D2_EXPORTC_CONV2_LAYER_H
