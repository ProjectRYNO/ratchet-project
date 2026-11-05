#include "common.h"
#include "game_section.h"


extern unsigned char mSaveErrorSpaceTransition __asm__("mSaveErrorSpaceTransition");
void Global_ClearSaveErrorInSpaceTransition() __asm__("Global_ClearSaveErrorInSpaceTransition");
void HandleSpecialSwitchLevelCases(int &) __asm__("HandleSpecialSwitchLevelCases");
struct ProgressFlags {
	/* 0x00 */ unsigned char completed;
	/* 0x01 */ unsigned char unk01[15];
};
extern ProgressFlags GameProgress __asm__("D_171B66");
int GetGameCompleted() __asm__("GetGameCompleted");
int IsGameInChallengeMode() __asm__("IsGameInChallengeMode");

struct MovieEntry {
	/* 0x00 */ int id;
	/* 0x04 */ int type;
};
struct MovieQueue {
	/* 0x00 */ int active;
	/* 0x04 */ int unk04;
	/* 0x08 */ MovieEntry entries[10];
	/* 0x58 */ int head;
	/* 0x5c */ int tail;
	/* 0x60 */ int count;
	/* 0x64 */ unsigned char unk64;
	/* 0x68 */ int mode;
	/* 0x6c */ unsigned char playing;
};
void Flush(MovieQueue *) __asm__("Flush");
void Construct(MovieQueue *) __asm__("Construct");
void Abort(MovieQueue *) __asm__("Abort___dupe2");
void TagMoviesAsPlayed(MovieQueue *) __asm__("TagMoviesAsPlayed");
struct ThreadParam {
	/* 0x00 */ int unk00[6];
	/* 0x18 */ int currentPriority;
	/* 0x1c */ int unk1c[5];
};
int GetThreadId() __asm__("GetThreadId");
int ReferThreadStatus(int, ThreadParam *) __asm__("ReferThreadStatus");
int GetCurrentThreadPriority() __asm__("GetCurrentThreadPriority");
extern "C" void *memset(void *, int, unsigned int);
int QueueMovie(MovieQueue *, int) __asm__("QueueMovie");
extern unsigned int MoviesPlayedRecord[] __asm__("MoviesPlayedRecord");
int DeQueueMovie(MovieQueue *, int &, int &) __asm__("DeQueueMovie");
struct EnemySkinDef {
	/* 0x00 */ int skin;
	/* 0x04 */ int oClass;
};
extern int Level __asm__("Level");
extern EnemySkinDef TBL_EnemySkinDefTable[] __asm__("TBL_EnemySkinDefTable");
int GetMobySkinBase(int) __asm__("GetMobySkinBase");
extern int gameMode __asm__("gameMode");
int mode_requestChange(int, int, int, int, char *) __asm__("mode_requestChange");
int PlayNextQueuedMovie(MovieQueue *) __asm__("PlayNextQueuedMovie");
int g_newlevel __asm__("g_newlevel") GAME_GP_DATA = 0;
int SwitchingLevels() __asm__("SwitchingLevels");
struct McState {
	/* 0x000 */ char unk000[0x18];
	/* 0x018 */ short command;
	/* 0x01a */ char unk01a[0x1e4 - 0x1a];
	/* 0x1e4 */ int pending;
};
int g_gameType __asm__("g_gameType") GAME_GP_DATA = 0;
extern int g_newlevelnum __asm__("g_newlevelnum");
extern int g_newmissionindex __asm__("g_newmissionindex");
extern int PreviousLevel __asm__("D_21DA78");
extern McState mcState __asm__("D_171948");
void AbortMissionLoad() __asm__("AbortMissionLoad");
void MCSTATE_ClearCommand(int) __asm__("MCSTATE_ClearCommand");
void memcard_Save(int, int) __asm__("memcard_Save");
void SwitchToLevel(int, int, int) __asm__("SwitchToLevel");
struct BootArgList {
	/* 0x00 */ char *options;
	/* 0x04 */ const char *name;
};
int RebootArgsInit __asm__("D_2212A8") GAME_GP_DATA = 0;
BootArgList RebootArgs __asm__("D_2212A0") GAME_GP_DATA = {0, 0};
extern const char RebootOptionName[] __asm__("D_21EEB8");
struct RebootOptions {
	/* 0x00 */ int head;
	/* 0x04 */ unsigned short tail;
	/* 0x06 */ char rest[0x1a];
};
extern const RebootOptions DefaultRebootOptions __asm__("D_21EEC0");
extern const char BOOTELF_NAME[] __asm__("BOOTELF_NAME");
void GetBootOptionsFromSettings(char *) __asm__("GetBootOptionsFromSettings");
void BootElf(const char *, int, BootArgList *) __asm__("BootElf");
void RebootToFrontEnd() __asm__("RebootToFrontEnd");

