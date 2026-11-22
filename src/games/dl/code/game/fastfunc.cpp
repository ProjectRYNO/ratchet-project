// GAME_EXTRA_FLAGS: -g0
#include "common.h"
#include "game_section.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fastfunc", FastMulQuats);

int FastDecTimer(int &) __asm__("FastDecTimer");
GAME_SECTION(FastDecTimer) int FastDecTimer(int &)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlw $1, 0x0($4)\n"
		"\taddi $2, $0, 0x1\n"
		"\tbeqz $1, .L004534F8\n"
		"\tpmaxw $1, $1, $2\n"
		"\taddi $1, $1, -0x1\n"
		"\taddi $2, $0, 0x0\n"
		"\tbgtz $1, .L004534F8\n"
		"\tsw $1, 0x0($4)\n"
		"\taddi $2, $0, 0x2\n"
		"\tnop\n"
		".L004534F8:\n"
		".set at\n.set reorder" : : : "memory");
}

void FastDecTimer___dupe2(void) __asm__("FastDecTimer___dupe2");
GAME_SECTION(FastDecTimer___dupe2) void FastDecTimer___dupe2(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlh $1, 0x0($4)\n"
		"\taddi $2, $0, 0x1\n"
		"\tbeqz $1, .L00453530\n"
		"\tpmaxw $1, $1, $2\n"
		"\taddi $1, $1, -0x1\n"
		"\taddi $2, $0, 0x0\n"
		"\tbgtz $1, .L00453530\n"
		"\tsh $1, 0x0($4)\n"
		"\taddi $2, $0, 0x2\n"
		"\tnop\n"
		".L00453530:\n"
		".set at\n.set reorder" : : : "memory");
}

void FastDecTimer___dupe3(void) __asm__("FastDecTimer___dupe3");
GAME_SECTION(FastDecTimer___dupe3) void FastDecTimer___dupe3(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlhu $1, 0x0($4)\n"
		"\taddi $2, $0, 0x1\n"
		"\tbeqz $1, .L0045355C\n"
		"\taddi $1, $1, -0x1\n"
		"\taddi $2, $0, 0x0\n"
		"\tbgtz $1, .L0045355C\n"
		"\tsh $1, 0x0($4)\n"
		"\tjr $31\n"
		"\taddi $2, $0, 0x2\n"
		".L0045355C:\n"
		"\tjr $31\n"
		"\tnop\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(FastDecTimer___dupe3) : : : "memory");
}

void FastDecTimer___dupe4(void) __asm__("FastDecTimer___dupe4");
GAME_SECTION(FastDecTimer___dupe4) void FastDecTimer___dupe4(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlbu $1, 0x0($4)\n"
		"\taddi $2, $0, 0x1\n"
		"\tbeqz $1, .L00453590\n"
		"\tpmaxw $1, $1, $2\n"
		"\taddi $1, $1, -0x1\n"
		"\taddi $2, $0, 0x0\n"
		"\tbgtz $1, .L00453590\n"
		"\tsb $1, 0x0($4)\n"
		"\taddi $2, $0, 0x2\n"
		"\tnop\n"
		".L00453590:\n"
		".set at\n.set reorder" : : : "memory");
}

void FastDecTimer___dupe5(void) __asm__("FastDecTimer___dupe5");
GAME_SECTION(FastDecTimer___dupe5) void FastDecTimer___dupe5(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlwc1 $f2, -0x7b7b($28)\n" /* NtscPalFrameTimeInSecondsFloat */
		"\tlwc1 $f1, 0x0($4)\n"
		"\tc.le.s $f1, $f2\n"
		"\tmfc1 $1, $f1\n"
		"\tbc1f .L004535D0\n"
		"\tnop\n"
		"\tdsll32 $1, $1, 0\n"
		"\tsw $0, 0x0($4)\n"
		"\tslti $2, $1, 0x1\n"
		"\taddiu $1, $0, 0x2\n"
		"\tjr $31\n"
		"\tsub $2, $2, $1\n"
		".L004535D0:\n"
		"\tsub.s $f1, $f1, $f2\n"
		"\taddi $2, $0, 0x0\n"
		"\tjr $31\n"
		"\tswc1 $f1, 0x0($4)\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(FastDecTimer___dupe5) : : : "memory");
}

void FastSitAndSpin(int) __asm__("FastSitAndSpin");
GAME_SECTION(FastSitAndSpin) void FastSitAndSpin(int)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tnop\n"
		"\tnop\n"
		"\tnop\n"
		"\tnop\n"
		"\tnop\n"
		"\tnop\n"
		"\tbgtz $4, FastSitAndSpin\n"
		"\taddi $4, $4, -0x2\n"
		".set at\n.set reorder" : : : "memory");
}

