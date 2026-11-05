#include "common.h"
#include "game_section.h"


extern int pendingGameMode __asm__("pendingGameMode");
extern int Level __asm__("Level");
extern int OcclMode __asm__("OcclMode");
void Freeze_SetFreezeOcclusion(int) __asm__("Freeze_SetFreezeOcclusion");
void MODELEVEL_HandleOcclusionExceptions() __asm__("MODELEVEL_HandleOcclusionExceptions");

/* Retail's table spans levels 0xb..0x1d, and level 0xb leaves OcclMode unchanged. */
extern int g_gameType __asm__("g_gameType");
extern int gameMode __asm__("gameMode");
extern int lastGameMode __asm__("lastGameMode");
extern int modeRequestDelayCounter __asm__("modeRequestDelayCounter");
extern int rmc_arg0 __asm__("rmc_arg0");
extern int rmc_arg1 __asm__("rmc_arg1");
extern char *rmc_callback_flag __asm__("rmc_callback_flag");
extern int screenMode __asm__("screenMode");
extern int pendingScreenMode __asm__("pendingScreenMode");
extern int *gNumLocalHeroes __asm__("gNumLocalHeroes");
extern int LevelChunk __asm__("LevelChunk");
extern unsigned char InEndgame __asm__("InEndgame");
extern float SceneScreenFade __asm__("SceneScreenFade");
extern float ScreenFade[2] __asm__("ScreenFade");
extern int gFadeVolumes[6] __asm__("gFadeVolumes");
extern void *pPuzzleMaster __asm__("D_21FC90");
extern int vu1_bufSize __asm__("vu1_bufSize");
typedef struct sceneData {
	/* 0x00 */ char unk00[0x8e];
	/* 0x8e */ short pre_init;
	/* 0x90 */ char unk90[0x100];
} sceneData_t;
typedef struct vcData {
	/* 0x00 */ char unk00[0xb0];
	/* 0xb0 */ float fovRatio;
	/* 0xb4 */ char unkb4[0x100];
} vcData_t;
typedef struct musicData {
	/* 0x00 */ char unk00[4];
	/* 0x04 */ short loading;
	/* 0x06 */ char unk06[0x100];
} musicData_t;
typedef struct memSlotsView {
	/* 0x00 */ char unk00[0xc];
	/* 0x0c */ char *vu1_chain;
	/* 0x10 */ char unk10[0x100];
} memSlotsView_t;
typedef struct wadScene {
	/* 0x000 */ int mobyloadOffset;
	/* 0x004 */ int mobyloadLength;
	/* 0x008 */ char unk08[0x144];
} wadScene_t;
typedef struct wadData {
	/* 0x0000 */ char unk00[0xdabc];
	/* 0xdabc */ int sector;
	/* 0xdac0 */ char unkdac0[0x30];
	/* 0xdaf0 */ wadScene_t scenes[1];
} wadData_t;
extern sceneData_t Scene __asm__("Scene");
extern vcData_t VC __asm__("VC");
extern musicData_t Music __asm__("Music");
extern memSlotsView_t MemSlots __asm__("D_0023AB00");
extern wadData_t g_wad __asm__("D_001C2040");
void WPN_KillAllSoundsForPendingScene(void *) __asm__("WPN_KillAllSoundsForPendingScene");
int MCSTATE_GetState() __asm__("MCSTATE_GetState");
void Mode_PauseUnInit() __asm__("Mode_PauseUnInit");
void mode_freezeUnInit() __asm__("mode_freezeUnInit");
void mode_movieUnInit() __asm__("mode_movieUnInit");
void mode_sceneUnInit() __asm__("mode_sceneUnInit");
void Camera_SetFov(float, float, float, float, int, int, int) __asm__("Camera_SetFov");
void UpdateViewContext() __asm__("UpdateViewContext");
void UnInitModeGadgetPuzzle() __asm__("UnInitModeGadgetPuzzle");
void WPN_UpgradeModeUnInit() __asm__("WPN_UpgradeModeUnInit");
void mode_lobbyUnInit() __asm__("mode_lobbyUnInit");
void mode_creditsUnInit() __asm__("mode_creditsUnInit");
void ResetTieLightingCache() __asm__("ResetTieLightingCache");
void GUI_SetMap(int, int) __asm__("GUI_SetMap");
void RefreshPauseModeCoolDown(int) __asm__("RefreshPauseModeCoolDown");
int GetLastFreezeDialogType() __asm__("GetLastFreezeDialogType");
void Mode_PauseInit(int) __asm__("Mode_PauseInit");
void mode_freezeInit(int, int) __asm__("mode_freezeInit");
void mode_movieInit(int) __asm__("mode_movieInit");
void music_Pause(int) __asm__("music_Pause");
void music_Sync(int) __asm__("music_Sync");
int GetMovieOffset(int) __asm__("GetMovieOffset");
void VU1_setBufSizeByLevel() __asm__("VU1_setBufSizeByLevel");
void LoadAsync(int, char *, int, int, int *, void *, void *) __asm__("LoadAsync");
void Delt(float *, float, float) __asm__("Delt");
void mode_sceneInit(int) __asm__("mode_sceneInit");
void InitModeGadgetPuzzle(void *, int) __asm__("InitModeGadgetPuzzle");
void WPN_UpgradeModeInit(void *) __asm__("WPN_UpgradeModeInit");
void mode_lobbyInit() __asm__("mode_lobbyInit");
void mpMemcardModeInit(int) __asm__("mpMemcardModeInit");
void mode_creditsInit() __asm__("mode_creditsInit");
void FadeToBlack(int, int) __asm__("FadeToBlack");
void mode_doChange() __asm__("mode_doChange");

GAME_SECTION(MODELEVEL_HandleOcclusionExceptions) void MODELEVEL_HandleOcclusionExceptions()
{
	if ((unsigned int)(pendingGameMode - 3) < 2) {
		switch (Level) {
		case 0x12:
		case 0x14:
		case 0x1a:
		case 0x1d:
			OcclMode = 2;
			break;
		case 0xb:
			break;
		}
		Freeze_SetFreezeOcclusion(OcclMode);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mode_level", mode_doChange);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mode_level", func_0047F530);
