#include "common.h"
#include "game_section.h"

struct TransitionData_Undefined {
	/* 0x00 */ int m_Timer;
};
extern TransitionData_Undefined g_TransitionData_Undefined __asm__("g_TransitionData_Undefined");
void Transition_LoadWad(bool, bool) __asm__("Transition_LoadWad");
void FadeToBlack(int, unsigned int) __asm__("FadeToBlack");
bool TransitionPre_Undefined(unsigned int, unsigned int) __asm__("TransitionPre_Undefined");
struct SpaceDef {
	/* 0x00 */ short unk00;
	/* 0x02 */ short timer;
	/* 0x04 */ short unk04[3];
	/* 0x0a */ short draw_monitors;
	/* 0x0c */ short ship_trans;
	/* 0x0e */ short unk0e[9];
};
extern SpaceDef Space __asm__("Space");
void Transition_UpdateScreenFade(int, int, int, int) __asm__("Transition_UpdateScreenFade");
int FastDecTimer(int &) __asm__("FastDecTimer");
bool TransitionUpdate_Undefined(bool) __asm__("TransitionUpdate_Undefined");
void TransitionDraw_Undefined() __asm__("TransitionDraw_Undefined");
void Transition_SetKeepLastFrame(bool) __asm__("Transition_SetKeepLastFrame");
bool TransitionPre_E3(unsigned int, unsigned int) __asm__("TransitionPre_E3");
struct TransitionData_E3 {
	/* 0x00 */ char unk00[0x4c];
	/* 0x4c */ int m_Timer;
	/* 0x50 */ unsigned char m_bUnloadedSounds;
	/* 0x51 */ char unk51[0xf];
};
extern TransitionData_E3 g_TransitionData_E3 __asm__("g_TransitionData_E3");
void Transition_UnloadSounds() __asm__("Transition_UnloadSounds");
bool TransitionUpdate_E3(bool) __asm__("TransitionUpdate_E3");
extern void *PartUpdate[0x100] __asm__("PartUpdate");
void UpdatePart_097(void *) __asm__("UpdatePart_097");
void UpdatePart_127(void *) __asm__("UpdatePart_127");
void TransitionSpace_ResetParticles() __asm__("TransitionSpace_ResetParticles");

struct MobyInstance {
	/* 0x00 */ char unk00[0x34];
	/* 0x34 */ unsigned short modeBits;
	/* 0x36 */ char unk36[0xa8 - 0x36];
	/* 0xa8 */ void *pUpdate;
	/* 0xac */ char unkac[0xbc - 0xac];
	/* 0xbc */ short oClass;
	/* 0xbe */ char unkbe[0x100 - 0xbe];
};
extern void *pRegistered_MobyDraws __asm__("pRegistered_MobyDraws");
void RegisterDrawFunction(void *&, void (*)(MobyInstance *), MobyInstance *) __asm__("RegisterDrawFunction");
void TransitionSpace_DrawMobyPlanet(MobyInstance *) __asm__("TransitionSpace_DrawMobyPlanet");
void TransitionSpace_UpdateMobySpace(MobyInstance *) __asm__("TransitionSpace_UpdateMobySpace");
void Level_TransitionFX(bool) __asm__("Level_TransitionFX");
void TransitionSpace_DrawMobyShip(MobyInstance *) __asm__("TransitionSpace_DrawMobyShip");
void Transition_ResetParticles() __asm__("Transition_ResetParticles");
void Transition_CleanupMovie() __asm__("Transition_CleanupMovie");
void TransitionPost_Space() __asm__("TransitionPost_Space");
struct TransitionData_ShuttleInterior {
	/* 0x00 */ unsigned char m_bMovieDone;
	/* 0x01 */ unsigned char m_bPlayingFinalAproach;
};
extern TransitionData_ShuttleInterior g_TransitionData_ShuttleInterior __asm__("g_TransitionData_ShuttleInterior");
void Transition_SetupFirstMovie(int) __asm__("Transition_SetupFirstMovie");
void Transition_InitMobys(void (*)(MobyInstance *)) __asm__("Transition_InitMobys");
void Transition_LoadSounds(int, int *) __asm__("Transition_LoadSounds");
bool TransitionPre_ShuttleInterior(unsigned int, unsigned int) __asm__("TransitionPre_ShuttleInterior");
void TransitionShuttleInterior_InitMoby(MobyInstance *) __asm__("TransitionShuttleInterior_InitMoby");
void Transition_DefaultDraw(bool) __asm__("Transition_DefaultDraw");
void UpdateSceneMonitors() __asm__("UpdateSceneMonitors");
void TransitionDraw_ShuttleInterior(bool) __asm__("TransitionDraw_ShuttleInterior");
void TransitionPost_ShuttleInterior() __asm__("TransitionPost_ShuttleInterior");