void FastMemSet(void *, int, int) __asm__("FastMemSet");
GAME_SECTION(FastMemSet) void FastMemSet(void *, int, int)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tsw $5, 0x0($4)\n"
		"\taddi $6, $6, -0x4\n"
		"\tblez $6, .L00453628\n"
		"\taddi $4, $4, 0x4\n"
		"\tsw $5, 0x0($4)\n"
		"\taddi $6, $6, -0x4\n"
		"\tbgtz $6, FastMemSet\n"
		"\taddi $4, $4, 0x4\n"
		".L00453628:\n"
		".set at\n.set reorder" : : : "memory");
}

void FastMemZero16(void *dest, int size) __asm__("FastMemZero16");
GAME_SECTION(FastMemZero16) void FastMemZero16(void *dest, int size)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tsq $0, 0x0($4)\n"
		"\taddi $5, $5, -0x10\n"
		"\tblez $5, .L00453650\n"
		"\taddi $4, $4, 0x10\n"
		"\tsq $0, 0x0($4)\n"
		"\taddi $5, $5, -0x10\n"
		"\tbgtz $5, FastMemZero16\n"
		"\taddi $4, $4, 0x10\n"
		".L00453650:\n"
		".set at\n.set reorder" : : : "memory");
}

void FastMemZero(void *, int) __asm__("FastMemZero");
GAME_SECTION(FastMemZero) void FastMemZero(void *, int)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlui $11, (0xfffffff0 >> 16)\n"
		"\tadd $5, $4, $5\n"
		"\tori $11, $11, (0xfffffff0 & 0xffff)\n"
		"\tori $8, $11, 0xfff8\n"
		"\tand $9, $5, $11\n"
		"\tori $7, $11, 0xfffc\n"
		"\tand $8, $5, $8\n"
		"\tand $7, $5, $7\n"
		"\tandi $11, $4, 0x2\n"
		"\tnop\n"
		"\tbeqz $11, .L00453690\n"
		"\tnop\n"
		"\tsh $0, 0x0($4)\n"
		"\taddi $4, $4, 0x2\n"
		".L00453690:\n"
		"\tandi $11, $4, 0x4\n"
		"\tnop\n"
		"\tbeqz $11, .L004536A8\n"
		"\tnop\n"
		"\tsw $0, 0x0($4)\n"
		"\taddi $4, $4, 0x4\n"
		".L004536A8:\n"
		"\tandi $11, $4, 0x8\n"
		"\tnop\n"
		"\tbeqz $11, .L004536C0\n"
		"\tnop\n"
		"\tsd $0, 0x0($4)\n"
		"\taddi $4, $4, 0x8\n"
		".L004536C0:\n"
		"\tbeq $4, $9, .L004536E8\n"
		"\tnop\n"
		"\tsq $0, 0x0($4)\n"
		"\taddi $4, $4, 0x10\n"
		"\tbeq $4, $9, .L004536E8\n"
		"\tnop\n"
		"\tsq $0, 0x0($4)\n"
		"\tnop\n"
		"\tb .L004536C0\n"
		"\taddi $4, $4, 0x10\n"
		".L004536E8:\n"
		"\tbeq $4, $8, .L004536F8\n"
		"\tnop\n"
		"\tsd $0, 0x0($4)\n"
		"\taddi $4, $4, 0x8\n"
		".L004536F8:\n"
		"\tbeq $4, $7, .L00453708\n"
		"\tnop\n"
		"\tsw $0, 0x0($4)\n"
		"\taddi $4, $4, 0x4\n"
		".L00453708:\n"
		"\tbnel $4, $5, .L00453710\n"
		"\tsh $0, 0x0($4)\n"
		".L00453710:\n"
		".set at\n.set reorder" : : : "memory");
}

void FastMemCopy(void *, void *, int) __asm__("FastMemCopy");
GAME_SECTION(FastMemCopy) void FastMemCopy(void *, void *, int)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tpref 0x00, 0x0($5)\n"
		"\tor $1, $4, $5\n"
		"\tbeqz $6, .L004537C8\n"
		"\tor $1, $1, $6\n"
		"\tandi $2, $1, 0xf\n"
		"\tadd $6, $5, $6\n"
		"\tbeqz $2, .L004537A0\n"
		"\tandi $2, $1, 0x3\n"
		"\tbeqz $2, .L00453770\n"
		"\tnop\n"
		"\taddiu $7, $6, 0x1\n"
		"\taddiu $4, $4, -0x2\n"
		".L00453748:\n"
		"\tlb $1, 0x0($5)\n"
		"\taddiu $4, $4, 0x2\n"
		"\tlb $2, 0x1($5)\n"
		"\taddiu $5, $5, 0x2\n"
		"\tbeq $5, $7, .L004537C8\n"
		"\tsb $1, 0x0($4)\n"
		"\tbne $5, $6, .L00453748\n"
		"\tsb $2, 0x1($4)\n"
		"\tjr $31\n"
		"\tnop\n"
		".L00453770:\n"
		"\taddiu $7, $6, 0x4\n"
		"\taddiu $4, $4, -0x8\n"
		".L00453778:\n"
		"\tlw $1, 0x0($5)\n"
		"\taddiu $4, $4, 0x8\n"
		"\tlw $2, 0x4($5)\n"
		"\taddiu $5, $5, 0x8\n"
		"\tbeq $5, $7, .L004537C8\n"
		"\tsw $1, 0x0($4)\n"
		"\tbne $5, $6, .L00453778\n"
		"\tsw $2, 0x4($4)\n"
		"\tjr $31\n"
		"\tnop\n"
		".L004537A0:\n"
		"\taddiu $7, $6, 0x10\n"
		"\taddiu $4, $4, -0x20\n"
		".L004537A8:\n"
		"\tlq $1, 0x0($5)\n"
		"\taddiu $4, $4, 0x20\n"
		"\tlq $2, 0x10($5)\n"
		"\taddiu $5, $5, 0x20\n"
		"\tbeq $5, $7, .L004537C8\n"
		"\tsq $1, 0x0($4)\n"
		"\tbne $5, $6, .L004537A8\n"
		"\tsq $2, 0x10($4)\n"
		".L004537C8:\n"
		"\tjr $31\n"
		"\tnop\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(FastMemCopy) : : : "memory");
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fastfunc", FastMemCopy16);

