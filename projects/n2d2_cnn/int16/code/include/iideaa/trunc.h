#ifndef N2D2_EXPORT_C_TRUNC_H
#define N2D2_EXPORT_C_TRUNC_H

#define TRUNC_SAT(x, nab)   ((nab < (sizeof((x))*8)) ? nab : sizeof((x))*8)
#define TRUNC_MASK(x, nab)  (~((1 << TRUNC_SAT(x,nab)) - 1))
#define TRUNCATE(x, nab)    ((x) & TRUNC_MASK(x,nab))


#endif //N2D2_EXPORT_C_TRUNC_H

