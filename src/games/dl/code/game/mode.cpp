#include "common.h"
#include "game_section.h"



/* Recovered from the retail boot instructions, using names from the prototype's debug data. */
typedef struct pushedMode {
	/* 0x00 */ int mode;
	/* 0x04 */ int rmc0;
	/* 0x08 */ int rmc1;
} pushedMode_t;
int modeStackIndex __asm__("modeStackIndex") GAME_GP_DATA = 0;
extern pushedMode_t modeStack[8] __asm__("modeStack");
int mode_peek() __asm__("mode_peek");

extern int modePauseModeCoolDown __asm__("D_21F2E0");
void RefreshPauseModeCoolDown(int frames) __asm__("RefreshPauseModeCoolDown");
extern int modeRequestDelayCounter __asm__("modeRequestDelayCounter");
void SetModeChangeRequestDelay(int numberOfFrames) __asm__("SetModeChangeRequestDelay");
extern int pendingGameMode __asm__("pendingGameMode");
extern int gameMode __asm__("gameMode");
bool IsThisGameModePending(int gameMode) __asm__("IsThisGameModePending");

typedef struct hero {
	/* 0x0000 */ char unk00[0x2e20];
	/* 0x2e20 */ float hitPoints;
	/* 0x2e24 */ char unk2e24[0x100];
	/* 0x2f24 */ float maxHP;
} hero_t;
extern int g_gameType __asm__("g_gameType");
extern int g_gameRules __asm__("g_gameRules");
extern int InTheEndOfGameSequence __asm__("InTheEndOfGameSequence");
extern hero_t *g_Hero[10] __asm__("g_Hero");
extern unsigned char gModePauseDisabledFlags[] __asm__("D_3D7D70");
int rmc_arg0 __asm__("rmc_arg0") GAME_GP_DATA = 0;
int rmc_arg1 __asm__("rmc_arg1") GAME_GP_DATA = 0;
char *rmc_callback_flag __asm__("rmc_callback_flag") GAME_GP_DATA = 0;
int MCSTATE_GetState() __asm__("MCSTATE_GetState");
int mode_pop(int arg0, int arg1) __asm__("mode_pop");
int mode_requestChange(int newMode, int switchType, int arg0, int arg1, char *callback_flag) __asm__("mode_requestChange");
inline unsigned char isModePauseDisabled(int mode)
{
	unsigned char flag;
	if (mode >= 0) flag = gModePauseDisabledFlags[mode];
	else flag = 0;
	return flag;
}

GAME_SECTION(RefreshPauseModeCoolDown) void RefreshPauseModeCoolDown(int frames)
{
	modePauseModeCoolDown = frames;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mode", func_0047F540);

GAME_SECTION(SetModeChangeRequestDelay) void SetModeChangeRequestDelay(int numberOfFrames)
{
	modeRequestDelayCounter = numberOfFrames;
}

GAME_SECTION(IsThisGameModePending) bool IsThisGameModePending(int gameMode)
{
	return pendingGameMode == gameMode;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mode", mode_requestChange);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mode", mode_pop);

GAME_SECTION(mode_peek) int mode_peek()
{
	if (modeStackIndex != 0) return modeStack[modeStackIndex - 1].mode;
	return -2;
}
