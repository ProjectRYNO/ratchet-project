#include "common.h"
#include "game_section.h"

/* ===== AJ near misses ===== */
struct StashInfo {
	/* 0x00 */ char *base;
	/* 0x04 */ int size;
	/* 0x08 */ int unk08[10];
	/* 0x30 */ char *free;
	/* 0x34 */ int block;
	/* 0x38 */ char *gadgetram;
};
struct StashBlock {
	/* 0x00 */ char *ram;
	/* 0x04 */ int qwc;
	/* 0x08 */ const char *comment;
	/* 0x0c */ int pad;
};
extern StashInfo Stash __asm__("Stash");
extern StashBlock Blocks[64] __asm__("Blocks");
extern char g_StashEEMemory[] __asm__("g_StashEEMemory");
extern char *g_StashMainMemory __asm__("D_21DD7C");
extern char *g_StashGadgetMemory __asm__("g_StashGadgetMemory");
extern int g_gameType __asm__("g_gameType");
void FastMemSet(void *, int, int) __asm__("FastMemSet");
void FastMemCopy(void *, const void *, int) __asm__("FastMemCopy");
void Stash_InitOnce() __asm__("Stash_InitOnce");
int Stash_SendData(void *src, int data_qwc, int alloc_qwc, const char *comment) __asm__("Stash_SendData");

GAME_SECTION(Stash_InitOnce) void Stash_InitOnce()
{
	int i;
	char *mem = g_StashEEMemory;
	FastMemSet(mem, 0, 0xd000);
	g_StashMainMemory = mem;
	g_StashGadgetMemory = g_StashEEMemory + 0xc800;
	if (g_gameType != 1) {
		Stash.base = mem;
		Stash.size = 0xc800;
		Stash.free = mem;
		Stash.block = 0;
		Stash.gadgetram = g_StashEEMemory + 0xc800;
		for (i = 0; i < 0x40; i++) {
			Blocks[i].ram = 0;
			Blocks[i].qwc = 0;
		}
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stash", Stash_SendData);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/stash", func_004E2A68);
