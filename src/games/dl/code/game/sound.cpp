#include "common.h"
#include "game_section.h"


struct moby {
	/* 0x00 */ char unk00[0x6e];
	/* 0x6e */ short soundChannel;
	/* 0x70 */ char unk70[0x90];
};
struct SoundInstance;
struct SoundDef;
struct SoundData {
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
	/* 0x1c */ moby *pMoby;
	/* 0x20 */ float pos[4];
	/* 0x30 */ float offset[4];
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
struct SoundGlobals {
	/* 0x000 */ char unk000[0x2c0];
	/* 0x2c0 */ SoundData channels[52];
};
struct lineEmitter {
	/* 0x00 */ unsigned short uniqueId;
	/* 0x02 */ short channels[3];
	/* 0x08 */ float radius;
	/* 0x0c */ unsigned int flags;
	/* 0x10 */ unsigned int sound;
	/* 0x14 */ moby *pOwner;
	/* 0x18 */ int oclass;
	/* 0x1c */ int unk1c;
	/* 0x20 */ float p0[4];
	/* 0x30 */ float p1[4];
	/* 0x40 */ char used;
	/* 0x41 */ unsigned char unused8[3];
	/* 0x44 */ unsigned int unused32[3];
};
extern SoundGlobals Sound __asm__("Sound");
extern lineEmitter gsLineEmitters[12] __asm__("gsLineEmitters");
unsigned short sound_unique_id __asm__("D_21FCC4") GAME_GP_DATA = 0;
struct WadDef {
	/* 0x0000 */ char unk0000[0xcbbc];
	/* 0xcbbc */ int reverb_type;
};
extern WadDef g_wad __asm__("D_001C2040");
extern "C" {
	void snd_PreAllocReverbWorkArea(int, int);
}
struct GadgetCache {
	static void Reset() __asm__("Reset___dupe2");
};
SoundData *sound_GetChannelFromHandle(short) __asm__("sound_GetChannelFromHandle");
short sound_CreateHandle(int) __asm__("sound_CreateHandle");
void sound_LevelInit() __asm__("sound_LevelInit");
int IsMobyPlayingSound(moby *, short) __asm__("IsMobyPlayingSound");
void sound_Kill(int) __asm__("sound_Kill");
void sound_KillByChannel(SoundData *) __asm__("sound_KillByChannel");
void sound_BasicCB(unsigned int, unsigned long) __asm__("sound_BasicCB");
void sound_PlayCB(unsigned int, unsigned long) __asm__("sound_PlayCB");
void sound_FreshenCB(unsigned int, unsigned long) __asm__("sound_FreshenCB");
void sound_initLineEmitters() __asm__("sound_initLineEmitters");

short sound_MobyPlay(unsigned int, unsigned int, moby *) __asm__("sound_MobyPlay");
void SOUND_PLAY_LOOP(int &, moby *, int) __asm__("SOUND_PLAY_LOOP");
void sound_KillById(int, moby *) __asm__("sound_KillById");
void sound_KillByMoby(moby *, int) __asm__("sound_KillByMoby");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", sound_CreateHandle);

GAME_SECTION(SOUND_PLAY_LOOP) void SOUND_PLAY_LOOP(int &handle, moby *pMoby, int sound_id)
{
	SoundData *channel = sound_GetChannelFromHandle(handle);
	if (channel == 0 || (pMoby == channel->pMoby && channel->status == 0)) {
		handle = sound_MobyPlay(sound_id, 4, pMoby);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", sound_CamOfs);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", sound_Occl);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", sound_GetFade);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", sound_GetFade___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", sound_GetPan);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", sound_setVolumes);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", sound_Init);

GAME_SECTION(sound_LevelInit) void sound_LevelInit()
{
	snd_PreAllocReverbWorkArea(2, g_wad.reverb_type);
	GadgetCache::Reset();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", FUN_004e0858);

GAME_SECTION(IsMobyPlayingSound) int IsMobyPlayingSound(moby *pMoby, short handle)
{
	int ret = 0;
	SoundData *channel = sound_GetChannelFromHandle(handle);
	if (channel) {
		if (pMoby == channel->pMoby) ret = channel->status != 0;
	}
	return ret;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", func_004E19D0);

GAME_SECTION(sound_KillById) void sound_KillById(int sound_id, moby *pMoby)
{
	int i;
	SoundData *channel = Sound.channels;
	for (i = 0x33; i >= 0; i--) {
		if ((pMoby == 0 || pMoby == channel->pMoby) && sound_id == channel->def_index) {
			sound_KillByChannel(channel);
		}
		channel++;
	}
}

GAME_SECTION(sound_KillByMoby) void sound_KillByMoby(moby *pMoby, int bLoopingSoundsOnly)
{
	int i;
	SoundData *channel;
	if (pMoby) {
		channel = Sound.channels;
		for (i = 0x33; i >= 0; i--) {
			if (pMoby == channel->pMoby && (bLoopingSoundsOnly == 0 || (channel->flags & 4))) {
				sound_KillByChannel(channel);
			}
			channel++;
		}
		pMoby->soundChannel = -1;
	}
}

GAME_SECTION(sound_Kill) void sound_Kill(int handle)
{
	SoundData *channel = sound_GetChannelFromHandle(handle);
	if (channel) sound_KillByChannel(channel);
}

GAME_SECTION(sound_KillByChannel) void sound_KillByChannel(SoundData *channel)
{
	unsigned char status = channel->status;
	if (status == 7) {
		channel->pMoby = 0;
		channel->pAmbient = 0;
		channel->status = 0;
		return;
	}
	if (status != 0 && status != 6) channel->status = 4;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", sound_GetFreeChannel);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", FUN_004e1c00);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", sound_MobyPlay);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", sound_MobyPlay___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", sound_MobyPlay___dupe3);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", sound_CorePlay);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", func_004E2278);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", sound_FootstepPlay);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", sound_SetOffset);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", func_004E2388);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", sound_StopAllSounds);

