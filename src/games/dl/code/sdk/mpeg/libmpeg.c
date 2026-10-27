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
extern void sceIpuInit(void);
extern const char sdkMpegErrFormat[];
extern const char sdkMpegErrSpatialScalable[];
extern const char sdkMpegErrSequenceScalable[];
extern const char sdkMpegErrAlloc[];
extern const char sdkMpegErrFlush[];
extern const char sdkMpegErrBufMode[];
extern const char sdkMpegErrPictureData[];
extern const char sdkMpegErrPictureStructure[];
extern void scePrintf(const char *, ...);
extern int sceSnprintf(char *, int, const char *, ...);
extern void sceIpuRestartDMA(mpegIpuDmaEnv_t *);
extern void sceIpuStopDMA(mpegIpuDmaEnv_t *);
extern int sceIpuSync(int, int);
extern void _sceMpegWaitIpuIdle(mpegInternal_t *);
extern long _sceMpegWaitIpuIdle64(mpegInternal_t *);
extern int _decodeOrSkipField(mpeg_t *, void *, int);
extern int _decodeOrSkipFrame(mpeg_t *, void *, int);
extern int _sceMpegDispatchMpegCallback(mpeg_t *, void *);
extern void _dispRefImage(mpegInternal_t *, mpegRefImage_t *, int);
extern void _dispRefImageField(mpegInternal_t *, mpegRefImage_t *, mpegRefImage_t *, int);
extern int _sceMpegPictureData0(mpegInternal_t *);
void _sceMpegError(mpegInternal_t *sys, const char *message);
void _waitIpuIdle(mpegInternal_t *sys);
void _sceMpegFlushBuf(mpegInternal_t *sys, int bits);
void _flushBuf___dupe2(mpegInternal_t *sys, int bits);
void _waitIpuIdle___dupe2(mpegInternal_t *sys);
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

unsigned int MPEG_SECTION(_sceMpegPeepBit) _sceMpegPeepBit(mpegInternal_t *sys, int bits)
{
	if (sys->bitsInvalid || sys->bitCount < bits) {
		_waitIpuIdle(sys);
		*(volatile unsigned int *)0x10002000 = 0x40000000;
		sys->bitsInvalid = 0;
		sys->ipuCmd = 0x40000000;
		sys->bitBuffer = _sceMpegWaitIpuIdle64(sys);
		sys->bitCount = 0x20;
	}
	return sys->bitBuffer >> (32 - bits);
}

void MPEG_SECTION(_sceMpegFlushBuf) _sceMpegFlushBuf(mpegInternal_t *sys, int bits)
{
	unsigned int cmd;
	_waitIpuIdle(sys);
	cmd = bits | 0x40000000;
	*(volatile unsigned int *)0x10002000 = cmd;
	cmd &= 0xf0000000;
	sys->ipuCmd = cmd;
	if (cmd == 0x20000000 || cmd == 0x30000000 || cmd == 0x40000000) sys->bitsInvalid = 0;
	else sys->bitsInvalid = 1;
	sys->bitBuffer = _sceMpegWaitIpuIdle64(sys);
	sys->bitCount = 0x20;
}

void MPEG_SECTION(_waitIpuIdle) _waitIpuIdle(mpegInternal_t *sys)
{
	if ((*(volatile unsigned int *)0x10002010 & 0x80004000) == 0x80000000) _sceMpegWaitIpuIdle(sys);
}

void MPEG_SECTION(_flushBuf) _flushBuf(mpegInternal_t *sys, int bits)
{
	_sceMpegFlushBuf(sys, bits);
}

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

void MPEG_SECTION(_sequenceScalableExtension) _sequenceScalableExtension(mpegInternal_t *sys)
{
	_sceMpegError(sys, sdkMpegErrSequenceScalable);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _unknown_extension);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _pictureCodingExtension);

void MPEG_SECTION(_pictureSpatialScalableExtension) _pictureSpatialScalableExtension(mpegInternal_t *sys)
{
	_sceMpegError(sys, sdkMpegErrSpatialScalable);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _pictureTemporalScalableExtension);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _extensionAndUserData);

void MPEG_SECTION(_waitIpuIdle___dupe2) _waitIpuIdle___dupe2(mpegInternal_t *sys)
{
	if ((*(volatile unsigned int *)0x10002010 & 0x80004000) == 0x80000000) _sceMpegWaitIpuIdle(sys);
}

