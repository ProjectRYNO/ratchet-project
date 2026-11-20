#ifndef MOBYANIM_C_H
#define MOBYANIM_C_H

#include "vector.h"

struct MobyAnimInfo;

struct MobySeq { // 0x20
	/* 0x00 */ BSphere bSphere;
	/* 0x10 */ unsigned char frameCnt;
	/* 0x11 */ signed char sound;
	/* 0x12 */ unsigned char trigsCnt;
	/* 0x13 */ unsigned char pad;
	/* 0x14 */ short *trigs;
	/* 0x18 */ MobyAnimInfo *animInfo;
	/* 0x1c */ void *frameData;
};

#endif
