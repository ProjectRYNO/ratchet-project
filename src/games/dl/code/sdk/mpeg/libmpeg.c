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
extern long _sceMpegWaitIpuIdle64(mpegInternal_t *);
extern void _sequenceHeader(mpegInternal_t *);
extern const mpegExtTable_t sdkMpegExtTable;
extern const char sdkMpegErrTemporalScalable[];
extern const char sdkMpegErrUnknownExtension[];
extern const char sdkMpegErrBdec[];
extern const char sdkMpegErrQuantIntra[];
extern const char sdkMpegErrQuantNonIntra[];
extern const char sdkMpegErrChroma[];
extern const char sdkMpegErrProfile[];
void flushByteBoundary(mpegInternal_t *sys);
void flushBuf32(mpegInternal_t *sys);
unsigned int _sceMpegPeepBit(mpegInternal_t *sys, int bits);
unsigned int _sceMpegNextBit(mpegInternal_t *sys, int bits);
void _extensionAndUserData(mpegInternal_t *sys);
void _pictureHeader(mpegInternal_t *sys);
void _groupOfPicturesHeader(mpegInternal_t *sys);
#define IPU_CMD (*(volatile unsigned int *)0x10002000)
#define IPU_CTRL (*(volatile int *)0x10002010)
#define IPU_IN_FIFO (*(volatile mpegQword *)0x10007010)
extern volatile mpegQword sdkIpuVlcTable[5];
extern volatile mpegQword sdkIpuCscTable[2];
void setD4_CHCR___dupe2(unsigned int value);
extern void *memset(void *, int, unsigned int);
extern const char sdkMpegErrWorkSize[];
extern const char sdkMpegErrBstagAlign[];
extern const char sdkMpegErrIdctAlign[];
extern void _clearOnce(mpegInternal_t *);
int sceMpegReset(mpeg_t *mp);
int sceMpegClearRefBuff(mpeg_t *mp);
void _sceMpegError1(mpegInternal_t *sys, const char *format, int value);
void _sceMpegAlalcInit(mpegAlalc_t *a, unsigned int base, int size);
void _sceMpegAlalcSetDynamic(mpegAlalc_t *a);
unsigned int _sceMpegAlalcAlloc(mpegInternal_t *sys, mpegAlalc_t *a, unsigned int size, unsigned int align);
int _sceMpegDefaultStopDMA(mpeg_t *mp);
int _sceMpegDefaultRestartDMA(mpeg_t *mp);
extern int _sceMpegDispatchMpegCbNodata(mpeg_t *);
extern void _motionVector(mpegInternal_t *, int *, int *, int, int, int, int, int);
/* EXTERNS */

void MPEG_SECTION(_dualPrimeVector) _dualPrimeVector(mpegInternal_t *sys, int dmv[][2], int *dmvector, int mvx, int mvy)
{
	if (sys->pictureStructure == 3) {
		if (sys->unk188[0]) {
			dmv[0][0] = ((mvx + (mvx > 0)) >> 1) + dmvector[0];
			dmv[0][1] = ((mvy + (mvy > 0)) >> 1) + dmvector[1] - 1;
			dmv[1][0] = ((3 * mvx + (mvx > 0)) >> 1) + dmvector[0];
			dmv[1][1] = ((3 * mvy + (mvy > 0)) >> 1) + dmvector[1] + 1;
		} else {
			dmv[0][0] = ((3 * mvx + (mvx > 0)) >> 1) + dmvector[0];
			dmv[0][1] = ((3 * mvy + (mvy > 0)) >> 1) + dmvector[1] - 1;
			dmv[1][0] = ((mvx + (mvx > 0)) >> 1) + dmvector[0];
			dmv[1][1] = ((mvy + (mvy > 0)) >> 1) + dmvector[1] + 1;
		}
	} else {
		dmv[0][0] = ((mvx + (mvx > 0)) >> 1) + dmvector[0];
		dmv[0][1] = ((mvy + (mvy > 0)) >> 1) + dmvector[1];
		if (sys->pictureStructure == 1) dmv[0][1]--;
		else dmv[0][1]++;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _getAllRefs);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _motionComp0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _getRef0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _doMC);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegPictureData0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _slice0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _motionVector);

