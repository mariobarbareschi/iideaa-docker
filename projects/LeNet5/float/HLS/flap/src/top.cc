#include "network.h"
#include "fap.h"

extern ::fap::FloatPrecTy OP_9;
extern ::fap::FloatPrecTy OP_8;
extern ::fap::FloatPrecTy OP_7;
extern ::fap::FloatPrecTy OP_6;
extern ::fap::FloatPrecTy OP_5;
extern ::fap::FloatPrecTy OP_4;
extern ::fap::FloatPrecTy OP_3;
extern ::fap::FloatPrecTy OP_2;
extern ::fap::FloatPrecTy OP_1;
extern ::fap::FloatPrecTy OP_0;

void network_wrapper(
		DATA_T (&in_data)[CONV1_NB_CHANNELS][CONV1_CHANNELS_HEIGHT][CONV1_CHANNELS_WIDTH],
		uint32_t (&out_data)[OUTPUTS_HEIGHT][OUTPUTS_WIDTH])
{
  OP_0.mant_size = 17;
  OP_1.mant_size = 21;
  OP_2.mant_size = 19;
  OP_3.mant_size = 9;
  OP_4.mant_size = 12;
  OP_5.mant_size = 10;
  OP_6.mant_size = 14;
  OP_7.mant_size = 17;
  OP_8.mant_size = 10;
  OP_9.mant_size = 9;

  network(in_data, out_data);
}
