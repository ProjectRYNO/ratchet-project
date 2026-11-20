#include "common.h"
#include "game_section.h"
#include "globals.h"
#include "fs.h"
#include "ubersound.h"
#include "wad.h"
#include "gameglobals.h"
#include "stream.h"


/* missionload: UpdateMissionLoad. Jump table jtbl_003D34E0_text at 0x3d34e0, 0x1c bytes. */
extern MISSIONLOAD g_MissionLoad __asm__("D_1711A8");
extern wadinfo g_wad __asm__("D_001C2040");
extern MEMSLOTS MemSlots __asm__("D_0023AB00");
extern "C" int snd_FlushSoundCommands();
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
extern StreamInterface StreamSys __asm__("StreamSys");
int UnloadModuleByName(const char *name) __asm__("UnloadModuleByName");

GAME_SECTION(UpdateMissionLoad) void UpdateMissionLoad()
{
	snd_FlushSoundCommands();
	Fs::Sync(0);
	if (Fs::IsLoading()) return;
	switch (g_MissionLoad.State) {
	case 1:
		if (g_wad.level.gameplay_mission_data[g_MissionLoad.LoadingMission].offset != 0
			&& g_wad.level.gameplay_mission_data[g_MissionLoad.LoadingMission].length != 0) {
			unsigned int addr = (unsigned int)g_MissionLoad.LoadingMissionClasses + g_wad.level.max_mission_sizes[1].size
				- (g_wad.level.gameplay_mission_data[g_MissionLoad.LoadingMission].length << 11);
			Fs::Sync(1);
			Fs::LoadAsync(0, addr, g_wad.level.gameplay_mission_data[g_MissionLoad.LoadingMission].offset + g_wad.level.sector,
				g_wad.level.gameplay_mission_data[g_MissionLoad.LoadingMission].length, 0, EndLoadData_CB, &g_MissionLoad);
			return;
		}
		EndLoadData_CB(&g_MissionLoad, 0);
		return;
	case 2:
		Fs::LoadAsync(1, g_MissionLoad.LoadingMission, 0, 0, 0, EndLoadSound_CB, &g_MissionLoad);
		g_MissionLoad.State = 4;
		break;
	case 4: {
		int *hdr = (int *)((char *)g_MissionLoad.LoadingMissionClasses + g_wad.level.max_mission_sizes[1].size
			- (g_wad.level.gameplay_mission_data[g_MissionLoad.LoadingMission].length << 11));
		int size = hdr[0];
		if (size != 0) {
			FastDecompress((int)hdr + size - (g_wad.level.gameplay_mission_data[g_MissionLoad.LoadingMission].offset << 11), MemSlots.level_mission_load_buffer);
			g_MissionLoad.InstancesLoaded = 1;
		} else {
			g_MissionLoad.InstancesLoaded = 0;
		}
		g_MissionLoad.State = 5;
		break;
	}
	case 5: {
		char *classes = (char *)g_MissionLoad.LoadingMissionClasses;
		int *hdr = (int *)(classes + g_wad.level.max_mission_sizes[1].size
			- (g_wad.level.gameplay_mission_data[g_MissionLoad.LoadingMission].length << 11));
		int size = hdr[2];
		if (size != 0) {
			FastDecompress((int)hdr + size - (g_wad.level.gameplay_mission_data[g_MissionLoad.LoadingMission].offset << 11), classes);
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

JUNK_ASM(func_004FEC58,
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\tdaddu $2, $0, $0\n"
	"\tnop\n"
	"\tlw $2, 0x0($3)\n"
	"\tnop\n"
	"\tlw $2, 0x4($3)\n"
	"\tnop\n");

GAME_SECTION(IsMissionLoading) unsigned char IsMissionLoading()
{
	return g_MissionLoad.Loading;
}

JUNK_ASM(func_004FEC90,
	"\taddiu $2, $0, 0x1\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x60\n"
	"\tnop\n");

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
	MISSIONLOAD *load = (MISSIONLOAD *)ud;
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
	MISSIONLOAD *load = (MISSIONLOAD *)ud;
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
