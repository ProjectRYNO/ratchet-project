/* Newlib 1.9.0 source; original function placement for Deadlocked. */
struct exception;
int matherr(struct exception *) __attribute__((section(".libm_matherr")));
#include "../upstream/common/s_matherr.c"
