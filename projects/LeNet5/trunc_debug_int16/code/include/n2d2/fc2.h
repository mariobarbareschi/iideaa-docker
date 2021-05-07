// N2D2 auto-generated file.
// @ Mon Sep 16 12:44:48 2019

#ifndef N2D2_EXPORTC_FC2_LAYER_H
#define N2D2_EXPORTC_FC2_LAYER_H

#include "typedefs.h"
#define FC2_NB_OUTPUTS 10
#define FC2_NB_CHANNELS 84
#define FC2_OUTPUT_OFFSET 0

#define FC2_ACTIVATION Linear
#define FC2_SHIFT 2
static const BDATA_T fc2_biases[FC2_NB_OUTPUTS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#define FC2_NB_WEIGHTS (FC2_NB_OUTPUTS*FC2_NB_CHANNELS)

static const WDATA_T fc2_weights[FC2_NB_OUTPUTS][FC2_NB_CHANNELS] = 
{
    {-97, 147, -1070, -85, -1117, -20, -238, -61, -338, -69, -32, -141, 287, -100, 17890, -456, -100, -20, 17376, 17416, -51, -347, -535, -498, -41, -361, -210, -19, -126, 17054, -87, -36, -24, -1103, -21, -461, -92, -454, -1092, -52, -434, -12, -23, -81, 17245, -399, 17380, -189, -109, 10834, -447, -563, -200, -84, -5, -110, -162, -72, -509, -951, -324, -540, -1058, -1040, -17, 17093, -958, -112, -158, 17220, -118, -118, -195, -86, -450, -217, -32, -208, -84, -211, -80, 3867, -118, -184},
    {-183, 156, -207, -159, -142, -64, -157, -138, -197, 17423, -153, -134, 945, -60, -98, -234, 17012, -111, -123, -47, -90, -149, -165, -235, -35, -245, -186, 16868, 17199, -88, 17252, -50, -43, -145, -63, -257, -191, -185, -81, 15849, -168, -85, -132, -132, -127, -272, -128, -148, 16565, 101, -134, -204, -166, 38, -46, -123, -247, 17335, -232, -118, -149, -221, -157, -50, -71, -88, -99, -114, -182, -128, -20, -82, -139, -156, -270, -215, -52, -138, 17326, -159, -60, 1742, -101, -150},
    {-140, 143, 19647, -298, 20007, -160, -288, -69, -140, -26, -150, -329, 2560, -57, -929, -56, -38, -150, -831, -942, -421, 16, -7, 9, -303, -120, -205, -31, -72, -1001, -97, -200, -44, 20716, -348, -123, -92, -141, 19886, 69, 75, -399, -202, -228, -762, -108, -1070, -253, -70, 12733, 48, -59, -349, -198, -227, -41, -203, -21, -94, 19795, -176, -19, 20370, 20011, -365, -878, 19608, -258, -306, -1050, -190, -41, -307, -95, -117, -95, -130, -142, -44, -366, -136, 82, -77, -123},
    {-525, -77, -319, -763, -416, -374, -683, -163, -430, -66, -341, -835, 5469, -149, -6, -32, -59, -317, -53, -85, 20004, -52, -23, -36, 19976, -408, -295, -121, -68, -96, -115, 19327, -225, -382, 20064, -202, -129, -264, -247, -68, -41, 19948, 20114, -369, -60, -345, 8, -646, -50, -90, -28, -51, -898, -282, 18899, -136, -445, -113, -376, -271, -406, -37, -148, -333, 19877, -23, -156, -587, -444, -61, -484, -130, -614, -219, -399, -390, -260, -466, -49, -401, -406, 319, -154, -468},
    {-176, -146, -209, -1444, -38, -107, -1517, 21196, -281, 5, -86, -1634, 1906, 21261, -149, -97, -104, -109, -90, -67, -181, -128, -220, -364, -191, -277, -239, -79, -224, -103, -175, -191, -120, -148, -150, -255, 21327, -211, -84, 111, -236, -188, -199, -149, -135, -264, -66, -1343, -154, -52, -165, -293, -1484, -162, -148, 20782, -226, -178, -285, -117, -281, -30, -59, -113, -137, -41, -134, -1605, -180, -80, 14154, 21840, -1205, 21418, -270, -200, -136, -300, -190, -243, -112, 1977, 21634, -211},
    {-160, -186, -119, -449, -125, -152, -535, -200, 20254, -198, -155, -486, 2608, -141, -381, -651, -161, -200, -349, -317, -381, -598, -504, -548, -351, 20768, -493, -119, -172, -281, -181, -385, -122, -130, -172, 20547, -223, 21167, -77, -164, -598, -512, -266, -129, -324, 20112, -289, -277, -136, -266, -655, -772, -513, -203, 53, -228, -502, -118, 20240, -120, -510, -721, -100, -150, -389, -407, -127, -413, -670, -247, -309, -211, -475, -236, 20014, -341, -142, -347, -84, -596, -169, 6227, -245, -290},
    {-15, 13, 0, -192, -22, -7, -161, -226, -745, -172, -17, -180, -20, -209, -369, 17488, -150, -23, -422, -380, -22, 17904, 18159, 17827, 0, -844, -412, -131, -108, -430, -154, -7, -15, -25, 9, -595, -161, -832, -14, -93, 17304, 3, -23, -17, -401, -802, -520, -160, -207, -60, 17655, 17238, -203, -33, 17, -213, -422, -171, -756, 1, -383, 17085, -5, 10, -35, -347, -29, -142, -273, -329, -164, -206, -182, -219, -828, -305, -23, -296, -116, -356, -5, 7104, -268, -267},
    {18758, 203, -118, -485, -4, 19406, -476, -135, -186, -117, 18857, -469, 3336, -116, -30, -20, -103, 18671, -32, -24, -376, -19, -16, -18, -318, -191, -201, -89, -131, -30, -107, -418, 18675, -163, -302, -152, -96, -211, -213, -72, -14, -355, -370, 18961, -11, -161, -39, -422, -138, -85, -13, -23, -531, 18470, -202, -203, -166, -113, -207, -241, -280, -16, -196, -467, -276, -28, -295, -466, -304, -33, -66, -90, -494, -201, -171, -145, 19225, -219, 1, -240, 19223, 139, -101, -223},
    {-226, -40, -189, -476, -230, -167, -504, -172, -501, -75, -257, -482, 3432, -114, -166, -291, -45, -231, -160, -213, -322, -202, -329, -401, -392, -375, 22288, -103, -157, -93, -40, -321, -159, -196, -364, -441, -115, -459, -348, -145, -331, -448, -286, -206, -158, -485, -186, -417, -151, 130, -244, -380, -505, -177, -222, -197, 23232, -105, -345, -223, 22517, -310, -155, -297, -211, -90, -210, -407, 22788, -69, -220, -185, -367, -178, -519, 21766, -216, 22973, -278, 22501, -200, 2728, -180, 22507},
    {-323, 4, -352, 22104, -244, -413, 22542, -1536, -492, -131, -205, 22588, 6740, -1457, -93, -177, -130, -328, -180, -152, -669, -148, -182, -213, -635, -366, -490, -73, -136, -51, -103, -565, -280, -306, -680, -482, -1346, -513, -243, -88, -181, -619, -630, -437, -26, -469, -86, 22692, -129, -180, -156, -194, 22075, -275, -473, -1305, -375, -132, -460, -302, -417, -177, -258, -315, -540, -40, -306, 22368, -530, -105, 9053, -1186, 22066, -1264, -442, -340, -370, -565, -81, -533, -397, 1720, -1691, -563}};

#endif // N2D2_EXPORTC_FC2_LAYER_H
