#ifndef SDK_GRAPH_LIBGRAPH_H
#define SDK_GRAPH_LIBGRAPH_H

/* sceGsGParam: current display mode returned by sceGsGetGParam. 8-byte alignment lets
   GCC fold the interlace/ffmode test in sceGszbufaddr into one 64-bit compare, as retail does. */
typedef struct graphGParam {
	/* 0x00 */ short interlace;
	/* 0x02 */ short omode;
	/* 0x04 */ short ffmode;
	/* 0x06 */ short version;
	/* 0x08 */ int (*vsyncCallback)(int);
	/* 0x0c */ int vsyncHandlerId;
} __attribute__((aligned(8))) graphGParam_t;

/* sceGsDispEnv: privileged display registers written by sceGsPutDispEnv. */
typedef struct graphDispEnv {
	/* 0x00 */ unsigned long pmode;
	/* 0x08 */ unsigned long smode2;
	/* 0x10 */ unsigned long dispfb;
	/* 0x18 */ unsigned long display;
	/* 0x20 */ unsigned long bgcolor;
} graphDispEnv_t;

/* 128-bit quadword (VIF1 FIFO accesses). */
typedef unsigned int graphQword __attribute__((mode(TI)));

/* PRMODECONT register. */
typedef struct graphPrmode {
	/* 0x00 */ unsigned long AC:1;
	unsigned long pad:63;
} graphPrmode_t;

/* COLCLAMP register. */
typedef struct graphClamp {
	/* 0x00 */ unsigned long CLAMP:1;
	unsigned long pad:63;
} graphClamp_t;

/* DTHE register. */
typedef struct graphDthe {
	/* 0x00 */ unsigned long DTHE:1;
	unsigned long pad:63;
} graphDthe_t;

/* sceGsDrawEnv1 packet. */
typedef struct graphDrawEnv1 {
	/* 0x00 */ unsigned long frame1;
	/* 0x08 */ long frame1addr;
	/* 0x10 */ unsigned long zbuf1;
	/* 0x18 */ long zbuf1addr;
	/* 0x20 */ long xyoffset1;
	/* 0x28 */ long xyoffset1addr;
	/* 0x30 */ long scissor1;
	/* 0x38 */ long scissor1addr;
	/* 0x40 */ graphPrmode_t prmodecont;
	/* 0x48 */ long prmodecontaddr;
	/* 0x50 */ graphClamp_t colclamp;
	/* 0x58 */ long colclampaddr;
	/* 0x60 */ graphDthe_t dthe;
	/* 0x68 */ long ditheraddr;
	/* 0x70 */ long test1;
	/* 0x78 */ long test1addr;
} graphDrawEnv1_t;

/* GIF tag as a bitfield view. */
typedef struct graphGifTag {
	/* 0x00 */ unsigned long NLOOP:15;
	unsigned long EOP:1;
	unsigned long pad16:16;
	unsigned long id:14;
	unsigned long PRE:1;
	unsigned long PRIM:11;
	unsigned long FLG:2;
	unsigned long NREG:4;
	/* 0x08 */ unsigned long REGS0:4;
	unsigned long REGS1:4;
	unsigned long REGS2:4;
	unsigned long REGS3:4;
	unsigned long REGS4:4;
	unsigned long REGS5:4;
	unsigned long REGS6:4;
	unsigned long REGS7:4;
	unsigned long REGS8:4;
	unsigned long REGS9:4;
	unsigned long REGS10:4;
	unsigned long REGS11:4;
	unsigned long REGS12:4;
	unsigned long REGS13:4;
	unsigned long REGS14:4;
	unsigned long REGS15:4;
} __attribute__((aligned(16))) graphGifTag_t;

/* sceGsLoadImage packet. */
typedef struct graphLoadImage {
	/* 0x00 */ graphGifTag_t giftag0;
	/* 0x10 */ long bitbltbuf;
	/* 0x18 */ long bitbltbufaddr;
	/* 0x20 */ long trxpos;
	/* 0x28 */ long trxposaddr;
	/* 0x30 */ long trxreg;
	/* 0x38 */ long trxregaddr;
	/* 0x40 */ long trxdir;
	/* 0x48 */ long trxdiraddr;
	/* 0x50 */ graphGifTag_t giftag1;
} graphLoadImage_t;

/* sceGsStoreImage packet as built by sceGsSetDefStoreImage. */
typedef struct graphStoreImage2 {
	/* 0x00 */ unsigned int vifcode[4];
	/* 0x10 */ graphGifTag_t giftag;
	/* 0x20 */ long bitbltbuf;
	/* 0x28 */ long bitbltbufaddr;
	/* 0x30 */ long trxpos;
	/* 0x38 */ long trxposaddr;
	/* 0x40 */ long trxreg;
	/* 0x48 */ long trxregaddr;
	/* 0x50 */ long finish;
	/* 0x58 */ long finishaddr;
	/* 0x60 */ long trxdir;
	/* 0x68 */ long trxdiraddr;
} graphStoreImage2_t;

/* sceGsStoreImage packet. */
typedef struct graphStoreImage {
	/* 0x00 */ unsigned long giftag[2];
	/* 0x10 */ unsigned long giftag2[2];
	/* 0x20 */ unsigned long bitbltbuf;
	/* 0x28 */ unsigned long bitbltbufaddr;
	/* 0x30 */ unsigned long trxpos;
	/* 0x38 */ unsigned long trxposaddr;
	/* 0x40 */ unsigned long trxreg;
	/* 0x48 */ unsigned long trxregaddr;
} graphStoreImage_t;

#endif
