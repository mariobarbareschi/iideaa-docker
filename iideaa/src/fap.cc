//===- Fap.cpp --------------------------------------------------*- C++ -*-===//
//
//  Copyright (C) 2015, 2016  Federico Iannucci (fed.iannucci@gmail.com)
// 
//  This file is part of Fap.
//
//  Fap is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  Fap is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//
//  You should have received a copy of the GNU Affero General Public License
//  along with Fap. If not, see <http://www.gnu.org/licenses/>.
//
//===----------------------------------------------------------------------===//
/// \file Fap.cpp
/// \author Federico Iannucci
/// \brief Flexible Arbitrary Precision Library.
///        Implementation File
//===----------------------------------------------------------------------===//

#include "fap.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <iomanip>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
/// @defgroup FAP_PRIVATE_FUNCTIONS
/// @{

/// @brief This functions shif to right the mantissa \p mant of \p to_shift
/// positions, updating the grs bits.
/// @param mant Mantissa
/// @param to_shift Quantity of shifting
/// @param grs Original grs bits
void fap_shift_right_(uint128_t *bit_vector, int to_shift, uint8_t *grs) {
  // Shift of to_shift and take the last 3 bits and update the grs bits
  // Check if there was the sticky bit
  uint8_t sticky_1 = 0x00;
  if ((*grs & MASK_LOWER_HIGH(uint8_t, to_shift)) != 0x00) {
    sticky_1 = 0x01;
  }
#ifdef _FAP_DEBUG_
  printf("\nFAP_FP_RSHIFT - to_shift=%d\n", to_shift);
  printf("FAP_FP_RSHIFT - sticky=%02x\n", sticky_1);
  printf("FAP_FP_RSHIFT - grs=%02x\n", *grs);
#endif
  if (to_shift < 3) {
    *grs >>= to_shift;
    *grs |= (uint8_t)(((*bit_vector) & MASK_LOWER_HIGH(uint128_t, to_shift))
                      << (3 - to_shift));
    *grs |= sticky_1 != 0x00 ? 0x01 : 0x00;
  } else {
    *grs = (uint8_t)(((*bit_vector) >> (to_shift - 3)) &
                     MASK_LOWER_HIGH(uint8_t, 3));
    // Set the sticky bit, checking if the lower bits after it are != from 0 OR
    // If the previous grs bits were != 0x00
    if (((*bit_vector & MASK_LOWER_HIGH(uint128_t, (to_shift - 3))) !=
             (MantType)0 ||
         sticky_1) &&
        to_shift != 3) {
      *grs |= 0x1; // Set s bit
    }
  }
  *bit_vector >>= to_shift;
#ifdef _FAP_DEBUG_
  printf("FAP_FP_RSHIFT - new_grs=%02x\n", *grs);
#endif
}

/// @brief Same as fap_fp_rshift_mant_, but to the left
void fap_shift_left_(uint128_t *bit_vector, int to_shift, uint8_t *grs) {
#ifdef _FAP_DEBUG_
  printf("\nFAP_FP_LSHIFT - to_shift=%d\n", to_shift);
  printf("FAP_FP_LSHIFT - grs=%02x\n", *grs);
#endif
  // Shift of to_shift and take the last 3 bits and update the grs bits
  *bit_vector <<= to_shift;
  // Put the bit of grs
  // Zeros entered in the least significat bits of mantissa
  if (to_shift < 3) {
    *bit_vector |=
        (uint8_t)((*grs & MASK_LOWER_HIGH(uint8_t, 3)) >> (3 - to_shift));
  } else {
    *bit_vector |= ((MantType)*grs & MASK_LOWER_HIGH(uint8_t, 3))
                   << (to_shift - 3);
  }
  *grs = (*grs << to_shift) & MASK_LOWER_HIGH(uint8_t, 3);
#ifdef _FAP_DEBUG_
  printf("FAP_FP_LSHIFT - grs=%02x\n", *grs);
#endif
}
///////////////////////////////////////////////////////////////////////////////
// Fap Library - C++ Interface
//::fap::FloatingPointType& ::fap::FloatingPointType::operator=(FAP_fp_t fp) {
//  this->sign = fp.sign;
//  this->exp = fp.exp;
//  this->mant = fp.mant;
//  this->grs = fp.grs;
//  this->prec = fp.prec;
//  return *this;
//}