void FastMemCopyReverse16(void) __asm__("FastMemCopyReverse16");
GAME_SECTION(FastMemCopyReverse16) void FastMemCopyReverse16(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tadd $4, $4, $6\n"
		"\tadd $5, $5, $6\n"
		".L00453810:\n"
		"\tlq $3, -0x10($5)\n"
		"\taddi $5, $5, -0x10\n"
		"\taddi $4, $4, -0x10\n"
		"\taddi $6, $6, -0x10\n"
		"\tsq $3, 0x0($4)\n"
		"\tnop\n"
		"\tbgtz $6, .L00453810\n"
		"\tnop\n"
		".set at\n.set reorder" : : : "memory");
}

void FastMemOr16(void) __asm__("FastMemOr16");
GAME_SECTION(FastMemOr16) void FastMemOr16(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlq $2, 0x0($5)\n"
		"\taddi $5, $5, 0x10\n"
		"\tlq $3, 0x0($6)\n"
		"\taddi $6, $6, 0x10\n"
		"\taddi $4, $4, 0x10\n"
		"\taddi $7, $7, -0x10\n"
		"\tpor $2, $2, $3\n"
		"\tqmtc2.ni $0, $vf0\n"
		"\tbgtz $7, FastMemOr16\n"
		"\tsq $2, -0x10($4)\n"
		".set at\n.set reorder" : : : "memory");
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fastfunc", FastFromSpr);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fastfunc", FastVectorFromPackedChars);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fastfunc", FastVectorToPackedChars);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fastfunc", FastVectorFromSignedShorts);

int FastCountChars(void *, int) __asm__("FastCountChars");
GAME_SECTION(FastCountChars) int FastCountChars(void *, int)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\taddi $2, $0, 0x0\n"
		"\tnop\n"
		".L00453900:\n"
		"\tlbu $6, 0x0($4)\n"
		"\tnop\n"
		"\tlbu $7, 0x1($4)\n"
		"\taddi $4, $4, 0x2\n"
		"\tadd $2, $2, $6\n"
		"\taddi $5, $5, -0x2\n"
		"\tbgtz $5, .L00453900\n"
		"\tadd $2, $2, $7\n"
		".set at\n.set reorder" : : : "memory");
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fastfunc", FastCos);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fastfunc", FastSin);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fastfunc", FastArcSin);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fastfunc", FastArcTan);

JUNK_ASM(func_00453B08,
	"\tsqc2 $vf15, 0x0($5)\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fastfunc", FastAddRots);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fastfunc", FastSubRots);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fastfunc", FastWrapRot);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fastfunc", FastDiffRots);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fastfunc", FastMod);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fastfunc", FastTweenColor);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fastfunc", FastBsphereCheck);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fastfunc", FastBsphereCheck___dupe2);

JUNK_ASM(func_00453EA8,
	"\tsw $0, 0x0($24)\n"
	"\tnop\n");

void sound_GetChannelFromHandle(short) __asm__("sound_GetChannelFromHandle");
GAME_SECTION(sound_GetChannelFromHandle) void sound_GetChannelFromHandle(short)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlw $3, -0x5cbf($28)\n" /* D_21FCC0 */
		"\tadd $2, $0, $0\n"
		"\tandi $8, $4, 0x3f\n"
		"\taddi $12, $0, 0x3f\n"
		"\tbeq $8, $12, .L00453EE8\n"
		"\tandi $9, $4, 0xffff\n"
		"\tsll $10, $8, 7\n"
		"\tsrl $9, $9, 6\n"
		"\tadd $12, $10, $3\n"
		"\tnop\n"
		"\tlh $13, 0x58($12)\n"
		"\tnop\n"
		"\tbeql $9, $13, .L00453EE8\n"
		"\tadd $2, $0, $12\n"
		".L00453EE8:\n"
		".set at\n.set reorder" : : : "memory");
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fastfunc", FastPointInCuboid);
