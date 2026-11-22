// GAME_EXTRA_FLAGS: -g0
#include "common.h"
#include "game_section.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/cmecpu", CmeUnpack);

void _lookup_grid_pointer(void) __asm__("_lookup_grid_pointer");
GAME_SECTION(_lookup_grid_pointer) void _lookup_grid_pointer(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlhu $4, 0x0($24)\n"
		"\tlhu $5, 0x2($24)\n"
		"\tsub $3, $3, $4\n"
		"\tnop\n"
		"\tbltz $3, .L00441080\n"
		"\tsub $5, $5, $3\n"
		"\tblez $5, .L00441080\n"
		"\tsll $3, $3, 1\n"
		"\tadd $3, $3, $24\n"
		"\tlhu $3, 0x4($3)\n"
		"\tsll $3, $3, 2\n"
		"\tnop\n"
		"\tbeqz $3, .L00441080\n"
		"\tadd $3, $3, $24\n"
		"\tlhu $4, 0x0($3)\n"
		"\tlhu $5, 0x2($3)\n"
		"\tsub $2, $2, $4\n"
		"\tnop\n"
		"\tbltz $2, .L00441080\n"
		"\tsub $5, $5, $2\n"
		"\tblez $5, .L00441080\n"
		"\tsll $2, $2, 2\n"
		"\tadd $2, $2, $3\n"
		"\tlw $2, 0x4($2)\n"
		"\tbeqz $2, .L00441080\n"
		"\tadd $2, $2, $24\n"
		"\tlhu $4, 0x0($2)\n"
		"\tlhu $5, 0x2($2)\n"
		"\tsub $1, $1, $4\n"
		"\tnop\n"
		"\tbltz $1, .L00441080\n"
		"\tsub $5, $5, $1\n"
		"\tblez $5, .L00441080\n"
		"\tsll $1, $1, 2\n"
		"\tadd $1, $1, $2\n"
		"\tlw $1, 0x4($1)\n"
		"\tjr $31\n"
		"\tnop\n"
		".L00441080:\n"
		"\tjr $31\n"
		"\taddi $1, $0, 0x0\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(_lookup_grid_pointer) : : : "memory");
}
