/***********************************************************************
*                                                                      *
*    Program to calculate the first kind Bessel function of integer    *
*    order N, for any REAL X, using the function BESSJ(N,X).           *
*                                                                      *
* -------------------------------------------------------------------- *
*                                                                      *
*    SAMPLE RUN:                                                       *
*                                                                      *
*    (Calculate Bessel function for N=2, X=0.75).                      *
*                                                                      *
*    Bessel function of order  2 for X =  0.7500:                      *
*                                                                      *
*         Y =  0.06707400                                              *
*                                                                      *
* -------------------------------------------------------------------- *
*   Reference: From Numath Library By Tuan Dang Trong in Fortran 77.   *
*                                                                      *
*                               C++ Release 1.0 By J-P Moreau, Paris.  *
*                                        (www.jpmoreau.fr)             *
***********************************************************************/
#include <math.h>
#include <stdio.h>
#include <cstdlib>

#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>

#include "bessel.h"

#include "fap.h"


::fap::FloatPrecTy OP_45(11,52);
::fap::FloatPrecTy OP_44(11,52);
::fap::FloatPrecTy OP_43(11,52);
::fap::FloatPrecTy OP_42(11,52);
::fap::FloatPrecTy OP_41(11,52);
::fap::FloatPrecTy OP_40(11,52);
::fap::FloatPrecTy OP_39(11,52);
::fap::FloatPrecTy OP_38(11,52);
::fap::FloatPrecTy OP_37(11,52);
::fap::FloatPrecTy OP_36(11,52);
::fap::FloatPrecTy OP_35(11,52);
::fap::FloatPrecTy OP_34(11,52);
::fap::FloatPrecTy OP_33(11,52);
::fap::FloatPrecTy OP_32(11,52);
::fap::FloatPrecTy OP_31(11,52);
::fap::FloatPrecTy OP_30(11,52);
::fap::FloatPrecTy OP_29(11,52);
::fap::FloatPrecTy OP_28(11,52);
::fap::FloatPrecTy OP_27(11,52);
::fap::FloatPrecTy OP_26(11,52);
::fap::FloatPrecTy OP_25(11,52);
::fap::FloatPrecTy OP_24(11,52);
::fap::FloatPrecTy OP_23(11,52);
::fap::FloatPrecTy OP_22(11,52);
::fap::FloatPrecTy OP_21(11,52);
::fap::FloatPrecTy OP_20(11,52);
::fap::FloatPrecTy OP_19(11,52);
::fap::FloatPrecTy OP_18(11,52);
::fap::FloatPrecTy OP_17(11,52);
::fap::FloatPrecTy OP_16(11,52);
::fap::FloatPrecTy OP_15(11,52);
::fap::FloatPrecTy OP_14(11,52);
::fap::FloatPrecTy OP_13(11,52);
::fap::FloatPrecTy OP_12(11,52);
::fap::FloatPrecTy OP_11(11,52);
::fap::FloatPrecTy OP_10(11,52);
::fap::FloatPrecTy OP_9(11,52);
::fap::FloatPrecTy OP_8(11,52);
::fap::FloatPrecTy OP_7(11,52);
::fap::FloatPrecTy OP_6(11,52);
::fap::FloatPrecTy OP_5(11,52);
::fap::FloatPrecTy OP_4(11,52);
::fap::FloatPrecTy OP_3(11,52);
::fap::FloatPrecTy OP_2(11,52);
::fap::FloatPrecTy OP_1(11,52);
::fap::FloatPrecTy OP_0(11,52);
double BESSJ0 ( double X )
{
    /***********************************************************************
          This subroutine calculates the First Kind Bessel Function of
          order 0, for any real number X. The polynomial approximation by
          series of Chebyshev polynomials is used for 0<X<8 and 0<8/X<1.
          REFERENCES:
          M.ABRAMOWITZ,I.A.STEGUN, HANDBOOK OF MATHEMATICAL FUNCTIONS, 1965.
          C.W.CLENSHAW, NATIONAL PHYSICAL LABORATORY MATHEMATICAL TABLES,
          VOL.5, 1962.
    ************************************************************************/
    const double P1 = 1.0, P2 = -0.1098628627E-2, P3 = 0.2734510407E-4,
                 P4 = -0.2073370639E-5, P5 = 0.2093887211E-6,
                 Q1 = -0.1562499995E-1, Q2 = 0.1430488765E-3,
                 Q3 = -0.6911147651E-5, Q4 = 0.7621095161E-6,
                 Q5 = -0.9349451520E-7, R1 = 57568490574.0, R2 = -13362590354.0,
                 R3 = 651619640.7, R4 = -11214424.18, R5 = 77392.33017,
                 R6 = -184.9052456, S1 = 57568490411.0, S2 = 1029532985.0,
                 S3 = 9494680.718, S4 = 59272.64853, S5 = 267.8532712, S6 = 1.0;
    double AX, FR, FS, Z, FP, FQ, XX, Y, TMP;

    if ( X == 0.0 ) {
        return 1.0;
    }
    AX = fabs ( X );
    if ( AX < 8.0 ) {
        Y = (double)(::fap::FloatingPointType((double) X, OP_0)) * (double)(::fap::FloatingPointType((double) X, OP_0));
        FR = (double)(::fap::FloatingPointType((double) R1, OP_1)) + (double)(::fap::FloatingPointType((double) Y, OP_2)) * ( (double)(::fap::FloatingPointType((double) R2, OP_3)) + (double)(::fap::FloatingPointType((double) Y, OP_4)) * ( (double)(::fap::FloatingPointType((double) R3, OP_5)) + (double)(::fap::FloatingPointType((double) Y, OP_6)) * ( (double)(::fap::FloatingPointType((double) R4, OP_7)) + (double)(::fap::FloatingPointType((double) Y, OP_8)) * ( (double)(::fap::FloatingPointType((double) R5, OP_9)) + (double)(::fap::FloatingPointType((double) Y, OP_10)) * (double)(::fap::FloatingPointType((double) R6, OP_10)) ) ) ) );
        FS = (double)(::fap::FloatingPointType((double) S1, OP_11)) + (double)(::fap::FloatingPointType((double) Y, OP_12)) * ( (double)(::fap::FloatingPointType((double) S2, OP_13)) + (double)(::fap::FloatingPointType((double) Y, OP_14)) * ( (double)(::fap::FloatingPointType((double) S3, OP_15)) + (double)(::fap::FloatingPointType((double) Y, OP_16)) * ( (double)(::fap::FloatingPointType((double) S4, OP_17)) + (double)(::fap::FloatingPointType((double) Y, OP_18)) * ( (double)(::fap::FloatingPointType((double) S5, OP_19)) + (double)(::fap::FloatingPointType((double) Y, OP_20)) * (double)(::fap::FloatingPointType((double) S6, OP_20)) ) ) ) );
        TMP = (double)(::fap::FloatingPointType((double) FR, OP_21)) / (double)(::fap::FloatingPointType((double) FS, OP_21));
    } else {
        Z = (double)(::fap::FloatingPointType((double) 8., OP_22)) / (double)(::fap::FloatingPointType((double) AX, OP_22));
        Y = (double)(::fap::FloatingPointType((double) Z, OP_23)) * (double)(::fap::FloatingPointType((double) Z, OP_23));
        XX = (double)(::fap::FloatingPointType((double) AX, OP_24)) - (double)(::fap::FloatingPointType((double) 0.785398164, OP_24));
        FP = (double)(::fap::FloatingPointType((double) P1, OP_25)) + (double)(::fap::FloatingPointType((double) Y, OP_26)) * ( (double)(::fap::FloatingPointType((double) P2, OP_27)) + (double)(::fap::FloatingPointType((double) Y, OP_28)) * ( (double)(::fap::FloatingPointType((double) P3, OP_29)) + (double)(::fap::FloatingPointType((double) Y, OP_30)) * ( (double)(::fap::FloatingPointType((double) P4, OP_31)) + (double)(::fap::FloatingPointType((double) Y, OP_32)) * (double)(::fap::FloatingPointType((double) P5, OP_32)) ) ) );
        FQ = (double)(::fap::FloatingPointType((double) Q1, OP_33)) + (double)(::fap::FloatingPointType((double) Y, OP_34)) * ( (double)(::fap::FloatingPointType((double) Q2, OP_35)) + (double)(::fap::FloatingPointType((double) Y, OP_36)) * ( (double)(::fap::FloatingPointType((double) Q3, OP_37)) + (double)(::fap::FloatingPointType((double) Y, OP_38)) * ( (double)(::fap::FloatingPointType((double) Q4, OP_39)) + (double)(::fap::FloatingPointType((double) Y, OP_40)) * (double)(::fap::FloatingPointType((double) Q5, OP_40)) ) ) );
        TMP = (double)(::fap::FloatingPointType((double) sqrt ( 0.636619772 / AX ), OP_41)) * ( (double)(::fap::FloatingPointType((double) (double)(::fap::FloatingPointType((double) FP, OP_43)) * (double)(::fap::FloatingPointType((double) cos ( XX ), OP_42)), OP_43)) - (double)(::fap::FloatingPointType((double) (double)(::fap::FloatingPointType((double) Z, OP_45)) * (double)(::fap::FloatingPointType((double) FQ, OP_45)) * (double)(::fap::FloatingPointType((double) sin ( XX ), OP_42)), OP_44)) );
    }
    return TMP;
}

