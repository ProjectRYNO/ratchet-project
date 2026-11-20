#include "common.h"
#include "game_section.h"
#include "globals.h"
#include "memcard.h"


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
int g_gameType __asm__("g_gameType") GAME_GP_DATA = 0;
extern int g_newlevelnum __asm__("g_newlevelnum");
extern int g_newmissionindex __asm__("g_newmissionindex");
extern int PreviousLevel __asm__("D_21DA78");
extern memcard_globals mcState __asm__("D_171948");
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
extern LobbySettings LobbyControllerSettings __asm__("LobbyControllerSettings");
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
	self->mHead = 0;
	self->mTail = 0;
	self->mItemCount = 0;
	memset(self->mItemsToPlay, 0xcd, 0x50);
	self->mLocked = 0;
	self->mTypeOfRequest = 1;
}

GAME_SECTION(DeQueueMovie) int DeQueueMovie(MovieQueue *self, int &movieId, int &movieType)
{
	int next;
	if (!self->mItemCount) return 0;
	if (--self->mItemCount == 0) self->mLocked = 0;
	movieId = self->mItemsToPlay[self->mTail].movieId;
	movieType = self->mItemsToPlay[self->mTail].movieType;
	self->mItemsToPlay[self->mTail].movieId = -1;
	self->mItemsToPlay[self->mTail].movieType = -1;
	next = self->mTail + 1;
	if (next == 10) next = 0;
	self->mTail = next;
	return 1;
}

GAME_SECTION(QueueMovie) int QueueMovie(MovieQueue *self, int movieId)
{
	int next;
	if (self->mItemCount == 10 || self->mLocked) return 0;
	self->mItemsToPlay[self->mHead].movieId = movieId;
	self->mItemsToPlay[self->mHead].movieType = movieId >= 0x64;
	next = self->mHead + 1;
	if (next == 10) next = 0;
	self->mItemCount++;
	self->mHead = next;
	return 1;
}

GAME_SECTION(Flush) void Flush(MovieQueue *self)
{
	Construct(self);
}

GAME_SECTION(TagMoviesAsPlayed) void TagMoviesAsPlayed(MovieQueue *self)
{
	int i;
	for (i = self->mTail; i != self->mHead; i = i + 1 == 10 ? 0 : i + 1) {
		int id = self->mItemsToPlay[i].movieId;
		if (id >= 0) MoviesPlayedRecord[(unsigned int)id >> 5] |= 1 << (id & 0x1f);
	}
}

GAME_SECTION(Abort___dupe2) void Abort(MovieQueue *self)
{
	TagMoviesAsPlayed(self);
	self->intro = 0;
	Flush(self);
}

GAME_SECTION(PlayNextQueuedMovie) int PlayNextQueuedMovie(MovieQueue *self)
{
	int movieId, movieType, ret;
	if (self->mItemCount) {
		self->mAborted = 0;
		self->mLocked = 1;
		movieId = 0;
		movieType = 0;
		ret = 0;
		DeQueueMovie(self, movieId, movieType);
		self->mTypeOfRequest = (unsigned int)(gameMode - 1) <= 1 ? 2 : 1;
		if (movieType == 0) ret = mode_requestChange(1, self->mTypeOfRequest, 0, movieId, 0);
		else if (movieType == 1) ret = mode_requestChange(2, self->mTypeOfRequest, movieId, 0, 0);
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
		if (mcState.autosave) mcState.autosave = 0;
		if (mcState.memcards[0].saveslot >= 0) mcState.memcards[0].saveslot = -1;
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

JUNK_ASM(func_0045CB30,
	"\tdaddu $2, $0, $0\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\tsb $4, 0xb4($2)\n"
	"\tnop\n");

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

JUNK_ASM(func_0045CB78,
	"\tsb $2, 0x0($28)\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n");

GAME_SECTION(InitializeLobbyControllerSettingsToDefaults) void InitializeLobbyControllerSettingsToDefaults()
{
	int i;
	for (i = 0; i < 8; i++) {
		LobbyControllerSettings.values[0][i] = bootSettings.CameraElevationDir[0][0];
		LobbyControllerSettings.values[1][i] = bootSettings.CameraElevationDir[1][0];
		LobbyControllerSettings.values[2][i] = bootSettings.CameraElevationDir[2][0];
		LobbyControllerSettings.values[3][i] = bootSettings.CameraAzimuthDir[0][0];
		LobbyControllerSettings.values[4][i] = bootSettings.CameraAzimuthDir[1][0];
		LobbyControllerSettings.values[5][i] = bootSettings.CameraAzimuthDir[2][0];
		LobbyControllerSettings.values[6][i] = bootSettings.CameraRotateSpeed[0][0];
		LobbyControllerSettings.values[7][i] = bootSettings.CameraRotateSpeed[1][0];
		LobbyControllerSettings.values[8][i] = bootSettings.CameraRotateSpeed[2][0];
		LobbyControllerSettings.a[i] = bootSettings.FirstPersonModeOn[0];
		LobbyControllerSettings.b[i] = bootSettings.ControllerVibrationOn[0];
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

JUNK_ASM(func_0045CEB8,
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n");

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

JUNK_ASM(func_0045CF88,
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\taddiu $29, $29, 0xa0\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x80\n"
	"\tnop\n"
	"\tnop\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x90\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x90\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $2, $0, 0x1\n"
	"\tnop\n"
	"\tdaddu $2, $5, $0\n"
	"\tnop\n"
	"\tnop\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\tdaddu $2, $0, $0\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\tlw $2, 0x0($3)\n"
	"\tnop\n"
	"\taddiu $2, $0, 0x1\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\tnop\n"
	"\tnop\n"
	"\tdaddu $2, $0, $0\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n");
