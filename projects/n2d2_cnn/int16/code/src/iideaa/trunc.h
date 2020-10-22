#ifndef N2D2_EXPORT_C_TRUNC_H
#define N2D2_EXPORT_C_TRUNC_H

#define TRUNC_MAX(x, y, nab)  ((sizeof((x)) < sizeof(y)) ? ((nab) % (sizeof((x))*8)) : ((nab) % (sizeof((y))*8)))
#define TRUNC_MASK(x, y, nab) (~((1 << TRUNC_MAX(x,y,nab)) - 1))
#define TRUNC_ADD(x, y, nab)  ((((x) & TRUNC_MASK(x, y, nab)) + ((y) & TRUNC_MASK(x, y, nab))) & TRUNC_MASK(x, y, nab))
#define TRUNC_SUB(x, y, nab)  ((((x) & TRUNC_MASK(x, y, nab)) - ((y) & TRUNC_MASK(x, y, nab))) & TRUNC_MASK(x, y, nab))
#define TRUNC_MUL(x, y, nab)  ((((x) & TRUNC_MASK(x, y, nab)) * ((y) & TRUNC_MASK(x, y, nab))) & TRUNC_MASK(x, y, nab))
#define TRUNC_DIV(x, y, nab)  ((((x) & TRUNC_MASK(x, y, nab)) / ((y) & TRUNC_MASK(x, y, nab))) & TRUNC_MASK(x, y, nab))

#endif //N2D2_EXPORT_C_TRUNC_H
