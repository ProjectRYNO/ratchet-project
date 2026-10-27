#include "common.h"
#include "libmpeg.h"

/* Recovered directly from the retail boot instructions; no vendor source. */
#define MPEG_SECTION(name) __attribute__((section(".mpeg_" #name)))

/* Functions not yet recovered, and original padding words, stay in their own slots. */
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
	__asm__(".section .mpeg_" #NAME ",\"ax\",@progbits\n" \
		".set noat\n.set noreorder\n" \
		".include \"" FOLDER "/" #NAME ".s\"\n" \
		".set reorder\n.set at\n.text\n")
#endif

extern int _getpic(mpeg_t *);
extern void _clearEach(mpegInternal_t *);
extern int DIntr(void);
extern int EIntr(void);
void setD3_CHCR(unsigned int value);
void setD4_CHCR(unsigned int value);
/* EXTERNS */

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _dualPrimeVector);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _getAllRefs);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _motionComp0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _getRef0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _doMC);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegPictureData0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _slice0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _motionVector);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _motionVectors);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _decMB0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegMbAddressIncrement);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegWaitIpuIdle);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegWaitIpuIdle64);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegNextBit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegPeepBit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegFlushBuf);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _waitIpuIdle);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _flushBuf);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _skipMB0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _copyAddRefImage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _copyRefImage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", dmaRefImage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _rix_000);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _ri0_000);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _rix_001);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _ri0_001);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _rix_010);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _ri0_010);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _rix_011);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _ri0_011);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _rix_100);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _ri0_100);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _rix_101);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _ri0_101);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _rix_110);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _ri0_110);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _rix_111);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _ri0_111);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", receiveDataFromIPU);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegSliceA0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _initSeq);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sequenceHeader);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _groupOfPicturesHeader);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _pictureHeader);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sequenceExtension);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _quantMatrixExtension);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sequenceScalableExtension);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _unknown_extension);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _pictureCodingExtension);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _pictureSpatialScalableExtension);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _pictureTemporalScalableExtension);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _extensionAndUserData);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _waitIpuIdle___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _flushBuf___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegNextHeader);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", flushBuf32);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", flushByteBoundary);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sequenceDisplayExtension);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _copyrightExtension);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _pictureDisplayExtension);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", func_00141514);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _clearOnce);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", sceMpegCreate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _clearEach);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _getpic);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _updateRefImage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _decodeOrSkipFrame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _decodeOrSkipField);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", sceMpegInit);

int MPEG_SECTION(sceMpegDelete) sceMpegDelete(mpeg_t *mp)
{
	return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", func_00142148);

int MPEG_SECTION(sceMpegGetPicture) sceMpegGetPicture(mpeg_t *mp, void *rgb32, int mbCount)
{
	mpegInternal_t *sys;
	rgb32 = (void *)(((unsigned int)rgb32 & 0x0fffffff) | 0x20000000);
	sys = mp->sys;
	sys->unkC4 = 1;
	sys->outAddr = (unsigned int)rgb32;
	sys->mbCount = mbCount;
	sys->unkF4 = 0;
	sys->unkF0 = 0;
	return _getpic(mp);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", func_00142198);

int MPEG_SECTION(sceMpegReset) sceMpegReset(mpeg_t *mp)
{
	mpegInternal_t *sys = mp->sys;
	sys->unk878 = 0;
	sys->isEnd = 0;
	sys->refBuffCount = 0;
	sys->unk08 = 0;
	mp->frameCount = 0;
	sys->unkC0 = 0;
	sys->unk98 = -1;
	_clearEach(sys);
	sys->unk128 = 0;
	sys->unk858 = 0;
	*(volatile unsigned int *)0x10002010 = (*(volatile unsigned int *)0x10002010 & ~0x800000) | 0x800000;
	return 1;
}

int MPEG_SECTION(sceMpegIsEnd) sceMpegIsEnd(mpeg_t *mp)
{
	return mp->sys->isEnd;
}

int MPEG_SECTION(sceMpegIsRefBuffEmpty) sceMpegIsRefBuffEmpty(mpeg_t *mp)
{
	return !mp->sys->refBuffCount;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", func_00142240);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", sceMpegAddCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", func_00142280);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegDispatchMpegCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegDispatchMpegCbNodata);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _decodeOrSkip);

int MPEG_SECTION(sceMpegClearRefBuff) sceMpegClearRefBuff(mpeg_t *mp)
{
	mpegInternal_t *sys = mp->sys;
	if (sys->refs[0].top) sys->refs[0].top->status = 0;
	if (sys->refs[1].top) sys->refs[1].top->status = 0;
	if (sys->refs[2].top) sys->refs[2].top->status = 0;
	if (sys->refs[0].bottom) sys->refs[0].bottom->status = 0;
	if (sys->refs[1].bottom) sys->refs[1].bottom->status = 0;
	if (sys->refs[2].bottom) sys->refs[2].bottom->status = 0;
	return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", func_00142420);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _decPicture);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", func_00142514);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegAlalcInit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegAlalcSetDynamic);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegAlalcFree);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegAlalcAlloc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegDefaultStopDMA);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegDefaultRestartDMA);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", func_0014260C);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _cpr8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _dispRefImage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _dispRefImageField);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegFlush);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegOutputFrame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _doCSC2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegCscStoreRefImage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _ch3dmaCSC);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _ch4dma);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", func_00143984);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _system_header);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _pack_header);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _PES_packet);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", sceMpegDemuxPssRing);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", sceMpegAddStrCallback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _ErrMessage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegStopIpuDma);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegErrorBdec);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegError);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegError1);