struct LobbySettings {
	/* 0x000 */ int values[9][8];
	/* 0x120 */ unsigned char a[8];
	/* 0x128 */ unsigned char b[8];
	/* 0x130 */ int ids[4];
};
struct BootSettings {
	/* 0x00 */ char unk00[0x18];
	/* 0x18 */ int v0;
	/* 0x1c */ char unk1c[0xc];
	/* 0x28 */ int v1;
	/* 0x2c */ char unk2c[0xc];
	/* 0x38 */ int v2;
	/* 0x3c */ char unk3c[0xc];
	/* 0x48 */ int v3;
	/* 0x4c */ char unk4c[0xc];
	/* 0x58 */ int v4;
	/* 0x5c */ char unk5c[0xc];
	/* 0x68 */ int v5;
	/* 0x6c */ char unk6c[0xc];
	/* 0x78 */ int v6;
	/* 0x7c */ char unk7c[0xc];
	/* 0x88 */ int v7;
	/* 0x8c */ char unk8c[0xc];
	/* 0x98 */ int v8;
	/* 0x9c */ char unk9c[0xc];
	/* 0xa8 */ unsigned char a;
	/* 0xa9 */ char unka9[0xb];
	/* 0xb4 */ unsigned char b;
};
extern LobbySettings LobbyControllerSettings __asm__("LobbyControllerSettings");
extern BootSettings bootSettings __asm__("bootSettings");
void InitializeLobbyControllerSettingsToDefaults() __asm__("InitializeLobbyControllerSettingsToDefaults");


GAME_SECTION(RebootToFrontEnd) void RebootToFrontEnd()
{
	RebootOptions options;
	if (!RebootArgsInit) {
		BootArgList args;
		args.options = (char *)&options;
		args.name = RebootOptionName;
		RebootArgsInit = 1;
		RebootArgs = args;
	}
	options.head = DefaultRebootOptions.head;
	options.tail = DefaultRebootOptions.tail;
	GetBootOptionsFromSettings((char *)&options + 5);
	BootElf(BOOTELF_NAME, 2, &RebootArgs);
}

GAME_SECTION(Construct) void Construct(MovieQueue *self)
{
	self->head = 0;
	self->tail = 0;
	self->count = 0;
	memset(self->entries, 0xcd, 0x50);
	self->playing = 0;
	self->mode = 1;
}

GAME_SECTION(DeQueueMovie) int DeQueueMovie(MovieQueue *self, int &movieId, int &movieType)
{
	int next;
	if (!self->count) return 0;
	if (--self->count == 0) self->playing = 0;
	movieId = self->entries[self->tail].id;
	movieType = self->entries[self->tail].type;
	self->entries[self->tail].id = -1;
	self->entries[self->tail].type = -1;
	next = self->tail + 1;
	if (next == 10) next = 0;
	self->tail = next;
	return 1;
}

GAME_SECTION(QueueMovie) int QueueMovie(MovieQueue *self, int movieId)
{
	int next;
	if (self->count == 10 || self->playing) return 0;
	self->entries[self->head].id = movieId;
	self->entries[self->head].type = movieId >= 0x64;
	next = self->head + 1;
	if (next == 10) next = 0;
	self->count++;
	self->head = next;
	return 1;
}

GAME_SECTION(Flush) void Flush(MovieQueue *self)
{
	Construct(self);
}

GAME_SECTION(TagMoviesAsPlayed) void TagMoviesAsPlayed(MovieQueue *self)
{
	int i;
	for (i = self->tail; i != self->head; i = i + 1 == 10 ? 0 : i + 1) {
		int id = self->entries[i].id;
		if (id >= 0) MoviesPlayedRecord[(unsigned int)id >> 5] |= 1 << (id & 0x1f);
	}
}

GAME_SECTION(Abort___dupe2) void Abort(MovieQueue *self)
{
	TagMoviesAsPlayed(self);
	self->active = 0;
	Flush(self);
}

