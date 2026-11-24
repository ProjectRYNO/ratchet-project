#ifndef GUBER_LOCALHERO_H
#define GUBER_LOCALHERO_H

#include "RemoteHero.h"
#include "PadStream.h"

// dltypes.txt:6275; ghidra-layout.
typedef struct { // 0x28
    /* 0x00 */ float LinearPredictionCutoff;
    /* 0x04 */ float LinearConvergenceThreshold;
    /* 0x08 */ float MaxLinearConvergenceDelta;
    /* 0x0c */ float MinLinearConvergenceDelta;
    /* 0x10 */ float MinSmoothConvergenceDelta;
    /* 0x14 */ float PositionErrorThreshold;
    /* 0x18 */ float MaxTrackSpeed;
    /* 0x1c */ float MaxConvergeSpeed;
    /* 0x20 */ float Accel;
    /* 0x24 */ float Decel;
} tDR_Profile;

struct LocalHero : Hero { // 0x31f0
	/* 0x2fe0 */ int frameSentStick __attribute__((aligned(16)));
	/* 0x2fe4 */ float damageDone;
	/* 0x2fe8 */ short numKills;
	/* 0x2fea */ unsigned char slot;
	/* 0x2fec */ PadStream padStream;
	/* 0x31cc */ unsigned char startGameButtonOffFrames;
	/* 0x31cd */ unsigned char curPadMsgSequenceNum;
	/* 0x31ce */ unsigned char curPadMsgFrame;
	/* 0x31cf */ unsigned char framesUntilStateRot;
	/* 0x31d0 */ unsigned char mapTimer;
	/* 0x31d2 */ short lastMineId;
	/* 0x31d4 */ HeroCommand command;
	/* 0x31e0 */ MobyInstance *pRespawnDest;
};

#endif
