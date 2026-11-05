#include "common.h"
#include "game_section.h"



struct MemcardSlot {
	/* 0x00 */ int unk00[9];
	/* 0x24 */ unsigned int patch_size;
	/* 0x28 */ char unk28[0xac];
};
struct MemcardDef {
	/* 0x000 */ MemcardSlot memcards[2];
	/* 0x1a8 */ int unk1a8[2];
	/* 0x1b0 */ int useslot;
	/* 0x1b4 */ int unk1b4[4];
	/* 0x1c4 */ int stage;
	/* 0x1c8 */ int unk1c8;
	/* 0x1cc */ int nextstage;
	/* 0x1d0 */ int nextsubstage;
	/* 0x1d4 */ int unk1d4[2];
	/* 0x1dc */ unsigned char *addr;
};
struct mc_data {
	/* 0x00 */ void *addr;
	/* 0x04 */ int size;
	/* 0x08 */ int unk08[2];
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


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_GetName);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_ResetGame);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_PrepData);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", memcard_RestoreInfo);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/memcard", DNAS_ExtractPatch);
