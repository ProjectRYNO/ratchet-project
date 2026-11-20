#ifndef TYPES_H
#define TYPES_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long int u64;
typedef unsigned int u128 __attribute__((mode(TI)));

typedef char s8;
typedef short s16;
typedef int s32;
typedef long int s64;
typedef int s128 __attribute__((mode(TI)));

typedef float f32;
typedef double f64;

#define nullptr 0
#define NULL 0
#define true 1
#define false 0


#endif
