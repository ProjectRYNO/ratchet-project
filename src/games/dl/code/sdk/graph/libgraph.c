#include "common.h"
#include "libgraph.h"

/* Recovered directly from the retail boot instructions; no vendor source. */
#define GRAPH_SECTION(name) __attribute__((section(".graph_" #name)))

/* Functions not yet recovered, and original padding words, stay in their own slots. */
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
	__asm__(".section .graph_" #NAME ",\"ax\",@progbits\n" \
		".set noat\n.set noreorder\n" \
		".include \"" FOLDER "/" #NAME ".s\"\n" \
		".set reorder\n.set at\n.text\n")
#endif

extern graphGParam_t sdkGsGParam;
extern const char sdkGsRomVerPath[];
extern const char sdkGsDmaTimeoutMsg[];
extern const char sdkGsLoadTimeoutMsg[];
extern int sceOpen(const char *, int);
extern int sceRead(int, void *, int);
extern int sceClose(int);
extern int atoi(const char *);
extern void scePrintf(const char *, ...);
extern int VSync(void);
extern long VSync2(void);
extern int DisableIntc(int);
extern int EnableIntc(int);
extern int RemoveIntcHandler(int, int);
extern int AddIntcHandler(int, int (*)(int), int);
graphGParam_t *sceGsGetGParam(void);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/graph/libgraph", sceGsResetGraph);

graphGParam_t *GRAPH_SECTION(sceGsGetGParam) sceGsGetGParam(void)
{
	return &sdkGsGParam;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/graph/libgraph", func_001384EC);

int GRAPH_SECTION(checkModelVersion) checkModelVersion(void)
{
	char buffer[0x100];
	unsigned int i;
	int fd = sceOpen(sdkGsRomVerPath, 1);
	if (fd < 0) return -1;
	for (i = 0; i < 0x100; i++) {
		sceRead(fd, &buffer[i], 1);
		if (!buffer[i]) break;
	}
	sceClose(fd);
	return atoi(&buffer[i - 9]) > 20010608;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/graph/libgraph", _GetGsDxDyOffset);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/graph/libgraph", sceGsSetDefDispEnv);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/graph/libgraph", func_00138914);

void GRAPH_SECTION(sceGsPutDispEnv) sceGsPutDispEnv(graphDispEnv_t *env)
{
	if (sceGsGetGParam()->version == 1) {
		*(volatile unsigned long *)0x12000000 = env->pmode;
		*(volatile unsigned long *)0x12000070 = env->dispfb;
		*(volatile unsigned long *)0x12000080 = env->display;
		*(volatile unsigned long *)0x120000c0 = env->bgcolor;
	} else {
		*(volatile unsigned long *)0x12000000 = env->pmode;
		*(volatile unsigned long *)0x12000020 = env->smode2;
		*(volatile unsigned long *)0x12000090 = env->dispfb;
		*(volatile unsigned long *)0x120000a0 = env->display;
		*(volatile unsigned long *)0x120000e0 = env->bgcolor;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/graph/libgraph", func_001389D4);

short GRAPH_SECTION(sceGszbufaddr) sceGszbufaddr(short psm, short width, short height)
{
	graphGParam_t *param = sceGsGetGParam();
	short fbw = (width + 63) / 64;
	short fbh;
	if (psm & 2) fbh = (height + 63) / 64;
	else fbh = (height + 31) / 32;
	if (param->interlace == 1 && param->ffmode == 0) return fbw * fbh;
	return fbw * fbh * 2;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/graph/libgraph", sceGsSetDefDrawEnv);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/graph/libgraph", func_00138C84);

int GRAPH_SECTION(sceGsPutDrawEnv) sceGsPutDrawEnv(unsigned long *packet)
{
	unsigned int i = 0;
	while (*(volatile unsigned int *)0x1000a000 & 0x100) {
		if (i++ > 0x1000000) {
			scePrintf(sdkGsDmaTimeoutMsg);
			return -1;
		}
	}
	*(volatile unsigned int *)0x1000a020 = (int)(*packet & 0x7fff) + 1;
	if (((unsigned int)packet & 0x70000000) == 0x70000000)
		*(volatile unsigned int *)0x1000a010 = ((unsigned int)packet & 0x0fffffff) | 0x80000000;
	else
		*(volatile unsigned int *)0x1000a010 = (unsigned int)packet & 0x0fffffff;
	*(volatile unsigned int *)0x1000a000 = 0x101;
	return 0;
}

int GRAPH_SECTION(sceGsSyncV) sceGsSyncV(int mode)
{
	graphGParam_t *param = sceGsGetGParam();
	if (!param->vsyncCallback) {
		VSync();
		if (param->interlace == 1) return (*(volatile unsigned long *)0x12001000 >> 13) & 1;
		return 1;
	} else {
		long field = (VSync2() >> 13) & 1;
		if (param->interlace == 1) return field;
		return 1;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/graph/libgraph", func_00138E04);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/graph/libgraph", sceGsSetDefLoadImage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/graph/libgraph", func_00138FEC);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/graph/libgraph", sceGsSetDefStoreImage);

int GRAPH_SECTION(sceGsExecLoadImage) sceGsExecLoadImage(unsigned long *image, void *data)
{
	unsigned int i = 0;
	while (*(volatile unsigned int *)0x1000a000 & 0x100) {
		if (i++ > 0x1000000) {
			scePrintf(sdkGsLoadTimeoutMsg);
			return -1;
		}
	}
	*(volatile unsigned int *)0x1000a020 = 6;
	if (((unsigned int)image & 0x70000000) == 0x70000000)
		*(volatile unsigned int *)0x1000a010 = ((unsigned int)image & 0x0fffffff) | 0x80000000;
	else
		*(volatile unsigned int *)0x1000a010 = (unsigned int)image & 0x0fffffff;
	*(volatile unsigned int *)0x1000a000 = 0x101;
	while (*(volatile unsigned int *)0x1000a000 & 0x100) {
		if (i++ > 0x1000000) {
			scePrintf(sdkGsLoadTimeoutMsg);
			return -1;
		}
	}
	*(volatile unsigned int *)0x1000a020 = (int)(image[10] & 0x7fff);
	if (((unsigned int)data & 0x70000000) == 0x70000000)
		*(volatile unsigned int *)0x1000a010 = ((unsigned int)data & 0x0fffffff) | 0x80000000;
	else
		*(volatile unsigned int *)0x1000a010 = (unsigned int)data & 0x0fffffff;
	*(volatile unsigned int *)0x1000a000 = 0x101;
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/graph/libgraph", func_001392AC);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/graph/libgraph", sceGsExecStoreImage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/graph/libgraph", func_0013993C);

void *GRAPH_SECTION(sceGsSyncVCallback) sceGsSyncVCallback(int (*func)(int))
{
	graphGParam_t *param = sceGsGetGParam();
	int (*old)(int) = param->vsyncCallback;
	if (!func) {
		DisableIntc(2);
		RemoveIntcHandler(2, param->vsyncHandlerId);
		param->vsyncHandlerId = 0;
		param->vsyncCallback = 0;
	} else {
		if (old) {
			DisableIntc(2);
			RemoveIntcHandler(2, param->vsyncHandlerId);
		}
		param->vsyncCallback = func;
		param->vsyncHandlerId = AddIntcHandler(2, func, -1);
		EnableIntc(2);
	}
	return (void *)old;
}
