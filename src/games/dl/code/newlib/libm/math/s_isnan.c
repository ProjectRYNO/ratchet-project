/* Newlib 1.9.0 source; original function placement for Deadlocked. */
int isnan(double) __attribute__((section(".libm_isnan")));
#include "../upstream/math/s_isnan.c"