void MPEG_SECTION(_motionVectors) _motionVectors(mpegInternal_t *sys, int pmv[2][2][2], int *dmvector, int mvfs[2][2], int s, int count, int mvFormat, int hSize, int vSize, int dmv, int mvScale)
{
	if (count == 1) {
		if (mvFormat == 0 && !dmv) {
			mvfs[1][s] = mvfs[0][s] = _sceMpegNextBit(sys, 1);
		}
		_motionVector(sys, pmv[0][s], dmvector, hSize, vSize, dmv, mvScale, 0);
		pmv[1][s][0] = pmv[0][s][0];
		pmv[1][s][1] = pmv[0][s][1];
	} else {
		mvfs[0][s] = _sceMpegNextBit(sys, 1);
		_motionVector(sys, pmv[0][s], dmvector, hSize, vSize, dmv, mvScale, 0);
		mvfs[1][s] = _sceMpegNextBit(sys, 1);
		_motionVector(sys, pmv[1][s], dmvector, hSize, vSize, dmv, mvScale, 0);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _decMB0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegMbAddressIncrement);

void MPEG_SECTION(_sceMpegWaitIpuIdle) _sceMpegWaitIpuIdle(mpegInternal_t *sys)
{
	int i = 0;
	while ((*(volatile unsigned int *)0x10002010 & 0x80004000) == 0x80000000) {
		unsigned int bp = *(volatile unsigned int *)0x10002020;
		int cmd = sys->ipuCmd;
		unsigned int avail = ((bp & 0xff00) >> 1) + ((bp & 0x30000) >> 9) - (bp & 0x7f);
		if ((cmd == 0x20000000 || cmd == 0x30000000 || cmd == 0x40000000) && avail < 0x20 && !*(volatile unsigned int *)0x1000b420) {
			_sceMpegDispatchMpegCbNodata(sys->mp);
			if (sys->unk878) {
				_sceMpegStopIpuDma();
				break;
			}
			i = 0;
		}
		if (i++ > 5000) {
			_sceMpegDispatchMpegCbNodata(sys->mp);
			if (sys->unk878) {
				_sceMpegStopIpuDma();
				break;
			}
			i = 0;
		}
	}
	sys->ipuCmd = 0;
}

long MPEG_SECTION(_sceMpegWaitIpuIdle64) _sceMpegWaitIpuIdle64(mpegInternal_t *sys)
{
	long cmd;
	int i = 0;
	while ((cmd = *(volatile long *)0x10002000) < 0 && !(*(volatile unsigned int *)0x10002010 & 0x4000)) {
		unsigned int bp = *(volatile unsigned int *)0x10002020;
		int ipuCmd = sys->ipuCmd;
		unsigned int avail = ((bp & 0xff00) >> 1) + ((bp & 0x30000) >> 9) - (bp & 0x7f);
		if ((ipuCmd == 0x20000000 || ipuCmd == 0x30000000 || ipuCmd == 0x40000000) && avail < 0x20 && !*(volatile unsigned int *)0x1000b420) {
			_sceMpegDispatchMpegCbNodata(sys->mp);
			if (sys->unk878) {
				_sceMpegStopIpuDma();
				break;
			}
			i = 0;
		}
		if (i++ > 500) {
			_sceMpegDispatchMpegCbNodata(sys->mp);
			if (sys->unk878) {
				_sceMpegStopIpuDma();
				break;
			}
			i = 0;
		}
	}
	sys->ipuCmd = 0;
	return cmd;
}

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

void MPEG_SECTION(receiveDataFromIPU) receiveDataFromIPU(unsigned int addr, int size)
{
	int intr = DIntr();
	if ((addr >> 28) == 7) {
		addr &= 0x0fffffff;
		addr |= 0x80000000;
	} else addr &= 0x0fffffff;
	*(volatile unsigned int *)0x1000b010 = addr;
	*(volatile unsigned int *)0x1000b020 = size >> 4;
	*(volatile unsigned int *)0x1000b000 = 0x100;
	if (intr) EIntr();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sceMpegSliceA0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _initSeq);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _sequenceHeader);

