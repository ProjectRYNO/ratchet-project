#include "common.h"
#include "game_section.h"

void Moby2dReset() __asm__("Moby2dReset");
void TransitionPost_MultiPlayer() __asm__("TransitionPost_MultiPlayer");
void Transition_LobbyDrawTitle() __asm__("Transition_LobbyDrawTitle");
void SetupGifPaging(int) __asm__("SetupGifPaging");
void DoGifPaging() __asm__("DoGifPaging");
void Transition_DrawBootLoadTexture() __asm__("Transition_DrawBootLoadTexture");
void TransitionDraw_Lobby() __asm__("TransitionDraw_Lobby");
typedef struct lobbyTransition {
	/* 0x00 */ int state;
	/* 0x04 */ int timer;
	/* 0x08 */ int arg;
	/* 0x0c */ int unk0c;
	/* 0x10 */ int randomValue;
	/* 0x14 */ float scale;
} lobbyTransition_t;
typedef struct gameControllerData {
	/* 0x0000 */ char unk00[0x1390];
	/* 0x1390 */ char mapName[0x20];
	/* 0x13b0 */ char gameName[0x20];
	/* 0x13d0 */ char unk13d0[0x3a0];
	/* 0x1770 */ lobbyTransition_t lobby;
} gameControllerData_t;
extern gameControllerData_t g_GameControllerData __asm__("g_GameControllerData");
int MB_randRangeInt(int min, int max) __asm__("MB_randRangeInt");
void Transition_LoadWad(int, int) __asm__("Transition_LoadWad");
int TransitionPre_Lobby(int arg) __asm__("TransitionPre_Lobby");
float g_xGameName __asm__("g_xGameName") GAME_GP_DATA = 0;
float g_yGameName __asm__("g_yGameName") GAME_GP_DATA = 0;
float g_xMapName __asm__("g_xMapName") GAME_GP_DATA = 0;
float g_yMapName __asm__("g_yMapName") GAME_GP_DATA = 0;
unsigned long g_Map_Color __asm__("g_Map_Color") GAME_GP_DATA = 0;
typedef struct nwInfo {
	/* 0x00 */ int onlyLocalPlayers;
	/* 0x04 */ char unk04[0x100];
} nwInfo_t;
extern nwInfo_t g_nwInfo __asm__("D_1723B8");
void FontPrintScaled(float x, float y, unsigned long color, const char *text, int len, float scale) __asm__("FontPrintScaled");
void TransitionMP_DrawTitleText() __asm__("TransitionMP_DrawTitleText");
void *Moby2dGetPtr(int) __asm__("Moby2dGetPtr");
float FastAddRots(float, float) __asm__("FastAddRots");
void UpdateMobyAnim(void *) __asm__("UpdateMobyAnim");
void AnimEvaluateResolve(void *) __asm__("AnimEvaluateResolve");
void PostUpdateMoby(void *) __asm__("PostUpdateMoby");
void TransitionMP_UpdateMoby() __asm__("TransitionMP_UpdateMoby");
typedef struct scrnData {
	/* 0x00 */ int size_x;
	/* 0x04 */ int size_y;
	/* 0x08 */ char unk08[0x100];
} scrnData_t;
extern scrnData_t Scrn __asm__("Scrn");
float D_220FEC __asm__("D_220FEC") GAME_GP_DATA = 0;
float D_220FF0 __asm__("D_220FF0") GAME_GP_DATA = 0;
float D_220FF4 __asm__("D_220FF4") GAME_GP_DATA = 0;
float D_220FF8 __asm__("D_220FF8") GAME_GP_DATA = 0;
void DrawRectOverlay(int, int, int, int, unsigned long) __asm__("DrawRectOverlay");
void TransitionMP_DrawOverlay() __asm__("TransitionMP_DrawOverlay");


