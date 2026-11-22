// GAME_EXTRA_FLAGS: -g0
#include "common.h"
#include "game_section.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partproc", CreatePart);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partproc", DeletePart);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partproc", UpdateParts);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partproc", PartProc);

void _part_load_tex(void) __asm__("_part_load_tex");
GAME_SECTION(_part_load_tex) void _part_load_tex(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tsrl $6, $8, 4\n"
		"\tandi $7, $8, 0xf\n"
		"\tdsrl32 $5, $8, 4\n"
		"\tsw $6, 0x0($18)\n"
		"\tsw $5, 0x8($18)\n"
		"\tdsrl32 $6, $8, 0\n"
		"\tqmfc2.ni $8, $vf20\n"
		"\tandi $6, $6, 0xf\n"
		"\tsb $6, 0xc($18)\n"
		"\taddi $5, $0, 0x400\n"
		"\tsb $6, 0xd($18)\n"
		"\tdsll $6, $6, 26\n"
		"\tor $8, $8, $6\n"
		"\tdsll $6, $6, 4\n"
		"\tor $8, $8, $6\n"
		"\tsh $7, 0x4($18)\n"
		"\tsll $7, $7, 8\n"
		"\taddi $17, $17, 0x1\n"
		"\tsub $5, $5, $7\n"
		"\tdsll32 $7, $7, 11\n"
		"\tor $8, $8, $7\n"
		"\tsrl $6, $16, 8\n"
		"\tsh $6, 0x6($18)\n"
		"\taddiu $7, $0, 0x93\n"
		"\tsb $7, 0x5($18)\n"
		"\tadd $16, $16, $5\n"
		"\tdsll32 $6, $6, 5\n"
		"\tlbu $7, 0xc($18)\n"
		"\tor $8, $8, $6\n"
		"\tsrl $6, $16, 8\n"
		"\tor $8, $8, $6\n"
		"\tsh $6, 0xe($18)\n"
		"\taddi $6, $0, 0x1\n"
		"\taddi $18, $18, 0x10\n"
		"\tsllv $6, $6, $7\n"
		"\tnop\n"
		"\tsllv $6, $6, $7\n"
		"\tadd $16, $16, $6\n"
		"\tjr $31\n"
		"\tsd $8, 0x3000($9)\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(_part_load_tex) : : : "memory");
}
