#include "common.h"
#include "game_section.h"


struct SpaceDef {
	/* 0x00 */ short unk00;
	/* 0x02 */ short timer;
	/* 0x04 */ short unk04[3];
	/* 0x0a */ short draw_monitors;
	/* 0x0c */ short ship_trans;
	/* 0x0e */ short unk0e[3];
	/* 0x14 */ int movie_index;
	/* 0x18 */ int movie_cnt;
	/* 0x1c */ int unk1c;
};
extern SpaceDef Space __asm__("Space");
extern unsigned char g_TransitionMoviePlayed[0x10] __asm__("g_TransitionMoviePlayed");
struct PifHeader;
unsigned long QueuePifLoad(PifHeader *) __asm__("QueuePifLoad");
void Transition_ParseMovie(int) __asm__("Transition_ParseMovie");
void ParseSpaceSceneChunk(int) __asm__("ParseSpaceSceneChunk");
void Transition_UpdateMovieMobys() __asm__("Transition_UpdateMovieMobys");
void Transition_InitPlanetTex(void *, unsigned long &) __asm__("Transition_InitPlanetTex");
void Transition_ResetPlayedMovies() __asm__("Transition_ResetPlayedMovies");
void Transition_SetupFirstMovie(int) __asm__("Transition_SetupFirstMovie");
void Transition_SetupNextMovie(int) __asm__("Transition_SetupNextMovie");


/* Data transition.cpp defines (reached through $gp outside delay slots, or delay-slot only and named
 * g_Transition* in the prototype). */