void MPEG_SECTION(_groupOfPicturesHeader) _groupOfPicturesHeader(mpegInternal_t *sys)
{
	sys->unkFC = 0;
	sys->unk85C[2] = 1;
	sys->unk85C[0] = sys->unk85C[1] + 1;
	_sceMpegNextBit(sys, 1);
	_sceMpegNextBit(sys, 5);
	_sceMpegNextBit(sys, 6);
	_sceMpegNextBit(sys, 1);
	_sceMpegNextBit(sys, 6);
	_sceMpegNextBit(sys, 6);
	sys->unk1B4[0] = _sceMpegNextBit(sys, 1);
	sys->unk1B4[1] = _sceMpegNextBit(sys, 1);
	_extensionAndUserData(sys);
}

void MPEG_SECTION(_pictureHeader) _pictureHeader(mpegInternal_t *sys)
{
	int tref, wrap, last;
	tref = _sceMpegNextBit(sys, 10);
	sys->unk160 = _sceMpegNextBit(sys, 3);
	_sceMpegNextBit(sys, 16);
	if (sys->unk160 == 2 || sys->unk160 == 3) {
		sys->unk164[0] = _sceMpegNextBit(sys, 1);
		sys->unk164[1] = _sceMpegNextBit(sys, 3);
	}
	if (sys->unk160 == 3) {
		sys->unk164[2] = _sceMpegNextBit(sys, 1);
		sys->unk164[3] = _sceMpegNextBit(sys, 3);
	}
	while (_sceMpegNextBit(sys, 1)) _flushBuf___dupe2(sys, 8);
	_extensionAndUserData(sys);
	wrap = 0;
	last = 0;
	if (sys->unk160 != 3 && tref) {
		if (tref < 0) wrap = !sys->unk85C[2];
		sys->unk85C[2] = 0;
		last = tref;
	}
	sys->unk1B4[2] = sys->unk85C[0] + tref;
	if (wrap && !(last < tref)) sys->unk1B4[2] += 0x400;
	sys->unk85C[1] = sys->unk85C[1] < sys->unk1B4[2] ? sys->unk1B4[2] : sys->unk85C[1];
}

void MPEG_SECTION(_sequenceExtension) _sequenceExtension(mpegInternal_t *sys)
{
	unsigned int value, profile, hsize, vsize, bitrate, vbv;
	sys->unk858 = 1;
	*(volatile unsigned int *)0x10002010 &= ~0x800000;
	value = _sceMpegNextBit(sys, 28);
	bitrate = (value >> 1) & 0xfff;
	vsize = (value >> 13) & 3;
	hsize = (value >> 15) & 3;
	sys->unk134[7] = (value >> 17) & 3;
	if (sys->unk134[7] != 1) _sceMpegError(sys, sdkMpegErrChroma);
	sys->unk134[6] = (value >> 19) & 1;
	profile = value >> 20;
	vbv = _sceMpegNextBit(sys, 16) >> 8;
	if (profile != 0x48 && profile != 0x58 && profile != 0x44) _sceMpegError(sys, sdkMpegErrProfile);
	sys->unk134[0] = (hsize << 12) | (sys->unk134[0] & 0xfff);
	sys->unk134[1] = (vsize << 12) | (sys->unk134[1] & 0xfff);
	sys->unk134[4] += bitrate << 18;
	sys->unk134[5] += vbv << 10;
}

void MPEG_SECTION(_quantMatrixExtension) _quantMatrixExtension(mpegInternal_t *sys)
{
	if ((sys->unk850[0] = _sceMpegNextBit(sys, 1))) {
		_waitIpuIdle___dupe2(sys);
		*(volatile unsigned int *)0x10002000 = 0x50000000;
		sys->ipuCmd = 0x50000000;
		sys->bitsInvalid = 1;
		_waitIpuIdle___dupe2(sys);
	}
	if ((sys->unk850[1] = _sceMpegNextBit(sys, 1))) {
		_waitIpuIdle___dupe2(sys);
		*(volatile unsigned int *)0x10002000 = 0x58000000;
		sys->ipuCmd = 0x50000000;
		sys->bitsInvalid = 1;
		_waitIpuIdle___dupe2(sys);
	}
	if (_sceMpegNextBit(sys, 1)) _sceMpegError(sys, sdkMpegErrQuantIntra);
	if (_sceMpegNextBit(sys, 1)) _sceMpegError(sys, sdkMpegErrQuantNonIntra);
}

