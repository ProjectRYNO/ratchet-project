#include "common.h"
#include "game_section.h"

int lastFreezeDialogType __asm__("D_21ED20") GAME_GP_DATA = 0;
int GetLastFreezeDialogType() __asm__("GetLastFreezeDialogType");

struct FreezeDef {
	/* 0x00 */ char unk00[0x40];
	/* 0x40 */ int mode;
	/* 0x44 */ char unk44[0x10];
	/* 0x54 */ int restorePage;
	/* 0x58 */ int state;
	/* 0x5c */ int unk5c[4];
	/* 0x6c */ int unk6c[4];
	/* 0x7c */ short nodraw;
	/* 0x7e */ short noOverlay;
	/* 0x80 */ int data0;
	/* 0x84 */ short lastUserResponse;
	/* 0x86 */ short unk86;
	/* 0x88 */ int unk88;
	/* 0x8c */ int unk8c[2];
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
	/* 0x00 */ void (*func0)();
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


/* unknown-size declarations: these settings bytes are not small data (split lui/load) */
extern int memcardAutosave[] __asm__("D_171B2C");
extern unsigned char settingsAspect[] __asm__("D_171DF5");
extern "C" void snd_PauseAllSoundsInGroup(int);
int mode_peek() __asm__("mode_peek");
void music_Pause(int) __asm__("music_Pause");
void sound_CorePlay(int, int, int) __asm__("sound_CorePlay");
char *msg_string(int) __asm__("msg_string");
void Dialog_Start(int, char *, void *, int, float, int, int, int) __asm__("FUN_0049e790");
void mode_freezeInit(int, int) __asm__("mode_freezeInit");

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

JUNK_ASM(func_00459960,
	"\tsb $7, -0x4000($28)\n"
	"\tnop\n"
	"\tlw $2, 0x40($3)\n"
	"\tnop\n"
	"\tlw $2, 0x88($3)\n"
	"\tnop\n");

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

GAME_SECTION(mode_freezeInit) void mode_freezeInit(int dialog, int restorePage)
{
	CameraTrainingInterface *pInterface;
	int i;
	float forcedHeight;
	if (dialog == 0) dialog = Freeze.mode;
	lastFreezeDialogType = dialog;
	if (dialog == 5) Freeze.data0 = memcardAutosave[0];
	else Freeze.data0 = 0;
	Freeze.restorePage = restorePage;
	Freeze.noOverlay = dialog == 0xb;
	Freeze.mode = dialog;
	Freeze.nodraw = 0;
	Freeze.state = 0;
	Freeze.unk88 = (mode_peek() == 3 || mode_peek() == 0x10) ? 0 : 1;
	if (gameMode != 3) {
		snd_PauseAllSoundsInGroup(1);
		if (dialog != 0xb) music_Pause(0);
	}
	for (i = 0; i < 4; i++) {
		Freeze.unk5c[i] = 0;
		Freeze.unk6c[i] = 0;
	}
	pInterface = MobyGetInterface(0x2120, 0, 0xc);
	if (pInterface && pInterface->func0) pInterface->func0();
	if (dialog == 9) {
		sound_CorePlay(0x12, 0, 0);
	} else if (dialog == 0x10) {
		Dialog_Start(4, msg_string(Freeze.messageId), (void *)Freeze.messageCallBack, Freeze.messageType, -1.0f, 0, 0, 0);
	} else if (dialog == 2) {
		forcedHeight = 0.35f;
		if (settingsAspect[0] == 4) forcedHeight = 0.4f;
		Dialog_Start(4, msg_string(0x3464), 0, 1, forcedHeight, 0, 0, 0);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/freeze", DrawDialogText);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/freeze", UpdateModeFreeze);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/freeze", Freeze_SphereMap_OrientDown);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/freeze", Freeze_SphereMap_Spin);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/freeze", Freeze_SphereMap_Strafe);

JUNK_ASM(func_0045C578,
	"\tlh $2, 0x84($3)\n"
	"\tnop\n");

GAME_SECTION(Freeze_ClearLastUserResponse) void Freeze_ClearLastUserResponse()
{
	Freeze.lastUserResponse = 0;
}

JUNK_ASM(func_0045C590,
	"\tlw $2, 0x40($3)\n"
	"\tnop\n");

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
