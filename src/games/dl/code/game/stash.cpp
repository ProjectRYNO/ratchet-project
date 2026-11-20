#include "common.h"
#include "game_section.h"
#include "gameglobals.h"
#include "stash.h"

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

JUNK_ASM(func_004E2A68,
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\tnop\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\tnop\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\tsh $6, 0x30($3)\n"
	"\tnop\n"
	"\tsh $0, 0x0($4)\n"
	"\tnop\n"
	"\tdaddu $2, $0, $0\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\tsq $2, 0x0($4)\n"
	"\tnop\n"
	"\tsq $2, 0x0($4)\n"
	"\tnop\n");