struct SceneActors {
	/* 0x000 */ char unk000[0x74];
	/* 0x074 */ int iframe;
	/* 0x078 */ int cframe;
	/* 0x07c */ int ichunk;
	/* 0x080 */ short frame_cnt;
	/* 0x082 */ short unk082;
	/* 0x084 */ short actor_cnt;
	/* 0x086 */ char unk086[0x16a];
	/* 0x1f0 */ MobyInstance *actors[16];
	/* 0x230 */ char unk230[0x10];
};
extern SceneActors Scene __asm__("Scene");
extern MobyInstance *MobyInstances __asm__("MobyInstances");
extern MobyInstance *MobyInstancePermEnd __asm__("MobyInstancePermEnd");
extern int g_TransitionSpace_Amb __asm__("g_TransitionSpace_Amb");
void SetMobyLights(MobyInstance *, int, int, int, int) __asm__("SetMobyLights");
void PostUpdateMobyBsphere(MobyInstance *) __asm__("PostUpdateMobyBsphere");
bool Transition_UpdateMovie() __asm__("Transition_UpdateMovie");
void LevelTScene_VoxShuttle_UpdateMonitors() __asm__("LevelTScene_VoxShuttle_UpdateMonitors");
void LevelTScene_VoxShuttle_UpdateFX() __asm__("LevelTScene_VoxShuttle_UpdateFX");
void TransitionSpace_InitMoby(MobyInstance *) __asm__("TransitionSpace_InitMoby");
bool TransitionUpdate_ShuttleInterior(bool) __asm__("TransitionUpdate_ShuttleInterior");

/* ===== AM additions ===== */
int Transition_GetNumMoviesPlayed() __asm__("Transition_GetNumMoviesPlayed");
void Transition_UpdateMidSceneOrMovie() __asm__("Transition_UpdateMidSceneOrMovie");
void TransitionPostUpdate_ShuttleInterior(bool) __asm__("TransitionPostUpdate_ShuttleInterior");
struct TransitionData_Space {
	/* 0x00 */ char unk00[0x10];
	/* 0x10 */ char m_StrPlanetName[64];
	/* 0x50 */ unsigned char m_bMovieDone;
	/* 0x51 */ unsigned char m_bPlayingFinalAproach;
	/* 0x52 */ char unk52[2];
};
extern TransitionData_Space g_TransitionData_Space __asm__("g_TransitionData_Space");
struct SpaceShipClass {
	/* 0x00 */ char unk00[0x24];
	/* 0x24 */ float scale;
};
struct SpaceShip {
	/* 0x00 */ char unk00[0x24];
	/* 0x24 */ SpaceShipClass *pClass;
	/* 0x28 */ char unk28[0x69 - 0x28];
	/* 0x69 */ unsigned char alpha;
	/* 0x6a */ char unk6a[6];
	/* 0x70 */ float scale;
};
bool TransitionUpdate_Space(bool) __asm__("TransitionUpdate_Space");
struct PartInstanceAM {
	/* 0x00 */ unsigned char unk00;
	/* 0x01 */ unsigned char type;
	/* 0x02 */ unsigned char unk02[5];
	/* 0x07 */ unsigned char alpha;
	/* 0x08 */ char unk08[0x38];
};
extern PartInstanceAM *PartInstances __asm__("PartInstances");
extern int PartIndexTop __asm__("PartIndexTop");
extern int TransitionSpace_MovieIds[] __asm__("TransitionSpace_MovieIds");
int Transition_GetMovieId() __asm__("Transition_GetMovieId");
void Transition_SetupNextMovie(int) __asm__("Transition_SetupNextMovie");
void TransitionPostUpdate_Space(bool) __asm__("TransitionPostUpdate_Space");
struct ScrnAM {
	/* 0x00 */ int size_x;
	/* 0x04 */ int size_y;
};
extern ScrnAM Scrn __asm__("Scrn");
extern int g_CurrentFontName __asm__("g_CurrentFontName");
int FontStringLength(const char *, int, float) __asm__("FontStringLength");
void FontPrint(float, float, unsigned long, char *, int, float, float, int, bool, unsigned long, float, float) __asm__("FontPrint");
void FontSet(int) __asm__("FUN_00454350");
void SetupGifPaging(int) __asm__("SetupGifPaging");
void DoGifPaging() __asm__("DoGifPaging");
void VU1_addGSregister(unsigned int, unsigned long, int) __asm__("VU1_addGSregister");
void DrawTextShadow(int, int, int, int, int, int) __asm__("DrawTextShadow");
void TransitionDraw_Space(bool) __asm__("TransitionDraw_Space");