::fap::FloatingPointType & ::fap::FloatingPointType::operator=(float fp) {
  this->prec.mant_size = FLOAT_MANT_SIZE;
  this->prec.exp_size = FLOAT_EXP_SIZE;
  uint32_t f_as_4_byte = *(uint32_t *)(&fp);
  this->setSign(f_as_4_byte >> (FLOAT_SIZE - FLOAT_SIGN_SIZE));
  this->setExp(
      (f_as_4_byte >> (FLOAT_SIZE - FLOAT_SIGN_SIZE - FLOAT_EXP_SIZE)));
  this->setMant(f_as_4_byte);
  this->setGrs(0);
  return *this;
}

::fap::FloatingPointType & ::fap::FloatingPointType::operator=(double fp) {
  this->prec.mant_size = DOUBLE_MANT_SIZE;
  this->prec.exp_size = DOUBLE_EXP_SIZE;
  uint64_t d_as_8_byte = *(uint64_t *)(&fp);
  this->setSign(d_as_8_byte >> (DOUBLE_SIZE - DOUBLE_SIGN_SIZE));
  this->setExp(
      (d_as_8_byte >> (DOUBLE_SIZE - DOUBLE_SIGN_SIZE - DOUBLE_EXP_SIZE)));
  this->setMant(d_as_8_byte);
  this->setGrs(0);
  return *this;
}

//::fap::FloatingPointType::operator FAP_fp_t() const {
//  FAP_fp_t temp;
//  temp.sign = this->sign;
//  temp.exp = this->exp;
//  temp.mant = this->mant;
//  temp.grs = this->grs;
//  temp.prec = this->prec;
//  return temp;
//}

::fap::FloatingPointType::operator float() const {
  // Check precision to check that 'enters' in the float type
  if (this->prec.exp_size > FLOAT_EXP_SIZE ||
      this->prec.mant_size > FLOAT_MANT_SIZE) {
    ::std::cerr << "FloatingPointType precision is more than the float";
    exit(1);
  }

  uint32_t ext_sign = ((uint32_t) this->getSign())
                      << (FLOAT_SIZE - FLOAT_SIGN_SIZE);

  // De-bias with exponent size
  int64_t debiased_exp = this->getExp() - EXPONENT_BIAS(this->prec.exp_size);
  // Re-bias with the float size
  debiased_exp += EXPONENT_BIAS(FLOAT_EXP_SIZE);
  uint32_t ext_exp = ((uint32_t)debiased_exp)
                     << (FLOAT_SIZE - FLOAT_SIGN_SIZE - FLOAT_EXP_SIZE);

  uint32_t ext_mant =
      ((uint32_t) this->getMant() << (FLOAT_MANT_SIZE - this->prec.mant_size));

  uint32_t fp = ext_sign | ext_exp | ext_mant;
  return *(float *)(&fp);
}

::fap::FloatingPointType::operator double() const {
  // Check precision to check that 'enters' in the double type
  if (this->prec.exp_size > DOUBLE_EXP_SIZE ||
      this->prec.mant_size > DOUBLE_MANT_SIZE) {
    return 0.0;
  }

  uint64_t ext_sign = ((uint64_t) this->getSign())
                      << (DOUBLE_SIZE - DOUBLE_SIGN_SIZE);

  // De-bias with exponent size
  ExpType debiased_exp = this->getExp() - EXPONENT_BIAS(this->prec.exp_size);
  // Re-bias with the float size
  debiased_exp += EXPONENT_BIAS(DOUBLE_EXP_SIZE);
  uint64_t ext_exp = ((uint64_t)debiased_exp)
                     << (DOUBLE_SIZE - DOUBLE_SIGN_SIZE - DOUBLE_EXP_SIZE);

  uint64_t ext_mant =
      ((uint64_t) this->getMant() << (DOUBLE_MANT_SIZE - this->prec.mant_size));

  uint64_t d = ext_sign | ext_exp | ext_mant;
  return *(double *)(&d);
}
///////////////////////////////////////////////////////////////////////////////
::std::ostream &operator<<(::std::ostream &out,
                           const ::fap::FloatingPointType &fp) {
  if (fp.getName() != "") {
    out << fp.getName() << " - ";
  }
  //  out << " s | exp              | mant                             | grs\n";
  //  for (uint16_t i = 0; i < strlen(descr) + 3; ++i){
  //    out << " ";
  //  }
  out << "[" << fp.getPrec().exp_size << ":" << fp.getPrec().mant_size << "]";
  out << "[";
  out << setw(1) << (int)fp.getSign() << " | ";
  out << setw(16) << setfill('0') << ::std::hex << fp.getExp() << ::std::dec
      << " | ";
  out << fp.getMant();
  out << " | ";
  out << (((fp.getGrs()) & MASK_BIT_HIGH(uint8_t, 2)) >> 2);
  out << (((fp.getGrs()) & MASK_BIT_HIGH(uint8_t, 1)) >> 1);
  out << (((fp.getGrs()) & MASK_BIT_HIGH(uint8_t, 0)));
  out << "]\n";

  return out;
}

