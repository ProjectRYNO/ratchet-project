#include "common.h"
#include "game_section.h"
#include "globals.h"
struct binblock;
struct UberSound;

typedef struct restartData {
	/* 0x00 */ int flag;
	/* 0x04 */ char unk04[0x100];
} restartData_t;
typedef struct spaceData {
	/* 0x00 */ char unk00[8];
	/* 0x08 */ short restart;
	/* 0x0a */ char unk0a[0x100];
} spaceData_t;
typedef struct soundDataView {
	/* 0x00 */ char unk00[0x43];
	/* 0x43 */ unsigned char reverb_changed;
	/* 0x44 */ char unk44[0x100];
} soundDataView_t;

extern restartData_t restartData __asm__("D_171B2C");
void *mpeg_malloc(unsigned int size, unsigned int align) __asm__("mpeg_malloc");
extern spaceData_t Space __asm__("Space");
extern int g_easyAbort __asm__("g_easyAbort");
void SwitchToLevel(int, int, int) __asm__("SwitchToLevel");
extern void (*SceneEndFunc)(void *) __asm__("SceneEndFunc");
void RestartGame() __asm__("RestartGame");
void *mpeg_a_buff __asm__("D_2206C0") GAME_GP_DATA = 0;
void *mpeg_b_buff __asm__("D_2206C4") GAME_GP_DATA = 0;
void *mpeg_c_buff __asm__("D_2206C8") GAME_GP_DATA = 0;
unsigned int mpeg_a_size __asm__("D_2206CC") GAME_GP_DATA = 0;
unsigned int mpeg_b_size __asm__("D_2206D0") GAME_GP_DATA = 0;
unsigned int mpeg_c_size __asm__("D_2206D4") GAME_GP_DATA = 0;
unsigned int mpeg_a_allocated __asm__("D_2206D8") GAME_GP_DATA = 0;
unsigned int mpeg_b_allocated __asm__("D_2206DC") GAME_GP_DATA = 0;
unsigned int mpeg_c_allocated __asm__("D_2206E0") GAME_GP_DATA = 0;
void FastMemZero(void *, int) __asm__("FastMemZero");
void mpeg_malloc_reset(void *a, unsigned int size_a, void *b, unsigned int size_b, void *c, unsigned int size_c) __asm__("mpeg_malloc_reset");
extern soundDataView_t Sound __asm__("Sound");
extern MovieQueue gMovieQueue __asm__("gMovieQueue");
extern int gFadeVolumes[6] __asm__("gFadeVolumes");
extern int pendingGameMode __asm__("pendingGameMode");
extern void *SceneEndParam __asm__("SceneEndParam");
extern int movie_track __asm__("movie_track");
void FadeToBlack(int, int) __asm__("FadeToBlack");
void FastMemSet(void *, int, int) __asm__("FastMemSet");
void music_StartTrack(int, int, int) __asm__("music_StartTrack");
void music_Unpause() __asm__("music_Unpause");
void VU1_initChain() __asm__("VU1_initChain");
void mode_movieUnInit() __asm__("mode_movieUnInit");


struct musicStartView {
	/* 0x00 */ char unk00[0x1c];
	/* 0x1c */ short track;
	/* 0x1e */ char unk1e[0x100];
};
extern musicStartView musicStart __asm__("musicStart");
extern int g_movie_lsn __asm__("g_movie_lsn");
extern int g_movie_size __asm__("g_movie_size");
extern binblock *g_movie_subtitles __asm__("g_movie_subtitles");
extern int g_movie_language __asm__("g_movie_language");
extern int g_fullscreen __asm__("g_fullscreen");
extern "C" int snd_SetReverbEx(int, int, int, int, int);
extern "C" void FlushCache(int);
void UberSound_Stop(unsigned int) __asm__("Stop___dupe2");
void Help_Kill() __asm__("Help_Kill");
void mode_movieInit(int lsn, int size, binblock *subtitles, int language, bool fullscreen) __asm__("mode_movieInit___dupe2");

GAME_SECTION(mpeg_malloc_reset) void mpeg_malloc_reset(void *a, unsigned int size_a, void *b, unsigned int size_b, void *c, unsigned int size_c)
{
	mpeg_b_buff = b;
	mpeg_b_size = size_b;
	mpeg_c_buff = c;
	mpeg_c_size = size_c;
	mpeg_a_buff = a;
	mpeg_a_size = size_a;
	mpeg_c_allocated = 0;
	mpeg_b_allocated = 0;
	mpeg_a_allocated = 0;
	FastMemZero(a, size_a);
	FastMemZero(mpeg_b_buff, mpeg_b_size);
	FastMemZero(mpeg_c_buff, mpeg_c_size);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/update_core", mpeg_malloc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/update_core", mode_movieInit);

GAME_SECTION(mode_movieInit___dupe2) void mode_movieInit(int lsn, int size, binblock *subtitles, int language, bool fullscreen)
{
	Sound.reverb_changed |= 8;
	snd_SetReverbEx(2, 0, 0, 0, 0);
	FlushCache(0);
	g_movie_lsn = lsn;
	g_movie_size = size;
	g_movie_subtitles = subtitles;
	g_movie_language = language;
	g_fullscreen = fullscreen;
	FadeToBlack(4, 1);
	movie_track = musicStart.track;
	UberSound_Stop(1);
	FastMemSet(gFadeVolumes, 0x400, 0x18);
	Help_Kill();
}

GAME_SECTION(mode_movieUnInit) void mode_movieUnInit()
{
	if (g_easyAbort == 0) g_easyAbort = 1;
	FadeToBlack(4, 0);
	FastMemSet(gFadeVolumes, 0x400, 0x18);
	music_StartTrack(movie_track, 1, 0x400);
	music_Unpause();
	Sound.reverb_changed |= 0x10;
	VU1_initChain();
	if (SceneEndFunc && gMovieQueue.mItemCount == 0 && pendingGameMode != 2 && pendingGameMode != 1) {
		SceneEndFunc(SceneEndParam);
		SceneEndFunc = 0;
		SceneEndParam = 0;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/update_core", UpdateModeMovie);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/update_core", func_004E5548);

GAME_SECTION(RestartGame) void RestartGame()
{
	int one = 1;
	Space.restart = one;
	restartData.flag = one;
	g_easyAbort = one;
	SwitchToLevel(1, 1, -1);
}
