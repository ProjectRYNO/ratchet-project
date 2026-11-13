#include "common.h"
#include "game_section.h"



struct McClock {
	/* 0x0 */ unsigned char b[8];
};
struct MemcardInfo {
	/* 0x00 */ int level;
	/* 0x04 */ int bolts;
	/* 0x08 */ int completes;
	/* 0x0c */ int elapsedTime;
	/* 0x10 */ McClock saveTime;
	/* 0x18 */ int savedDifficultyLevel;
	/* 0x1c */ int bad;
};
struct MemcardSlot {
	/* 0x00 */ int unk00[6];
	/* 0x18 */ short saveslot;
	/* 0x1a */ short unk1a;
	/* 0x1c */ int unk1c[2];
	/* 0x24 */ unsigned int patch_size;
	/* 0x28 */ int oldsave;
	/* 0x2c */ int unk2c[2];
	/* 0x34 */ MemcardInfo info[5];
};
struct MemcardDef {
	/* 0x000 */ MemcardSlot memcards[2];
	/* 0x1a8 */ int unk1a8[2];
	/* 0x1b0 */ int useslot;
	/* 0x1b4 */ int curslot;
	/* 0x1b8 */ int level;
	/* 0x1bc */ int unk1bc[2];
	/* 0x1c4 */ int stage;
	/* 0x1c8 */ int unk1c8;
	/* 0x1cc */ int nextstage;
	/* 0x1d0 */ int nextsubstage;
	/* 0x1d4 */ int unk1d4[2];
	/* 0x1dc */ unsigned char *addr;
	/* 0x1e0 */ int unk1e0;
	/* 0x1e4 */ int autosave;
};
struct mc_data {
	/* 0x00 */ void *addr;
	/* 0x04 */ int size;
	/* 0x08 */ int iff;
	/* 0x0c */ int mark;
};
void FastMemZero(void *, int) __asm__("FastMemZero");
int memcard_LoadPatch(unsigned char *, unsigned int) __asm__("memcard_LoadPatch");
extern mc_data mc_leveldata[] __asm__("mc_leveldata");
int memcard_PrepData(char *, int, mc_data *) __asm__("memcard_PrepData");
void memcard_MakeWholeSave(char *) __asm__("memcard_MakeWholeSave");
void memcard_RestoreData(char *, char *, int, mc_data *) __asm__("memcard_RestoreData");
void memcard_RestoreGame(char *) __asm__("memcard_RestoreGame");
void memcard_cleanupbeforesession() __asm__("memcard_cleanupbeforesession");
extern "C" int sceMcInit();
void memcard_Init() __asm__("memcard_Init");
extern MemcardDef g_memcard __asm__("D_171948");
bool memcard_LoadNet() __asm__("memcard_LoadNet");
int memcard_GetDataSize(mc_data *p) __asm__("memcard_GetDataSize");
int memcard_PatchLoaded(int *p) __asm__("memcard_PatchLoaded");
bool memcard_TestChecksum(int *p) __asm__("memcard_TestChecksum");
int memcard_Checksum(char *addr, int size) __asm__("memcard_Checksum");
extern mc_data mc_gamedata[] __asm__("mc_gamedata");
int _memcard_Checksum(char *addr, int size) __asm__("_memcard_Checksum");





