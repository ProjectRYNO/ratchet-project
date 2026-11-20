#ifndef MATHUTIL_H
#define MATHUTIL_H

#include "vector.h"

struct MathUtilities { // 0x1
	int WrapValue(int value, int low, int high) __asm__("WrapValue");
	s128 VecSlerp(vec4 vFrom, vec4 vTo, float fInterp, float fLimit, bool bNormalized, bool bClamp) __asm__("VecSlerp");
};

#endif
