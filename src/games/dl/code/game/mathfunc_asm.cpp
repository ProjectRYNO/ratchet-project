#include "common.h"
#include "game_section.h"

void VecLimitLen2(void) __asm__("VecLimitLen2");
GAME_SECTION(VecLimitLen2) void VecLimitLen2(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tqmtc2.ni $4, $vf20\n"
		"\tmul.s $f4, $f12, $f12\n"
		"\tvmul.xyzw $vf21, $vf20, $vf20\n"
		"\tmfc1 $8, $f12\n"
		"\tqmtc2.ni $8, $vf22\n"
		"\tmfc1 $8, $f4\n"
		"\tvaddy.x $vf21, $vf21, $vf21y\n"
		"\tvrsqrt Q, $vf22x, $vf21x\n"
		"\tqmfc2.ni $9, $vf21\n"
		"\tpextlw $9, $0, $9\n"
		"\tslt $10, $8, $9\n"
		"\tnop\n"
		"\tbeqz $10, .L004FE070\n"
		"\tnop\n"
		"\tbeqz $9, .L004FE078\n"
		"\tnop\n"
		"\tvwaitq\n"
		"\tvmulq.xy $vf20, $vf20, Q\n"
		".L004FE070:\n"
		"\tjr $31\n"
		"\tqmfc2.ni $2, $vf20\n"
		".L004FE078:\n"
		"\tjr $31\n"
		"\tpcpyud $2, $0, $4\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(VecLimitLen2) : : : "memory");
}

void VecLimitLen3(void) __asm__("VecLimitLen3");
GAME_SECTION(VecLimitLen3) void VecLimitLen3(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tqmtc2.ni $4, $vf20\n"
		"\tvmaxw.xyzw $vf23, $vf0, $vf0w\n"
		"\tvmul.xyzw $vf21, $vf20, $vf20\n"
		"\tmul.s $f4, $f12, $f12\n"
		"\tvadday.x ACC, $vf21, $vf21y\n"
		"\tmfc1 $8, $f12\n"
		"\tqmtc2.ni $8, $vf22\n"
		"\tnop\n"
		"\tvmaddz.x $vf21, $vf23, $vf21z\n"
		"\tmfc1 $8, $f4\n"
		"\tvrsqrt Q, $vf22x, $vf21x\n"
		"\tqmfc2.ni $9, $vf21\n"
		"\tpextlw $9, $0, $9\n"
		"\tslt $10, $8, $9\n"
		"\tbeqz $10, .L004FE0D0\n"
		"\tpcpyud $4, $0, $4\n"
		"\tbeqz $9, .L004FE0D8\n"
		"\tprot3w $4, $4\n"
		"\tvwaitq\n"
		"\tvmulq.xyz $vf20, $vf20, Q\n"
		".L004FE0D0:\n"
		"\tjr $31\n"
		"\tqmfc2.ni $2, $vf20\n"
		".L004FE0D8:\n"
		"\tjr $31\n"
		"\tpcpyud $2, $0, $4\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(VecLimitLen3) : : : "memory");
}