void MPEG_SECTION(_sequenceScalableExtension) _sequenceScalableExtension(mpegInternal_t *sys)
{
	_sceMpegError(sys, sdkMpegErrSequenceScalable);
}

void MPEG_SECTION(_unknown_extension) _unknown_extension(mpegInternal_t *sys)
{
	_sceMpegError(sys, sdkMpegErrUnknownExtension);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _pictureCodingExtension);

void MPEG_SECTION(_pictureSpatialScalableExtension) _pictureSpatialScalableExtension(mpegInternal_t *sys)
{
	_sceMpegError(sys, sdkMpegErrSpatialScalable);
}

void MPEG_SECTION(_pictureTemporalScalableExtension) _pictureTemporalScalableExtension(mpegInternal_t *sys)
{
	_sceMpegError(sys, sdkMpegErrTemporalScalable);
}

void MPEG_SECTION(_extensionAndUserData) _extensionAndUserData(mpegInternal_t *sys)
{
	mpegExtTable_t table = sdkMpegExtTable;
	unsigned int code, id;
	flushByteBoundary(sys);
	while (_sceMpegPeepBit(sys, 24) != 1 && !sys->unk878) _flushBuf___dupe2(sys, 8);
	while ((code = _sceMpegPeepBit(sys, 32)) == 0x1b5 || code == 0x1b2) {
		if (code == 0x1b5) {
			flushBuf32(sys);
			id = _sceMpegNextBit(sys, 4);
			id = id > 10 ? 0 : id;
			table.funcs[id](sys);
			flushByteBoundary(sys);
			while (_sceMpegPeepBit(sys, 24) != 1 && !sys->unk878) _flushBuf___dupe2(sys, 8);
		} else {
			flushBuf32(sys);
			flushByteBoundary(sys);
			while (_sceMpegPeepBit(sys, 24) != 1 && !sys->unk878) _flushBuf___dupe2(sys, 8);
		}
	}
}

void MPEG_SECTION(_waitIpuIdle___dupe2) _waitIpuIdle___dupe2(mpegInternal_t *sys)
{
	if ((*(volatile unsigned int *)0x10002010 & 0x80004000) == 0x80000000) _sceMpegWaitIpuIdle(sys);
}

void MPEG_SECTION(_flushBuf___dupe2) _flushBuf___dupe2(mpegInternal_t *sys, int bits)
{
	_sceMpegFlushBuf(sys, bits);
}

int MPEG_SECTION(_sceMpegNextHeader) _sceMpegNextHeader(mpegInternal_t *sys)
{
	struct { int type; int pad; long pts; long dts; } cb;
	while (1) {
		if (sys->unk878) return -1;
		flushByteBoundary(sys);
		while (_sceMpegPeepBit(sys, 24) != 1 && !sys->unk878) _flushBuf___dupe2(sys, 8);
		switch (_sceMpegNextBit(sys, 32)) {
		case 0x1b3:
			_sequenceHeader(sys);
			break;
		case 0x1b8:
			_groupOfPicturesHeader(sys);
			break;
		case 0x100:
			_pictureHeader(sys);
			cb.type = 5;
			cb.pts = -1;
			cb.dts = -1;
			_sceMpegDispatchMpegCallback(sys->mp, &cb);
			sys->pts = cb.pts;
			sys->dts = cb.dts;
			return sys->unk160;
		case 0x1b7:
			return 0;
		}
	}
}

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

void MPEG_SECTION(_sequenceDisplayExtension) _sequenceDisplayExtension(mpegInternal_t *sys)
{
	_sceMpegNextBit(sys, 3);
	if (_sceMpegNextBit(sys, 1)) {
		_sceMpegNextBit(sys, 8);
		_sceMpegNextBit(sys, 8);
		sys->unk134[8] = _sceMpegNextBit(sys, 8);
	}
	sys->unk134[9] = _sceMpegNextBit(sys, 14);
	_sceMpegNextBit(sys, 1);
	sys->unk134[10] = _sceMpegNextBit(sys, 14);
}

