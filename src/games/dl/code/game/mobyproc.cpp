// GAME_EXTRA_FLAGS: -g0
#include "common.h"
#include "game_section.h"



typedef struct mobyLights {
	/* 0x00 */ char unk00[0x38];
	/* 0x38 */ unsigned long lights;
} mobyLights_t;
void SetMobyAmbientLights(mobyLights_t *moby, unsigned int r, unsigned int g, unsigned int b) __asm__("SetMobyAmbientLights");

void SetMobyLights(mobyLights_t *moby, unsigned long ambient, unsigned long a, unsigned long b, unsigned long c) __asm__("SetMobyLights");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", SetMobyLights);

GAME_SECTION(SetMobyAmbientLights) void SetMobyAmbientLights(mobyLights_t *moby, unsigned int r, unsigned int g, unsigned int b)
{
	*(unsigned int *)((char *)moby + 0x3c) = r | (g << 8) | (b << 16);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", GetMobyAmbientLights);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", AllocMobyVar);

void FreeMobyVar(void) __asm__("FreeMobyVar");
GAME_SECTION(FreeMobyVar) void FreeMobyVar(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlw $5, -0x455b($28)\n" /* MobyVarsBlockCnt + 0x8 */
		"\tlw $6, -0x4557($28)\n" /* MobyVarListTail */
		"\tlw $7, -0x4553($28)\n" /* MobyVarListTail + 0x4 */
		"\tlw $9, -0x455f($28)\n" /* MobyVarsBlockCnt + 0x4 */
		"\tlw $10, -0x4567($28)\n" /* MobyVars */
		"\tnop\n"
		"\tsub $4, $4, $10\n"
		"\tsrl $4, $4, 6\n"
		"\tdaddu $11, $5, $0\n"
		"\tori $12, $0, 0x0\n"
		"\tlw $1, 0x0($11)\n"
		"\tnop\n"
		".L00470290:\n"
		"\tnop\n"
		"\tnop\n"
		"\tsrl $2, $1, 8\n"
		"\tsra $3, $1, 20\n"
		"\tandi $2, $2, 0xfff\n"
		"\tsll $3, $3, 2\n"
		"\tbeq $2, $4, .L004702C8\n"
		"\tnop\n"
		"\tdaddu $12, $11, $0\n"
		"\tadd $11, $9, $3\n"
		"\tbgez $3, .L00470290\n"
		"\tlw $1, 0x0($11)\n"
		"\tteq $0, $0, 0\n"
		"\tnop\n"
		".L004702C8:\n"
		"\tsw $0, 0x0($11)\n"
		"\tpminw $7, $7, $11\n"
		"\tbeq $5, $6, .L00470328\n"
		"\tsw $7, -0x4553($28)\n" /* MobyVarListTail + 0x4 */
		"\tbeq $5, $11, .L00470310\n"
		"\tsrl $2, $1, 20\n"
		"\tlw $3, 0x0($12)\n"
		"\tsll $2, $2, 20\n"
		"\tsll $3, $3, 12\n"
		"\tsrl $3, $3, 12\n"
		"\tor $3, $3, $2\n"
		"\tnop\n"
		"\tbeq $6, $11, .L00470308\n"
		"\tsw $3, 0x0($12)\n"
		"\tjr $31\n"
		"\tnop\n"
		".L00470308:\n"
		"\tjr $31\n"
		"\tsw $12, -0x4557($28)\n" /* MobyVarListTail */
		".L00470310:\n"
		"\tsrl $2, $1, 20\n"
		"\tsll $2, $2, 2\n"
		"\tadd $2, $2, $9\n"
		"\tnop\n"
		"\tjr $31\n"
		"\tsw $2, -0x455b($28)\n" /* MobyVarsBlockCnt + 0x8 */
		".L00470328:\n"
		"\tsw $0, -0x455b($28)\n" /* MobyVarsBlockCnt + 0x8 */
		"\tsw $0, -0x4557($28)\n" /* MobyVarListTail */
		"\tjr $31\n"
		"\tsw $9, -0x4553($28)\n" /* MobyVarListTail + 0x4 */
		".set at\n.set reorder\n" GAME_ASM_TAIL(FreeMobyVar) : : : "memory");
}