/* ===== AM additions ===== */
void FastMemSet(void *, int, int) __asm__("FastMemSet");
void FastMemCopy(void *, const void *, int) __asm__("FastMemCopy");
void memcard_RestoreInfo(char *, int, int) __asm__("memcard_RestoreInfo");
extern "C" int sceCdReadClock(McClock *);
extern "C" int sceScfGetLocalTimefromRTC(McClock *);
extern McClock LastSaveTime __asm__("LastSaveTime");
extern unsigned char mc_gameprepbuff[] __asm__("mc_gameprepbuff");
extern mc_data mc_netdata[] __asm__("mc_netdata");
int memcard_SaveNet() __asm__("memcard_SaveNet");
struct MiscWadDef {
	/* 0x000 */ char unk000[0x64c];
	/* 0x64c */ int misc_sector;
	/* 0x650 */ char unk650[0x10];
	/* 0x660 */ int savegame_offset;
	/* 0x664 */ int savegame_length;
};
extern MiscWadDef g_wadMisc __asm__("D_001C2040");
struct GameSettingsBlock {
	/* 0x00 */ int w[0x31];
};
extern GameSettingsBlock bootSettings __asm__("bootSettings");
extern int g_FirstPersonDesiredMode[10] __asm__("D_1711D0");
extern int g_gameType __asm__("g_gameType");
extern int Level __asm__("Level");
int PM_Malloc(unsigned int, void **) __asm__("PM_Malloc");
int music_Sync(int) __asm__("music_Sync");
struct Fs {
	static void Sync(unsigned int) __asm__("Sync");
	static int Load(int, unsigned int, unsigned int, unsigned int, unsigned int, void *, void *) __asm__("Load");
};
void MCSTATE_ClearCommand(int) __asm__("MCSTATE_ClearCommand");
void memcard_ResetGame() __asm__("memcard_ResetGame");
extern "C" int sceDNAS2InstInit_nohdd();
extern "C" int sceDNAS2InstExtractDataLength_nohdd(int, unsigned char *, unsigned int *);
extern "C" int sceDNAS2InstExtractData_nohdd(int, unsigned int, unsigned char *);
extern "C" int sceDNAS2InstShutdown_nohdd();
int DNAS_ExtractPatch(unsigned char *, unsigned int, unsigned int *) __asm__("DNAS_ExtractPatch");
extern unsigned char mc_levelprepbuff[] __asm__("mc_levelprepbuff");
extern int HeroSave __asm__("HeroSave");
extern int ElapsedTime __asm__("ElapsedTime");
extern int TN_savedDifficultyLevel __asm__("TN_savedDifficultyLevel");
int GetGameCompleted() __asm__("GetGameCompleted");
void MCSTATE_SetCommand(int, int, int (*)(), int (*)()) __asm__("MCSTATE_SetCommand");
static inline int GetLevel() { return Level; }
static inline int GetElapsedTime() { return ElapsedTime; }
static inline int GetLevelIndex(int l) { return (l - 1) % 20; }
int memcard_Save(int) __asm__("memcard_Save");

/* ===== AM additions (pass 3) ===== */
extern "C" char *strncpy(char *, const char *, unsigned int);
extern char BOOTELF_NAME[] __asm__("BOOTELF_NAME");
extern char SAVEGAME_NAME[] __asm__("SAVEGAME_NAME");
extern char SAVEGAME_WILD[] __asm__("SAVEGAME_WILD");
extern char SAVEGAME_SYS[] __asm__("SAVEGAME_SYS");
extern char SAVEGAME_VIEW[] __asm__("SAVEGAME_VIEW");
extern char SAVEGAME_MAIN[] __asm__("SAVEGAME_MAIN");
extern char SAVEGAME_NET[] __asm__("SAVEGAME_NET");
extern char SAVEGAME_PATCH[] __asm__("SAVEGAME_PATCH");
extern char SAVEGAME_SLOT[] __asm__("SAVEGAME_SLOT");
void memcard_GetName(char *) __asm__("memcard_GetName");
extern "C" int memcmp(const void *, const void *, unsigned int);
int g_loaderr __asm__("g_loaderr") GAME_GP_DATA = 0;
int memcard_RestoreDataAM(char *, char *, int, mc_data *) __asm__("memcard_RestoreData");