int MPEG_SECTION(_copyrightExtension) _copyrightExtension(mpegInternal_t *sys)
{
	int ret;
	_sceMpegNextBit(sys, 1);
	_sceMpegNextBit(sys, 8);
	_sceMpegNextBit(sys, 1);
	_sceMpegNextBit(sys, 7);
	_sceMpegNextBit(sys, 1);
	_sceMpegNextBit(sys, 20);
	_sceMpegNextBit(sys, 1);
	_sceMpegNextBit(sys, 22);
	_sceMpegNextBit(sys, 1);
	ret = _sceMpegNextBit(sys, 22);
	return ret;
}

void MPEG_SECTION(_pictureDisplayExtension) _pictureDisplayExtension(mpegInternal_t *sys)
{
	int count, i;
	if (sys->unk134[6]) {
		if (sys->unk188[3]) count = sys->unk188[0] ? 3 : 2;
		else count = 1;
	} else if (sys->pictureStructure != 3) {
		count = 1;
	} else {
		count = sys->unk188[3] ? 3 : 2;
	}
	for (i = 0; i < count; i++) {
		sys->frameHOffset[i] = _sceMpegNextBit(sys, 16);
		_sceMpegNextBit(sys, 1);
		sys->frameVOffset[i] = _sceMpegNextBit(sys, 16);
		_sceMpegNextBit(sys, 1);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", func_00141514);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mpeg/libmpeg", _clearOnce);

int MPEG_SECTION(sceMpegCreate) sceMpegCreate(mpeg_t *mp, void *work, int size)
{
	mpegInternal_t *sys;
	int remain;
	int align;
	memset(work, 0, size);
	sys = (mpegInternal_t *)((((unsigned int)work + 3) >> 2) << 2);
	remain = size - ((unsigned int)sys - (unsigned int)work);
	if (remain < 0x19a0) {
		_sceMpegError(sys, sdkMpegErrWorkSize);
		return 0;
	}
	mp->sys = sys;
	_sceMpegAlalcInit(&sys->alalc, (unsigned int)sys + 0x19a0, remain - 0x19a0);
	mp->width = 0;
	mp->height = 0;
	mp->frameCount = 0;
	mp->pts = -1;
	mp->dts = -1;
	mp->flags = 0;
	mp->pts2nd = -1;
	mp->dts2nd = -1;
	mp->flags2nd = 0;
	sys->unkC8[0] = 0;
	sys->unkC8[1] = 0;
	sys->unkC8[2] = 0;
	sys->unkC8[3] = 0;
	sys->unkC8[4] = 0;
	sys->unkC8[5] = 0;
	sys->unkC8[6] = 0;
	sys->unkC8[7] = 0;
	sys->unkC8[8] = 0;
	sys->outAddr = 0;
	sys->unkF0 = 0;
	sys->unkF4 = 0;
	sys->mbCount = 0;
	sys->unkFC = 0;
	sys->outputState = 0;
	sys->callbacks[0].func = 0;
	sys->callbacks[1].func = 0;
	sys->callbacks[4].func = 0;
	sys->callbacks[5].func = 0;
	sys->callbacks[6].func = 0;
	sys->unk100 = -1;
	sys->callbacks[2].func = _sceMpegDefaultStopDMA;
	sys->callbacks[3].func = _sceMpegDefaultRestartDMA;
	sys->unk60[0] = _sceMpegAlalcAlloc(sys, &sys->alalc, 0x800, 8);
	sys->unk60[1] = 0;
	sys->unk10C[0] = 0;
	sys->unk10C[1] = 0;
	sys->unk10C[2] = 0;
	sys->unk8C = 0;
	sys->unk90 = 0;
	sys->unk98 = -1;
	sys->unkA0 = 0;
	sys->unk9C = 0;
	sys->unkC0 = 0;
	sys->unkA8[0] = -1;
	sys->unkA8[1] = -1;
	sys->unkA8[2] = -1;
	sys->mp = mp;
	sys->unkC4 = 1;
	_clearOnce(sys);
	sceMpegReset(mp);
	sceMpegClearRefBuff(mp);
	sys->refs[0].top = (mpegRefImage_t *)&sys->refImages[0];
	sys->refs[0].bottom = (mpegRefImage_t *)&sys->refImages[1];
	sys->refs[0].display = (mpegRefImage_t *)&sys->refImages[2];
	sys->refs[1].top = (mpegRefImage_t *)&sys->refImages[3];
	sys->refs[1].bottom = (mpegRefImage_t *)&sys->refImages[4];
	sys->refs[1].display = (mpegRefImage_t *)&sys->refImages[5];
	sys->refs[2].top = (mpegRefImage_t *)&sys->refImages[6];
	sys->refs[2].bottom = (mpegRefImage_t *)&sys->refImages[7];
	sys->refs[2].display = (mpegRefImage_t *)&sys->refImages[8];
	_sceMpegAlalcSetDynamic(&sys->alalc);
	sys->unk85C[1] = -1;
	sys->unk85C[0] = 0;
	sys->unk85C[2] = 0;
	align = (unsigned int)sys->unk880 & 0x3f;
	if (align) {
		_sceMpegError1(sys, sdkMpegErrBstagAlign, align);
		return 0;
	}
	align = (unsigned int)sys->unkB80 & 0x3f;
	if (align) {
		_sceMpegError1(sys, sdkMpegErrIdctAlign, align);
		return 0;
	}
	return 1;
}

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

void MPEG_SECTION(_sceMpegErrorBdec) _sceMpegErrorBdec(mpegInternal_t *sys)
{
	struct { int type; int data[5]; } cb;
	int intr;
	_sceMpegError(sys, sdkMpegErrBdec);
	cb.type = 2;
	_sceMpegDispatchMpegCallback(sys->mp, &cb);
	*(volatile unsigned int *)0x10002010 = 0x40000000;
	cb.type = 3;
	_sceMpegDispatchMpegCallback(sys->mp, &cb);
	intr = DIntr();
	*(volatile unsigned int *)0x1000f590 = *(volatile unsigned int *)0x1000f520 | 0x10000;
	*(volatile unsigned int *)0x1000b000 = 0;
	*(volatile unsigned int *)0x1000f590 = *(volatile unsigned int *)0x1000f520 & ~0x10000;
	if (intr) EIntr();
	*(volatile unsigned int *)0x1000b020 = 0;
}

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

void MPEG_SECTION(sceIpuInit) sceIpuInit(void)
{
	setD4_CHCR___dupe2(1);
	IPU_CTRL = 0x40000000;
	while (IPU_CTRL < 0) {}
	IPU_CMD = 0;
	while (IPU_CTRL < 0) {}
	IPU_IN_FIFO = sdkIpuVlcTable[0];
	IPU_IN_FIFO = sdkIpuVlcTable[1];
	IPU_IN_FIFO = sdkIpuVlcTable[2];
	IPU_IN_FIFO = sdkIpuVlcTable[3];
	IPU_IN_FIFO = sdkIpuVlcTable[4];
	IPU_IN_FIFO = sdkIpuVlcTable[4];
	IPU_IN_FIFO = sdkIpuVlcTable[4];
	IPU_IN_FIFO = sdkIpuVlcTable[4];
	IPU_CMD = 0x50000000;
	while (IPU_CTRL < 0) {}
	IPU_CMD = 0x58000000;
	while (IPU_CTRL < 0) {}
	IPU_IN_FIFO = sdkIpuCscTable[0];
	IPU_IN_FIFO = sdkIpuCscTable[1];
	IPU_CMD = 0x60000000;
	while (IPU_CTRL < 0) {}
	IPU_CMD = 0x90000000;
	while (IPU_CTRL < 0) {}
	IPU_CTRL = 0x40000000;
	while (IPU_CTRL < 0) {}
	IPU_CMD = 0;
	while (IPU_CTRL < 0) {}
}