typedef bool (*fnTransition_Update)();
typedef void (*fnTransition_PostUpdate)(bool);
typedef void (*fnTransition_Draw)(int);
int g_LevelTransitions_LevelTo __asm__("g_LevelTransitions_LevelTo") GAME_GP_DATA = 0;
int g_LevelTransitions_LevelFrom __asm__("g_LevelTransitions_LevelFrom") GAME_GP_DATA = 0;
fnTransition_Update g_fnTransitionUpdate __asm__("D_220938") GAME_GP_DATA = 0;
fnTransition_PostUpdate g_fnTransitionPostUpdate __asm__("D_22093C") GAME_GP_DATA = 0;
fnTransition_Draw g_fnTransitionDraw __asm__("D_220940") GAME_GP_DATA = 0;
unsigned int g_TransitionFlags __asm__("D_220954") GAME_GP_DATA = 0;
int g_TransitionNumMoviesPlayed __asm__("D_22095C") GAME_GP_DATA = 0;
unsigned int g_TransitionNumSounds __asm__("D_220960") GAME_GP_DATA = 0;
float g_TransitionFade __asm__("D_220970") GAME_GP_DATA = 0;
unsigned char g_bTransitionKeepLastFrame __asm__("D_220975") GAME_GP_DATA = 0;
int g_TransitionNumMovieIds __asm__("D_220978") GAME_GP_DATA = 0;
int g_TransitionFinalMovieId __asm__("D_22097C") GAME_GP_DATA = 0;
int g_SpaceScene __asm__("g_SpaceScene") GAME_GP_DATA = 0;
extern int g_gameType __asm__("g_gameType");
extern int g_gameRules __asm__("g_gameRules");
extern int gameMode __asm__("gameMode");
extern int worldUpdateTime __asm__("worldUpdateTime");
extern int active_vu1_mpg __asm__("active_vu1_mpg");
extern int PartIndexNext __asm__("PartIndexNext");
extern int PartIndexTop __asm__("PartIndexTop");
extern int PartActiveCnt __asm__("PartActiveCnt");
extern int JointCacheNumEntries __asm__("JointCacheNumEntries");
extern int g_TransitionSoundIds[16] __asm__("g_TransitionSoundIds");
extern void *g_TransitionSoundBanks[16] __asm__("g_TransitionSoundBanks");
extern int g_TransitionSoundHandles[16] __asm__("g_TransitionSoundHandles");
extern int g_TransitionMovieIds[16] __asm__("g_TransitionMovieIds");
struct MusicGlobals {
	/* 0x00 */ void *trackPos;
	/* 0x04 */ short loading;
	/* 0x06 */ char stop;
	/* 0x07 */ char off;
	/* 0x08 */ char unk08[0xdc];
};
extern MusicGlobals Music __asm__("Music");
struct MobyInstance {
	/* 0x00 */ char unk00[0xac];
	/* 0xac */ void *pVar;
};
struct SceneDef {
	/* 0x000 */ char unk000[0x84];
	/* 0x084 */ short actor_cnt;
	/* 0x086 */ char unk086[0x16a];
	/* 0x1f0 */ MobyInstance *actors[16];
};
extern SceneDef Scene __asm__("Scene");
struct MemSlotsDef {
	/* 0x00 */ char unk00[0x9c];
	/* 0x9c */ char *perm_base;
};
extern MemSlotsDef MemSlots __asm__("D_0023AB10");
struct GsMemDef {
	/* 0x00 */ int unk00[2];
	/* 0x08 */ int zbuf;
};
extern GsMemDef GSmem __asm__("GSmem");
extern "C" {
	int snd_FlushSoundCommands();
	void snd_StartCaching();
	void snd_SendCache();
	void snd_UnloadBank(void *);
	void snd_ResolveBankXREFS();
	void snd_PlaySoundVolPanPMPB_CB(void *, int, int, int, int, int, void (*)(unsigned int, unsigned long), unsigned long);
	void BankLoadFromEE_SpuLoc_CB(unsigned int, unsigned int, unsigned int, void (*)(unsigned int, unsigned long), unsigned long);
	int sceGsSyncV(int);
}
void sound_BasicCB(unsigned int, unsigned long) __asm__("sound_BasicCB");
void VoiceProcess() __asm__("VoiceProcess");
void nwUpdate() __asm__("nwUpdate");
void UpdateParts() __asm__("UpdateParts");
void ComposeCameraMatrix() __asm__("ComposeCameraMatrix");
void ResetGsRegisters() __asm__("ResetGsRegisters");
void AA_BlurPass() __asm__("AA_BlurPass");
void DeleteMoby(MobyInstance *) __asm__("DeleteMoby");
void SetupSkyGifPaging() __asm__("SetupSkyGifPaging");
void SkyLevelGeneric() __asm__("SkyLevelGeneric");
void DoSkyGifPaging() __asm__("DoSkyGifPaging");
void VU1_addGSregister(unsigned int, unsigned long, int) __asm__("VU1_addGSregister");
void mode_movieInit(int) __asm__("mode_movieInit");
void mode_movieUnInit() __asm__("mode_movieUnInit");
void UpdateModeMovie(void *, unsigned int, void *, unsigned int, void *, unsigned int) __asm__("UpdateModeMovie");
int Transition_GetDropshipTexture(int) __asm__("Transition_GetDropshipTexture");
int Transition_GetLandStalkerTexture(int) __asm__("Transition_GetLandStalkerTexture");
int Transition_GetLevelTo() __asm__("Transition_GetLevelTo");
int Transition_GetLevelFrom() __asm__("Transition_GetLevelFrom");
void Transition_LoadSoundBank(void *, int *, int, int) __asm__("Transition_LoadSoundBank");
void Transition_PlaySound_cb(unsigned int, unsigned long) __asm__("Transition_PlaySound_cb");
void Transition_PlaySound(int) __asm__("Transition_PlaySound");
void Transition_UnloadSounds() __asm__("Transition_UnloadSounds");
void Transition_CleanupMovie() __asm__("Transition_CleanupMovie");
void Transition_Draw(int) __asm__("Transition_Draw");
void Transition_PostDraw() __asm__("Transition_PostDraw");
bool Transition_Update(bool) __asm__("Transition_Update");
void Transition_DrawSky() __asm__("Transition_DrawSky");
void Transition_SetupMovieIds(int, int *, int) __asm__("Transition_SetupMovieIds");
int Transition_GetNumMoviesPlayed() __asm__("Transition_GetNumMoviesPlayed");
void Transition_ResetParticles() __asm__("Transition_ResetParticles");
void Transition_SetScreenFade(float) __asm__("Transition_SetScreenFade");
void Transition_UpdateMidSceneOrMovie() __asm__("Transition_UpdateMidSceneOrMovie");
void Transition_DoMovieMpeg() __asm__("Transition_DoMovieMpeg");
void Transition_DoMovieNpc() __asm__("Transition_DoMovieNpc");
void Transition_SetKeepLastFrame(int) __asm__("Transition_SetKeepLastFrame");

