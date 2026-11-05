#include "common.h"
#include "game_section.h"

extern "C" {
	int sceSifStopModule(int, int, const char *, int *);
	int sceSifUnloadModule(int);
	int sceSifSearchModuleByName(const char *);
}

int UnloadModuleByName(const char *name) __asm__("UnloadModuleByName");

int UnloadModule(int id) __asm__("UnloadModule");

/* ubersound */
struct UberSound {
	static void Stop(unsigned int b_wait) __asm__("Stop___dupe2");
};
extern "C" {
	
	void StopAllFs(int) __asm__("StopAll");
	void sound_StopAllSounds() __asm__("sound_StopAllSounds");
	void music_Stop() __asm__("music_Stop");
	void sound_Update() __asm__("FUN_004e0858");
	int snd_FlushSoundCommands();
	void sceGsSyncV(int);
}
struct StreamInterface {
	/* 0x00 */ char unk00[0x100];
	void StopAll(unsigned int, int, void (*)(void *), void *) __asm__("StopAll___dupe2");
};
extern StreamInterface StreamSys __asm__("StreamSys");
/* missionload */
struct MissionLoad {
	/* 0x00 */ int ActiveMission;
	/* 0x04 */ int LoadingMission;
	/* 0x08 */ int ErrorCode;
	/* 0x0c */ int QueuedMission;
	/* 0x10 */ unsigned char Success;
	/* 0x11 */ unsigned char ResetLevel;
	/* 0x12 */ unsigned char Loading;
	/* 0x13 */ unsigned char Parse;
	/* 0x14 */ unsigned char Switch;
	/* 0x15 */ unsigned char DoubleBuffer;
	/* 0x16 */ unsigned char QueuedLoad;
	/* 0x17 */ unsigned char InstancesActive;
	/* 0x18 */ unsigned char ClassesActive;
	/* 0x19 */ unsigned char InstancesLoaded;
	/* 0x1a */ unsigned char ClassesLoaded;
	/* 0x1b */ unsigned char SoundLoaded;
	/* 0x1c */ void *ActiveMissionClasses;
	/* 0x20 */ void *LoadingMissionClasses;
	/* 0x24 */ int State;
};
extern MissionLoad g_MissionLoad __asm__("D_1711A8");
void UpdateMissionLoad() __asm__("UpdateMissionLoad");
unsigned char IsMissionLoading() __asm__("IsMissionLoading");
void AbortMissionLoad() __asm__("AbortMissionLoad");
void EndLoadData_CB(void *ud, int status) __asm__("EndLoadData_CB");
void EndLoadSound_CB(void *ud, int status) __asm__("EndLoadSound_CB");
struct Fs { static void Abort() __asm__("Abort"); };

GAME_SECTION(UnloadModule) int UnloadModule(int id)
{
	int result;
	int ret = -1;
	if (id >= 0) {
		ret = sceSifStopModule(id, 0, 0, &result);
		if (ret < 0) return ret;
		ret = sceSifUnloadModule(id);
		if (ret >= 0) ret = 0;
	}
	return ret;
}

GAME_SECTION(UnloadModuleByName) int UnloadModuleByName(const char *name)
{
	int id = sceSifSearchModuleByName(name);
	if (id >= 0) return UnloadModule(id);
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/init", BootElf);