double Sign ( double X, double Y )
{
    if ( Y < 0.0 ) {
        return ( -fabs ( X ) );
    } else {
        return ( fabs ( X ) );
    }
}

double BESSJ1 ( double X )
{
    /**********************************************************************
          This subroutine calculates the First Kind Bessel Function of
          order 1, for any real number X. The polynomial approximation by
          series of Chebyshev polynomials is used for 0<X<8 and 0<8/X<1.
          REFERENCES:
          M.ABRAMOWITZ,I.A.STEGUN, HANDBOOK OF MATHEMATICAL FUNCTIONS, 1965.
          C.W.CLENSHAW, NATIONAL PHYSICAL LABORATORY MATHEMATICAL TABLES,
          VOL.5, 1962.
    ***********************************************************************/
    const double P1 = 1.0, P2 = 0.183105E-2, P3 = -0.3516396496E-4,
                 P4 = 0.2457520174E-5, P5 = -0.240337019E-6, P6 = 0.636619772,
                 Q1 = 0.04687499995, Q2 = -0.2002690873E-3, Q3 = 0.8449199096E-5,
                 Q4 = -0.88228987E-6, Q5 = 0.105787412E-6, R1 = 72362614232.0,
                 R2 = -7895059235.0, R3 = 242396853.1, R4 = -2972611.439,
                 R5 = 15704.48260, R6 = -30.16036606, S1 = 144725228442.0,
                 S2 = 2300535178.0, S3 = 18583304.74, S4 = 99447.43394,
                 S5 = 376.9991397, S6 = 1.0;

    double AX, FR, FS, Y, Z, FP, FQ, XX, TMP;

    AX = fabs ( X );
    if ( AX < 8.0 ) {
        Y = X * X;
        FR = R1 + Y * ( R2 + Y * ( R3 + Y * ( R4 + Y * ( R5 + Y * R6 ) ) ) );
        FS = S1 + Y * ( S2 + Y * ( S3 + Y * ( S4 + Y * ( S5 + Y * S6 ) ) ) );
        TMP = X * ( FR / FS );
    } else {
        Z = 8.0 / AX;
        Y = Z * Z;
        XX = AX - 2.35619491;
        FP = P1 + Y * ( P2 + Y * ( P3 + Y * ( P4 + Y * P5 ) ) );
        FQ = Q1 + Y * ( Q2 + Y * ( Q3 + Y * ( Q4 + Y * Q5 ) ) );
        TMP = sqrt ( P6 / AX ) * ( cos ( XX ) * FP - Z * sin ( XX ) * FQ ) * Sign ( S6, X );
    }
    return TMP;
}

