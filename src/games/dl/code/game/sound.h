#ifndef SOUND_H
#define SOUND_H

#include "vector.h"

struct MobyInstance;
struct SoundInstance;

struct SoundDef { // 0x20
	/* 0x00 */ float minRange;
	/* 0x04 */ float maxRange;
	/* 0x08 */ int minVolume;
	/* 0x0c */ int maxVolume;
	/* 0x10 */ int minPitch;
	/* 0x14 */ int maxPitch;
	/* 0x18 */ unsigned char loop;
	/* 0x19 */ unsigned char flags;
	/* 0x1a */ short index;
	/* 0x1c */ int bank_index;
};

struct SoundData { // 0x80
	/* 0x00 */ unsigned int handle;
	/* 0x04 */ SoundDef *def;
	/* 0x08 */ short index;
	/* 0x0a */ short def_index;
	/* 0x0c */ short volumeMod;
	/* 0x0e */ unsigned short occlpos;
	/* 0x10 */ unsigned char status;
	/* 0x11 */ char loop;
	/* 0x12 */ char priority;
	/* 0x13 */ unsigned char unused0;
	/* 0x14 */ int pitch;
	/* 0x18 */ int pitchMod;
	/* 0x1c */ MobyInstance *pMoby;
	/* 0x20 */ vec4 pos;
	/* 0x30 */ vec4 offset;
	/* 0x40 */ SoundInstance *pAmbient;
	/* 0x44 */ int lineEmitter;
	/* 0x48 */ int oClass;
	/* 0x4c */ float pan;
	/* 0x50 */ int delay;
	/* 0x54 */ int flags;
	/* 0x58 */ unsigned short unique_id;
	/* 0x5a */ unsigned short pad16_0;
	/* 0x5c */ char occl[36];
};

#endif
