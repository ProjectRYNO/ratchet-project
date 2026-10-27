#ifndef SDK_MPEG_LIBMPEG_H
#define SDK_MPEG_LIBMPEG_H

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

/* Top/bottom reference image pair. */
typedef struct mpegRefPair {
	/* 0x00 */ mpegRefImage_t *top;
	/* 0x04 */ mpegRefImage_t *bottom;
	/* 0x08 */ int unk08[2];
} mpegRefPair_t;

/* Internal decoder state at sceMpeg.sys; only fields used by recovered code are named. */
typedef struct mpegInternal {
	/* 0x000 */ int isEnd;
	/* 0x004 */ int refBuffCount;
	/* 0x008 */ int unk08;
	/* 0x00c */ mpegCallback_t callbacks[8];
	/* 0x06c */ char unk6C[0x2c];
	/* 0x098 */ int unk98;
	/* 0x09c */ char unk9C[0x24];
	/* 0x0c0 */ int unkC0;
	/* 0x0c4 */ int unkC4;
	/* 0x0c8 */ char unkC8[0x24];
	/* 0x0ec */ unsigned int outAddr;
	/* 0x0f0 */ int unkF0;
	/* 0x0f4 */ int unkF4;
	/* 0x0f8 */ int mbCount;
	/* 0x0fc */ char unkFC[0x2c];
	/* 0x128 */ int unk128;
	/* 0x12c */ char unk12C[0x9c];
	/* 0x1c8 */ mpegRefPair_t refs[3];
	/* 0x1f8 */ char unk1F8[0x660];
	/* 0x858 */ int unk858;
	/* 0x85c */ char unk85C[0x1c];
	/* 0x878 */ int unk878;
} mpegInternal_t;

/* sceMpeg handle. */
typedef struct mpeg {
	/* 0x00 */ int width;
	/* 0x04 */ int height;
	/* 0x08 */ int frameCount;
	/* 0x0c */ int unk0C[13];
	/* 0x40 */ mpegInternal_t *sys;
} mpeg_t;

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

#endif