// Arithmetic operators
::fap::FloatingPointType & ::fap::FloatingPointType::
operator+=(const FloatingPointType &fp) {
  //  ::std::cout << "Custom Add";
  FloatingPointType &lhs = *this;
  FloatingPointType rhs = fp;

#ifdef _FAP_DEBUG_
  lhs.setName("Result");
  rhs.setName("Operand 2");
#endif

  this->adaptPrec(rhs);

  // One of the operands is NaN
  if (lhs.isNaN() || rhs.isNaN()) {
    // Set the result NaN
    lhs.setNaN();
    return lhs;
  }

  // One of the operands is infinity
  if (lhs.isInf() || rhs.isInf()) {
    if ((lhs.isPinf() && rhs.isNinf()) || (rhs.isPinf() && lhs.isNinf())) {
      // Set the result NaN
      lhs.setNaN();
    }
    if ((lhs.isPinf() && rhs.isPinf())) {
      // Set the result PINF
      lhs.setPinf();
    }
    if ((lhs.isNinf() && rhs.isNinf())) {
      // Set the result NINF
      lhs.setNinf();
    }
    // Not both are infinity, the infinity dominates
    if (lhs.isInf()) {
    } else if (rhs.isInf()) {
      lhs = rhs;
    }
    return lhs;
  }

  // Check special cases
  if (lhs.isZero()) {
    lhs = rhs;
    return lhs;
  } else if (rhs.isZero()) {
    return lhs;
  }

  ///////////////////////////////////////////////////////////////////////////////
  // Always take the minor exponent and take it to the major
  // Local vars
  // Compute in double result precision
  uint16_t op_prec = this->prec.mant_size + 1;
  // When shift use the extended mantissa
  lhs.setMantHb();
  rhs.setMantHb();
  lhs.shift(-op_prec);
  rhs.shift(-op_prec);
#ifdef _FAP_DEBUG_
  printf("FAP_FP_ADD - exp_diff=%d\n", exp_diff);
  fap_print_binary(&op1, "FAP_FP_ADD - op1");
  fap_print_binary(&op2, "FAP_FP_ADD - op2");
#endif

  int exp_diff = lhs.getExp() - rhs.getExp();
  FloatingPointType *less_exp_op = &lhs;
  ExpType res_exp = lhs.getExp();
  if (exp_diff > 0) {
    less_exp_op = &rhs;
  } else if (exp_diff < 0) {
    exp_diff = -exp_diff;
    res_exp = rhs.getExp();
  }

  lhs.setExp(res_exp);
  less_exp_op->shift(exp_diff);
  lhs.setGrs(less_exp_op->getGrs()); // Set the result grs
//  less_exp_op->exp += (exp_diff);

#ifdef _FAP_DEBUG_
  fap_print_binary(&op1, "FAP_FP_ADD - op1_post_shift");
  fap_print_binary(&op2, "FAP_FP_ADD - op2_post_shift");
  fap_print_binary(fp_res, "FAP_FP_ADD - res_pre");
#endif
  // Now the mantix are alligned on radix point
  // Manage the mantissa and sign
  // If the sign are egual remains that
  if (lhs.getSign() == rhs.getSign()) {
    this->mant = lhs.getMant() + rhs.getMant();
  } else {
    if (lhs.getMant() >= rhs.getMant()) {
      //      this->sign = fap_fp_get_sign(&op1);
      this->mant = lhs.getMant() - rhs.getMant();
    } else {
      this->sign = rhs.getSign();
      this->mant = -lhs.getMant() + rhs.getMant();
    }
  }

  // Case the SUM is 0
  if (this->mant == 0) {
    lhs.setExp(0);
  }
#ifdef _FAP_DEBUG_
  fap_print_binary(fp_res, "FAP_FP_ADD - res");
#endif
  // Normalize
  lhs.normalize((sizeof(MantType) * 8), op_prec * 2);
  // Shift
  lhs.shift(op_prec);
  // Mask
  lhs.setMant(lhs.getMant());
  // Round
  lhs.round();
  ///////////////////////////////////////////////////////////////////////////////

  return lhs;
}

