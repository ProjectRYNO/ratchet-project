#include "common.h"
#include "game_section.h"

int lastFreezeDialogType __asm__("D_21ED20") GAME_GP_DATA = 0;
int GetLastFreezeDialogType() __asm__("GetLastFreezeDialogType");

struct FreezeDef {
	/* 0x00 */ char unk00[0x84];
	/* 0x84 */ short lastUserResponse;
	/* 0x86 */ char unk86[0xe];
	/* 0x94 */ int occlusion;
	/* 0x98 */ int messageId;
	/* 0x9c */ int messageType;
	/* 0xa0 */ void (*messageCallBack)(void *);
};
extern FreezeDef Freeze __asm__("Freeze");
extern "C" {
	int snd_ContinueAllSoundsInGroup(int);
	int snd_FlushSoundCommands();
}
struct PAD;
void Freeze_ClearLastUserResponse() __asm__("Freeze_ClearLastUserResponse");
void Freeze_SetFreezeOcclusion(int) __asm__("Freeze_SetFreezeOcclusion");
extern int progressiveScan __asm__("progressiveScan");
void VU1_syncChain(int) __asm__("VU1_syncChain");
void SetVideoMode() __asm__("SetVideoMode");
void SetupFS_AA_buffer(int, int, int, int, int, int) __asm__("SetupFS_AA_buffer");
void PostEffects_Init() __asm__("PostEffects_Init");
void UpdateProgressiveScan() __asm__("UpdateProgressiveScan");
struct CameraTrainingInterface {
	/* 0x00 */ int unk00;
	/* 0x04 */ void (*func)();
};
bool IsThisGameModePending(int) __asm__("IsThisGameModePending");
void music_Unpause() __asm__("music_Unpause");
void InitPadRing(PAD *) __asm__("InitPadRing");
CameraTrainingInterface *MobyGetInterface(int, int, int) __asm__("MobyGetInterface___dupe2");
void mode_freezeUnInit() __asm__("mode_freezeUnInit");
extern int gameMode __asm__("gameMode");
extern int pendingGameMode __asm__("pendingGameMode");
void mode_requestChange(int, int, int, int, char *) __asm__("mode_requestChange");
void Freeze_MessageCallback(void *) __asm__("Freeze_MessageCallback");
void Freeze_DisplayMessage(int, int, void (*)(void *)) __asm__("Freeze_DisplayMessage");
void Freeze_KillMessage() __asm__("Freeze_KillMessage");
void GuiSupport_AbortDialog(int) __asm__("GuiSupport_AbortDialog");
void mode_pop(int, int) __asm__("mode_pop");


GAME_SECTION(GetLastFreezeDialogType) int GetLastFreezeDialogType()
{
	return lastFreezeDialogType;
}

GAME_SECTION(UpdateProgressiveScan) void UpdateProgressiveScan()
{
	VU1_syncChain(1);
	SetVideoMode();
	if (progressiveScan != 0) {
		SetupFS_AA_buffer(0x200, 0x1a0, 0x280, 0x1c0, 0, 0);
	} else {
		SetupFS_AA_buffer(0x200, 0x1a0, 0x200, 0x1c0, 0, 0);
	}
	PostEffects_Init();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/freeze", func_00459960);

GAME_SECTION(mode_freezeUnInit) void mode_freezeUnInit()
{
	CameraTrainingInterface *pInterface;
	if (!IsThisGameModePending(3)) {
		snd_ContinueAllSoundsInGroup(1);
		music_Unpause();
		snd_FlushSoundCommands();
	}
	InitPadRing(0);
	pInterface = MobyGetInterface(0x2120, 0, 0xc);
	if (pInterface && pInterface->func) {
		pInterface->func();
	}
}

GAME_SECTION(Freeze_SetFreezeOcclusion) void Freeze_SetFreezeOcclusion(int occlusion)
{
	Freeze.occlusion = occlusion;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/freeze", mode_freezeInit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/freeze", DrawDialogText);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/freeze", UpdateModeFreeze);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/freeze", Freeze_SphereMap_OrientDown);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/freeze", Freeze_SphereMap_Spin);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/freeze", Freeze_SphereMap_Strafe);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/freeze", func_0045C578);

GAME_SECTION(Freeze_ClearLastUserResponse) void Freeze_ClearLastUserResponse()
{
	Freeze.lastUserResponse = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/freeze", func_0045C590);

GAME_SECTION(Freeze_DisplayMessage) void Freeze_DisplayMessage(int messageId, int type, void (*messageCallBack)(void *))
{
	Freeze.messageId = messageId;
	Freeze.messageType = type;
	if (messageCallBack) Freeze.messageCallBack = messageCallBack;
	else Freeze.messageCallBack = Freeze_MessageCallback;
	if (gameMode == 0 && pendingGameMode == -2) {
		mode_requestChange(4, 1, 0x10, 0, 0);
	}
}

GAME_SECTION(Freeze_MessageCallback) void Freeze_MessageCallback(void *pArg)
{
	Freeze_KillMessage();
}

GAME_SECTION(Freeze_KillMessage) void Freeze_KillMessage()
{
	GuiSupport_AbortDialog(4);
	if (gameMode == 4) {
		mode_pop(0, 0);
	}
}
