#ifndef SDK_MPEG_LIBMPEG_H
#define SDK_MPEG_LIBMPEG_H

/* 128-bit quadword (IPU FIFO writes). */
typedef unsigned int mpegQword __attribute__((mode(TI)));

/* Decoder callback registration (sceMpegAddCallback). */
typedef struct mpegCallback {
	/* 0x00 */ void *func;
	/* 0x04 */ void *data;
	/* 0x08 */ int gp;
} mpegCallback_t;

/* Reference image; only the status word is recovered. */
typedef struct mpegRefImage {
	/* 0x00 */ int unk00[10];
	/* 0x28 */ int status;
} mpegRefImage_t;

/* Reference image storage (0x68 bytes each, nine per decoder). */
typedef struct mpegRefImageBuf {
	/* 0x00 */ char data[0x68];
} mpegRefImageBuf_t;

/* Reference image pair: top/bottom fields and the current/display images. */
typedef struct mpegRefPair {
	/* 0x00 */ mpegRefImage_t *top;
	/* 0x04 */ mpegRefImage_t *bottom;
	/* 0x08 */ mpegRefImage_t *current;
	/* 0x0c */ mpegRefImage_t *display;
} mpegRefPair_t;

/* Linear allocator state (_sceMpegAlalc*). */
typedef struct mpegAlalc {
	/* 0x00 */ unsigned int base;
	/* 0x04 */ unsigned int size;
	/* 0x08 */ unsigned int ptr;
	/* 0x0c */ unsigned int dynamic;
} mpegAlalc_t;

/* Error callback payload (_sceMpegError). */
typedef struct mpegCbError {
	/* 0x00 */ int type;
	/* 0x04 */ const char *message;
} mpegCbError_t;

/* sceIpuDmaEnv: IPU DMA state saved by sceIpuStopDMA and restored by sceIpuRestartDMA. */
typedef struct mpegIpuDmaEnv {
	/* 0x00 */ unsigned int d4madr;
	/* 0x04 */ unsigned int d4tadr;
	/* 0x08 */ unsigned int d4qwc;
	/* 0x0c */ unsigned int d4chcr;
	/* 0x10 */ unsigned int d3madr;
	/* 0x14 */ unsigned int d3qwc;
	/* 0x18 */ unsigned int d3chcr;
	/* 0x1c */ unsigned int ipubp;
	/* 0x20 */ unsigned int ipuctrl;
} mpegIpuDmaEnv_t;

/* Internal decoder state at sceMpeg.sys; only fields used by recovered code are named. */
typedef struct mpegInternal {
	/* 0x000 */ int isEnd;
	/* 0x004 */ int refBuffCount;
	/* 0x008 */ int unk08;
	/* 0x00c */ mpegCallback_t callbacks[7];
	/* 0x060 */ int unk60[2];
	/* 0x068 */ mpegIpuDmaEnv_t dmaEnv;
	/* 0x08c */ int unk8C;
	/* 0x090 */ long unk90;
	/* 0x098 */ int unk98;
	/* 0x09c */ int unk9C;
	/* 0x0a0 */ long unkA0;
	/* 0x0a8 */ int unkA8[3];
	/* 0x0b4 */ int unkB4[3];
	/* 0x0c0 */ int unkC0;
	/* 0x0c4 */ int unkC4;
	/* 0x0c8 */ int unkC8[9];
	/* 0x0ec */ unsigned int outAddr;
	/* 0x0f0 */ int unkF0;
	/* 0x0f4 */ int unkF4;
	/* 0x0f8 */ int mbCount;
	/* 0x0fc */ int unkFC;
	/* 0x100 */ long unk100;
	/* 0x108 */ int outputState;
	/* 0x10c */ int unk10C[3];
	/* 0x118 */ mpegAlalc_t alalc;
	/* 0x128 */ int unk128;
	/* 0x12c */ int unk12C;
	/* 0x130 */ int unk130;
	/* 0x134 */ int unk134[11];
	/* 0x160 */ int unk160;
	/* 0x164 */ int unk164[8];
	/* 0x184 */ int pictureStructure;
	/* 0x188 */ int unk188[5];
	/* 0x19c */ int frameHOffset[3];
	/* 0x1a8 */ int frameVOffset[3];
	/* 0x1b4 */ int unk1B4[3];
	/* 0x1c0 */ int unk1C0;
	/* 0x1c4 */ int unk1C4;
	/* 0x1c8 */ mpegRefPair_t refs[3];
	/* 0x1f8 */ mpegRefImageBuf_t refImages[9];
	/* 0x5a0 */ unsigned int unk5A0;
	/* 0x5a4 */ unsigned int unk5A4;
	/* 0x5a8 */ int unk5A8[78];
	/* 0x6e0 */ unsigned int unk6E0;
	/* 0x6e4 */ unsigned int unk6E4;
	/* 0x6e8 */ int unk6E8[78];
	/* 0x820 */ int unk820;
	/* 0x824 */ int unk824;
	/* 0x828 */ int bitsInvalid;
	/* 0x82c */ unsigned int ipuCmd;
	/* 0x830 */ unsigned int unk830;
	/* 0x834 */ int unk834;
	/* 0x838 */ long pts;
	/* 0x840 */ long dts;
	/* 0x848 */ unsigned int bitBuffer;
	/* 0x84c */ int bitCount;
	/* 0x850 */ int unk850[2];
	/* 0x858 */ int unk858;
	/* 0x85c */ int unk85C[3];
	/* 0x868 */ struct mpeg *mp;
	/* 0x86c */ int unk86C[3];
	/* 0x878 */ int unk878;
	/* 0x87c */ int unk87C;
	/* 0x880 */ char unk880[0x300];
	/* 0xb80 */ char unkB80[0x300];
	/* 0xe80 */ char unkE80[0x10];
} mpegInternal_t;

/* sceMpeg handle. */
typedef struct mpeg {
	/* 0x00 */ int width;
	/* 0x04 */ int height;
	/* 0x08 */ int frameCount;
	/* 0x0c */ int unk0C;
	/* 0x10 */ long pts;
	/* 0x18 */ long dts;
	/* 0x20 */ unsigned long flags;
	/* 0x28 */ long pts2nd;
	/* 0x30 */ long dts2nd;
	/* 0x38 */ unsigned long flags2nd;
	/* 0x40 */ mpegInternal_t *sys;
} mpeg_t;


/* Extension parser table copied to the stack by _extensionAndUserData. */
typedef void (*mpegExtFunc)(mpegInternal_t *);
typedef struct mpegExtTable {
	/* 0x00 */ mpegExtFunc funcs[11];
} mpegExtTable_t;

#endif