extern int g_NW_GameSettings __asm__("g_NW_GameSettings");
typedef struct localGameOptions {
	/* 0x00 */ char unk00[0x3c];
	/* 0x3c */ unsigned int weapons;
	/* 0x40 */ char unk40[0x100];
} localGameOptions_t;
extern localGameOptions_t g_LocalGameOptions __asm__("g_LocalGameOptions");
int nFluxingAlpha __asm__("D_220F24") GAME_GP_DATA = 0;
int nDir __asm__("D_220F28") GAME_GP_DATA = 0;
float nFontYPosition __asm__("D_220F2C") GAME_GP_DATA = 0;
extern unsigned char SettingsLanguage __asm__("D_171DF5");
extern char *tm_sLoadingString[] __asm__("D_3E57C0");
void FontPrintCenterScaledLarge(int, int, unsigned long, const char *, int, float) __asm__("FontPrintCenterScaledLarge");
int FastDecTimer(int *) __asm__("FastDecTimer");
void Transition_SetScreenFade(float) __asm__("Transition_SetScreenFade");
typedef struct mpTransition {
	/* 0x00 */ char unk00[0x10];
	/* 0x10 */ int m_Timer;
	/* 0x14 */ int m_State;
	/* 0x18 */ char unk18[0x100];
} mpTransition_t;
extern mpTransition_t g_TransitionData_Multiplayer __asm__("g_TransitionData_Multiplayer");
extern lobbyTransition_t g_TransitionData_Lobby __asm__("g_TransitionData_Lobby");
int TransitionUpdate_Multiplayer(int almostDone) __asm__("TransitionUpdate_Multiplayer");
int TransitionUpdate_Lobby(int almostDone) __asm__("TransitionUpdate_Lobby");
int mpIsWeaponEnabled(unsigned int weapon) __asm__("mpIsWeaponEnabled");



char *msg_string(int) __asm__("msg_string");
char *GetMapName(int nLevel) __asm__("GetMapName");

GAME_SECTION(TransitionPre_Lobby) int TransitionPre_Lobby(int arg)
{
	lobbyTransition_t *t = &g_GameControllerData.lobby;
	t->arg = arg;
	t->state = 0;
	t->timer = 0x5a;
	t->scale = 1.0f;
	t->unk0c = 0;
	t->randomValue = MB_randRangeInt(0x1a, 0x23);
	Transition_LoadWad(0, 0);
	return 1;
}

GAME_SECTION(TransitionUpdate_Lobby) int TransitionUpdate_Lobby(int almostDone)
{
	lobbyTransition_t *t = &g_TransitionData_Lobby;
	int done = 0;
	switch (g_TransitionData_Lobby.state) {
	case 0:
		if (FastDecTimer(&t->timer)) {
			g_TransitionData_Lobby.state = 1;
			t->timer = 0x5a;
		} else {
			t->scale = (float)t->timer / 90.0f;
		}
		break;
	case 1:
		if (FastDecTimer(&t->timer)) {
			g_TransitionData_Lobby.state = 2;
			t->timer = 0x1e;
		}
		t->scale = 0.0f;
		break;
	case 2:
		done = 0;
		if (FastDecTimer(&t->timer)) done = almostDone;
		t->scale = 1.0f - (float)g_TransitionData_Multiplayer.m_Timer / 30.0f;
		break;
	}
	Transition_SetScreenFade(0.0f);
	return done;
}

GAME_SECTION(TransitionDraw_Lobby) void TransitionDraw_Lobby()
{
	SetupGifPaging(1);
	Transition_DrawBootLoadTexture();
	Transition_LobbyDrawTitle();
	DoGifPaging();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transitionmulti", Transition_LobbyDrawTitle);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transitionmulti", TransitionPre_Multiplayer);

GAME_SECTION(TransitionPost_MultiPlayer) void TransitionPost_MultiPlayer()
{
	Moby2dReset();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transitionmulti", TransitionMP_SetupCommonRulesText);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transitionmulti", TransitionMP_SetupGameRulesText);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transitionmulti", func_0054C248);

