cmake_minimum_required(VERSION 3.3)
project("iidea-axlib" VERSION 0.1 LANGUAGES CXX)

SET (CMAKE_C_FLAGS_INIT                                        "-Wall -std=c99")
SET (CMAKE_C_FLAGS_DEBUG_INIT                                              "-g")
SET (CMAKE_C_FLAGS_MINSIZEREL_INIT                               "-Os -DNDEBUG")
SET (CMAKE_C_FLAGS_RELEASE_INIT                                  "-O3 -DNDEBUG")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO_INIT                                 "-O2 -g")
SET (CMAKE_CXX_FLAGS_INIT                                               "-Wall")
SET (CMAKE_CXX_FLAGS_DEBUG_INIT                                            "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL_INIT                             "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE_INIT                                "-O3 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT                               "-O2 -g")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY                     ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY                    ${CMAKE_BINARY_DIR}/libs)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY                    ${CMAKE_BINARY_DIR}/libs)
set (CMAKE_CXX_FLAGS     "${CMAKE_CXX_FLAGS} -fsigned-char -march=native -fPIC")
set (CMAKE_CXX_STANDARD                                                      11)
set (CXX_STANDARD_REQUIRED                                                   ON)
set (CMAKE_EXPORT_COMPILE_COMMANDS                                           ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Wno-format-truncation")
else()
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_BUILD_TYPE Debug)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wextra -ggdb3 -O0 --coverage")
    endif()
endif()
set (INCLUDE_DIR                              ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(
    iideaa STATIC
    src/fap.cc
    src/trunc.cc
    src/vpa.cc
    src/vpa_n.cc
    src/evoapproxlib.cc
    src/evoapproxlib-lite/add8s_6FC.c
    src/evoapproxlib-lite/add8s_6FR.c
    src/evoapproxlib-lite/add8s_6H2.c
    src/evoapproxlib-lite/add8s_6HF.c
    src/evoapproxlib-lite/add8s_6J2.c
    src/evoapproxlib-lite/add8s_6PA.c
    src/evoapproxlib-lite/add8s_6PM.c
    src/evoapproxlib-lite/add8s_6QJ.c
    src/evoapproxlib-lite/add8s_6R6.c
    src/evoapproxlib-lite/add8s_6S5.c
    src/evoapproxlib-lite/add8s_6SN.c
    src/evoapproxlib-lite/add8s_6T8.c
    src/evoapproxlib-lite/add8s_6TN.c
    src/evoapproxlib-lite/add8s_6TR.c
    src/evoapproxlib-lite/add8s_6UC.c
    src/evoapproxlib-lite/add8s_6UN.c
    src/evoapproxlib-lite/add8s_6X7.c
    src/evoapproxlib-lite/add8s_6X9.c
    src/evoapproxlib-lite/add8s_6XL.c
    src/evoapproxlib-lite/add8s_6YE.c
    src/evoapproxlib-lite/add8s_6YG.c
    src/evoapproxlib-lite/add8s_6ZP.c
    src/evoapproxlib-lite/add8s_701.c
    src/evoapproxlib-lite/add8s_704.c
    src/evoapproxlib-lite/add8s_70F.c
    src/evoapproxlib-lite/add8s_70S.c
    src/evoapproxlib-lite/add8s_70Z.c
    src/evoapproxlib-lite/add8s_7YK.c
    src/evoapproxlib-lite/add8s_83C.c
    src/evoapproxlib-lite/add8s_83N.c
    src/evoapproxlib-lite/add8se_72D.c
    src/evoapproxlib-lite/add8se_76P.c
    src/evoapproxlib-lite/add8se_78P.c
    src/evoapproxlib-lite/add8se_7A2.c
    src/evoapproxlib-lite/add8se_7C9.c
    src/evoapproxlib-lite/add8se_7J7.c
    src/evoapproxlib-lite/add8se_7LN.c
    src/evoapproxlib-lite/add8se_7N1.c
    src/evoapproxlib-lite/add8se_8TX.c
    src/evoapproxlib-lite/add8se_8UF.c
    src/evoapproxlib-lite/add8se_8UN.c
    src/evoapproxlib-lite/add8se_8UT.c
    src/evoapproxlib-lite/add8se_8V4.c
    src/evoapproxlib-lite/add8se_8VV.c
    src/evoapproxlib-lite/add8se_8XS.c
    src/evoapproxlib-lite/add8se_8YC.c
    src/evoapproxlib-lite/add8se_8ZU.c
    src/evoapproxlib-lite/add8se_8ZX.c
    src/evoapproxlib-lite/add8se_90J.c
    src/evoapproxlib-lite/add8se_90R.c
    src/evoapproxlib-lite/add8se_90X.c
    src/evoapproxlib-lite/add8se_90Z.c
    src/evoapproxlib-lite/add8se_91D.c
    src/evoapproxlib-lite/add8se_91V.c
    src/evoapproxlib-lite/add8se_91X.c
    src/evoapproxlib-lite/add8se_91Y.c
    src/evoapproxlib-lite/add8se_92J.c
    src/evoapproxlib-lite/add8u_006.c
    src/evoapproxlib-lite/add8u_01R.c
    src/evoapproxlib-lite/add8u_04A.c
    src/evoapproxlib-lite/add8u_0CA.c
    src/evoapproxlib-lite/add8u_0FP.c
    src/evoapproxlib-lite/add8u_0H4.c
    src/evoapproxlib-lite/add8u_1DK.c
    src/evoapproxlib-lite/add8u_2XT.c
    src/evoapproxlib-lite/add8u_4T8.c
    src/evoapproxlib-lite/add8u_5EZ.c
    src/evoapproxlib-lite/add8u_5G5.c
    src/evoapproxlib-lite/add8u_5HQ.c
    src/evoapproxlib-lite/add8u_5LT.c
    src/evoapproxlib-lite/add8u_5M7.c
    src/evoapproxlib-lite/add8u_5ME.c
    src/evoapproxlib-lite/add8u_5NH.c
    src/evoapproxlib-lite/add8u_5NQ.c
    src/evoapproxlib-lite/add8u_5QL.c
    src/evoapproxlib-lite/add8u_5R3.c
    src/evoapproxlib-lite/add8u_5SY.c
    src/evoapproxlib-lite/add8u_88L.c
    src/evoapproxlib-lite/add8u_8AS.c
    src/evoapproxlib-lite/add8u_8BB.c
    src/evoapproxlib-lite/add8u_8ES.c
    src/evoapproxlib-lite/add8u_8FD.c
    src/evoapproxlib-lite/add8u_8FF.c
    src/evoapproxlib-lite/add8u_8GM.c
    src/evoapproxlib-lite/add8u_8KJ.c
    src/evoapproxlib-lite/add8u_8KZ.c
    src/evoapproxlib-lite/add8u_8LL.c
    src/evoapproxlib-lite/add8u_8MK.c
    src/evoapproxlib-lite/mul8s_1KR3.c
    src/evoapproxlib-lite/mul8s_1KR6.c
    src/evoapproxlib-lite/mul8s_1KR8.c
    src/evoapproxlib-lite/mul8s_1KRC.c
    src/evoapproxlib-lite/mul8s_1KTY.c
    src/evoapproxlib-lite/mul8s_1KV8.c
    src/evoapproxlib-lite/mul8s_1KVA.c
    src/evoapproxlib-lite/mul8s_1KVB.c
    src/evoapproxlib-lite/mul8s_1KVL.c
    src/evoapproxlib-lite/mul8s_1KX2.c
    src/evoapproxlib-lite/mul8s_1L1G.c
    src/evoapproxlib-lite/mul8s_1L2D.c
    src/evoapproxlib-lite/mul8s_1L2H.c
    src/evoapproxlib-lite/mul8u_125K.c
    src/evoapproxlib-lite/mul8u_12N4.c
    src/evoapproxlib-lite/mul8u_13QR.c
    src/evoapproxlib-lite/mul8u_1446.c
    src/evoapproxlib-lite/mul8u_14VP.c
    src/evoapproxlib-lite/mul8u_150Q.c
    src/evoapproxlib-lite/mul8u_17C8.c
    src/evoapproxlib-lite/mul8u_17KS.c
    src/evoapproxlib-lite/mul8u_17QU.c
    src/evoapproxlib-lite/mul8u_185Q.c
    src/evoapproxlib-lite/mul8u_18DU.c
    src/evoapproxlib-lite/mul8u_19DB.c
    src/evoapproxlib-lite/mul8u_1AGV.c
    src/evoapproxlib-lite/mul8u_1CMB.c
    src/evoapproxlib-lite/mul8u_1JFF.c
    src/evoapproxlib-lite/mul8u_2AC.c
    src/evoapproxlib-lite/mul8u_2HH.c
    src/evoapproxlib-lite/mul8u_2P7.c
    src/evoapproxlib-lite/mul8u_7C1.c
    src/evoapproxlib-lite/mul8u_CK5.c
    src/evoapproxlib-lite/mul8u_DM1.c
    src/evoapproxlib-lite/mul8u_E9R.c
    src/evoapproxlib-lite/mul8u_FTA.c
    src/evoapproxlib-lite/mul8u_GS2.c
    src/evoapproxlib-lite/mul8u_JQQ.c
    src/evoapproxlib-lite/mul8u_JV3.c
    src/evoapproxlib-lite/mul8u_KEM.c
    src/evoapproxlib-lite/mul8u_L40.c
    src/evoapproxlib-lite/mul8u_LM7.c
    src/evoapproxlib-lite/mul8u_NGR.c
    src/evoapproxlib-lite/mul8u_QJD.c
    src/evoapproxlib-lite/mul8u_QKX.c
    src/evoapproxlib-lite/mul8u_RCG.c
    src/evoapproxlib-lite/mul8u_Y48.c
    src/evoapproxlib-lite/mul8u_YX7.c
    src/evoapproxlib-lite/mul8u_ZFB.c
)

target_include_directories(iideaa PRIVATE include)

add_subdirectory(test)
