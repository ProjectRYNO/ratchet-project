// GAME_EXTRA_FLAGS: -g0
#include "common.h"
#include "game_section.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mathfunc_asm", VecLimitLen2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mathfunc_asm", VecLimitLen3);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mathfunc_asm", VecReflect3);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mathfunc_asm", SinCos);

void SetRotX(void) __asm__("SetRotX");
GAME_SECTION(SetRotX) void SetRotX(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\taddi $25, $31, 0x0\n"
		"\tsq $0, 0x0($4)\n"
		"\tlui $5, (0x3f800000 >> 16)\n"
		"\tsq $0, 0x10($4)\n"
		"\tsq $0, 0x20($4)\n"
		"\tsqc2 $vf0, 0x30($4)\n"
		"\tjal SinCos\n"
		"\tsw $5, 0x0($4)\n"
		"\tneg.s $f4, $f1\n"
		"\tswc1 $f2, 0x14($4)\n"
		"\tswc1 $f1, 0x18($4)\n"
		"\tnop\n"
		"\taddi $31, $25, 0x0\n"
		"\tswc1 $f4, 0x24($4)\n"
		"\tjr $31\n"
		"\tswc1 $f2, 0x28($4)\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(SetRotX) : : : "memory");
}

void SetRotX___dupe2(void) __asm__("SetRotX___dupe2");
GAME_SECTION(SetRotX___dupe2) void SetRotX___dupe2(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\taddi $25, $31, 0x0\n"
		"\tsq $0, 0x0($4)\n"
		"\tlui $5, (0x3f800000 >> 16)\n"
		"\tsq $0, 0x10($4)\n"
		"\tjal SinCos\n"
		"\tsq $0, 0x20($4)\n"
		"\tneg.s $f4, $f1\n"
		"\tswc1 $f2, 0x14($4)\n"
		"\tswc1 $f1, 0x18($4)\n"
		"\tsw $5, 0x0($4)\n"
		"\taddi $31, $25, 0x0\n"
		"\tswc1 $f4, 0x24($4)\n"
		"\tjr $31\n"
		"\tswc1 $f2, 0x28($4)\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(SetRotX___dupe2) : : : "memory");
}

void SetRotZ(void) __asm__("SetRotZ");
GAME_SECTION(SetRotZ) void SetRotZ(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\taddi $25, $31, 0x0\n"
		"\tsq $0, 0x0($4)\n"
		"\tlui $5, (0x3f800000 >> 16)\n"
		"\tsq $0, 0x10($4)\n"
		"\tjal SinCos\n"
		"\tsq $0, 0x20($4)\n"
		"\tneg.s $f4, $f1\n"
		"\tswc1 $f2, 0x0($4)\n"
		"\tswc1 $f1, 0x4($4)\n"
		"\tsw $5, 0x28($4)\n"
		"\taddi $31, $25, 0x0\n"
		"\tswc1 $f4, 0x10($4)\n"
		"\tjr $31\n"
		"\tswc1 $f2, 0x14($4)\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(SetRotZ) : : : "memory");
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mathfunc_asm", QuatSlerp);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mathfunc_asm", QuatLerp);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mathfunc_asm", FastPointInSphere);