::fap::FloatingPointType & ::fap::FloatingPointType::
operator-=(const FloatingPointType &fp) {
  //  ::std::cout << "Custom Sub";
  *this += (-fp);
  return *this;
}

::fap::FloatingPointType & ::fap::FloatingPointType::
operator*=(const FloatingPointType &fp) {
  FloatingPointType &lhs = *this;
  FloatingPointType rhs = fp;

#ifdef _FAP_DEBUG_
  lhs.setName("Result");
  rhs.setName("Operand 2");
#endif

  this->adaptPrec(rhs);

  // One of the operands is NaN
  // x * NaN or NaN * NaN
  if (lhs.isNaN() || rhs.isNaN()) {
    // Set the result NaN
    lhs.isNaN();
    return lhs;
  }

  // Set the sign
  lhs.setSign(lhs.getSign() ^ rhs.getSign());
  // One of the operands is infinity
  if (lhs.isInf() || rhs.isInf()) {
    // Infinity * Infinity
    if (lhs.isInf() && rhs.isInf()) {
      // Set the result NaN
      lhs.setNaN();
      return lhs;
    }
    // Not both are infinity, the infinity dominates
    // Infinity * 0
    if (lhs.isZero() || rhs.isZero()) {
      // Set the result NaN
      lhs.setNaN();
      return lhs;
    }
    lhs.setInf();
    return lhs;
  }

  // Check special cases
  // x * 0
  if (lhs.isZero() || rhs.isZero()) {
    lhs.setZero();
    return lhs;
  }

  lhs.setMantHb();
  rhs.setMantHb();
#ifdef _FAP_DEBUG_
  fap_print_binary(&op1, "FAP_FP_MUL - op1_whb");
  fap_print_binary(&op2, "FAP_FP_MUL - op2_whb");
#endif

  // MASK_BIT_HIGH of mant size create a mask with the mant_size + 1 bit high
  // Create result product between mantissa and mask with mant_size * 2 mask
  int mant_double_size = (lhs.getPrec().mant_size + 1) * 2;
  this->mant = MASK_LOWER_HIGH(MantType, mant_double_size) &
               (lhs.getMant() * rhs.getMant());
  // Compute exponent subtracting the bias (exp + bias + exp + bias -> new_exp +
  // 2bias -bias --> new_exp + bias
  lhs.setExp(lhs.getExp() + rhs.getExp() -
             EXPONENT_BIAS(lhs.getPrec().exp_size));
#ifdef _FAP_DEBUG_
  fap_print_binary(fp_res, "FAP_FP_MUL - res");
#endif
  // Multiplication of mantissas create a double sized mantissa
  // Multiplying 2 number of the type 1.x * 1.x --> yy.xx so there are 2 bits
  // after the radix,
  // there are problems when yy = 01 because there is a shift more
  // Manage this problem
  int actual_mant_prec = mant_double_size - 1; // Covers 10/11
  lhs.normalize((sizeof(MantType) * 8), actual_mant_prec);

  // Re-shift to mant_size
  int to_shift = actual_mant_prec - (lhs.getPrec().mant_size + 1);
  lhs.shift(to_shift);
#ifdef _FAP_DEBUG_
  fap_print_binary(fp_res, "FAP_FP_MUL - res_post_shift");
#endif
  // Mask
  lhs.setMant(lhs.getMant());
  // Round
  lhs.round();

  return lhs;
}

