// GAME_EXTRA_FLAGS: -g0
#include "common.h"
#include "game_section.h"

void _ssp_load_tex(void) __asm__("_ssp_load_tex");
GAME_SECTION(_ssp_load_tex) void _ssp_load_tex(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlw $6, -0x477b($28)\n" /* GifLoadCnt */
		"\tlui $7, %%hi(GifLoads)\n"
		"\taddiu $7, $7, %%lo(GifLoads)\n"
		"\tlw $1, -0x7f4f($28)\n" /* GSloc */
		"\taddi $2, $6, 0x1\n"
		"\tsll $6, $6, 4\n"
		"\tsw $2, -0x477b($28)\n" /* GifLoadCnt */
		"\tadd $7, $7, $6\n"
		"\tsrl $2, $1, 8\n"
		"\taddi $1, $1, 0x400\n"
		"\tsh $2, 0x6($7)\n"
		"\tsrl $3, $1, 8\n"
		"\tsh $3, 0xe($7)\n"
		"\taddiu $4, $0, 0x93\n"
		"\tsb $4, 0x5($7)\n"
		"\tnop\n"
		"\tlbu $4, 0xc($9)\n"
		"\taddi $6, $0, 0x1\n"
		"\tlbu $5, 0xe($9)\n"
		"\tnop\n"
		"\tsb $4, 0xc($7)\n"
		"\tsllv $6, $6, $4\n"
		"\tsb $5, 0xd($7)\n"
		"\tsllv $6, $6, $5\n"
		"\tadd $1, $1, $6\n"
		"\tsb $0, 0x4($7)\n"
		"\tsw $1, -0x7f4f($28)\n" /* GSloc */
		"\tnop\n"
		"\tlhu $1, 0xa($9)\n"
		"\tlhu $6, 0x8($9)\n"
		"\tsll $1, $1, 4\n"
		"\tsll $6, $6, 4\n"
		"\tadd $1, $1, $13\n"
		"\tadd $6, $6, $13\n"
		"\tsw $1, 0x0($7)\n"
		"\taddi $1, $4, -0x6\n"
		"\tsw $6, 0x8($7)\n"
		"\taddi $6, $0, 0x1\n"
		"\tqmfc2.ni $8, $vf23\n"
		"\tpmaxw $1, $1, $0\n"
		"\tsllv $6, $6, $1\n"
		"\tnop\n"
		"\tor $8, $8, $3\n"
		"\tdsll $6, $6, 14\n"
		"\tor $8, $8, $6\n"
		"\tdsll $4, $4, 26\n"
		"\tor $8, $8, $4\n"
		"\tdsll $5, $5, 30\n"
		"\tor $8, $8, $5\n"
		"\tdsll32 $2, $2, 5\n"
		"\tor $8, $8, $2\n"
		"\tnop\n"
		"\tjr $31\n"
		"\tsd $8, 0x0($9)\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(_ssp_load_tex) : : : "memory");
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/skyproc", SkyShellSetup);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/skyproc", SkyProcessVerts);

void SkyDrawClusterGouraud(void) __asm__("SkyDrawClusterGouraud");
GAME_SECTION(SkyDrawClusterGouraud) void SkyDrawClusterGouraud(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlw $25, -0x3b5f($28)\n" /* vu1_bufPtr */
		"\tnop\n"
		"\tlw $8, 0x0($5)\n"
		"\tpcpyld $13, $0, $0\n"
		"\tsqc2 $vf28, 0x0($25)\n"
		"\tpcpyld $14, $0, $0\n"
		"\tsqc2 $vf29, 0x10($25)\n"
		"\tpcpyld $15, $0, $0\n"
		"\taddi $9, $0, 0x0\n"
		"\taddiu $24, $25, 0x20\n"
		".L004DFA10:\n"
		"\tblez $4, .L004DFAC0\n"
		"\tsll $10, $8, 4\n"
		"\tsrl $11, $8, 4\n"
		"\tsrl $12, $8, 12\n"
		"\tandi $10, $10, 0xff0\n"
		"\tandi $11, $11, 0xff0\n"
		"\tandi $12, $12, 0xff0\n"
		"\tadd $13, $10, $7\n"
		"\tlbu $1, 0xf($13)\n"
		"\tadd $14, $11, $7\n"
		"\tlbu $2, 0xf($14)\n"
		"\tadd $15, $12, $7\n"
		"\tlbu $3, 0xf($15)\n"
		"\taddi $4, $4, -0x1\n"
		"\tand $1, $1, $2\n"
		"\taddi $5, $5, 0x4\n"
		"\tand $1, $1, $3\n"
		"\tlw $8, 0x0($5)\n"
		"\tbgtz $1, .L004DFA10\n"
		"\tsrl $10, $10, 2\n"
		"\tsrl $11, $11, 2\n"
		"\tsrl $12, $12, 2\n"
		"\tadd $10, $10, $6\n"
		"\tnop\n"
		"\tlwu $10, 0x0($10)\n"
		"\tadd $11, $11, $6\n"
		"\tlwu $11, 0x0($11)\n"
		"\tadd $12, $12, $6\n"
		"\tlwu $12, 0x0($12)\n"
		"\tld $13, 0x0($13)\n"
		"\tld $14, 0x0($14)\n"
		"\tld $15, 0x0($15)\n"
		"\tsd $10, 0x0($24)\n"
		"\tppach $13, $0, $13\n"
		"\tsd $11, 0x10($24)\n"
		"\tppach $14, $0, $14\n"
		"\tsd $12, 0x20($24)\n"
		"\tppach $15, $0, $15\n"
		"\tsd $13, 0x8($24)\n"
		"\tsd $14, 0x18($24)\n"
		"\tsd $15, 0x28($24)\n"
		"\taddi $24, $24, 0x30\n"
		"\tbgtz $4, .L004DFA10\n"
		"\taddi $9, $9, 0x3\n"
		".L004DFAC0:\n"
		"\tbeqz $9, .L004DFAE0\n"
		"\taddi $1, $9, 0x1\n"
		"\tsh $1, 0x0($25)\n"
		"\tsh $1, 0xc($25)\n"
		"\tori $9, $9, 0x8000\n"
		"\tsw $9, 0x10($25)\n"
		"\tsw $24, -0x3b5f($28)\n" /* vu1_bufPtr */
		"\tnop\n"
		".L004DFAE0:\n"
		".set at\n.set reorder" : : : "memory");
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/skyproc", SkyDrawClusterTextured);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/skyproc", SkyBsphereCheck);