void FreeMobyGridLists(void) __asm__("FreeMobyGridLists");
GAME_SECTION(FreeMobyGridLists) void FreeMobyGridLists(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\taddi $2, $0, 0x1\n"
		"\tlui $1, %%hi(MobyGridAlloc)\n"
		"\taddiu $1, $1, %%lo(MobyGridAlloc)\n"
		"\taddi $3, $0, -0x1\n"
		".L00470348:\n"
		"\tandi $6, $4, 0x7\n"
		"\tsrl $7, $4, 3\n"
		"\tadd $7, $7, $1\n"
		"\tsllv $6, $2, $6\n"
		"\tlbu $8, 0x0($7)\n"
		"\txor $6, $6, $3\n"
		"\taddi $4, $4, 0x1\n"
		"\taddi $5, $5, -0x1\n"
		"\tand $6, $8, $6\n"
		"\tnop\n"
		"\tbeq $6, $8, .L00470388\n"
		"\tnop\n"
		"\tbgtz $5, .L00470348\n"
		"\tsb $6, 0x0($7)\n"
		"\tjr $31\n"
		"\tnop\n"
		".L00470388:\n"
		"\tteq $0, $0, 0\n"
		"\tnop\n"
		"\tjr $31\n"
		"\tnop\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(FreeMobyGridLists) : : : "memory");
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", AllocMobyGridLists);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", UpdateMobyGrids);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", PostUpdateMoby);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", PostUpdateMobyBsphere);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", BuildMobyTextureDma);

void MobyAnimProc(void) __asm__("MobyAnimProc");
GAME_SECTION(MobyAnimProc) void MobyAnimProc(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tmtc1 $4, $f0\n"
		"\tlui $1, %%hi(MobyTexLookup + 0xf10)\n"
		"\taddiu $1, $1, %%lo(MobyTexLookup + 0xf10)\n"
		"\tmtc1 $5, $f1\n"
		"\tsd $28, 0x40($1)\n"
		"\tsd $29, 0x48($1)\n"
		"\tsd $30, 0x50($1)\n"
		"\tsd $31, 0x58($1)\n"
		"\tjal PreserveRegsOld\n"
		"\tnop\n"
		"\tlhu $1, 0x0($4)\n"
		"\tnop\n"
		"\tbeqz $1, .L00470BA0\n"
		"\tnop\n"
		".L00470B70:\n"
		"\tlw $5, 0x8($4)\n"
		"\tlhu $6, 0x4($4)\n"
		"\tjal AnimPrepareBindMats\n"
		"\tlw $4, 0xc($4)\n"
		"\tmfc1 $4, $f0\n"
		"\tnop\n"
		"\tjal CmeUnpack\n"
		"\tmfc1 $5, $f1\n"
		"\tlw $1, 0x0($2)\n"
		"\taddi $4, $2, 0x0\n"
		"\tbnez $1, .L00470B70\n"
		"\tmtc1 $4, $f0\n"
		".L00470BA0:\n"
		"\tlui $1, (0x1000d000 >> 16)\n"
		"\tori $1, $1, (0x1000d000 & 0xffff)\n"
		".L00470BA8:\n"
		"\tlw $2, 0x0($1)\n"
		"\tnop\n"
		"\tandi $2, $2, 0x100\n"
		"\tnop\n"
		"\tbnez $2, .L00470BA8\n"
		"\tnop\n"
		"\tlui $1, %%hi(MobyTexLookup + 0xf10)\n"
		"\taddiu $1, $1, %%lo(MobyTexLookup + 0xf10)\n"
		"\tld $28, 0x40($1)\n"
		"\tld $29, 0x48($1)\n"
		"\tjal RestoreRegsAsmOld\n"
		"\tld $30, 0x50($1)\n"
		"\tlui $1, %%hi(MobyTexLookup + 0xf10)\n"
		"\taddiu $1, $1, %%lo(MobyTexLookup + 0xf10)\n"
		"\tld $31, 0x58($1)\n"
		"\tnop\n"
		".set at\n.set reorder" : : : "memory");
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", FUN_00470bf0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyproc", SetMobyLightCuboid);

JUNK_ASM(func_00472510,
	"\tlw $2, 0x20($3)\n"
	"\tnop\n");