::fap::FloatingPointType & ::fap::FloatingPointType::
operator/=(const FloatingPointType &fp) {
  FloatingPointType &lhs = *this;
  FloatingPointType rhs = fp;

#ifdef _FAP_DEBUG_
  lhs.setName("Result");
  rhs.setName("Operand 2");
#endif

  this->adaptPrec(rhs);

  // One of the operands is NaN
  // x * NaN or NaN * NaN
  if (lhs.isNaN() || rhs.isNaN()) {
    // Set the result NaN
    lhs.isNaN();
    return lhs;
  }

  // Set the sign
  lhs.setSign(lhs.getSign() ^ rhs.getSign());
  // Dividend is infinity
  // - infinity/x
  if (lhs.isInf()) {
    // infinity/infinity
    if (rhs.isInf()) {
      lhs.isNaN();
      return lhs;
    }
    lhs.setInf();
  }
  // Divisor is infinity
  if (rhs.isInf()) {
    // x/infinity
    lhs.setZero();
    return lhs;
  }
  // Divisor is 0
  if (rhs.isZero()) {
    lhs.setInf();
    return lhs;
  }

  // Check special cases
  // Dividend is 0
  if (lhs.isZero()) {
    return lhs;
  }

  // Normal cases
  uint16_t precision = lhs.getPrec().mant_size + 1;
  lhs.setMantHb();
  rhs.setMantHb();
#ifdef _FAP_DEBUG_
  fap_print_binary(&op1, "FAP_FP_DIV - op1_whb");
  fap_print_binary(&op2, "FAP_FP_DIV - op2_whb");
#endif
  // Shift dividend
  int round_shift = (sizeof(MantType) * 8) - precision * 2;
  int dividend_shift =
      precision +
      round_shift; // + round_shift for the guard,round and sticky bits
  lhs.shift(-dividend_shift);

#ifdef _FAP_DEBUG_
  fap_print_binary(&op1, "FAP_FP_DIV - op1_whb_shift");
#endif

  // MASK_BIT_HIGH of mant size create a mask with the mant_size + 1 bit high
  // Create result product between mantissa and mask with mant_size * 2 mask
  this->mant = (lhs.getMant() / rhs.getMant());
  lhs.shift(round_shift);

  // Calculate exponent
  lhs.setExp(lhs.getExp() - rhs.getExp() +
             EXPONENT_BIAS(lhs.getPrec().exp_size) - 1);
#ifdef _FAP_DEBUG_
  fap_print_binary(fp_res, "FAP_FP_DIV - res");
#endif
  // Multiplication of mantissas create a double sized mantissa
  lhs.normalize((sizeof(MantType) * 8), precision);
  // Truncate to correct mant precision
  lhs.setMant(this->mant);
  // Round
  lhs.round();

  return lhs;
}
///////////////////////////////////////////////////////////////////////////////
void ::fap::FloatingPointType::changePrec(::fap::FloatPrecTy new_prec) {
  // Check if it's necessary to apply the rounding: shift + rounding method
  int prec_diff = 0;
#ifdef _FAP_DEBUG_
  printf("\nFAP_FP_CHANGE_PREC - old_prec.exp=%d | old_prec.mant=%d\n",
         this->prec.exp_size, this->prec.mant_size);
  printf("FAP_FP_CHANGE_PREC - new_prec.exp=%d | new_prec.mant=%d\n",
         new_prec.exp_size, new_prec.mant_size);
  fap_print_binary(this, "FAP_FP_CHANGE_PREC - old");
#endif
  if (this->prec.exp_size != new_prec.exp_size) {
    // Re-bias and round, if necessary, the exponent
    uint128_t expanded_exp = this->exp;
    // De-bias the exponent
    expanded_exp -= EXPONENT_BIAS(this->prec.exp_size);

    // Rounding, reducing the "grain level" of representation
    prec_diff = this->prec.exp_size - new_prec.exp_size;
    // Zeroes the prec_diff lower the bits
    expanded_exp &= MASK_LOWER_LOW(uint128_t, prec_diff);
//     if (to_shift > 0) {
//       uint8_t grs = 0x00;
//       // Shift the exponent to the right to match the correct size
//       fap_shift_right_(&expanded_exp, to_shift, &grs);
//       expanded_exp <<= to_shift;
//       // Round to nearest
//       //      fap_round_nearest(&expanded_exp, grs);
//     }
    //    // Check limits of new exponent range : [-(2^n-1)+2; (2^n-1)-1]
    //    int lower_bound = -((MASK_LOWER_HIGH(fap_fp_exp_t, new_prec.exp_size)
    //    >> 2) << 1);
    //    int upper_bound = ((MASK_LOWER_HIGH(fap_fp_exp_t, new_prec.exp_size)
    //    >> 2) << 1) + 1;
    //    if (expanded_exp < lower_bound){
    //      expanded_exp = lower_bound;
    //    } else if (expanded_exp > upper_bound){
    //      expanded_exp = upper_bound;
    //    }

    // Re-bias
    //expanded_exp += EXPONENT_BIAS(new_prec.exp_size);
    expanded_exp += EXPONENT_BIAS(this->prec.exp_size);
    this->exp = (ExpType)expanded_exp;
  }
  // Update exponent size, NO: it remains the same only the lower bits are zeroed
//   this->prec.exp_size = new_prec.exp_size;

#ifdef _FAP_DEBUG_
  fap_print_binary(this, "FAP_FP_CHANGE_PREC - after_exp");
#endif
  if (this->prec.mant_size != new_prec.mant_size) {
    // Shift the mantissa to fit the new precision
    prec_diff = this->prec.mant_size - new_prec.mant_size;
    this->shift(prec_diff);

    // Update mantissa size
    this->prec.mant_size = new_prec.mant_size;
    // Apply round if necessary
    if (prec_diff > 0) {
      // Round
      this->round();
    }
  }
#ifdef _FAP_DEBUG_
  fap_print_binary(this, "FAP_FP_CHANGE_PREC - after_mant");
#endif
}

