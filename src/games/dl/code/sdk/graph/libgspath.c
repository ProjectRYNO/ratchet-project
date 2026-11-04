#include "common.h"

/* Recovered directly from the retail boot instructions; no vendor source. */
#define GSPATH_SECTION(name) __attribute__((section(".gspath_" #name)))

/* D16: reads the VU1 status through a single cfc2 fragment. */
int GSPATH_SECTION(sceGsSyncPath) sceGsSyncPath(int mode, unsigned short timeout)
{
	int ret;
	do {
		int vu;
		ret = 0;
		if (*(volatile unsigned int *)0x10009000 & 0x100) ret = 1;
		if (*(volatile unsigned int *)0x1000a000 & 0x100) ret |= 2;
		if (*(volatile unsigned int *)0x10003c00 & 3) ret |= 4;
		__asm__ volatile("cfc2.ni %0, $vi29" : "=r"(vu));
		if (vu & 0x100) ret |= 8;
		if (*(volatile unsigned int *)0x10003020 & 0xc00) ret |= 0x10;
	} while (ret);
	return 0;
}
