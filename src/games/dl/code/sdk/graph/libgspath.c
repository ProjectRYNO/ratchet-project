#include "common.h"

/* Recovered directly from the retail boot instructions; no vendor source. */
#define GSPATH_SECTION(name) __attribute__((section(".gspath_" #name)))

typedef unsigned int gsPathQword __attribute__((mode(TI)));
extern gsPathQword sdkGsResetVifA;
extern gsPathQword sdkGsResetVifB;

/* D18: the COP2 control sequence stays one block; the rest is C. */
void GSPATH_SECTION(sceGsResetPath) sceGsResetPath(void)
{
	*(volatile unsigned int *)0x10003c10 = 1;
	*(volatile unsigned int *)0x10003c20 = 2;
	__asm__ volatile(
		"\tdaddu $4, $0, $0\n"
		"\tsync\n"
		"\tcfc2.ni $4, $vi28\n"
		"\tnop\n"
		"\tori $4, $4, 0x200\n"
		"\tctc2.ni $4, $vi28\n"
		"\tsync.p\n"
		".set noreorder\n"
		"1:\n"
		"\tcfc2.ni $4, $vi29\n"
		"\tnop\n"
		"\tnop\n"
		"\tnop\n"
		"\tandi $4, $4, 0x100\n"
		"\tbnez $4, 1b\n"
		"\tnop\n"
		".set reorder\n"
		"\taddiu $4, $0, 0x404\n"
		"\tctc2.ni $4, $vi28\n"
		"\tnop"
		: : : "$4");
	*(volatile gsPathQword *)0x10005000 = sdkGsResetVifA;
	*(volatile gsPathQword *)0x10005000 = sdkGsResetVifB;
	*(volatile unsigned int *)0x10003000 = 1;
	/* Emits nothing: keeps the assembler from moving the store into the return's delay slot. */
	__asm__ volatile(".set noreorder\n.set reorder");
}

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