GAME_SECTION(TransitionUpdate_Multiplayer) int TransitionUpdate_Multiplayer(int almostDone)
{
	int done = 0;
	mpTransition_t *t;
	TransitionMP_UpdateMoby();
	t = &g_TransitionData_Multiplayer;
	switch (t->m_State) {
	case 0:
		if (FastDecTimer(&t->m_Timer)) {
			t->m_State = 1;
			t->m_Timer = 0x1e;
		}
		Transition_SetScreenFade(1.0f);
		break;
	case 1:
		if (FastDecTimer(&t->m_Timer)) {
			t->m_State = 2;
			t->m_Timer = 300;
		}
		Transition_SetScreenFade((float)t->m_Timer / 30.0f);
		break;
	case 2:
		if (FastDecTimer(&t->m_Timer)) {
			t->m_State = 3;
			t->m_Timer = 0x1e;
		}
		Transition_SetScreenFade(0.0f);
		break;
	case 3:
		if (almostDone) {
			done = 0;
			if (FastDecTimer(&t->m_Timer)) done = 1;
		}
		Transition_SetScreenFade(1.0f - (float)t->m_Timer / 30.0f);
		break;
	}
	return done;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transitionmulti", func_0054C3B8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transitionmulti", Transition_DrawBootLoadTexture);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transitionmulti", func_0054C8B0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transitionmulti", TransitionDraw_Multiplayer);

GAME_SECTION(TransitionMP_DrawOverlay) void TransitionMP_DrawOverlay()
{
	DrawRectOverlay((int)((float)Scrn.size_y * D_220FF4), (int)((float)Scrn.size_y * D_220FF8), (int)((float)Scrn.size_x * D_220FEC), (int)((float)Scrn.size_x * D_220FF0), 0x64191919);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transitionmulti", TransitionMP_DrawSplashArt);

GAME_SECTION(TransitionMP_DrawTitleText) void TransitionMP_DrawTitleText()
{
	if (!g_nwInfo.onlyLocalPlayers) FontPrintScaled(g_xGameName, g_yGameName, g_Map_Color, g_GameControllerData.gameName, -1, 1.0f);
	FontPrintScaled(g_xMapName, g_yMapName, g_Map_Color, g_GameControllerData.mapName, -1, 1.0f);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transitionmulti", TransitionMP_DrawWeaponsAndVehicleIcons);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transitionmulti", TransitionMP_SetupSpinningMoby);

GAME_SECTION(TransitionMP_UpdateMoby) void TransitionMP_UpdateMoby()
{
	char *moby = (char *)Moby2dGetPtr(0);
	*(float *)(moby + 0xf8) = FastAddRots(*(float *)(moby + 0xf8), 0.024543693f);
	UpdateMobyAnim(moby);
	AnimEvaluateResolve(moby);
	PostUpdateMoby(moby);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transitionmulti", TransitionMP_DrawTextData);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transitionmulti", mpIsWeaponEnabled);

GAME_SECTION(GetMapName) char *GetMapName(int nLevel)
{
	char *name;
	switch (nLevel) {
	case 0x29:
		name = msg_string(0x2eb5);
		break;
	case 0x2a:
		name = msg_string(0x2eb6);
		break;
	case 0x2c:
		name = msg_string(0x2eb7);
		break;
	case 0x2d:
		name = msg_string(0x2eb8);
		break;
	case 0x2e:
		name = msg_string(0x2eb9);
		break;
	case 0x2f:
		name = msg_string(0x2eba);
		break;
	case 0x30:
		name = msg_string(0x2ebb);
		break;
	case 0x32:
		name = msg_string(0x2ebc);
		break;
	case 0x33:
		name = msg_string(0x2ebd);
		break;
	case 0x35:
		name = msg_string(0x2ebe);
		break;
	case 0x36:
		name = msg_string(0x2ebf);
		break;
	default:
		name = msg_string(-1);
		break;
	}
	return name;
}