void ::fap::FloatingPointType::adaptPrec(FloatingPointType &rhs) {
#ifdef _FAP_DEBUG_
  fap_print_binary(op1, "FAP_FP_ADAPT_PREC - op1_pre");
  fap_print_binary(op2, "FAP_FP_ADAPT_PREC - op2_pre");
#endif
  FloatPrecTy min_prec, rhs_prec = rhs.getPrec();
  min_prec.exp_size = this->prec.exp_size < rhs_prec.exp_size
                          ? this->prec.exp_size
                          : rhs_prec.exp_size;

  min_prec.mant_size = this->prec.mant_size < rhs_prec.mant_size
                           ? this->prec.mant_size
                           : rhs_prec.mant_size;

  // Change precision
  this->changePrec(min_prec);
  rhs.changePrec(min_prec);
#ifdef _FAP_DEBUG_
  printf("FAP_FP_ADAPT_PREC - min_prec %d:%d\n", min_prec.exp_size,
         min_prec.mant_size);
  fap_print_binary(op1, "FAP_FP_ADAPT_PREC - op1");
  fap_print_binary(op2, "FAP_FP_ADAPT_PREC - op2");
#endif
}

void ::fap::FloatingPointType::test(float op1, float op2) {
  float res;
  ::fap::FloatingPointType fop1 = op1, fop2 = op2, fp_res, fapf_res_to_0,
                           fapf_res_to_pinf, fapf_res_to_ninf;

  if ((float)fop1 != op1) {
    ::std::cout << "Operand1 doens't match" << ::std::endl;
    exit(1);
  }
  if ((float)fop2 != op2) {
    ::std::cout << "Operand2 doens't match" << ::std::endl;
    exit(1);
  }

  bool isDifferent = false;

  res = op1 + op2;
  fp_res = fop1 + fop2;
  if (res != (float)fp_res) {
    ::std::cout << "Fail on Addition" << ::std::endl;
    isDifferent = true;
  }

  res = op1 - op2;
  fp_res = fop1 - fop2;
  if (res != (float)fp_res) {
    ::std::cout << "Fail on Sub" << ::std::endl;
    isDifferent = true;
  }

  res = op1 * op2;
  fp_res = fop1 * fop2;
  if (res != (float)fp_res) {
    ::std::cout << "Fail on Mul" << ::std::endl;
    isDifferent = true;
  }

  res = op1 / op2;
  fp_res = fop1 / fop2;
  if (res != (float)fp_res) {
    ::std::cout << "Fail on Div" << ::std::endl;
    isDifferent = true;
  }

  if (isDifferent) {
    ::std::cout
        << "*********************************************************\n";
    ::std::cout << res << "!=" << (float)fp_res << ::std::endl;

    fop1.setName("Operand 1");
    fop2.setName("Operand 2");
    ::std::cout << fop1 << ::std::endl;
    ::std::cout << fop2 << ::std::endl;
    fp_res.setName("Custom Result");
    ::std::cout << fp_res << ::std::endl;
    ::std::cout << FloatingPointType(res) << ::std::endl;

    exit(1);
  }
}

