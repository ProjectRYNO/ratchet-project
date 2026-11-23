#include "common.h"
#include "game_section.h"

void srand(void) __asm__("srand");
GAME_SECTION(srand) void srand(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlui $8, %%hi(g_RandSeed)\n"
		"\tjr $31\n"
		"\tsw $4, %%lo(g_RandSeed)($8)\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(srand) : : : "memory");
}

void rand(void) __asm__("rand");
GAME_SECTION(rand) void rand(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlui $8, %%hi(g_RandSeed)\n"
		"\tlui $9, %%hi(D_003343FD)\n"
		"\taddiu $8, $8, %%lo(g_RandSeed)\n"
		"\taddiu $9, $9, %%lo(D_003343FD)\n"
		"\tlw $10, 0x0($8)\n"
		"\tlui $11, (0x269ec3 >> 16)\n"
		"\tlui $12, (0x7fffffff >> 16)\n"
		"\tori $11, $11, (0x269ec3 & 0xffff)\n"
		"\tmult $10, $10, $9\n"
		"\tori $12, $12, (0x7fffffff & 0xffff)\n"
		"\taddu $10, $10, $11\n"
		"\tsw $10, 0x0($8)\n"
		"\tjr $31\n"
		"\tand $2, $10, $12\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(rand) : : : "memory");
}

void rand16(void) __asm__("rand16");
GAME_SECTION(rand16) void rand16(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlui $8, %%hi(g_RandSeed)\n"
		"\tlui $9, %%hi(D_003343FD)\n"
		"\taddiu $8, $8, %%lo(g_RandSeed)\n"
		"\taddiu $9, $9, %%lo(D_003343FD)\n"
		"\tlw $10, 0x0($8)\n"
		"\tlui $11, (0x269ec3 >> 16)\n"
		"\taddi $12, $0, 0x7fff\n"
		"\tori $11, $11, (0x269ec3 & 0xffff)\n"
		"\tmult $10, $10, $9\n"
		"\taddu $10, $10, $11\n"
		"\tsrl $2, $10, 16\n"
		"\tsw $10, 0x0($8)\n"
		"\tjr $31\n"
		"\tand $2, $2, $12\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(rand16) : : : "memory");
}

JUNK_ASM(func_00163440,
	"\tsq $3, 0x20($2)\n"
	"\tnop\n");
