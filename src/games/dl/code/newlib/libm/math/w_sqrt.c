/* Newlib 1.9.0 source; original function placement for Deadlocked. */
double sqrt(double) __attribute__((section(".libm_sqrt")));
#include "../upstream/math/w_sqrt.c"