GAME_SECTION(sound_BasicCB) void sound_BasicCB(unsigned int ret_val, unsigned long data)
{
	unsigned int *handle = (unsigned int *)(int)data;
	if (handle) *handle = ret_val;
}

GAME_SECTION(sound_PlayCB) void sound_PlayCB(unsigned int ret_val, unsigned long data)
{
	SoundData *channel = (SoundData *)(int)data;
	if (channel) {
		channel->handle = ret_val;
		if (ret_val != 0) {
			if (channel->status == 1) {
				channel->status = 2;
				return;
			}
		} else {
			channel->pMoby = 0;
			channel->pAmbient = 0;
			channel->status = 0;
		}
	}
}

GAME_SECTION(sound_FreshenCB) void sound_FreshenCB(unsigned int ret_val, unsigned long data)
{
	SoundData *channel = (SoundData *)(int)data;
	if (channel && channel->unused0 == channel->pad16_0) {
		channel->handle = ret_val;
		if (ret_val == 0) {
			channel->pMoby = 0;
			channel->pAmbient = 0;
			channel->status = 0;
		}
		channel->unused0 = 0;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", func_004E24E0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", lineEmitterSetAttrib);

GAME_SECTION(sound_initLineEmitters) void sound_initLineEmitters()
{
	int i;
	for (i = 0; i < 12; i++) {
		gsLineEmitters[i].used = 0;
		gsLineEmitters[i].channels[0] = -1;
		gsLineEmitters[i].channels[1] = -1;
		gsLineEmitters[i].channels[2] = -1;
		gsLineEmitters[i].flags = 0;
		gsLineEmitters[i].radius = 0.0f;
		gsLineEmitters[i].uniqueId = 0xffff;
		gsLineEmitters[i].sound = 0xffffffff;
		gsLineEmitters[i].pOwner = 0;
		gsLineEmitters[i].oclass = -1;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", func_004E25D0);