GAME_SECTION(Transition_GetDropshipTexture) int Transition_GetDropshipTexture(int level)
{
	int tex = 0;
	int index = level - 1;
	if (g_gameType == 0 && g_gameRules == 1) {
		index = level - 0x15;
	}
	switch (index) {
	case 0:
	case 1:
	case 3:
	case 4:
		tex = 0;
		break;
	case 5:
	case 7:
		tex = 1;
		break;
	case 6:
	case 9:
		tex = 2;
		break;
	case 10:
	case 12:
		tex = 3;
		break;
	case 13:
	case 14:
		tex = 4;
		break;
	}
	return tex;
}

GAME_SECTION(Transition_GetLandStalkerTexture) int Transition_GetLandStalkerTexture(int level)
{
	int index = level - 1;
	if (g_gameType == 0 && g_gameRules == 1) {
		index = level - 0x15;
	}
	switch (index) {
	case 0:
	case 1:
	case 3:
	case 4:
		return 0;
	case 5:
	case 7:
		return 1;
	case 6:
	case 9:
		return 2;
	case 10:
	case 12:
		return 3;
	case 13:
	case 14:
		return 4;
	}
	return 0;
}

GAME_SECTION(Transition_GetLevelTo) int Transition_GetLevelTo()
{
	return g_LevelTransitions_LevelTo;
}

GAME_SECTION(Transition_GetLevelFrom) int Transition_GetLevelFrom()
{
	return g_LevelTransitions_LevelFrom;
}

GAME_SECTION(Transition_LoadSoundBank) void Transition_LoadSoundBank(void *addr, int *handle, int sram_addr, int sram_size)
{
	*handle = -1;
	BankLoadFromEE_SpuLoc_CB((unsigned int)addr, sram_addr, sram_size, sound_BasicCB, (long)handle);
	do {
		FlushCache(0);
		sceGsSyncV(0);
		snd_FlushSoundCommands();
		if (g_gameType == 1) {
			VoiceProcess();
			nwUpdate();
		}
	} while (*handle == -1);
}

GAME_SECTION(Transition_PlaySound_cb) void Transition_PlaySound_cb(unsigned int ret_val_, unsigned long data_)
{
	*(int *)(int)data_ = ret_val_;
}

GAME_SECTION(Transition_PlaySound) void Transition_PlaySound(int SoundId_)
{
	if (SoundId_ >= 0 && SoundId_ < (int)g_TransitionNumSounds) {
		int RemappedId = g_TransitionSoundIds[SoundId_];
		g_TransitionSoundHandles[RemappedId] = -1;
		snd_StartCaching();
		snd_PlaySoundVolPanPMPB_CB(g_TransitionSoundBanks[RemappedId], 0, 0x400, 0, 0, 0, Transition_PlaySound_cb,
			(long)&g_TransitionSoundHandles[RemappedId]);
		snd_SendCache();
		snd_FlushSoundCommands();
	}
}

GAME_SECTION(Transition_UnloadSounds) void Transition_UnloadSounds()
{
	unsigned int i;
	snd_StartCaching();
	for (i = 0; i < g_TransitionNumSounds; i++) {
		snd_UnloadBank(g_TransitionSoundBanks[i]);
	}
	snd_SendCache();
	while (snd_FlushSoundCommands()) {
		if (g_gameType == 1) {
			VoiceProcess();
			nwUpdate();
		}
	}
	snd_ResolveBankXREFS();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_LoadWad);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_LoadSounds);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_LoadPlanetTex);