void MPEG_SECTION(_flushBuf___dupe2) _flushBuf___dupe2(mpegInternal_t *sys, int bits)
{
	_sceMpegFlushBuf(sys, bits);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegNextHeader);

void MPEG_SECTION(flushBuf32) flushBuf32(mpegInternal_t *sys)
{
	_flushBuf___dupe2(sys, 0x20);
}

void MPEG_SECTION(flushByteBoundary) flushByteBoundary(mpegInternal_t *sys)
{
	int bits;
	_waitIpuIdle___dupe2(sys);
	bits = -(*(volatile unsigned int *)0x10002020 & 7) & 7;
	if (bits) _flushBuf___dupe2(sys, bits);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sequenceDisplayExtension);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _copyrightExtension);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _pictureDisplayExtension);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", func_00141514);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _clearOnce);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", sceMpegCreate);

void MPEG_SECTION(_clearEach) _clearEach(mpegInternal_t *sys)
{
	int intr;
	sys->bitsInvalid = 1;
	sys->unk1C0 = 0;
	intr = DIntr();
	*(volatile unsigned int *)0x1000f590 = *(volatile unsigned int *)0x1000f520 | 0x10000;
	*(volatile unsigned int *)0x1000b000 = 0;
	*(volatile unsigned int *)0x1000b400 = 0;
	*(volatile unsigned int *)0x1000d400 = 0;
	*(volatile unsigned int *)0x1000f590 = *(volatile unsigned int *)0x1000f520 & ~0x10000;
	if (intr) EIntr();
	*(volatile unsigned int *)0x1000b020 = 0;
	*(volatile unsigned int *)0x1000b420 = 0;
	*(volatile unsigned int *)0x1000d420 = 0;
	*(volatile unsigned int *)0x10002010 = 0x40000000;
	sceIpuSync(0, 0);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _getpic);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _updateRefImage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _decodeOrSkipFrame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _decodeOrSkipField);

int MPEG_SECTION(sceMpegInit) sceMpegInit(void)
{
	int intr = DIntr();
	*(volatile unsigned int *)0x1000f590 = *(volatile unsigned int *)0x1000f520 | 0x10000;
	*(volatile unsigned int *)0x1000b000 &= ~0x100;
	*(volatile unsigned int *)0x1000b400 &= ~0x100;
	*(volatile unsigned int *)0x1000f590 = *(volatile unsigned int *)0x1000f520 & ~0x10000;
	if (intr) EIntr();
	*(volatile unsigned int *)0x1000b020 = 0;
	*(volatile unsigned int *)0x1000b420 = 0;
	sceIpuInit();
	return 1;
}

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

int MPEG_SECTION(_decodeOrSkip) _decodeOrSkip(mpeg_t *mp, void *data, int count)
{
	int ret;
	if (mp->sys->pictureStructure != 3) ret = _decodeOrSkipField(mp, data, count);
	else ret = _decodeOrSkipFrame(mp, data, count);
	return ret;
}

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