void PreserveRegsOld(void) __asm__("PreserveRegsOld");
GAME_SECTION(PreserveRegsOld) void PreserveRegsOld(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tpcpyld $8, $8, $0\n"
		"\tpcpyld $9, $9, $0\n"
		"\tlui $8, %%hi(g_PeInfo + 0x1140)\n"
		"\tlui $9, %%hi(D_220A68)\n"
		"\taddiu $8, $8, %%lo(g_PeInfo + 0x1140)\n"
		"\tlw $1, %%lo(D_220A68)($9)\n"
		"\tbnez $1, .L004FE3E0\n"
		"\tnop\n"
		"\taddi $1, $1, 0x1\n"
		"\tsw $1, %%lo(D_220A68)($9)\n"
		"\tsqc2 $vf1, 0x0($8)\n"
		"\tsqc2 $vf2, 0x10($8)\n"
		"\tsqc2 $vf3, 0x20($8)\n"
		"\tsqc2 $vf4, 0x30($8)\n"
		"\tsqc2 $vf5, 0x40($8)\n"
		"\tsqc2 $vf6, 0x50($8)\n"
		"\tsqc2 $vf7, 0x60($8)\n"
		"\tsqc2 $vf8, 0x70($8)\n"
		"\tsqc2 $vf9, 0x80($8)\n"
		"\tsqc2 $vf10, 0x90($8)\n"
		"\tsqc2 $vf11, 0xa0($8)\n"
		"\tsqc2 $vf12, 0xb0($8)\n"
		"\tsqc2 $vf13, 0xc0($8)\n"
		"\tsqc2 $vf14, 0xd0($8)\n"
		"\tsq $16, 0xe0($8)\n"
		"\tsq $17, 0xf0($8)\n"
		"\tsq $18, 0x100($8)\n"
		"\tsq $19, 0x110($8)\n"
		"\tsq $20, 0x120($8)\n"
		"\tsq $21, 0x130($8)\n"
		"\tsq $22, 0x140($8)\n"
		"\tsq $23, 0x150($8)\n"
		"\tpcpyud $8, $8, $0\n"
		"\tpcpyud $9, $9, $0\n"
		"\tjr $31\n"
		"\tnop\n"
		".L004FE3E0:\n"
		"\tbreak 0\n"
		"\tnop\n"
		"\tpcpyud $8, $8, $0\n"
		"\tpcpyud $9, $9, $0\n"
		"\tjr $31\n"
		"\tnop\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(PreserveRegsOld) : : : "memory");
}

void RestoreRegsAsmOld(void) __asm__("RestoreRegsAsmOld");
GAME_SECTION(RestoreRegsAsmOld) void RestoreRegsAsmOld(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tpcpyld $8, $8, $0\n"
		"\tpcpyld $9, $9, $0\n"
		"\tlui $8, %%hi(g_PeInfo + 0x1140)\n"
		"\tlui $9, %%hi(D_220A68)\n"
		"\taddiu $8, $8, %%lo(g_PeInfo + 0x1140)\n"
		"\tlw $1, %%lo(D_220A68)($9)\n"
		"\taddi $1, $1, -0x1\n"
		"\tsw $1, %%lo(D_220A68)($9)\n"
		"\tbnez $1, .L004FE488\n"
		"\tnop\n"
		"\tlqc2 $vf1, 0x0($8)\n"
		"\tlqc2 $vf2, 0x10($8)\n"
		"\tlqc2 $vf3, 0x20($8)\n"
		"\tlqc2 $vf4, 0x30($8)\n"
		"\tlqc2 $vf5, 0x40($8)\n"
		"\tlqc2 $vf6, 0x50($8)\n"
		"\tlqc2 $vf7, 0x60($8)\n"
		"\tlqc2 $vf8, 0x70($8)\n"
		"\tlqc2 $vf9, 0x80($8)\n"
		"\tlqc2 $vf10, 0x90($8)\n"
		"\tlqc2 $vf11, 0xa0($8)\n"
		"\tlqc2 $vf12, 0xb0($8)\n"
		"\tlqc2 $vf13, 0xc0($8)\n"
		"\tlqc2 $vf14, 0xd0($8)\n"
		"\tlq $16, 0xe0($8)\n"
		"\tlq $17, 0xf0($8)\n"
		"\tlq $18, 0x100($8)\n"
		"\tlq $19, 0x110($8)\n"
		"\tlq $20, 0x120($8)\n"
		"\tlq $21, 0x130($8)\n"
		"\tlq $22, 0x140($8)\n"
		"\tpcpyud $9, $9, $0\n"
		"\tlq $23, 0x150($8)\n"
		"\tnop\n"
		"\tjr $31\n"
		"\tpcpyud $8, $8, $0\n"
		".L004FE488:\n"
		"\tbreak 0\n"
		"\tnop\n"
		"\tpcpyud $8, $8, $0\n"
		"\tpcpyud $9, $9, $0\n"
		"\tjr $31\n"
		"\tnop\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(RestoreRegsAsmOld) : : : "memory");
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mathfunc_asm", PreserveRegs);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mathfunc_asm", RestoreRegs);
