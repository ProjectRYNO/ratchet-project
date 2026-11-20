#include "common.h"
#include "game_section.h"
#include "draw.h"
#include "globals.h"
#include "help.h"

int bootTimeOutCounter __asm__("D_21E1E8") GAME_GP_DATA = 0;
void Boot_ResetTimeOutCounter() __asm__("Boot_ResetTimeOutCounter");
int GetCurrentFrameRate() __asm__("GetCurrentFrameRate");
void InitForCheats() __asm__("InitForCheats");
void LevelTScene_VoxShuttle_UpdateFX() __asm__("LevelTScene_VoxShuttle_UpdateFX");
void LevelTScene_VoxShuttle_UpdateMonitors() __asm__("LevelTScene_VoxShuttle_UpdateMonitors");
void UpdateSceneMonitors() __asm__("UpdateSceneMonitors");
void mode_lobbyInit() __asm__("mode_lobbyInit");
void mode_lobbyUnInit() __asm__("mode_lobbyUnInit");
void _mode_creditsInit() __asm__("_mode_creditsInit");
void mode_creditsInit() __asm__("mode_creditsInit");
void _mode_creditsUnInit() __asm__("_mode_creditsUnInit");
void mode_creditsUnInit() __asm__("mode_creditsUnInit");
struct BootMemoryMap;
extern MEMSLOTS MemSlots __asm__("D_0023AB00");
BootMemoryMap *bmmRet __asm__("bmmRet") GAME_GP_DATA = 0;
int bmmRetGuard __asm__("bmmRetGuard") GAME_GP_DATA = 0;
BootMemoryMap *GetBootMemoryMap() __asm__("GetBootMemoryMap");

struct MobyInstance;
extern SceneDef Scene __asm__("Scene");
extern void *pRegistered_PostDraws __asm__("pRegistered_PostDraws");
void RegisterDrawFunction(void *&, void (*)(MobyInstance *), MobyInstance *) __asm__("RegisterDrawFunction");
void Level_PostTransitionFX(MobyInstance *) __asm__("Level_PostTransitionFX");
void Level_TransitionFX(bool) __asm__("Level_TransitionFX");
void *GetBootPlate(int) __asm__("GetBootPlate");


struct LangOffset {
	/* 0x00 */ int offset;
	/* 0x04 */ int size;
};
struct BootSettingsDef {
	/* 0x00 */ char unk00[0xbd];
	/* 0xbd */ unsigned char Language;
	/* 0xbe */ char unkbe[0x42];
};
extern BootSettingsDef bootSettings __asm__("bootSettings");
extern HelpDef Help __asm__("Help");
extern HelpMsg *HelpMsgs __asm__("HelpMsgs");
LangOffset *helpLangTable __asm__("D_21E1CC") GAME_GP_DATA = 0;
char *helpDecompBuffer __asm__("D_21E1C8") GAME_GP_DATA = 0;
int FastDecompress(char *, char *) __asm__("FastDecompress");
void SetLanguage(unsigned short language) __asm__("SetLanguage");

GAME_SECTION(LevelTScene_VoxShuttle_UpdateMonitors) void LevelTScene_VoxShuttle_UpdateMonitors()
{
}

GAME_SECTION(LevelTScene_VoxShuttle_UpdateFX) void LevelTScene_VoxShuttle_UpdateFX()
{
}

GAME_SECTION(UpdateSceneMonitors) void UpdateSceneMonitors()
{
}

GAME_SECTION(InitForCheats) void InitForCheats()
{
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/bmain", Level_PostTransitionFX);

GAME_SECTION(Level_TransitionFX) void Level_TransitionFX(bool b)
{
	RegisterDrawFunction(pRegistered_PostDraws, Level_PostTransitionFX, Scene.actors[0]);
}

GAME_SECTION(SetLanguage) void SetLanguage(unsigned short language)
{
	char *src = 0;
	int i;
	LangOffset *table = helpLangTable;
	if (!table || !helpDecompBuffer) return;
	bootSettings.Language = language;
	switch (bootSettings.Language) {
	case 0:
	case 1:
		src = (char *)table + table[0].offset;
		break;
	case 2:
		src = (char *)table + table[1].offset;
		break;
	case 3:
		src = (char *)table + table[2].offset;
		break;
	case 4:
		src = (char *)table + table[3].offset;
		break;
	case 5:
		src = (char *)table + table[4].offset;
		break;
	}
	FastDecompress(src, helpDecompBuffer);
	HelpMsgs = (HelpMsg *)helpDecompBuffer;
	Help.num_message = *(unsigned int *)HelpMsgs >> 4;
	for (i = 0; i < Help.num_message; i++) *(int *)&HelpMsgs[i].text += (int)HelpMsgs;
}

GAME_SECTION(GetCurrentFrameRate) int GetCurrentFrameRate()
{
	return 0;
}

GAME_SECTION(mode_creditsInit) void mode_creditsInit()
{
	_mode_creditsInit();
}

GAME_SECTION(mode_creditsUnInit) void mode_creditsUnInit()
{
	_mode_creditsUnInit();
}

GAME_SECTION(mode_lobbyUnInit) void mode_lobbyUnInit()
{
}

GAME_SECTION(mode_lobbyInit) void mode_lobbyInit()
{
}

JUNK_ASM(func_00437E20,
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n");

GAME_SECTION(GetBootMemoryMap) BootMemoryMap *GetBootMemoryMap()
{
	if (bmmRetGuard == 0) {
		bmmRetGuard = 1;
		bmmRet = (BootMemoryMap *)((char *)MemSlots.level_base + 0x900000);
	}
	return bmmRet;
}

GAME_SECTION(GetBootPlate) void *GetBootPlate(int iPlate)
{
	return (char *)GetBootMemoryMap() + iPlate * 0xd0800;
}

JUNK_ASM(func_00437EA8,
	"\tsw $4, -0x4000($28)\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/bmain", startlevel);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/bmain", UpdateBoot);

JUNK_ASM(func_00438C80,
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n");

GAME_SECTION(Boot_ResetTimeOutCounter) void Boot_ResetTimeOutCounter()
{
	bootTimeOutCounter = 0;
}
