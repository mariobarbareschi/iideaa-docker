#include "trunc.h"

uint8_t truncate::ax_integer::getMaxApprxGrade () const
{
  switch (internal_type)
  {
    case int8:  return 7U;
    case int16: return 15U;
    case int32: return 31U;
    case int64: return 63U;
    case uint8: return 8U;
    case uint16: return 16U;
    case uint32: return 32U;
    case uint64: return 64U;
    default: return 0U;
  }
}