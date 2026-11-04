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
extern int GsPutIMR(int);
extern int GsGetIMR(void);
extern volatile graphQword sdkGsFifoFlush;
extern const char sdkGsStoreDmaTimeoutMsg[];
extern const char sdkGsStoreCsrTimeoutMsg[];
extern const char sdkGsStoreDmaFifoMsg[];
extern const char sdkGsStoreFifoMsg[];
#define D1_CHCR (*(volatile unsigned int *)0x10009000)
#define D1_MADR (*(volatile unsigned int *)0x10009010)
#define D1_QWC (*(volatile unsigned int *)0x10009020)
#define VIF1_STAT (*(volatile unsigned int *)0x10003c00)
#define VIF1_FBRST (*(volatile unsigned int *)0x10003c10)
#define VIF1_FIFO (*(volatile graphQword *)0x10005000)
#define GIF_CTRL (*(volatile unsigned int *)0x10003000)
#define GS_CSR (*(volatile unsigned long *)0x12001000)
#define GS_BUSDIR (*(volatile unsigned long *)0x12001040)
extern void SetGsCrt(short, short, short);
extern const char sdkGsLoadImageSizeMsg[];
graphGParam_t *sceGsGetGParam(void);

void GRAPH_SECTION(sceGsResetGraph) sceGsResetGraph(short mode, short interlace, short omode, short ffmode)
{
	graphGParam_t *param;
	switch (mode) {
	case 0:
		param = sceGsGetGParam();
		*(volatile unsigned long *)0x12001000 = 0x200;
		param->interlace = interlace;
		param->omode = omode;
		param->version = (*(volatile unsigned long *)0x12001000 >> 16) & 0xff;
		GsPutIMR(0xff00);
		param->ffmode = ffmode != 0;
		if (param->vsyncCallback) {
			DisableIntc(2);
			RemoveIntcHandler(2, param->vsyncHandlerId);
			param->vsyncCallback = 0;
			param->vsyncHandlerId = 0;
		}
		SetGsCrt(interlace & 1, omode & 0xff, ffmode & 1);
		break;
	case 1:
		*(volatile unsigned long *)0x12001000 = 0x100;
		break;
	case 5:
		param = sceGsGetGParam();
		param->ffmode = ffmode != 0;
		param->interlace = interlace;
		param->omode = omode;
		param->version = (*(volatile unsigned long *)0x12001000 >> 16) & 0xff;
		SetGsCrt(interlace & 1, omode & 0xff, ffmode & 1);
		break;
	}
}

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

int GRAPH_SECTION(sceGsSetDefDrawEnv) sceGsSetDefDrawEnv(graphDrawEnv1_t *draw, short psm, short w, short h, short ztest, short zpsm)
{
	draw->frame1addr = 0x4c;
	draw->frame1 = (unsigned long)(((w + 63) >> 6) & 0x3f) << 16 | (unsigned long)(psm & 0xf) << 24;
	draw->zbuf1addr = 0x4e;
	if (ztest == 0)
		draw->zbuf1 = (long)sceGszbufaddr(psm, w, h) | (unsigned long)(zpsm & 0xf) << 24 | (1L << 32);
	else
		draw->zbuf1 = (long)sceGszbufaddr(psm, w, h) | (unsigned long)(zpsm & 0xf) << 24;
	draw->xyoffset1addr = 0x18;
	draw->xyoffset1 = (0x800L - (w >> 1)) << 4 | (0x800L - (h >> 1)) << 36;
	draw->scissor1addr = 0x40;
	draw->scissor1 = (long)(w - 1) << 16 | (long)(h - 1) << 48;
	draw->prmodecontaddr = 0x1a;
	draw->prmodecont.AC = 1;
	draw->colclampaddr = 0x46;
	draw->colclamp.CLAMP = 1;
	draw->ditheraddr = 0x45;
	if (psm & 2) draw->dthe.DTHE = 1;
	else draw->dthe.DTHE = 0;
	draw->test1addr = 0x47;
	if (ztest) draw->test1 = (unsigned long)(ztest & 3) << 17 | 0x10000;
	else draw->test1 = 0x30000;
	__asm__ volatile("sync");
	return 8;
}

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

