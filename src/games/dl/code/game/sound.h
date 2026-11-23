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

struct SoundGlobals { // 0x1d30
	/* 0x0000 */ int sfxVol;
	/* 0x0004 */ int musicVol;
	/* 0x0008 */ int dialogVol;
	/* 0x000c */ int ambientVol;
	/* 0x0010 */ int shellVol;
	/* 0x0014 */ int mpegVol;
	/* 0x0018 */ int pad32_0[2];
	/* 0x0020 */ int vol_backup[6];
	/* 0x0038 */ int pad32_1[2];
	/* 0x0040 */ unsigned char reverb_type;
	/* 0x0041 */ unsigned char reverb_delay;
	/* 0x0042 */ unsigned char reverb_feedback;
	/* 0x0043 */ unsigned char reverb_changed;
	/* 0x0044 */ MobyInstance *occl_ignore;
	/* 0x0048 */ int cam_history_pos;
	/* 0x004c */ int load_busy;
	/* 0x0050 */ vec4 cam_history[4];
	/* 0x0090 */ unsigned int handles[132];
	/* 0x02a0 */ int cam_ofs_frame;
	/* 0x02a4 */ short kludgeVolState;
	/* 0x02a6 */ short kludgeVolTimer;
	/* 0x02a8 */ SoundInstance *pReverbOwner;
	/* 0x02ac */ int reverb_depth;
	/* 0x02b0 */ int ambientCnt;
	/* 0x02b4 */ SoundInstance *pAmbient;
	/* 0x02c0 */ SoundData channels[52];
	/* 0x1cc0 */ vec4 cam_ofs[6];
	/* 0x1d20 */ unsigned int volFlags;
	/* 0x1d24 */ int pad32_2[3];
};

#endif