void ::fap::FloatingPointType::test(double op1, double op2) {
  double res;
  ::fap::FloatingPointType fop1 = op1, fop2 = op2, fp_res, fapf_res_to_0,
                           fapf_res_to_pinf, fapf_res_to_ninf;

  if ((double)fop1 != op1) {
    ::std::cout << "Operand1 doens't match" << ::std::endl;
    exit(1);
  }
  if ((double)fop2 != op2) {
    ::std::cout << "Operand2 doens't match" << ::std::endl;
    exit(1);
  }

  bool isDifferent = false;

  res = op1 + op2;
  fp_res = fop1 + fop2;
  if (res != (double)fp_res) {
    ::std::cout << "Fail on Addition" << ::std::endl;
    isDifferent = true;
  }

  res = op1 - op2;
  fp_res = fop1 - fop2;
  if (res != (double)fp_res) {
    ::std::cout << "Fail on Sub" << ::std::endl;
    isDifferent = true;
  }

  res = op1 * op2;
  fp_res = fop1 * fop2;
  if (res != (double)fp_res) {
    ::std::cout << "Fail on Mul" << ::std::endl;
    isDifferent = true;
  }

  res = op1 / op2;
  fp_res = fop1 / fop2;
  if (res != (double)fp_res) {
    ::std::cout << "Fail on Div" << ::std::endl;
    isDifferent = true;
  }

  if (isDifferent) {
    ::std::cout
        << "*********************************************************\n";
    ::std::cout << res << "!=" << (double)fp_res << ::std::endl;

    fop1.setName("Operand 1");
    fop2.setName("Operand 2");
    ::std::cout << fop1 << ::std::endl;
    ::std::cout << fop2 << ::std::endl;
    fp_res.setName("Custom Result");
    ::std::cout << fp_res << ::std::endl;
    ::std::cout << FloatingPointType(res) << ::std::endl;

    exit(1);
  }
}

void ::fap::FloatingPointType::shift(int to_shift) {
#ifdef _FAP_DEBUG_
  printf("\nFAP_FP_SHIFT - to_shift=%d\n", to_shift);
  fap_print_binary(fp, "FAP_FP_SHIFT - old");
#endif
  uint128_t ex_mant = this->mant;
  if (to_shift > 0) {
    fap_shift_right_(&ex_mant, to_shift, &(this->grs));
  } else if (to_shift < 0) {
    fap_shift_left_(&ex_mant, -to_shift, &(this->grs));
  }
  this->mant = (MantType)ex_mant;
#ifdef _FAP_DEBUG_
  printf("\n");
  fap_print_binary(fp, "FAP_FP_SHIFT - new");
#endif
}

void ::fap::FloatingPointType::normalize(int max_prec, int actual_prec) {
  // First bit high relative to prec
  int first_bit_high = 0;
  while (((MASK_BIT_HIGH(MantType, ((max_prec - 1) - first_bit_high)) &
           this->mant) == 0) &&
         (first_bit_high < max_prec))
    first_bit_high++;
  if (first_bit_high != max_prec) {
    // Have to shift on the left or on the right?
    // Check the first high bit position respect to actual_prec
    int first_bit_high_pos = (max_prec - first_bit_high);
    int to_shift = (actual_prec - first_bit_high_pos);
#ifdef _FAP_DEBUG_
    printf("\nFAPF_NORMALIZE - to_shift=%d\n", -to_shift);
    fap_print_binary(fp, "FAP_FP_NORMALIZE - old");
#endif
    this->shift(-to_shift);
    this->exp -= to_shift;
#ifdef _FAP_DEBUG_
    fap_print_binary(fp, "FAP_FP_NORMALIZE - new");
#endif
    this->mant &= MASK_LOWER_HIGH(MantType, actual_prec);
  }
}

void ::fap::FloatingPointType::round(FAP_rounding_method method) {
#ifdef _FAP_DEBUG_
  printf("\nFAP_FP_ROUND - round_m=%d\n", round_m);
  fap_print_binary(fp, "FAP_FP_ROUND - old");
#endif
  // Modify the grs to match the proper rounding method
  switch (method) {
  case FAP_FP_ROUND_TOWARD_0: {
    this->grs = 0;
  } break;
  case FAP_FP_ROUND_TOWARD_PINF: {
    if (this->getSign() == 0x00 && this->grs != 0x00) {
      this->grs = 0x07;
    } else {
      this->grs = 0x00;
    }
  } break;
  case FAP_FP_ROUND_TOWARD_NINF: {
    if (this->getSign() == 0x01 && this->grs != 0x00) {
      this->grs = 0x07;
    } else {
      this->grs = 0x00;
    }
  } break;
  default:
    break;
  }

  // Apply nearest rounding method with grs updated
  if (this->grs == 0x4 &&
      ((this->mant & MASK_BIT_HIGH(MantType, 0)) == (MantType)1)) {
    this->mant += 0x1;
  } else if (grs >= 0x05) {
    this->mant += 0x1;
  }
  // Check if the mant is now all zeros, but the hidden bit, mant_size-nth bit
  if ((this->mant & MASK_BIT_HIGH(MantType, this->prec.mant_size)) !=
      (MantType)0) {
    this->exp += 0x1;
  }

  // The round method has been applied reset the grs
  this->grs = 0x00;
  this->setMant(this->mant);
#ifdef _FAP_DEBUG_
  fap_print_binary(fp, "FAP_FP_ROUND - new");
#endif
}

