#include "common.h"
#include "game_section.h"


/* Music state at D_00203E2D + 0x2b1b; only the volume fields used here are named. */


/* Music state at D_00203E2D + 0x2b1b; only the volume fields used here are named. */
typedef struct musicVolume {
	/* 0x00 */ char unk00[0x24];
	/* 0x24 */ int nextspeech_track;
	/* 0x28 */ void *nextspeech_moby;
	/* 0x2c */ short transition;
	/* 0x2e */ short pad0;
	/* 0x30 */ int transition_length;
	/* 0x34 */ int transition_fade_time;
	/* 0x38 */ int transition_delay;
	/* 0x3c */ short transition_track;
	/* 0x3e */ short transition_transition;
	/* 0x40 */ unsigned char cdTrycount;
	/* 0x41 */ unsigned char cdSpindlctrl;
	/* 0x42 */ unsigned char cdDatapattern;
	/* 0x43 */ unsigned char cdPad;
	/* 0x44 */ unsigned int playHandle;
	/* 0x48 */ short playTrack;
	/* 0x4a */ short playVolume;
	/* 0x4c */ short playFlags;
	/* 0x4e */ short playStatus;
	/* 0x50 */ short vol0;
	/* 0x52 */ short vol0Rate;
	/* 0x54 */ char unk54[0x6c - 0x54];
	/* 0x6c */ unsigned int speechHandle;
	/* 0x70 */ char unk70[6];
	/* 0x76 */ short speechStatus;
	/* 0x78 */ short vol1;
	/* 0x7a */ short vol1Rate;
	/* 0x7c */ char unk7c[0xbc - 0x7c];
	/* 0xbc */ unsigned int transHandle;
	/* 0xc0 */ char unkc0[6];
	/* 0xc6 */ short transStatus;
	/* 0xc8 */ short vol2;
	/* 0xca */ short vol2Rate;
	/* 0xcc */ char unkcc[0x100];
} musicVolume_t;
void Sync(int) __asm__("Sync");
int snd_FlushSoundCommands() __asm__("snd_FlushSoundCommands");
void music_Update() __asm__("music_Update");
int IsLoading() __asm__("IsLoading");
void music_Pause(int immediate) __asm__("music_Pause");
void music_Unpause() __asm__("music_Unpause");
void music_LoadBankCB(unsigned int handle, unsigned long user) __asm__("music_LoadBankCB");
void music_QueueLengthCB(int length, unsigned long user) __asm__("music_QueueLengthCB");
int music_Sync(int wait) __asm__("music_Sync");

extern musicVolume_t musicVolume __asm__("Music");

typedef struct musicTrack {
	/* 0x00 */ int handle;
	/* 0x04 */ char unk04[6];
	/* 0x0a */ short state;
	/* 0x0c */ char unk0c[4];
	/* 0x10 */ short startPending;
	/* 0x12 */ short fade;
	/* 0x14 */ int queuelen;
	/* 0x18 */ int remain;
	/* 0x1c */ char unk1c[0xc];
} musicTrack_t;
typedef struct soundData {
	/* 0x00 */ char unk00[0x90];
	/* 0x90 */ unsigned int handles[8];
	/* 0xb0 */ char unkb0[0x100];
} soundData_t;
typedef struct musicStart {
	/* 0x00 */ short value;
	/* 0x02 */ char unk02[0x100];
} musicStart_t;
extern soundData_t Sound __asm__("Sound");
extern musicStart_t musicStart __asm__("musicStart");
extern int g_stream_handle __asm__("g_stream_handle");
unsigned int snd_BankLoadFromEE(void *) __asm__("snd_BankLoadFromEE");
void music_ResetQueue(void *) __asm__("Reset___dupe3");
extern char musicQueue[] __asm__("musicQueue");
void music_FreshenCB(int handle, unsigned long user) __asm__("music_FreshenCB");
void music_LoadBankFromEE(void *data, int slot) __asm__("music_LoadBankFromEE");
void music_PreseekCB(int result, unsigned long user) __asm__("music_PreseekCB");
void music_StartCB(int handle, unsigned long user) __asm__("music_StartCB");
void music_UnpauseDelay(int time) __asm__("music_UnpauseDelay");
void music_Init() __asm__("music_Init");

extern int g_gameType __asm__("g_gameType");
void music_StartHeadCB(unsigned int, unsigned long) __asm__("music_StartHeadCB");
void music_StartBodyCB(unsigned int, unsigned long) __asm__("music_StartBodyCB");

/* ===== AG additions ===== */
struct WadDef {
	/* 0x0000 */ char unk0000[0xcbb4];
	/* 0xcbb4 */ int sector;
	/* 0xcbb8 */ char unkcbb8[0xcbd0 - 0xcbb8];
	/* 0xcbd0 */ int core_bank_offset;
};
extern WadDef g_wad __asm__("D_001C2040");
int gMusicStopping __asm__("gMusicStopping") GAME_GP_DATA = 0;
void music_PreseekTrack(int, int, int) __asm__("music_PreseekTrack");
void snd_SRAMGetFreeMem() __asm__("snd_SRAMGetFreeMem");
void snd_BankLoadByLoc_CB(int, int, void (*)(unsigned int, unsigned long), unsigned long) __asm__("snd_BankLoadByLoc_CB");
void music_LoadCoreBank() __asm__("music_LoadCoreBank");
void music_PreseekTrackCB(unsigned int, unsigned long) __asm__("music_PreseekTrackCB");
void music_TimeRemainingCB(unsigned int, unsigned long) __asm__("music_TimeRemainingCB");