GAME_SECTION(PlayNextQueuedMovie) int PlayNextQueuedMovie(MovieQueue *self)
{
	int movieId, movieType, ret;
	if (self->count) {
		self->unk64 = 0;
		self->playing = 1;
		movieId = 0;
		movieType = 0;
		ret = 0;
		DeQueueMovie(self, movieId, movieType);
		self->mode = (unsigned int)(gameMode - 1) <= 1 ? 2 : 1;
		if (movieType == 0) ret = mode_requestChange(1, self->mode, 0, movieId, 0);
		else if (movieType == 1) ret = mode_requestChange(2, self->mode, movieId, 0, 0);
		if (ret < 0) Flush(self);
		return ret == 0;
	}
	return 0;
}

GAME_SECTION(HandleSpecialSwitchLevelCases) void HandleSpecialSwitchLevelCases(int &newLevelNumber)
{
}

GAME_SECTION(SwitchToLevel) void SwitchToLevel(int newLevelNumber, int memCardSave, int missionIndex)
{
	AbortMissionLoad();
	HandleSpecialSwitchLevelCases(newLevelNumber);
	g_newlevel = 1;
	PreviousLevel = Level;
	g_newmissionindex = missionIndex;
	g_newlevelnum = newLevelNumber;
	if (newLevelNumber == -1) {
		if (mcState.pending) mcState.pending = 0;
		if (mcState.command >= 0) mcState.command = -1;
		MCSTATE_ClearCommand(7);
	}
	if (!g_gameType && memCardSave) {
		Global_ClearSaveErrorInSpaceTransition();
		memcard_Save(0, g_newlevelnum);
	}
}

GAME_SECTION(SwitchingLevels) int SwitchingLevels()
{
	return g_newlevel != 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/globals", func_0045CB30);

GAME_SECTION(IsGameInChallengeMode) int IsGameInChallengeMode()
{
	return GameProgress.completed != 0;
}

GAME_SECTION(GetGameCompleted) int GetGameCompleted()
{
	return GameProgress.completed;
}

GAME_SECTION(Global_ClearSaveErrorInSpaceTransition) void Global_ClearSaveErrorInSpaceTransition()
{
	mSaveErrorSpaceTransition = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/globals", func_0045CB78);

GAME_SECTION(InitializeLobbyControllerSettingsToDefaults) void InitializeLobbyControllerSettingsToDefaults()
{
	int i;
	for (i = 0; i < 8; i++) {
		LobbyControllerSettings.values[0][i] = bootSettings.v0;
		LobbyControllerSettings.values[1][i] = bootSettings.v1;
		LobbyControllerSettings.values[2][i] = bootSettings.v2;
		LobbyControllerSettings.values[3][i] = bootSettings.v3;
		LobbyControllerSettings.values[4][i] = bootSettings.v4;
		LobbyControllerSettings.values[5][i] = bootSettings.v5;
		LobbyControllerSettings.values[6][i] = bootSettings.v6;
		LobbyControllerSettings.values[7][i] = bootSettings.v7;
		LobbyControllerSettings.values[8][i] = bootSettings.v8;
		LobbyControllerSettings.a[i] = bootSettings.a;
		LobbyControllerSettings.b[i] = bootSettings.b;
	}
	LobbyControllerSettings.ids[0] = -1;
	LobbyControllerSettings.ids[1] = -1;
	LobbyControllerSettings.ids[2] = -1;
	LobbyControllerSettings.ids[3] = -1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/globals", ControllerSettingsToLobbyStorage);

GAME_SECTION(GetCurrentThreadPriority) int GetCurrentThreadPriority()
{
	ThreadParam info;
	ReferThreadStatus(GetThreadId(), &info);
	return info.currentPriority;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/globals", func_0045CEB8);

GAME_SECTION(GetMobySkinBase) int GetMobySkinBase(int oClass)
{
	int i = 0;
	if (oClass == 0x2726) {
		if (Level == 0xe || Level == 0x22) return 0x246a;
		return 0x2133;
	}
	if (oClass == 0x2727) {
		if (Level == 0xe || Level == 0x22) return 0x246d;
		return 0x2130;
	}
	for (; TBL_EnemySkinDefTable[i].skin != -1; i++) {
		if (oClass == TBL_EnemySkinDefTable[i].oClass) return TBL_EnemySkinDefTable[i].skin;
	}
	return oClass;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/globals", func_0045CF88);