void VecReflect3(void) __asm__("VecReflect3");
GAME_SECTION(VecReflect3) void VecReflect3(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tqmtc2.ni $4, $vf15\n"
		"\tqmtc2.ni $5, $vf16\n"
		"\tvsub.xyz $vf15, $vf0, $vf15\n"
		"\tvaddw.xyz $vf17, $vf0, $vf0w\n"
		"\tvmul.xyz $vf18, $vf16, $vf16\n"
		"\tvadday.x ACC, $vf18, $vf18y\n"
		"\tvmaddz.x $vf18, $vf17, $vf18z\n"
		"\tvrsqrt Q, $vf0w, $vf18x\n"
		"\tvwaitq\n"
		"\tvmulq.xyz $vf16, $vf16, Q\n"
		"\tvmul.xyz $vf18, $vf15, $vf16\n"
		"\tvadday.x ACC, $vf18, $vf18y\n"
		"\tvmaddz.x $vf18, $vf17, $vf18z\n"
		"\tqmfc2.ni $1, $vf18\n"
		"\tdsll32 $1, $1, 0\n"
		"\tvmulx.xyz $vf16, $vf16, $vf18x\n"
		"\tbltz $1, .L004FE140\n"
		"\tnop\n"
		"\tvsub.xyz $vf16, $vf16, $vf15\n"
		"\tvadd.xyz $vf16, $vf16, $vf16\n"
		"\tvadd.xyz $vf15, $vf15, $vf16\n"
		"\tqmfc2.ni $2, $vf15\n"
		"\tjr $31\n"
		"\tnop\n"
		".L004FE140:\n"
		"\tjr $31\n"
		"\tpor $2, $0, $4\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(VecReflect3) : : : "memory");
}

void SinCos(void) __asm__("SinCos");
GAME_SECTION(SinCos) void SinCos(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tmfc1 $8, $f12\n"
		"\tqmtc2.ni $8, $vf15\n"
		"\tvcallms 0xc60\n"
		"\tnop\n"
		"\tvnop\n"
		"\tnop\n"
		"\tqmfc2.ni $8, $vf15\n"
		"\tnop\n"
		"\tmtc1 $8, $f1\n"
		"\tprot3w $9, $8\n"
		"\tjr $31\n"
		"\tmtc1 $9, $f2\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(SinCos) : : : "memory");
}

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

void QuatSlerp(void) __asm__("QuatSlerp");
GAME_SECTION(QuatSlerp) void QuatSlerp(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tmfc1 $8, $f12\n"
		"\tqmtc2.ni $8, $vf23\n"
		"\tqmtc2.ni $4, $vf15\n"
		"\tqmtc2.ni $5, $vf16\n"
		"\tvsubx.w $vf23, $vf0, $vf23x\n"
		"\tvaddw.xyz $vf27, $vf0, $vf0w\n"
		"\tvmulw.xyzw $vf15, $vf15, $vf23w\n"
		"\tvmulx.xyzw $vf16, $vf16, $vf23x\n"
		"\tvadd.xyzw $vf24, $vf15, $vf16\n"
		"\tvmul.xyzw $vf26, $vf15, $vf16\n"
		"\tvmul.xyzw $vf25, $vf24, $vf24\n"
		"\tvaddax.y ACC, $vf26, $vf26x\n"
		"\tvmaddaz.y ACC, $vf27, $vf26z\n"
		"\tvmaddw.y $vf26, $vf27, $vf26w\n"
		"\tvadday.x ACC, $vf25, $vf25y\n"
		"\tvmaddaz.x ACC, $vf27, $vf25z\n"
		"\tvmaddw.x $vf25, $vf27, $vf25w\n"
		"\tqmfc2.ni $9, $vf26\n"
		"\tbgez $9, .L004FE290\n"
		"\tnop\n"
		"\tvsub.xyzw $vf24, $vf15, $vf16\n"
		"\tvmul.xyzw $vf25, $vf24, $vf24\n"
		"\tvadday.x ACC, $vf25, $vf25y\n"
		"\tvmaddaz.x ACC, $vf27, $vf25z\n"
		"\tvmaddw.x $vf25, $vf27, $vf25w\n"
		"\tnop\n"
		".L004FE290:\n"
		"\tnop\n"
		"\tnop\n"
		"\tvrsqrt Q, $vf0w, $vf25x\n"
		"\tvwaitq\n"
		"\tvmulq.xyzw $vf15, $vf24, Q\n"
		"\tqmfc2.ni $2, $vf15\n"
		".set at\n.set reorder" : : : "memory");
}