GAME_SECTION(music_LoadBankCB) void music_LoadBankCB(unsigned int handle, unsigned long user)
{
	unsigned int *p = (unsigned int *)(long)(int)user;
	if (p) *p = handle;
}

GAME_SECTION(music_LoadCoreBank) void music_LoadCoreBank()
{
	snd_SRAMGetFreeMem();
	Sound.handles[3] = 0xffffffff;
	snd_BankLoadByLoc_CB(g_wad.core_bank_offset + g_wad.sector, 0, music_LoadBankCB, (unsigned long)(unsigned int)&Sound.handles[3]);
}

GAME_SECTION(music_LoadBankFromEE) void music_LoadBankFromEE(void *data, int slot)
{
	Sound.handles[slot] = snd_BankLoadFromEE(data);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/music", music_Init);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/music", func_00488F28);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/music", music_PreseekTrack);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/music", music_StartTrack);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/music", music_StartTrackBody);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/music", music_Transition);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/music", music_Stop);

GAME_SECTION(music_Pause) void music_Pause(int immediate)
{
	musicVolume.vol0 = -0x8000;
	musicVolume.vol0Rate = 0;
	musicVolume.vol2 = -0x8000;
	musicVolume.vol2Rate = 0;
}

GAME_SECTION(music_Unpause) void music_Unpause()
{
	musicVolume.vol0 = 4;
	musicVolume.vol2 = 4;
	musicVolume.vol1 = 4;
}

GAME_SECTION(music_UnpauseDelay) void music_UnpauseDelay(int time)
{
	if (musicVolume.vol0 & 0x8000) musicVolume.vol0Rate = time;
	if (musicVolume.vol2 & 0x8000) musicVolume.vol2Rate = time;
	if (musicVolume.vol1 & 0x8000) musicVolume.vol1Rate = time;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/music", music_UpdateStream);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/music", music_Update);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/music", func_00489C20);

GAME_SECTION(music_Sync) int music_Sync(int wait)
{
	Sync(wait);
	while (snd_FlushSoundCommands()) {}
	music_Update();
	while (snd_FlushSoundCommands()) {}
	return IsLoading();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/music", func_00489C88);

GAME_SECTION(music_PreseekCB) void music_PreseekCB(int result, unsigned long user)
{
	musicTrack_t *t = (musicTrack_t *)(long)(int)user;
	if (t && result && t->state == 2) t->state = 3;
}

GAME_SECTION(music_PreseekTrackCB) void music_PreseekTrackCB(unsigned int ret_val, unsigned long p_data)
{
	musicTrack_t *mp = (musicTrack_t *)(int)p_data;
	if (mp) {
		mp->handle = ret_val;
		if (ret_val) {
			if (mp->state == 1) mp->state = 2;
		} else if (!gMusicStopping) {
			music_PreseekTrack(musicVolume.playTrack, musicVolume.playFlags, musicVolume.playVolume);
		} else {
			mp->state = 0;
		}
	}
}

GAME_SECTION(music_StartCB) void music_StartCB(int handle, unsigned long user)
{
	musicTrack_t *t = (musicTrack_t *)(long)(int)user;
	if (t) {
		t->handle = handle;
		if (handle) {
			short state = t->state;
			if (state == 1) {
				t->state = 4;
				if (t->startPending) musicStart.value = state;
			}
		} else {
			t->state = 0;
		}
	}
}

GAME_SECTION(music_StartBodyCB) void music_StartBodyCB(unsigned int ret_val, unsigned long p_data)
{
	musicTrack_t *mp = (musicTrack_t *)(int)p_data;
	if (mp) {
		if ((int)ret_val < 0) mp->handle = ret_val;
		if (ret_val != 0) {
			if (mp->state == 9) {
				mp->state = 4;
				if (mp->startPending) {
					musicStart.value = 1;
					return;
				}
			}
		} else {
			mp->state = 0;
		}
	}
}

GAME_SECTION(music_StartHeadCB) void music_StartHeadCB(unsigned int ret_val, unsigned long p_data)
{
	musicTrack_t *mp = (musicTrack_t *)(int)p_data;
	if (mp) {
		mp->handle = ret_val;
		if (ret_val != 0) {
			if (mp->state == 1) {
				if (g_gameType == 1) {
					mp->state = 4;
					return;
				}
				mp->state = 8;
			}
		} else {
			mp->state = 0;
		}
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/music", music_FreshenCB);

GAME_SECTION(music_QueueLengthCB) void music_QueueLengthCB(int length, unsigned long user)
{
	char *p = (char *)(long)(int)user;
	if (p) *(int *)(p + 0x14) = length;
}

GAME_SECTION(music_TimeRemainingCB) void music_TimeRemainingCB(unsigned int ret_val, unsigned long data)
{
	musicTrack_t *mp = (musicTrack_t *)(int)data;
	if (mp) {
		mp->remain = ret_val;
		if (mp->startPending && musicVolume.transition == 1 && ret_val) {
			musicVolume.transition = 2;
			musicVolume.transition_length = mp->remain;
			musicVolume.transition_fade_time = mp->remain / 4;
		}
	}
}
