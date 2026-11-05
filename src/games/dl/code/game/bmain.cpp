#include "common.h"
#include "game_section.h"

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
struct MemSlotsDef {
	/* 0x00 */ int unk00[4];
	/* 0x10 */ char *level_base;
	/* 0x14 */ int unk14[0x40];
};
struct BootMemoryMap;
extern MemSlotsDef MemSlots __asm__("D_0023AB10");
BootMemoryMap *bmmRet __asm__("bmmRet") GAME_GP_DATA = 0;
int bmmRetGuard __asm__("bmmRetGuard") GAME_GP_DATA = 0;
BootMemoryMap *GetBootMemoryMap() __asm__("GetBootMemoryMap");

struct MobyInstance;
struct SceneDef {
	/* 0x000 */ char unk000[0x1f0];
	/* 0x1f0 */ MobyInstance *actors[4];
};
extern SceneDef Scene __asm__("Scene");
extern void *pRegistered_PostDraws __asm__("pRegistered_PostDraws");
void RegisterDrawFunction(void *&, void (*)(MobyInstance *), MobyInstance *) __asm__("RegisterDrawFunction");
void Level_PostTransitionFX(MobyInstance *) __asm__("Level_PostTransitionFX");
void Level_TransitionFX(bool) __asm__("Level_TransitionFX");
void *GetBootPlate(int) __asm__("GetBootPlate");


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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/bmain", SetLanguage);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/bmain", func_00437E20);

GAME_SECTION(GetBootMemoryMap) BootMemoryMap *GetBootMemoryMap()
{
	if (bmmRetGuard == 0) {
		bmmRetGuard = 1;
		bmmRet = (BootMemoryMap *)(MemSlots.level_base + 0x900000);
	}
	return bmmRet;
}

GAME_SECTION(GetBootPlate) void *GetBootPlate(int iPlate)
{
	return (char *)GetBootMemoryMap() + iPlate * 0xd0800;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/bmain", func_00437EA8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/bmain", startlevel);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/bmain", UpdateBoot);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/bmain", func_00438C80);

GAME_SECTION(Boot_ResetTimeOutCounter) void Boot_ResetTimeOutCounter()
{
	bootTimeOutCounter = 0;
}