GAME_SECTION(Transition_InitMobys) void Transition_InitMobys(void (*fnInit_)(MobyInstance *))
{
	MobyInstance *pMoby;
	int cActor;
	for (pMoby = MobyInstances; pMoby != MobyInstancePermEnd; pMoby++) {
		fnInit_(pMoby);
	}
	for (cActor = 0; cActor < Scene.actor_cnt; cActor++) {
		if (Scene.actors[cActor]) fnInit_(Scene.actors[cActor]);
	}
}

GAME_SECTION(TransitionPre_Undefined) bool TransitionPre_Undefined(unsigned int Arg1_, unsigned int Arg2_)
{
	Transition_LoadWad(false, false);
	FadeToBlack(6, 0);
	g_TransitionData_Undefined.m_Timer = 300;
	return true;
}

GAME_SECTION(TransitionUpdate_Undefined) bool TransitionUpdate_Undefined(bool bLevelLoadAlmostDone_)
{
	bool done = FastDecTimer(g_TransitionData_Undefined.m_Timer) != 0;
	Transition_UpdateScreenFade(Space.timer, 300, 0xf, 0xf);
	return done;
}

GAME_SECTION(TransitionDraw_Undefined) void TransitionDraw_Undefined()
{
}

GAME_SECTION(TransitionPre_E3) bool TransitionPre_E3(unsigned int Arg1_, unsigned int Arg2_)
{
	Transition_LoadWad(false, false);
	Transition_SetKeepLastFrame(true);
	return true;
}