void MPEG_SECTION(setD3_CHCR) setD3_CHCR(unsigned int value)
{
	int intr = DIntr();
	*(volatile unsigned int *)0x1000f590 = *(volatile unsigned int *)0x1000f520 | 0x10000;
	*(volatile unsigned int *)0x1000b000 = value;
	*(volatile unsigned int *)0x1000f590 = *(volatile unsigned int *)0x1000f520 & ~0x10000;
	if (intr) EIntr();
}

void MPEG_SECTION(setD4_CHCR) setD4_CHCR(unsigned int value)
{
	int intr = DIntr();
	*(volatile unsigned int *)0x1000f590 = *(volatile unsigned int *)0x1000f520 | 0x10000;
	*(volatile unsigned int *)0x1000b400 = value;
	*(volatile unsigned int *)0x1000f590 = *(volatile unsigned int *)0x1000f520 & ~0x10000;
	if (intr) EIntr();
}

void MPEG_SECTION(sceIpuStopDMA) sceIpuStopDMA(mpegIpuDmaEnv_t *env)
{
	setD4_CHCR(1);
	env->d4madr = *(volatile unsigned int *)0x1000b410;
	env->d4tadr = *(volatile unsigned int *)0x1000b430;
	env->d4qwc = *(volatile unsigned int *)0x1000b420;
	env->d4chcr = *(volatile unsigned int *)0x1000b400;
	while (*(volatile unsigned int *)0x10002010 & 0xf0) {}
	setD3_CHCR(0);
	env->d3madr = *(volatile unsigned int *)0x1000b010;
	env->d3qwc = *(volatile unsigned int *)0x1000b020;
	env->d3chcr = *(volatile unsigned int *)0x1000b000;
	env->ipubp = *(volatile unsigned int *)0x10002020;
	env->ipuctrl = *(volatile unsigned int *)0x10002010;
}

void MPEG_SECTION(sceIpuRestartDMA) sceIpuRestartDMA(mpegIpuDmaEnv_t *env)
{
	int bp = env->ipubp & 0x7f;
	int count = ((env->ipubp >> 16) & 3) + ((env->ipubp >> 8) & 0xf);
	unsigned int madr = env->d4madr - (count << 4);
	unsigned int qwc = env->d4qwc + count;
	if (env->d3madr && env->d3qwc) {
		*(volatile unsigned int *)0x1000b010 = env->d3madr;
		*(volatile unsigned int *)0x1000b020 = env->d3qwc;
		setD3_CHCR(env->d3chcr | 0x100);
	}
	while (*(volatile int *)0x10002010 < 0) {}
	*(volatile unsigned int *)0x10002000 = bp;
	while (*(volatile int *)0x10002010 < 0) {}
	if (madr && qwc) {
		*(volatile unsigned int *)0x1000b410 = madr;
		*(volatile unsigned int *)0x1000b430 = env->d4tadr;
		*(volatile unsigned int *)0x1000b420 = qwc;
		setD4_CHCR(env->d4chcr | 0x100);
	}
}

int MPEG_SECTION(sceIpuSync) sceIpuSync(int mode)
{
	int ret = 0;
	switch (mode) {
	case 0:
		while (*(volatile int *)0x10002010 < 0) {}
		ret = 0;
		break;
	case 1:
		ret = *(volatile unsigned int *)0x10002010 >> 31;
		break;
	}
	return ret;
}

void MPEG_SECTION(setD4_CHCR___dupe2) setD4_CHCR___dupe2(unsigned int value)
{
	int intr = DIntr();
	*(volatile unsigned int *)0x1000f590 = *(volatile unsigned int *)0x1000f520 | 0x10000;
	*(volatile unsigned int *)0x1000b400 = value;
	*(volatile unsigned int *)0x1000f590 = *(volatile unsigned int *)0x1000f520 & ~0x10000;
	if (intr) EIntr();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", sceIpuInit);
