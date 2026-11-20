#include "common.h"
#include "game_section.h"
#include "draw.h"
#include "memcard.h"


/* space: DoSpaceTransition */
struct MusicDef {
	/* 0x00 */ char unk00[7];
	/* 0x07 */ char off;
	/* 0x08 */ char unk08[0x100];
};
struct SoundDefs {
	/* 0x00 */ char unk00[0x90];
	/* 0x90 */ void *handles[132];
};
/* GeneralScratchBuffer (0x23ac00) has no symbol yet; it is reached at D_0023AB10 + 0xf0 */
struct ScratchBufferView {
	/* 0x00 */ char unk00[0xf0];
	/* 0xf0 */ char GeneralScratchBuffer[0x100];
};
extern int g_gameType __asm__("g_gameType");
extern int g_newlevelnum __asm__("g_newlevelnum");
extern int Level __asm__("Level");
extern int LevelLoadState __asm__("LevelLoadState");
extern MusicDef Music __asm__("Music");
extern SoundDefs Sound __asm__("Sound");
extern void *LevelSounds __asm__("LevelSounds");
extern ViewContext VC __asm__("VC");
extern memcard_globals g_memcard __asm__("D_171948");
extern ScratchBufferView ScratchBufferBase __asm__("D_0023AB10");
extern unsigned char LevelFogR __asm__("LevelFogR");
extern unsigned char LevelFogG __asm__("LevelFogG");
extern unsigned char LevelFogB __asm__("LevelFogB");
extern float LevelFogNearDist __asm__("LevelFogNearDist");
extern float LevelFogFarDist __asm__("LevelFogFarDist");
extern float LevelFogNearIntensity __asm__("LevelFogNearIntensity");
extern float LevelFogFarIntensity __asm__("LevelFogFarIntensity");
extern "C" {
	int sceGsSyncV(int);
	int snd_SetReverbEx(int, int, int, int, int);
	int snd_SendCache();
	int snd_FlushSoundCommands();
	int snd_UnloadBank(void *);
	int snd_ResolveBankXREFS();
	int snd_StreamSafeCdSync(int);
}
bool Transition_DoTransition() __asm__("Transition_DoTransition");
void FadeToBlack(int, unsigned int) __asm__("FadeToBlack");
void VoiceProcess() __asm__("VoiceProcess");
void nwUpdate() __asm__("nwUpdate");
void sound_StopAllSounds() __asm__("sound_StopAllSounds");
void music_Stop() __asm__("music_Stop");
void SetBackgroundColor(int, int, int) __asm__("SetBackgroundColor");
void wad_GetLevelHeaders(int, char *) __asm__("wad_GetLevelHeaders");
void memcard_Update() __asm__("memcard_Update");
void UpdateMCState() __asm__("UpdateMCState");
int LoadLevelData() __asm__("LoadLevelData");
void DMAC_VIF1_Disable() __asm__("DMAC_VIF1_Disable");
void DoSpaceTransition() __asm__("DoSpaceTransition");


GAME_SECTION(DoSpaceTransition) void DoSpaceTransition()
{
	int i;
	if (!Transition_DoTransition()) {
		if (g_newlevelnum != 0) {
			FadeToBlack(6, 0);
		}
		Level = g_newlevelnum;
		LevelLoadState = 0;
		if (g_gameType == 1) {
			VoiceProcess();
			nwUpdate();
		}
		FlushCache(0);
		snd_SetReverbEx(2, 0, 0, 0, 0);
		snd_SendCache();
		snd_FlushSoundCommands();
		sound_StopAllSounds();
		music_Stop();
		Music.off = 1;
		for (i = 0; i < 0x84; i++) {
			if (Sound.handles[i] != 0) {
				snd_UnloadBank(Sound.handles[i]);
				snd_ResolveBankXREFS();
				LevelSounds = 0;
				Sound.handles[i] = 0;
			}
		}
		VC.fogB = 0x10;
		VC.fogR = 0;
		VC.fogG = 0;
		VC.fogNearDist = 0.0f;
		VC.fogFarDist = 524288.0f;
		VC.fogNearIntensity = 255.0f;
		VC.fogFarIntensity = 128.0f;
		LevelFogR = *(unsigned char *)&VC.fogR;
		LevelFogG = *(unsigned char *)&VC.fogG;
		LevelFogB = *(unsigned char *)&VC.fogB;
		LevelFogNearDist = VC.fogNearDist;
		LevelFogFarDist = VC.fogFarDist;
		LevelFogNearIntensity = VC.fogNearIntensity;
		LevelFogFarIntensity = VC.fogFarIntensity;
		SetBackgroundColor(0, 0, 0);
		wad_GetLevelHeaders(Level, ScratchBufferBase.GeneralScratchBuffer);
		Music.off = 1;
		do {
			FlushCache(0);
			sceGsSyncV(0);
			memcard_Update();
			UpdateMCState();
			if (g_gameType == 1) {
				VoiceProcess();
				nwUpdate();
			}
		} while (LoadLevelData() == 0);
		while (g_memcard.stage != 2 || g_memcard.nextstage >= 0) {
			FlushCache(0);
			sceGsSyncV(0);
			memcard_Update();
			UpdateMCState();
			if (g_gameType == 1) {
				VoiceProcess();
				nwUpdate();
			}
		}
		while (snd_FlushSoundCommands() != 0) {
		}
		snd_ResolveBankXREFS();
		snd_StreamSafeCdSync(0);
		snd_StreamSafeCdSync(0);
		Music.off = 0;
		DMAC_VIF1_Disable();
	}
	if (g_gameType == 1) {
		VoiceProcess();
		nwUpdate();
	}
}
