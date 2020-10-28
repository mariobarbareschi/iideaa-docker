#include "trunc.h"
#include <inttypes.h>
#include <iostream>

int main()
{
  int8_t    var_int8   = 123;
  uint8_t   var_uint8  = 123U;
  int16_t   var_int16  = 13255;
  uint16_t  var_uint16 = 13255U;
  int32_t   var_int32  = 757785422;
  uint32_t  var_uint32 = 757785422U;
  int64_t   var_int64  = 353363564634;
  uint64_t   var_uint64  = 353363564634U;
  
  std::cout << std::hex << var_int8   << std::endl;
  std::cout << std::hex << var_uint8  << std::endl;
  std::cout << std::hex << var_int16  << std::endl;
  std::cout << std::hex << var_uint16 << std::endl;
  std::cout << std::hex << var_int32  << std::endl;
  std::cout << std::hex << var_uint32 << std::endl;
  std::cout << std::hex << var_int64 << std::endl;
  std::cout << std::hex << var_uint64 << std::endl;
  
  truncate::ax_integer ax_int8(3, var_int8);
  truncate::ax_integer ax_uint8(4, var_uint8);
  truncate::ax_integer ax_int16(5, var_int16);
  truncate::ax_integer ax_uint16(6, var_uint16);
  truncate::ax_integer ax_int32(7, var_int32);
  truncate::ax_integer ax_uint32(8, var_uint32);
  truncate::ax_integer ax_int64(8, var_int64);
  truncate::ax_integer ax_uint64(9, var_uint64);
  
  std::cout << ax_int8.getNab()   << "\t" << std::hex << ax_int8.getMask()   << "\t" << std::hex << (int8_t) ax_int8     << std::endl;
  std::cout << ax_uint8.getNab()  << "\t" << std::hex << ax_uint8.getMask()  << "\t" << std::hex << (uint8_t)  ax_uint8  << std::endl;
  
  std::cout << ax_int16.getNab()  << "\t" << std::hex << ax_int16.getMask()  << "\t" << std::hex << (int16_t) ax_int16   << std::endl;
  std::cout << ax_uint16.getNab() << "\t" << std::hex << ax_uint16.getMask() << "\t" << std::hex << (uint16_t) ax_uint16 << std::endl;
  
  std::cout << ax_int32.getNab()  << "\t" << std::hex << ax_int32.getMask()  << "\t" << std::hex << (int32_t) ax_int32   << std::endl;
  std::cout << ax_uint32.getNab() << "\t" << std::hex << ax_uint32.getMask() << "\t" << std::hex << (uint32_t) ax_uint32 << std::endl;
  
  std::cout << ax_int64.getNab()  << "\t" << std::hex << ax_int64.getMask()  << "\t" << std::hex << (int64_t) ax_int64   << std::endl;
  std::cout << ax_uint64.getNab() << "\t" << std::hex << ax_uint64.getMask() << "\t" << std::hex << (uint64_t) ax_uint64 << std::endl;
}
