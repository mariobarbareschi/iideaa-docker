#ifndef HELPER_INTRINSICS_H
#define HELPER_INTRINSICS_H

#include <math.h>

#ifndef CHIMERA

#define fabsf(x) fabs(x)
#define __expf(x) expf(x)
#define sqrtf(x) sqrtf(x)
#define __logf(x) logf(x)

#else

extern float fabsf(float);
extern float __expf(float);
extern float sqrtf(float);
extern float __logf(float);

#endif


#endif /*HELPER_INTRINSICS_H*/