int GRAPH_SECTION(sceGsSetDefLoadImage) sceGsSetDefLoadImage(graphLoadImage_t *lp, short dbp, short dbw, short dpsm, short x, short y, short w, short h)
{
	int size = 0;
	switch (dpsm) {
	case 0: case 48: size = (w * h) >> 2; break;
	case 1: case 49: size = (w * h * 3) >> 4; break;
	case 2: case 10: case 50: case 58: size = (w * h) >> 3; break;
	case 19: case 27: size = (w * h) >> 4; break;
	case 20: case 36: case 44: size = (w * h) >> 5; break;
	}
	if (size > 0x7fff) { scePrintf(sdkGsLoadImageSizeMsg); return 0; }
	*(graphQword *)&lp->giftag1 = 0;
	lp->giftag1.NLOOP = size & 0x7fff;
	*(graphQword *)&lp->giftag0 = 0;
	lp->giftag0.NLOOP = 4;
	lp->trxdir = 0;
	lp->giftag0.NREG = 1;
	lp->giftag0.REGS0 = 0xe;
	lp->bitbltbuf = (long)dbp << 32 | (long)dbw << 48 | (long)dpsm << 56;
	lp->bitbltbufaddr = 0x50;
	lp->giftag1.EOP = 1;
	lp->trxpos = (long)x << 32 | (long)y << 48;
	lp->trxposaddr = 0x51;
	lp->trxreg = (long)w | (long)h << 32;
	lp->trxregaddr = 0x52;
	lp->trxdiraddr = 0x53;
	lp->giftag1.FLG = 2;
	__asm__ volatile("sync");
	return 6;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/graph/libgraph", func_00138FEC);

int GRAPH_SECTION(sceGsSetDefStoreImage) sceGsSetDefStoreImage(graphStoreImage2_t *sp, short sbp, short sbw, short spsm, short x, short y, short w, short h)
{
	long ty;
	*(graphQword *)&sp->giftag = 0;
	sp->vifcode[1] = 0x6008000;
	sp->vifcode[0] = 0;
	sp->finish = 0;
	sp->vifcode[2] = 0x13000000;
	sp->vifcode[3] = 0x50000006;
	sp->giftag.NLOOP = 5;
	sp->giftag.EOP = 1;
	sp->giftag.NREG = 1;
	sp->giftag.REGS0 = 0xe;
	ty = y << 16;
	sp->bitbltbuf = (long)sbp | (sbw << 16) | (long)spsm << 24;
	sp->bitbltbufaddr = 0x50;
	sp->trxpos = (long)x | ty;
	sp->trxposaddr = 0x51;
	sp->trxreg = (long)w | (long)h << 32;
	sp->trxregaddr = 0x52;
	sp->finishaddr = 0x61;
	sp->trxdir = 1;
	sp->trxdiraddr = 0x53;
	__asm__ volatile("sync");
	return 7;
}

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

int GRAPH_SECTION(sceGsExecStoreImage) sceGsExecStoreImage(graphStoreImage_t *image, graphQword *data)
{
	unsigned int i = 0;
	int dma = 0;
	int fifo = 0;
	int rem = 0;
	int discard = 0;
	int n, height, width, h2, bytes, t;
	int imr;
	char q[16];
	width = image->trxreg & 0xfff;
	height = (image->trxreg >> 32) & 0xfff;
	h2 = 0;
	switch ((int)((image->bitbltbuf >> 24) & 0x3f)) {
	case 0x00:
	case 0x30:
		bytes = (width * height) << 2;
		rem = bytes & 0xf;
		dma = (bytes >> 4) & 0xfffffff8;
		fifo = (bytes >> 4) & 7;
		if (!rem) {
			h2 = height;
			discard = 0;
		} else {
			h2 = (height + 3) & 0x1ffc;
			t = width * h2;
			discard = (t >> 2) - dma - fifo - 1;
		}
		break;
	case 0x01:
	case 0x31:
		bytes = width * height * 3;
		rem = bytes & 0xf;
		dma = (bytes >> 4) & 0xfffffff8;
		fifo = (bytes >> 4) & 7;
		if (!rem) {
			h2 = height;
			discard = 0;
		} else {
			h2 = (height + 15) & 0x1ff0;
			t = width * h2;
			t = ((t * 3) >> 4) - dma;
			discard = t - fifo - 1;
		}
		break;
	case 0x02:
	case 0x0a:
	case 0x32:
	case 0x3a:
		bytes = (width * height) << 1;
		rem = bytes & 0xf;
		fifo = (bytes >> 4) & 7;
		dma = (bytes >> 4) & 0xfffffff8;
		if (!rem) {
			h2 = height;
			discard = 0;
		} else {
			h2 = (height + 7) & 0xfffffff8;
			t = width * h2;
			discard = (t >> 3) - dma - fifo - 1;
		}
		break;
	case 0x13:
	case 0x1b:
		bytes = width * height;
		rem = bytes & 0xf;
		fifo = (bytes >> 4) & 7;
		dma = (bytes >> 4) & 0xfffffff8;
		if (!rem) {
			h2 = height;
			discard = 0;
		} else {
			h2 = (height + 7) & 0xfffffff8;
			t = width * h2;
			discard = (t >> 4) - dma - fifo - 1;
		}
		break;
	case 0x14:
	case 0x24:
	case 0x2c:
		bytes = (width * height) >> 1;
		rem = bytes & 0xf;
		fifo = (bytes >> 4) & 7;
		dma = (bytes >> 4) & 0xfffffff8;
		if (!rem) {
			h2 = height;
			discard = 0;
		} else {
			h2 = (height + 7) & 0xfffffff8;
			t = width * h2;
			discard = (t >> 5) - dma - fifo - 1;
		}
		break;
	}
	if (rem) {
		*(unsigned long *)((unsigned int)&image->trxreg | 0x20000000) = (unsigned long)(int)(image->trxreg & 0xfff) | ((unsigned long)h2 << 32);
	}
	while (D1_CHCR & 0x100) {
		if (i++ > 0x1000000) {
			scePrintf(sdkGsStoreDmaTimeoutMsg);
			return -1;
		}
	}
	imr = GsPutIMR(GsGetIMR() | 0x200);
	GS_CSR = 2;
	D1_QWC = 7;
	if (((unsigned int)image & 0x70000000) == 0x70000000)
		D1_MADR = ((unsigned int)image & 0x0fffffff) | 0x80000000;
	else
		D1_MADR = (unsigned int)image & 0x0fffffff;
	D1_CHCR = 0x101;
	while (D1_CHCR & 0x100) {
		if (i++ > 0x1000000) {
			scePrintf(sdkGsStoreDmaTimeoutMsg);
			return -1;
		}
	}
	while (!(GS_CSR & 2)) {
		if (i++ > 0x1000000) {
			scePrintf(sdkGsStoreCsrTimeoutMsg);
			VIF1_FIFO = sdkGsFifoFlush;
			return -1;
		}
	}
	VIF1_STAT = 0x800000;
	GS_BUSDIR = 1;
	if (dma) {
		D1_QWC = dma;
		if (((unsigned int)data & 0x70000000) == 0x70000000)
			D1_MADR = ((unsigned int)data & 0x0fffffff) | 0x80000000;
		else
			D1_MADR = (unsigned int)data & 0x0fffffff;
		D1_CHCR = 0x100;
		while (D1_CHCR & 0x100) {
			if (i++ > 0x1000000) {
				scePrintf(sdkGsStoreDmaFifoMsg);
				GS_CSR = 0x100; GS_BUSDIR = 0; GIF_CTRL = 1; VIF1_FBRST = 1; return -1;
			}
		}
	}
	for (n = 0; n < fifo; n++) {
		while (!(VIF1_STAT & 0x1f000000)) {
			if (i++ > 0x1000000) { scePrintf(sdkGsStoreFifoMsg); GS_CSR = 0x100; GS_BUSDIR = 0; GIF_CTRL = 1; VIF1_FBRST = 1; return -1; }
		}
		data[dma + n] = VIF1_FIFO;
	}
	if (rem) {
		while (!(VIF1_STAT & 0x1f000000)) {
			if (i++ > 0x1000000) { scePrintf(sdkGsStoreFifoMsg); GS_CSR = 0x100; GS_BUSDIR = 0; GIF_CTRL = 1; VIF1_FBRST = 1; return -1; }
		}
		*(graphQword *)q = VIF1_FIFO;
		for (n = 0; n < rem; n++) ((char *)&data[dma + fifo])[n] = q[n];
		for (n = 0; n < discard; n++) {
			while (!(VIF1_STAT & 0x1f000000)) {
				if (i++ > 0x1000000) { scePrintf(sdkGsStoreFifoMsg); GS_CSR = 0x100; GS_BUSDIR = 0; GIF_CTRL = 1; VIF1_FBRST = 1; return -1; }
			}
			*(graphQword *)q = VIF1_FIFO;
		}
	}
	VIF1_STAT = 0;
	GS_BUSDIR = 0;
	GsPutIMR(imr);
	{ graphQword f = sdkGsFifoFlush;
	GS_CSR = 2;
	VIF1_FIFO = f; }
	return 0;
}

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
