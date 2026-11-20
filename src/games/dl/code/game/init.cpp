#include "common.h"
#include "game_section.h"
#include "fs.h"
#include "ubersound.h"
#include "gameglobals.h"
#include "stream.h"

extern "C" {
	int sceSifStopModule(int, int, const char *, int *);
	int sceSifUnloadModule(int);
	int sceSifSearchModuleByName(const char *);
}

int UnloadModuleByName(const char *name) __asm__("UnloadModuleByName");

int UnloadModule(int id) __asm__("UnloadModule");

/* ubersound */
extern "C" {
	
	void StopAllFs(int) __asm__("StopAll");
	void sound_StopAllSounds() __asm__("sound_StopAllSounds");
	void music_Stop() __asm__("music_Stop");
	void sound_Update() __asm__("FUN_004e0858");
	int snd_FlushSoundCommands();
	void sceGsSyncV(int);
}
extern StreamInterface StreamSys __asm__("StreamSys");
/* missionload */
extern MISSIONLOAD g_MissionLoad __asm__("D_1711A8");
void UpdateMissionLoad() __asm__("UpdateMissionLoad");
unsigned char IsMissionLoading() __asm__("IsMissionLoading");
void AbortMissionLoad() __asm__("AbortMissionLoad");
void EndLoadData_CB(void *ud, int status) __asm__("EndLoadData_CB");
void EndLoadSound_CB(void *ud, int status) __asm__("EndLoadSound_CB");

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