///////////////////////////////////////////////////////////////////////////////
/// IntegerType

int128_t ::fap::IntegerType::getActualBits() const {
  if (this->neglectedBitsStatus) {
    return (this->bits
        | MASK_BIT_HIGH(uint128_t,
                        (this->oriPrecision - this->actualPrecision - 1)));
  }
  return this->bits;
}

// Arithmetic Operators
::fap::IntegerType & ::fap::IntegerType::operator+=(::fap::IntegerType rhs) {
  // Adapt precisions
  this->adaptPrec(rhs);
  this->bits += rhs.getBits();
  // Check the compensation
  if (this->compensate && rhs.isCompensate()) {
    // Use new neglectedBitsStatus to see if a compensation is necessary
    if (this->neglectedBitsStatus && rhs.getNeglectedBitsStatus()) {
      // Both true (0x01)
      this->bits +=
          MASK_BIT_HIGH(int128_t, (this->oriPrecision - this->actualPrecision));
    }
  }
  this->neglectedBitsStatus ^= rhs.getNeglectedBitsStatus();
  return *this;
}
::fap::IntegerType & ::fap::IntegerType::operator-=(::fap::IntegerType rhs) {
  // Adapt precisions
  this->adaptPrec(rhs);
  this->bits -= rhs.getBits();
  this->neglectedBitsStatus ^= rhs.getNeglectedBitsStatus();
  return *this;
}
::fap::IntegerType & ::fap::IntegerType::operator^=(::fap::IntegerType rhs) {
  // Adapt precisions
  this->adaptPrec(rhs);
  this->bits ^= rhs.getBits();
  this->neglectedBitsStatus ^= rhs.getNeglectedBitsStatus();
  return *this;
}
::fap::IntegerType & ::fap::IntegerType::operator*=(::fap::IntegerType rhs) {
  // Adapt precisions
  this->adaptPrec(rhs);
  int128_t partial_mul = this->bits * rhs.getBits();
  // Check the compensation
  if (this->compensate && rhs.isCompensate()) {
    // Use new neglectedBitsStatus to see if a compensation is necessary
    int diff_prec = this->oriPrecision - this->actualPrecision;
    // Add the others three terms
    if (this->neglectedBitsStatus) {
      partial_mul += rhs.getBits()
                     << (diff_prec -
                         1); // diff_prec - 1 ones followed by diff_prec zeroes
    }
    if (rhs.getNeglectedBitsStatus()) {
      partial_mul += this->bits << (diff_prec - 1);
    }
    if (this->neglectedBitsStatus && rhs.getNeglectedBitsStatus()) {
      // Last term
      partial_mul += MASK_BIT_HIGH(int128_t, 2 * (diff_prec - 1));
    }
  }
  this->bits = partial_mul;
  this->neglectedBitsStatus = 0;
  return *this;
}
::fap::IntegerType & ::fap::IntegerType::operator/=(::fap::IntegerType rhs) {
  // Adapt precisions
  this->adaptPrec(rhs);
  this->bits /= rhs.getBits();
  return *this;
}
///////////////////////////////////////////////////////////////////////////////

void ::fap::IntegerType::changePrec(IntegerPrecision n_prec) {
  // To sth if the precision is different from the actual one
  if (this->actualPrecision != n_prec) {
    IntegerPrecision prec_diff = this->oriPrecision - n_prec;
    // Check consistency
    if (prec_diff > 0) {
      // Clearing least significant bits
      this->bits &= MASK_LOWER_LOW(uint128_t, prec_diff);
      // Set the cleared bits
      //      this->bits |= MASK_BIT_HIGH(uint128_t, (prec_diff - 1));
      this->actualPrecision = n_prec;
    }
  }
}

void ::fap::IntegerType::adaptPrec(IntegerType &i) {
  // Find lowest precisionuint8_t
  ::fap::IntegerPrecision lowest_precision =
      this->actualPrecision < i.getActualPrecision() ? this->actualPrecision
                                                     : i.getActualPrecision();
  this->changePrec(lowest_precision);
  i.changePrec(lowest_precision);
}

::std::ostream &operator<<(::std::ostream &out, const ::fap::IntegerType &i) {
  out << "i[" << i.getOriPrecision() << "->" << i.getActualPrecision() << "]"
      << "[" << i.getActualBits() << "][" << (int)i.getNeglectedBitsStatus()
      << "]";
  return out;
}