GAME_SECTION(TransitionUpdate_E3) bool TransitionUpdate_E3(bool bLevelLoadAlmostDone_)
{
	if (!g_TransitionData_E3.m_bUnloadedSounds) {
		Transition_UnloadSounds();
		g_TransitionData_E3.m_bUnloadedSounds = 1;
	}
	return (FastDecTimer(g_TransitionData_E3.m_Timer) & bLevelLoadAlmostDone_) != 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transitionfunc", TransitionDraw_E3);

GAME_SECTION(TransitionSpace_ResetParticles) void TransitionSpace_ResetParticles()
{
	PartUpdate[0x61] = (void *)UpdatePart_097;
	PartUpdate[0x7f] = (void *)UpdatePart_127;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transitionfunc", FUN_004f5890);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transitionfunc", TransitionSpace_InitMoby);

GAME_SECTION(TransitionUpdate_Space) bool TransitionUpdate_Space(bool bLevelLoadAlmostDone_)
{
	bool bDone = false;
	MobyInstance *pMoby;
	float scale;
	SpaceShip *ship;
	for (pMoby = MobyInstances; pMoby < MobyInstancePermEnd; pMoby++) {
		PostUpdateMobyBsphere(pMoby);
	}
	g_TransitionData_Space.m_bMovieDone = Transition_UpdateMovie();
	if (g_TransitionData_Space.m_bMovieDone && bLevelLoadAlmostDone_) {
		bDone = g_TransitionData_Space.m_bPlayingFinalAproach != 0;
	}
	if (g_TransitionData_Space.m_bPlayingFinalAproach && Scene.frame_cnt - 0x50 < Scene.iframe) {
		ship = (SpaceShip *)Scene.actors[0];
		scale = ((float)(Scene.frame_cnt - Scene.iframe - 4) * 0.013157895f) >? 0.0f;
		ship->scale = ship->pClass->scale * scale;
		ship->alpha = 0x80 - (int)(scale * 128.0f);
	}
	return bDone;
}

GAME_SECTION(TransitionPostUpdate_Space) void TransitionPostUpdate_Space(bool bLevelLoadAlmostDone_)
{
	int MovieId;
	SpaceShip *ship;
	int max_alpha;
	PartInstanceAM *pTerm;
	PartInstanceAM *pPart;
	if (g_TransitionData_Space.m_bMovieDone) {
		Transition_CleanupMovie();
		if (Transition_GetNumMoviesPlayed() == 1) {
			Transition_UpdateMidSceneOrMovie();
		}
		if (!g_TransitionData_Space.m_bPlayingFinalAproach) {
			if (Transition_GetNumMoviesPlayed() > 0 && bLevelLoadAlmostDone_) {
				g_TransitionData_Space.m_bPlayingFinalAproach = 1;
				MovieId = TransitionSpace_MovieIds[0];
			} else {
				MovieId = Transition_GetMovieId();
			}
			Transition_SetupNextMovie(MovieId);
			Transition_InitMobys(TransitionSpace_InitMoby);
			Transition_ResetParticles();
			TransitionSpace_ResetParticles();
		}
	}
	if (g_TransitionData_Space.m_bPlayingFinalAproach) {
		Transition_UpdateScreenFade(Scene.iframe, Scene.frame_cnt + 1, 0xf, 0);
	} else {
		Transition_UpdateScreenFade(Scene.iframe, Scene.frame_cnt, 0xf, 0xf);
	}
	if (g_TransitionData_Space.m_bPlayingFinalAproach) {
		ship = (SpaceShip *)Scene.actors[0];
		max_alpha = 0;
		if (ship) {
			max_alpha = 0x80 - ship->alpha;
		}
		pTerm = PartInstances + PartIndexTop + 1;
		for (pPart = PartInstances; pPart < pTerm; pPart++) {
			if (!(pPart->type & 0x80)) {
				pPart->alpha = (pPart->alpha * max_alpha) >> 7;
			}
		}
	}
}

GAME_SECTION(TransitionSpace_UpdateMobySpace) void TransitionSpace_UpdateMobySpace(MobyInstance *pMoby_)
{
	RegisterDrawFunction(pRegistered_MobyDraws, TransitionSpace_DrawMobyPlanet, pMoby_);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transitionfunc", TransitionSpace_DrawMobyPlanet);

GAME_SECTION(TransitionSpace_DrawMobyShip) void TransitionSpace_DrawMobyShip(MobyInstance *pMoby_)
{
	Level_TransitionFX(true);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transitionfunc", TransitionDraw_Space);

GAME_SECTION(TransitionPost_Space) void TransitionPost_Space()
{
	Transition_ResetParticles();
	Transition_CleanupMovie();
	TransitionSpace_ResetParticles();
	Space.ship_trans = 1;
}

GAME_SECTION(TransitionPre_ShuttleInterior) bool TransitionPre_ShuttleInterior(unsigned int Arg1_, unsigned int Arg2_)
{
	g_TransitionData_ShuttleInterior.m_bMovieDone = 0;
	g_TransitionData_ShuttleInterior.m_bPlayingFinalAproach = 0;
	Transition_LoadWad(true, false);
	Transition_SetupFirstMovie(0);
	Transition_InitMobys(TransitionShuttleInterior_InitMoby);
	Transition_LoadSounds(7, 0);
	return true;
}

GAME_SECTION(TransitionShuttleInterior_InitMoby) void TransitionShuttleInterior_InitMoby(MobyInstance *pMoby_)
{
	int bUpdate = 0;
	if (pMoby_->oClass == 0x216a || pMoby_->oClass == 0x2567) {
		pMoby_->pUpdate = 0;
		bUpdate = 1;
	}
	if (bUpdate) {
		pMoby_->modeBits &= 0xfffd;
		return;
	}
	pMoby_->modeBits |= 2;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transitionfunc", TransitionUpdate_ShuttleInterior);

GAME_SECTION(TransitionPostUpdate_ShuttleInterior) void TransitionPostUpdate_ShuttleInterior(bool bLevelLoadAlmostDone_)
{
	if (g_TransitionData_ShuttleInterior.m_bMovieDone) {
		Transition_CleanupMovie();
		if (Transition_GetNumMoviesPlayed() == 1) {
			Transition_UpdateMidSceneOrMovie();
		}
		if (!g_TransitionData_ShuttleInterior.m_bPlayingFinalAproach) {
			g_TransitionData_ShuttleInterior.m_bPlayingFinalAproach = 1;
		}
	}
	Transition_UpdateScreenFade(Scene.iframe, Scene.frame_cnt, 0xf, 0xf);
}

GAME_SECTION(TransitionDraw_ShuttleInterior) void TransitionDraw_ShuttleInterior(bool b)
{
	Space.draw_monitors = 1;
	UpdateSceneMonitors();
	Space.draw_monitors = 0;
	Transition_DefaultDraw(b);
}

GAME_SECTION(TransitionPost_ShuttleInterior) void TransitionPost_ShuttleInterior()
{
	Transition_ResetParticles();
	Transition_CleanupMovie();
}
