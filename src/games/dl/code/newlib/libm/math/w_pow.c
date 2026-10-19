/* Newlib 1.9.0 source; original function placement for Deadlocked. */
double pow(double, double) __attribute__((section(".libm_pow")));
#include "../upstream/math/w_pow.c"