double BESSJ ( int N, double X )
{
    /************************************************************************
          This subroutine calculates the first kind modified Bessel function
          of integer order N, for any REAL X. We use here the classical
          recursion formula, when X > N. For X < N, the Miller's algorithm
          is used to avoid overflows.
          -----------------------------
          REFERENCE:
          C.W.CLENSHAW, CHEBYSHEV SERIES FOR MATHEMATICAL FUNCTIONS,
          MATHEMATICAL TABLES, VOL.5, 1962.
    *************************************************************************/
    const int IACC = 40;
    const double BIGNO = 1e10, BIGNI = 1e-10;

    double TOX, BJM, BJ, BJP, SUM, TMP;
    int J, JSUM, M;

    if ( N == 0 ) {
        return BESSJ0 ( X );
    }
    if ( N == 1 ) {
        return BESSJ1 ( X );
    }
    if ( X == 0.0 ) {
        return 0.0;
    }

    TOX = 2.0 / X;
    if ( X > 1.0 * N ) {
        BJM = BESSJ0 ( X );
        BJ = BESSJ1 ( X );
        for ( J = 1; J < N; J++ ) {
            BJP = J * TOX * BJ - BJM;
            BJM = BJ;
            BJ = BJP;
        }
        return BJ;
    } else {
        M = ( int ) ( 2 * ( ( N + floor ( sqrt ( 1.0 * ( IACC * N ) ) ) ) / 2 ) );
        TMP = 0.0;
        JSUM = 0;
        SUM = 0.0;
        BJP = 0.0;
        BJ = 1.0;
        for ( J = M; J > 0; J-- ) {
            BJM = J * TOX * BJ - BJP;
            BJP = BJ;
            BJ = BJM;
            if ( fabs ( BJ ) > BIGNO ) {
                BJ = BJ * BIGNI;
                BJP = BJP * BIGNI;
                TMP = TMP * BIGNI;
                SUM = SUM * BIGNI;
            }
            if ( JSUM != 0 ) {
                SUM += BJ;
            }
            JSUM = 1 - JSUM;
            if ( J == N ) {
                TMP = BJP;
            }
        }
        SUM = 2.0 * SUM - BJ;
        return ( TMP / SUM );
    }
}



char oracle_path[]= "./bessel_oracle.txt";


int main()
{

    double X, Y;
    int N;

    // Set seed
    srand ( 3353535634 );

    ::std::ofstream oracle ( oracle_path, ::std::ofstream::out );

    ::std::cout << "Bessel Values:\n";
    N = 0;
    for ( int i = 0; i < NUM_SAMPLES; i++ ) {
        X = ( double ) rand() / RAND_MAX;
        Y = BESSJ ( N, X );
        // Store the oracle
        ::std::cout << ::std::setprecision ( ::std::numeric_limits<double>::digits10 +
                                             1 )
                    << Y << "\n";
        oracle << ::std::setprecision ( ::std::numeric_limits<double>::digits10 + 1 )
               << X << " "
               << ::std::setprecision ( ::std::numeric_limits<double>::digits10 + 1 )
               << Y << "\n";
    }
    oracle.close();

    return 0;
}
