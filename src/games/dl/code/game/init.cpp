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


/* init: BootElf */
struct ezNetCtlStatus_t {
	/* 0x00 */ int unk00[12];
	/* 0x30 */ int state;
	/* 0x34 */ int unk34[3];
};
extern int g_gameType __asm__("g_gameType");
extern unsigned char bNetInitialized[] __asm__("D_1723C4");
extern const char sdkModuleName[] __asm__("D_21EF00");
extern "C" {
	int ezNetCtlGetStatus(ezNetCtlStatus_t *, char *, int);
	int ezNetCtlDownInterface();
	int ezNetCtlExit(int);
	int ezNetCnfExit();
	int DelayThread(int);
	int sceGsSyncPath(int, int);
	int sceGsSyncVCallback(void *);
	int DisableIntc(int);
	int scePadPortClose(int, int);
	int sceMtapPortClose(int);
	int scePadEnd();
	int sceMtapEnd();
	int sceMcSync(int, int *, int *);
	int sceMcEnd();
	int sceCdInit(int);
	int sceSifMExitRpc();
	int sceSifExitCmd();
	int LoadExecPS2(const char *, int, char **);
}
void FadeToBlack(int, unsigned int) __asm__("FadeToBlack");
void nwGuiRefreshCallback() __asm__("nwGuiRefreshCallback");
void UndoPowerOff() __asm__("UndoPowerOff");
void BootElf(char *elf, int argc, char **argv) __asm__("BootElf");

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

GAME_SECTION(BootElf) void BootElf(char *elf, int argc, char **argv)
{
	int Delay;
	ezNetCtlStatus_t status;
	char status_message[64];
	int i;

	FadeToBlack(5, 0);
	Fs::Abort();
	UberSound::Stop(1);
	Fs::Abort();
	Fs::Sync(1);
	if (g_gameType == 1 && bNetInitialized[0]) {
		ezNetCtlGetStatus(&status, status_message, 0x40);
		Delay = 5000;
		if (status.state != 5 && status.state != 0) {
			ezNetCtlDownInterface();
		}
		do {
			nwGuiRefreshCallback();
			ezNetCtlGetStatus(&status, status_message, 0x40);
			DelayThread(500);
			if (status.state == 5 || status.state == 0) break;
			Delay--;
		} while (Delay != -1);
		ezNetCtlExit(0);
		ezNetCnfExit();
	}
	sceGsSyncPath(0, 0);
	sceGsSyncVCallback(0);
	DisableIntc(2);
	for (i = 0; i < 8; i++) {
		scePadPortClose(i >= 4, i % 4);
	}
	sceMtapPortClose(0);
	sceMtapPortClose(1);
	scePadEnd();
	sceMtapEnd();
	sceMcSync(0, 0, 0);
	sceMcEnd();
	if (g_gameType == 1) {
		UndoPowerOff();
	}
	sceCdInit(5);
	if (g_gameType == 1) {
		UnloadModuleByName(sdkModuleName);
		sceSifMExitRpc();
	}
	sceSifExitCmd();
	i = 0x78;
	do {
		i--;
		sceGsSyncV(0);
	} while (i > 0);
	LoadExecPS2(elf, argc, argv);
}