GAME_SECTION(memcard_GetName) void memcard_GetName(char *buff)
{
	int i;
	strncpy(BOOTELF_NAME, buff + 8, 0x15);
	if ((unsigned char)buff[0x12] == 'E') {
		SAVEGAME_NAME[2] = 'E';
	} else if ((unsigned char)buff[0x12] == 'P') {
		SAVEGAME_NAME[2] = 'I';
	} else if ((unsigned char)buff[0x12] == 'K') {
		SAVEGAME_NAME[2] = 'K';
	}
	for (i = 3; i < 7; i++) {
		SAVEGAME_NAME[i] = buff[i + 0xd];
	}
	for (i = 8; i < 0xb; i++) {
		SAVEGAME_NAME[i] = buff[i + 0xd];
	}
	for (i = 0xb; i < 0xd; i++) {
		SAVEGAME_NAME[i] = buff[i + 0xe];
	}
	strncpy(SAVEGAME_WILD, SAVEGAME_NAME, 0xd);
	strncpy(SAVEGAME_SYS, SAVEGAME_NAME, 0xd);
	strncpy(SAVEGAME_VIEW, SAVEGAME_NAME, 0xd);
	strncpy(SAVEGAME_MAIN, SAVEGAME_NAME, 0xd);
	strncpy(SAVEGAME_MAIN + 0x14, SAVEGAME_NAME, 0xd);
	strncpy(SAVEGAME_NET, SAVEGAME_NAME, 0xd);
	strncpy(SAVEGAME_PATCH, SAVEGAME_NAME, 0xd);
	strncpy(SAVEGAME_SLOT, SAVEGAME_NAME, 0xd);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", func_004660E0);

GAME_SECTION(memcard_RestoreGame) void memcard_RestoreGame(char *addr)
{
	int g_size = memcard_GetDataSize(mc_gamedata);
	int l_size = memcard_GetDataSize(mc_leveldata);
	int level;
	if (*(int *)addr == g_size && *(int *)(addr + 4) == l_size) {
		addr += 8;
		memcard_RestoreData(addr, addr + g_size, 0, mc_gamedata);
		addr += g_size;
		for (level = 0; level < 0xf; level++) {
			memcard_RestoreData(addr, addr + l_size, level, mc_leveldata);
			addr += l_size;
		}
		memcard_cleanupbeforesession();
	}
}

GAME_SECTION(memcard_ResetGame) void memcard_ResetGame()
{
	void *a1;
	char *addr;
	int backupFirstPersonDesiredMode[10];
	GameSettingsBlock preserve_settings;
	if (g_gameType != 1) {
		PM_Malloc(g_wadMisc.savegame_length << 11, &a1);
		music_Sync(1);
		Fs::Sync(1);
		Fs::Load(0, (unsigned int)a1, g_wadMisc.savegame_offset + g_wadMisc.misc_sector, g_wadMisc.savegame_length, 0, 0, 0);
		addr = (char *)a1 + *(int *)((char *)a1 + 0x10);
		FastMemCopy(backupFirstPersonDesiredMode, g_FirstPersonDesiredMode, 0x28);
		FastMemCopy(&preserve_settings, &bootSettings, 0xc4);
		memcard_RestoreGame(addr);
		FastMemCopy(g_FirstPersonDesiredMode, backupFirstPersonDesiredMode, 0x28);
		FastMemCopy(&bootSettings, &preserve_settings, 0xc4);
		Level = 1;
		if (g_memcard.autosave) {
			g_memcard.autosave = 0;
		}
		if (g_memcard.memcards[0].saveslot >= 0) {
			g_memcard.memcards[0].saveslot = -1;
		}
		MCSTATE_ClearCommand(7);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_Update);

GAME_SECTION(memcard_MakeWholeSave) void memcard_MakeWholeSave(char *addr)
{
	int i;
	*(int *)addr = memcard_GetDataSize(mc_gamedata);
	*(int *)(addr + 4) = memcard_GetDataSize(mc_leveldata);
	addr += 8;
	addr += memcard_PrepData(addr, 0, mc_gamedata);
	for (i = 0; i < 0xf; i++) {
		addr += memcard_PrepData(addr, i, mc_leveldata);
	}
}

GAME_SECTION(memcard_Init) void memcard_Init()
{
	sceMcInit();
}

GAME_SECTION(memcard_GetDataSize) int memcard_GetDataSize(mc_data *p)
{
	int size = 8;
	while (p->addr) {
		size += 8;
		size += p->size;
		p++;
		size = (size + 3) & ~3;
	}
	return size + 8;
}

GAME_SECTION(_memcard_Checksum) int _memcard_Checksum(char *addr, int size)
{
	char *end = addr + size;
	unsigned int crc = 0xedb88320;
	while (addr < end) {
		int j;
		crc ^= (unsigned char)*addr++ << 8;
		for (j = 7; j >= 0; j--) {
			if (crc & 0x8000) crc = (crc << 1) ^ 0x1f45;
			else crc <<= 1;
		}
	}
	return crc & 0xffff;
}

GAME_SECTION(memcard_Checksum) int memcard_Checksum(char *addr, int size)
{
	if (memcard_GetDataSize(mc_gamedata) < size) return 0;
	return _memcard_Checksum(addr, size);
}

GAME_SECTION(memcard_TestChecksum) bool memcard_TestChecksum(int *p)
{
	int sum = p[1];
	int size = p[0];
	bool ret = false;
	if (sum != 0) ret = memcard_Checksum((char *)(p + 2), size) == sum;
	return ret;
}

GAME_SECTION(memcard_PrepData) int memcard_PrepData(char *addr, int index, mc_data *mcd)
{
	int *p = (int *)(addr + 8);
	int size = 0;
	int i;
	for (i = 0; mcd[i].addr; i++) {
		char *src = (char *)mcd[i].addr + index * mcd[i].size;
		size += 8;
		p[0] = mcd[i].iff;
		p[1] = mcd[i].size;
		p += 2;
		if (mcd[i].iff == 6000) {
			FastMemSet(p, 0, mcd[i].size);
		} else {
			FastMemCopy(p, src, mcd[i].size);
		}
		p = (int *)((char *)p + mcd[i].size);
		size += mcd[i].size;
		p = (int *)(((int)p + 3) & ~3);
		size = (size + 3) & ~3;
	}
	size += 8;
	p[1] = 0;
	p[0] = -1;
	*(int *)(addr + 4) = memcard_Checksum(addr + 8, size);
	*(int *)addr = size;
	return size + 8;
}

GAME_SECTION(memcard_RestoreInfo) void memcard_RestoreInfo(char *addr, int slot, int index)
{
	g_memcard.memcards[slot].info[index].bad = memcard_TestChecksum((int *)addr) == 0;
	addr += 0x10;
	g_memcard.memcards[slot].info[index].level = *(int *)addr;
	addr += 0xc;
	g_memcard.memcards[slot].info[index].bolts = *(int *)addr;
	g_memcard.memcards[slot].info[index].completes = (unsigned char)addr[0x26];
	addr += 0x44;
	g_memcard.memcards[slot].info[index].elapsedTime = *(int *)addr;
	addr += 0xc;
	g_memcard.memcards[slot].info[index].saveTime = *(McClock *)addr;
	g_memcard.memcards[slot].info[index].savedDifficultyLevel = *(int *)(addr + 0x1c);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_RestoreData);

GAME_SECTION(memcard_LoadNet) bool memcard_LoadNet()
{
	if (g_memcard.nextstage < 0) {
		g_memcard.nextsubstage = 0;
		g_memcard.nextstage = 0x20;
	}
	return g_memcard.nextstage == 0x20;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_SaveNet);

GAME_SECTION(memcard_LoadPatch) int memcard_LoadPatch(unsigned char *buffer_start, unsigned int buffer_size)
{
	FastMemZero(buffer_start, buffer_size);
	if (g_memcard.useslot == -1) return 0;
	if (buffer_size < g_memcard.memcards[g_memcard.useslot].patch_size) return 0;
	if (g_memcard.nextstage < 0) {
		g_memcard.nextsubstage = g_memcard.useslot;
		g_memcard.nextstage = 0x26;
	}
	g_memcard.addr = buffer_start;
	return g_memcard.nextstage == 0x26;
}

GAME_SECTION(memcard_PatchLoaded) int memcard_PatchLoaded(int *p)
{
	if (g_memcard.stage < 3 && g_memcard.nextstage < 0) return *p;
	return -1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", func_004692B8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_Save);

GAME_SECTION(memcard_cleanupbeforesession) void memcard_cleanupbeforesession()
{
}

GAME_SECTION(DNAS_ExtractPatch) int DNAS_ExtractPatch(unsigned char *buffer_start, unsigned int buffer_size, unsigned int *DNAS_res)
{
	int ret = 0;
	unsigned char *patch_addr = buffer_start + 8;
	int personalize_len = *(int *)buffer_start;
	unsigned int extract_len;
	int r;
	unsigned int i;
	if (*(int *)(buffer_start + 4) != _memcard_Checksum((char *)patch_addr, personalize_len)) {
		*DNAS_res = 0;
		return 9;
	}
	if ((*DNAS_res = sceDNAS2InstInit_nohdd()) == 0) {
		if ((*DNAS_res = sceDNAS2InstExtractDataLength_nohdd(personalize_len, patch_addr, &extract_len)) & 0x80000000) {
			ret = 4;
		} else if (buffer_size - 8 < extract_len) {
			*DNAS_res = extract_len;
			ret = 7;
		} else if ((*DNAS_res = sceDNAS2InstExtractData_nohdd(personalize_len, extract_len, patch_addr)) & 0x80000000) {
			ret = 5;
		} else {
			*DNAS_res = extract_len;
		}
		r = sceDNAS2InstShutdown_nohdd();
		if (r < 0 && ret == 0) {
			*DNAS_res = r;
			ret = 6;
		}
	} else {
		ret = 1;
	}
	if (ret != 0) {
		for (i = 0; i < buffer_size; i++) {
			buffer_start[i] = 0;
		}
	}
	return ret;
}