GAME_SECTION(Transition_InitPlanetTex) void Transition_InitPlanetTex(void *pPlanetTex_, unsigned long &Tex0_)
{
	Tex0_ = QueuePifLoad((PifHeader *)pPlanetTex_);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_ParseMovie);

GAME_SECTION(Transition_CleanupMovie) void Transition_CleanupMovie()
{
	int cActor;
	for (cActor = 0; cActor < Scene.actor_cnt; cActor++) {
		MobyInstance *pMoby = Scene.actors[cActor];
		if (pMoby) {
			pMoby->pVar = 0;
			DeleteMoby(pMoby);
			Scene.actors[cActor] = 0;
		}
	}
}

GAME_SECTION(Transition_Draw) void Transition_Draw(int bLevelLoadAlmostDone_)
{
	ComposeCameraMatrix();
	ResetGsRegisters();
	active_vu1_mpg = -1;
	if (g_fnTransitionDraw) {
		g_fnTransitionDraw(bLevelLoadAlmostDone_);
	}
	Transition_PostDraw();
	AA_BlurPass();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_PostDraw);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_Update);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_DefaultDraw);

GAME_SECTION(Transition_DrawSky) void Transition_DrawSky()
{
	SetupSkyGifPaging();
	SkyLevelGeneric();
	DoSkyGifPaging();
	VU1_addGSregister(0x47, 0x5360b, 0);
	VU1_addGSregister(0x4e, (GSmem.zbuf >> 0xd) | 0x1000000, 0);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_SetupForFrontend);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_Pre);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_Post);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_DoTransition);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_UpdateMovieCamera);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_DrawClankEffects);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_MovieRobotEyeGlow);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_UpdateClankEffects);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_UpdateMovieMobys);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_UpdateMovie);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_SetupMovieIds);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_ResetPlayedMovies);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_GetMovieId);

GAME_SECTION(Transition_SetupFirstMovie) void Transition_SetupFirstMovie(int MovieId_)
{
	Transition_ParseMovie(MovieId_);
	Space.movie_index = MovieId_;
	Space.movie_cnt = 0;
	ParseSpaceSceneChunk(0);
}

GAME_SECTION(Transition_SetupNextMovie) void Transition_SetupNextMovie(int MovieId_)
{
	Transition_ParseMovie(MovieId_);
	Space.movie_index = MovieId_;
	ParseSpaceSceneChunk(0);
	Transition_UpdateMovieMobys();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", func_004F4FF0);

GAME_SECTION(Transition_GetNumMoviesPlayed) int Transition_GetNumMoviesPlayed()
{
	return g_TransitionNumMoviesPlayed;
}

GAME_SECTION(Transition_ResetParticles) void Transition_ResetParticles()
{
	PartIndexNext = 0;
	PartIndexTop = -1;
	PartActiveCnt = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_UpdateScreenFade);

GAME_SECTION(Transition_SetScreenFade) void Transition_SetScreenFade(float Fade_)
{
	g_TransitionFade = Fade_;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_QueueMidSceneOrMovie);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_SetupMidSceneOrMovie);

GAME_SECTION(Transition_UpdateMidSceneOrMovie) void Transition_UpdateMidSceneOrMovie()
{
	if (g_SpaceScene) {
		Music.off = 0;
		if (g_SpaceScene < 0x19) {
			Transition_DoMovieMpeg();
		} else {
			Transition_DoMovieNpc();
		}
		Music.off = 1;
		gameMode = 6;
		g_SpaceScene = 0;
	}
}

GAME_SECTION(Transition_DoMovieMpeg) void Transition_DoMovieMpeg()
{
	mode_movieInit(g_SpaceScene);
	JointCacheNumEntries = 0;
	UpdateModeMovie(0, 0, 0, 0, MemSlots.perm_base - 0x2c0000, 0x2c0000);
	mode_movieUnInit();
}

GAME_SECTION(Transition_DoMovieNpc) void Transition_DoMovieNpc()
{
}

GAME_SECTION(Transition_SetKeepLastFrame) void Transition_SetKeepLastFrame(int bKeep_)
{
	g_bTransitionKeepLastFrame = bKeep_;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_DisplayPassBlur);
