#include "common.h"
#include "game_section.h"
#include "game_vu0.h"
#include "mobyutil.h"
#include "gameglobals.h"
#include "wad.h"
#include "sound.h"


struct SoundInstance;
struct SoundGlobals {
	/* 0x000 */ char unk000[0x48];
	/* 0x048 */ int cam_history_pos;
	/* 0x04c */ int unk04c;
	/* 0x050 */ s128 cam_history[4];
	/* 0x090 */ char unk090[0x2c0 - 0x90];
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
extern wadinfo g_wad __asm__("D_001C2040");
extern "C" {
	void snd_PreAllocReverbWorkArea(int, int);
}
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

struct SndMobyClass {
	/* 0x00 */ char unk00[0xd];
	/* 0x0d */ unsigned char sound_cnt;
	/* 0x0e */ char unk0e[0x1a];
	/* 0x28 */ SoundDef *sound_defs;
};
extern unsigned char MobyClassLookup[] __asm__("MobyClassLookup");
extern SndMobyClass *MobyClassPtrs[] __asm__("MobyClassPtrs");
int sound_Play(SoundDef *, unsigned int, moby *, float *, int) __asm__("FUN_004e1c00");
static inline SndMobyClass *sound_GetMobyClass(int oClass)
{
	int idx;
	if (oClass < 0) {
		return 0;
	}
	idx = MobyClassLookup[oClass];
	if (idx == 0xff) {
		return 0;
	}
	return MobyClassPtrs[idx];
}
short sound_MobyPlayOClass(int, unsigned int, moby *, int) __asm__("sound_MobyPlay___dupe2");
short sound_MobyPlayPos(int, unsigned int, moby *, float *, int) __asm__("sound_MobyPlay___dupe3");
extern int Level __asm__("Level");
static inline int IsMultiplayerLevel()
{
	return Level == 0 || Level >= 0x28;
}
static inline int sound_GetMinVolume(SoundDef *sd)
{
	int minVolume = sd->minVolume;
	if (IsMultiplayerLevel()) {
		minVolume = 0;
	}
	return minVolume;
}
int sound_GetFade(SoundDef *, float, float, float, bool) __asm__("sound_GetFade");

extern SoundDef *LevelSounds __asm__("LevelSounds");
extern int CoreSoundCnt __asm__("CoreSoundCnt");
extern int LevelSoundCnt __asm__("LevelSoundCnt");

int sound_SetOffset(short handle, vec4 &offset) __asm__("sound_SetOffset");
extern "C" {
	void snd_SendCache();
	int snd_FlushSoundCommands();
	void snd_StopAllSounds();
}
void sound_StopAllSounds() __asm__("sound_StopAllSounds");
void lineEmitterSetAttrib(lineEmitter *pEmitter, unsigned int attrib, void *value) __asm__("lineEmitterSetAttrib");

/* Camera is only reached here for its position quadword */
struct CameraPosView {
	/* 0x00 */ s128 pos;
};
extern CameraPosView Camera __asm__("Camera");
int sound_GetFade(SoundData *, s128 &, s128 *, bool) __asm__("sound_GetFade___dupe2");

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

GAME_SECTION(sound_GetFade___dupe2) int sound_GetFade(SoundData *channel, s128 &soundPos, s128 *camPos, bool bForceExp)
{
	volatile s128 tmp;
	volatile s128 tmp2;
	float dist;
	if (!camPos) camPos = &Camera.pos;
	{
		register s128 c __asm__("vf3") = *camPos;
		register s128 one __asm__("vf2");
		register s128 d __asm__("vf1");
		VU0_OP("vmaxw.xyzw %0, vf0, vf0w" : "=j"(one));
		d = soundPos;
		VU0_OP("vsub.xyz %0, %0, %1" : "+j"(d) : "j"(c));
		VU0_OP("vmul.xyzw %0, %0, %0" : "+j"(d));
		VU0_ASM("vadday.x ACC, %0, %0y" : : "j"(d));
		VU0_ASM("vmaddz.x %0, %0, %1z" : "+j"(one) : "j"(d));
		VU0_ASM("vsqrt Q, %0x" : : "j"(one));
		tmp = one;
		VU0_ASM("vwaitq");
		VU0_OP("vaddq.x %0, vf0, Q" : "=j"(d));
		tmp2 = d;
		VU0_OP("qmfc2.ni %0, %1" : "=r"(dist) : "j"(d));
	}
	return sound_GetFade(channel->def, dist, channel->def->minRange, channel->def->maxRange, bForceExp);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", sound_GetPan);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", sound_setVolumes);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/sound", sound_Init);

GAME_SECTION(sound_LevelInit) void sound_LevelInit()
{
	snd_PreAllocReverbWorkArea(2, g_wad.level.reverb.type);
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

JUNK_ASM(func_004E19D0,
	"\tdaddu $2, $7, $0\n"
	"\tnop\n");

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

GAME_SECTION(sound_MobyPlay___dupe3) short sound_MobyPlayPos(int sound, unsigned int flags, moby *pMoby, float *pos, int oClass)
{
	SndMobyClass *pClass = MobyClassPtrs[MobyClassLookup[oClass]];
	int channel;
	if (!pClass) {
		return -1;
	}
	if (!pClass->sound_defs || sound >= pClass->sound_cnt) {
		return -1;
	}
	channel = sound_Play((SoundDef *)((char *)pClass->sound_defs + sound * 0x20), flags, 0, pos, 0x400);
	if (channel >= 0) {
		SoundData *ch = (SoundData *)((char *)&Sound + channel * sizeof(SoundData));
		((SoundData *)((char *)ch + 0x2c0))->pMoby = pMoby;
		((SoundData *)((char *)ch + 0x2c0))->def_index = sound;
		((SoundData *)((char *)ch + 0x2c0))->oClass = oClass;
	}
	return sound_CreateHandle(channel);
}

short sound_CorePlay(unsigned int sound, unsigned int flags, moby *pMoby) __asm__("sound_CorePlay");
GAME_SECTION(sound_CorePlay) short sound_CorePlay(unsigned int sound, unsigned int flags, moby *pMoby)
{
	int channel;
	if (sound == 0xffffffff) return -1;
	if (!LevelSounds) return -1;
	if ((int)sound >= CoreSoundCnt) return -1;
	channel = sound_Play(LevelSounds + sound, flags, pMoby, 0, 0x400);
	if (channel >= 0) {
		SoundGlobals *g = (SoundGlobals *)((char *)&Sound + channel * sizeof(SoundData));
		g->channels[0].pMoby = pMoby;
		g->channels[0].def_index = sound;
	}
	return sound_CreateHandle(channel);
}

JUNK_ASM(func_004E2278,
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n");

short sound_FootstepPlay(unsigned int ground_type, unsigned int right_foot, unsigned int magneboots, unsigned int flags, moby *pMoby, int vol_mod) __asm__("sound_FootstepPlay");
GAME_SECTION(sound_FootstepPlay) short sound_FootstepPlay(unsigned int ground_type, unsigned int right_foot, unsigned int magneboots, unsigned int flags, moby *pMoby, int vol_mod)
{
	int channel;
	int sound;
	if (ground_type == 0xffffffff) return -1;
	sound = ground_type * 4 + right_foot * 2 + magneboots + CoreSoundCnt;
	if (sound >= LevelSoundCnt) return -1;
	channel = sound_Play(LevelSounds + sound, flags, pMoby, 0, vol_mod);
	if (channel >= 0) {
		SoundGlobals *g = (SoundGlobals *)((char *)&Sound + channel * sizeof(SoundData));
		g->channels[0].pMoby = pMoby;
		g->channels[0].def_index = sound;
	}
	return sound_CreateHandle(channel);
}

GAME_SECTION(sound_SetOffset) int sound_SetOffset(short handle, vec4 &offset)
{
	SoundData *channel = sound_GetChannelFromHandle(handle);
	if (channel) {
		channel->flags |= 0x40;
		channel->offset = offset;
	}
	return 1;
}

JUNK_ASM(func_004E2388,
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\tsw $3, 0x4($6)\n"
	"\tnop\n"
	"\tnop\n"
	"\tnop\n");

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

JUNK_ASM(func_004E24E0,
	"\tlh $2, 0x0($3)\n"
	"\tnop\n");

GAME_SECTION(lineEmitterSetAttrib) void lineEmitterSetAttrib(lineEmitter *pEmitter, unsigned int attrib, void *value)
{
	switch (attrib) {
	case 3:
		pEmitter->flags = *(unsigned int *)value;
		break;
	case 0:
		*(vec4 *)pEmitter->p0 = *(vec4 *)value;
		break;
	case 1:
		*(vec4 *)pEmitter->p1 = *(vec4 *)value;
		break;
	case 2:
		pEmitter->radius = *(float *)value;
		break;
	case 4:
		pEmitter->sound = *(unsigned int *)value;
		break;
	case 5:
		pEmitter->pOwner = (moby *)value;
		break;
	case 6:
		pEmitter->oclass = *(int *)value;
		break;
	}
}

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

JUNK_ASM(func_004E25D0,
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\tsq $3, 0x30($8)\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n");