int MPEG_SECTION(_decPicture) _decPicture(mpegInternal_t *sys)
{
	mpegRefImage_t *image;
	int ret;
	if (sys->pictureStructure == 3 && sys->unk130) {
		_sceMpegError(sys, sdkMpegErrPictureData);
		sys->unk130 = 0;
	}
	switch (sys->pictureStructure) {
	case 3:
		image = sys->refs[0].current;
		break;
	case 1:
		image = sys->refs[1].current;
		break;
	case 2:
		image = sys->refs[2].current;
		break;
	default:
		image = sys->refs[0].current;
		_sceMpegError(sys, sdkMpegErrPictureStructure);
	}
	ret = _sceMpegPictureData0(sys);
	if (ret) image->status = 1;
	return ret;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", func_00142514);

void MPEG_SECTION(_sceMpegAlalcInit) _sceMpegAlalcInit(mpegAlalc_t *a, unsigned int base, int size)
{
	a->base = base;
	a->size = size;
	a->ptr = base;
	a->dynamic = base;
}

void MPEG_SECTION(_sceMpegAlalcSetDynamic) _sceMpegAlalcSetDynamic(mpegAlalc_t *a)
{
	a->dynamic = a->ptr;
}

void MPEG_SECTION(_sceMpegAlalcFree) _sceMpegAlalcFree(mpegAlalc_t *a)
{
	a->ptr = a->dynamic;
}

unsigned int MPEG_SECTION(_sceMpegAlalcAlloc) _sceMpegAlalcAlloc(mpegInternal_t *sys, mpegAlalc_t *a, unsigned int size, unsigned int align)
{
	unsigned int p = (a->ptr + align - 1) / align * align;
	unsigned int end = p + size;
	if (a->base + a->size >= end) {
		a->ptr = end;
		return p;
	}
	_sceMpegError(sys, sdkMpegErrAlloc);
	return 0;
}

int MPEG_SECTION(_sceMpegDefaultStopDMA) _sceMpegDefaultStopDMA(mpeg_t *mp)
{
	sceIpuStopDMA(&mp->sys->dmaEnv);
	return 1;
}

int MPEG_SECTION(_sceMpegDefaultRestartDMA) _sceMpegDefaultRestartDMA(mpeg_t *mp)
{
	sceIpuRestartDMA(&mp->sys->dmaEnv);
	return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", func_0014260C);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _cpr8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _dispRefImage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _dispRefImageField);

int MPEG_SECTION(_sceMpegFlush) _sceMpegFlush(mpeg_t *mp)
{
	mpegInternal_t *sys = mp->sys;
	int ret = 0;
	if (sys->refBuffCount && sys->unk08) {
		int count = sys->unk128;
		if (sys->unk130) {
			_sceMpegError(sys, sdkMpegErrFlush);
		} else if (sys->pictureStructure == 3) {
			_dispRefImage(sys, sys->refs[0].bottom, count - 1);
		} else {
			_dispRefImageField(sys, sys->refs[1].bottom, sys->refs[2].bottom, count - 1);
		}
		ret = 1;
		sys->unk130 = 0;
		mp->frameCount = sys->unk128 - sys->unkC0;
		sys->refBuffCount = 0;
	}
	return ret;
}

void MPEG_SECTION(_sceMpegOutputFrame) _sceMpegOutputFrame(mpegInternal_t *sys, int count, int output)
{
	if (output) {
		if (sys->pictureStructure == 3) {
			mpegRefImage_t *image;
			if (sys->unk160 == 3) image = sys->refs[0].display;
			else image = sys->refs[0].top;
			_dispRefImage(sys, image, count - 1);
		} else {
			mpegRefImage_t *top, *bottom;
			if (sys->unk160 == 3) {
				top = sys->refs[1].display;
				bottom = sys->refs[2].display;
			} else {
				top = sys->refs[1].top;
				bottom = sys->refs[2].top;
			}
			_dispRefImageField(sys, top, bottom, count - 1);
		}
	}
	if (sys->outputState == 1) sys->outputState = 2;
}

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

void MPEG_SECTION(_ErrMessage) _ErrMessage(const char *message)
{
	scePrintf(sdkMpegErrFormat, message);
}

void MPEG_SECTION(_sceMpegStopIpuDma) _sceMpegStopIpuDma(void)
{
	int intr = DIntr();
	*(volatile unsigned int *)0x1000f590 = *(volatile unsigned int *)0x1000f520 | 0x10000;
	*(volatile unsigned int *)0x1000b000 = 0;
	*(volatile unsigned int *)0x1000b400 = 0;
	*(volatile unsigned int *)0x1000f590 = *(volatile unsigned int *)0x1000f520 & ~0x10000;
	if (intr) EIntr();
	*(volatile unsigned int *)0x1000b020 = 0;
	*(volatile unsigned int *)0x1000b420 = 0;
	*(volatile unsigned int *)0x10002010 = 0x40000000;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegErrorBdec);

void MPEG_SECTION(_sceMpegError) _sceMpegError(mpegInternal_t *sys, const char *message)
{
	mpegCbError_t cb;
	if (sys->mp && sys && sys->callbacks[0].func) {
		cb.message = message;
		cb.type = 0;
		_sceMpegDispatchMpegCallback(sys->mp, &cb);
		return;
	}
	_ErrMessage(message);
}

void MPEG_SECTION(_sceMpegError1) _sceMpegError1(mpegInternal_t *sys, const char *format, int value)
{
	char buffer[0x100];
	sceSnprintf(buffer, 0x100, format, value);
	_sceMpegError(sys, buffer);
}

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

int MPEG_SECTION(sceIpuSync) sceIpuSync(int mode, int timeout)
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
