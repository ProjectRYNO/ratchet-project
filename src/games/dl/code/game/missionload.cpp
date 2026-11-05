#include "common.h"
#include "game_section.h"


/* missionload: UpdateMissionLoad. Jump table jtbl_003D34E0_text at 0x3d34e0, 0x1c bytes. */
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
struct WadEntry {
	/* 0x00 */ int offset;
	/* 0x04 */ int length;
};
struct LevelWad {
	/* 0x0000 */ char unk0000[0xcbb4];
	/* 0xcbb4 */ int sector;
	/* 0xcbb8 */ char unkcbb8[0xc];
	/* 0xcbc4 */ int mission_size;
	/* 0xcbc8 */ char unkcbc8[0xd010 - 0xcbc8];
	/* 0xd010 */ WadEntry gameplay_mission_data[64];
};
struct MemSlotsDef {
	/* 0x00 */ char unk00[0x4c];
	/* 0x4c */ void *level_mission_load_buffer;
	/* 0x50 */ char unk50[0x100];
};
extern MissionLoad g_MissionLoad __asm__("D_1711A8");
extern LevelWad g_wad __asm__("D_001C2040");
extern MemSlotsDef MemSlots __asm__("D_0023AB10");
extern "C" int snd_FlushSoundCommands();
struct Fs {
	static void Sync(unsigned int) __asm__("Sync");
	static void Abort() __asm__("Abort");
	static unsigned int IsLoading() __asm__("IsLoading");
	static int LoadAsync(int, unsigned int, unsigned int, unsigned int, unsigned int, void (*)(void *, int), void *) __asm__("LoadAsync");
};
int FastDecompress(int, void *) __asm__("FastDecompress");
void EndLoadData_CB(void *ud, int status) __asm__("EndLoadData_CB");
void EndLoadSound_CB(void *ud, int status) __asm__("EndLoadSound_CB");
void UpdateMissionLoad() __asm__("UpdateMissionLoad");
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
unsigned char IsMissionLoading() __asm__("IsMissionLoading");
/* init */
extern "C" {
	int sceSifStopModule(int, int, const char *, int *);
	int sceSifUnloadModule(int);
	int sceSifSearchModuleByName(const char *);
}
int UnloadModule(int id) __asm__("UnloadModule");
void AbortMissionLoad() __asm__("AbortMissionLoad");


/* ubersound */
struct UberSound {
	static void Stop(unsigned int b_wait) __asm__("Stop___dupe2");
};
extern StreamInterface StreamSys __asm__("StreamSys");
int UnloadModuleByName(const char *name) __asm__("UnloadModuleByName");

GAME_SECTION(UpdateMissionLoad) void UpdateMissionLoad()
{
	snd_FlushSoundCommands();
	Fs::Sync(0);
	if (Fs::IsLoading()) return;
	switch (g_MissionLoad.State) {
	case 1:
		if (g_wad.gameplay_mission_data[g_MissionLoad.LoadingMission].offset != 0
			&& g_wad.gameplay_mission_data[g_MissionLoad.LoadingMission].length != 0) {
			unsigned int addr = (unsigned int)g_MissionLoad.LoadingMissionClasses + g_wad.mission_size
				- (g_wad.gameplay_mission_data[g_MissionLoad.LoadingMission].length << 11);
			Fs::Sync(1);
			Fs::LoadAsync(0, addr, g_wad.gameplay_mission_data[g_MissionLoad.LoadingMission].offset + g_wad.sector,
				g_wad.gameplay_mission_data[g_MissionLoad.LoadingMission].length, 0, EndLoadData_CB, &g_MissionLoad);
			return;
		}
		EndLoadData_CB(&g_MissionLoad, 0);
		return;
	case 2:
		Fs::LoadAsync(1, g_MissionLoad.LoadingMission, 0, 0, 0, EndLoadSound_CB, &g_MissionLoad);
		g_MissionLoad.State = 4;
		break;
	case 4: {
		int *hdr = (int *)((char *)g_MissionLoad.LoadingMissionClasses + g_wad.mission_size
			- (g_wad.gameplay_mission_data[g_MissionLoad.LoadingMission].length << 11));
		int size = hdr[0];
		if (size != 0) {
			FastDecompress((int)hdr + size - (g_wad.gameplay_mission_data[g_MissionLoad.LoadingMission].offset << 11), MemSlots.level_mission_load_buffer);
			g_MissionLoad.InstancesLoaded = 1;
		} else {
			g_MissionLoad.InstancesLoaded = 0;
		}
		g_MissionLoad.State = 5;
		break;
	}
	case 5: {
		char *classes = (char *)g_MissionLoad.LoadingMissionClasses;
		int *hdr = (int *)(classes + g_wad.mission_size
			- (g_wad.gameplay_mission_data[g_MissionLoad.LoadingMission].length << 11));
		int size = hdr[2];
		if (size != 0) {
			FastDecompress((int)hdr + size - (g_wad.gameplay_mission_data[g_MissionLoad.LoadingMission].offset << 11), classes);
			g_MissionLoad.ClassesLoaded = 1;
		} else {
			g_MissionLoad.ClassesLoaded = 0;
		}
		g_MissionLoad.State = 6;
		break;
	}
	case 6:
		if (g_MissionLoad.SoundLoaded) g_MissionLoad.State = 7;
		break;
	case 7:
		if (g_MissionLoad.ErrorCode) g_MissionLoad.Success = 0;
		else g_MissionLoad.Success = 1;
		g_MissionLoad.Loading = 0;
		g_MissionLoad.State = 0;
		break;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/missionload", func_004FEC58);

GAME_SECTION(IsMissionLoading) unsigned char IsMissionLoading()
{
	return g_MissionLoad.Loading;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/missionload", func_004FEC90);

GAME_SECTION(AbortMissionLoad) void AbortMissionLoad()
{
	if (IsMissionLoading()) {
		Fs::Abort();
		g_MissionLoad.ErrorCode = 2;
		g_MissionLoad.State = 7;
		UpdateMissionLoad();
	}
}

GAME_SECTION(EndLoadData_CB) void EndLoadData_CB(void *ud, int status)
{
	MissionLoad *load = (MissionLoad *)ud;
	switch (status) {
	case 0:
		load->State = 2;
		break;
	case 1:
		load->ErrorCode = status;
		load->State = 7;
		break;
	case 2:
		load->ErrorCode = status;
		load->State = 7;
		UpdateMissionLoad();
		break;
	}
}

GAME_SECTION(EndLoadSound_CB) void EndLoadSound_CB(void *ud, int status)
{
	MissionLoad *load = (MissionLoad *)ud;
	switch (status) {
	case 0:
		load->SoundLoaded = true;
		break;
	case 1:
		load->ErrorCode = 1;
		load->SoundLoaded = true;
		break;
	case 2:
		load->ErrorCode = status;
		load->SoundLoaded = true;
		UpdateMissionLoad();
		break;
	}
}
