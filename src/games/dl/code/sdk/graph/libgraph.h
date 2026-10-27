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

#endif
