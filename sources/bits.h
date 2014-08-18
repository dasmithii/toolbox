#ifndef BASELINE_BIT_UTILITIES
#define BASELINE_BIT_UTILITIES
#include <stdbool.h>


#define GET_BIT(b, i) ((b & (1<<(n))) >> (n))


#define SET_BIT(n, i, v) \
	if(v) FLAG_BIT(n,i); \
	else  CLEAR_BIT(n,i)


#define FLAG_BIT(n,i)\
	n |= 1 << i


#define CLEAR_BIT(n,i)\
	n &= ~(1 << i)


#endif