void QuatLerp(void) __asm__("QuatLerp");
GAME_SECTION(QuatLerp) void QuatLerp(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tvmaxw.xyzw $vf23, $vf0, $vf0w\n"
		"\tmfc1 $8, $f12\n"
		"\tqmtc2.ni $4, $vf15\n"
		"\tqmtc2.ni $5, $vf16\n"
		"\tvmul.xyzw $vf17, $vf15, $vf16\n"
		"\tvadday.x ACC, $vf17, $vf17y\n"
		"\tvmaddaz.x ACC, $vf23, $vf17z\n"
		"\tvmaddw.x $vf17, $vf23, $vf17w\n"
		"\tctc2.ni $8, $vi21\n"
		"\tvaddax.xyzw ACC, $vf15, $vf0x\n"
		"\tvmsubai.xyzw ACC, $vf15, I\n"
		"\tqmfc2.ni $9, $vf17\n"
		"\tsrl $9, $9, 31\n"
		"\tandi $9, $9, 0x1\n"
		"\tbeql $9, $0, .L004FE2F4\n"
		"\tvmaddi.xyzw $vf16, $vf16, I\n"
		"\tvmsubi.xyzw $vf16, $vf16, I\n"
		".L004FE2F4:\n"
		"\tvmul.xyzw $vf17, $vf16, $vf16\n"
		"\tvadday.x ACC, $vf17, $vf17y\n"
		"\tvmaddaz.x ACC, $vf23, $vf17z\n"
		"\tvmaddw.x $vf17, $vf23, $vf17w\n"
		"\tvrsqrt Q, $vf0w, $vf17x\n"
		"\tvwaitq\n"
		"\tvmulq.xyzw $vf16, $vf16, Q\n"
		"\tjr $31\n"
		"\tqmfc2.ni $2, $vf16\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(QuatLerp) : : : "memory");
}

unsigned int FastPointInSphere(void) __asm__("FastPointInSphere");
GAME_SECTION(FastPointInSphere) unsigned int FastPointInSphere(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tqmtc2.ni $4, $vf20\n"
		"\tlqc2 $vf21, 0x0($5)\n"
		"\tvmaxw.xyzw $vf23, $vf0, $vf0w\n"
		"\tvmul.w $vf21, $vf21, $vf21\n"
		"\tvsub.xyz $vf22, $vf20, $vf21\n"
		"\tvmul.xyz $vf22, $vf22, $vf22\n"
		"\tvadday.xyzw ACC, $vf22, $vf22y\n"
		"\tvmaddz.xyzw $vf22, $vf23, $vf22z\n"
		"\tvsubw.x $vf21, $vf22, $vf21w\n"
		"\tqmfc2.ni $2, $vf21\n"
		"\tsra $2, $2, 31\n"
		"\tjr $31\n"
		"\tandi $2, $2, 0x1\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(FastPointInSphere) : : : "memory");
}

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

void PreserveRegs(void) __asm__("PreserveRegs");
GAME_SECTION(PreserveRegs) void PreserveRegs(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tvcallms 0xe90\n"
		"\tnop\n"
		"\tqmtc2.ni $16, $vf16\n"
		"\tqmtc2.ni $17, $vf17\n"
		"\tqmtc2.ni $18, $vf18\n"
		"\tqmtc2.ni $19, $vf19\n"
		"\tqmtc2.ni $20, $vf20\n"
		"\tqmtc2.ni $21, $vf21\n"
		"\tqmtc2.ni $22, $vf22\n"
		"\tqmtc2.ni $23, $vf23\n"
		"\tvcallms 0xe10\n"
		"\tnop\n"
		"\tjr $31\n"
		"\tvnop\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(PreserveRegs) : : : "memory");
}

void RestoreRegs(void) __asm__("RestoreRegs");
GAME_SECTION(RestoreRegs) void RestoreRegs(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tvcallms 0xf40\n"
		"\tnop\n"
		"\tjr $31\n"
		"\tvnop\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(RestoreRegs) : : : "memory");
}
