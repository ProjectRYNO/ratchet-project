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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_GetDropshipTexture);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_GetLandStalkerTexture);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_GetLevelTo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_GetLevelFrom);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_LoadSoundBank);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_PlaySound_cb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_PlaySound);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_UnloadSounds);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_LoadWad);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_LoadSounds);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_LoadPlanetTex);

GAME_SECTION(Transition_InitPlanetTex) void Transition_InitPlanetTex(void *pPlanetTex_, unsigned long &Tex0_)
{
	Tex0_ = QueuePifLoad((PifHeader *)pPlanetTex_);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_ParseMovie);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_CleanupMovie);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_Draw);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_PostDraw);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_Update);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_DefaultDraw);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_DrawSky);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_GetNumMoviesPlayed);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_ResetParticles);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_UpdateScreenFade);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_SetScreenFade);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_QueueMidSceneOrMovie);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_SetupMidSceneOrMovie);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_UpdateMidSceneOrMovie);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_DoMovieMpeg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_DoMovieNpc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_SetKeepLastFrame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/transition", Transition_DisplayPassBlur);
