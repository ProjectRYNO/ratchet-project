#include "common.h"
#include "game_section.h"

void FastMulQuats(void) __asm__("FastMulQuats");





GAME_SECTION(FastMulQuats) void FastMulQuats(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlqc2 $vf15, 0x0($5)\n"
		"\tlqc2 $vf16, 0x0($6)\n"
		"\tvmul.xyzw $vf17, $vf15, $vf16\n"
		"\tvopmula.xyz ACC, $vf15, $vf16\n"
		"\tvmaddaw.xyz ACC, $vf15, $vf16w\n"
		"\tvmaddaw.xyz ACC, $vf16, $vf15w\n"
		"\tvopmsub.xyz $vf22, $vf16, $vf15\n"
		"\tvsubax.w ACC, $vf17, $vf17x\n"
		"\tvmsubay.w ACC, $vf0, $vf17y\n"
		"\tvmsubz.w $vf22, $vf0, $vf17z\n"
		"\tjr $31\n"
		"\tsqc2 $vf22, 0x0($4)\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(FastMulQuats) : : : "memory");
}

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

void FastMemCopy16(void) __asm__("FastMemCopy16");
GAME_SECTION(FastMemCopy16) void FastMemCopy16(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\taddu $9, $4, $6\n"
		"\taddiu $4, $4, -0x20\n"
		"\taddiu $8, $9, -0x10\n"
		"\taddiu $9, $9, -0x20\n"
		".L004537E0:\n"
		"\tlq $1, 0x0($5)\n"
		"\taddiu $4, $4, 0x20\n"
		"\tlq $2, 0x10($5)\n"
		"\taddiu $5, $5, 0x20\n"
		"\tbeq $4, $8, .L00453800\n"
		"\tsq $1, 0x0($4)\n"
		"\tbne $4, $9, .L004537E0\n"
		"\tsq $2, 0x10($4)\n"
		".L00453800:\n"
		".set at\n.set reorder" : : : "memory");
}

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

void FastFromSpr(void *, int, int) __asm__("FastFromSpr");
GAME_SECTION(FastFromSpr) void FastFromSpr(void *, int, int)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlui $1, (0x1000d000 >> 16)\n"
		"\tori $1, $1, (0x1000d000 & 0xffff)\n"
		"\tsw $5, 0x80($1)\n"
		"\tnop\n"
		"\tsw $4, 0x10($1)\n"
		"\tori $2, $0, 0x100\n"
		"\tsw $6, 0x20($1)\n"
		"\tsw $2, 0x0($1)\n"
		"\tlui $3, (0x20100000 >> 16)\n"
		"\tsync\n"
		"\tlw $3, (0x20100000 & 0xffff)($3)\n"
		"\tnop\n"
		"\tjr $31\n"
		"\tori $3, $3, 0x1\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(FastFromSpr) : : : "memory");
}

void FastVectorFromPackedChars(void *, int) __asm__("FastVectorFromPackedChars");
GAME_SECTION(FastVectorFromPackedChars) void FastVectorFromPackedChars(void *, int)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tpextlb $5, $0, $5\n"
		"\tpextlh $5, $0, $5\n"
		"\tqmtc2.ni $5, $vf15\n"
		"\tvitof0.xyzw $vf15, $vf15\n"
		"\tjr $31\n"
		"\tsqc2 $vf15, 0x0($4)\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(FastVectorFromPackedChars) : : : "memory");
}

void FastVectorToPackedChars(void *) __asm__("FastVectorToPackedChars");
GAME_SECTION(FastVectorToPackedChars) void FastVectorToPackedChars(void *)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlqc2 $vf15, 0x0($4)\n"
		"\tnop\n"
		"\tvftoi0.xyzw $vf15, $vf15\n"
		"\tnop\n"
		"\tqmfc2.ni $1, $vf15\n"
		"\tnop\n"
		"\tqmtc2.ni $0, $vf0\n"
		"\tppach $2, $0, $1\n"
		"\tjr $31\n"
		"\tppacb $2, $0, $2\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(FastVectorToPackedChars) : : : "memory");
}

void FastVectorFromSignedShorts(void *, long) __asm__("FastVectorFromSignedShorts");
GAME_SECTION(FastVectorFromSignedShorts) void FastVectorFromSignedShorts(void *, long)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tpextlh $5, $5, $0\n"
		"\tpsraw $5, $5, 16\n"
		"\tqmtc2.ni $5, $vf15\n"
		"\tvitof0.xyzw $vf15, $vf15\n"
		"\tjr $31\n"
		"\tsqc2 $vf15, 0x0($4)\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(FastVectorFromSignedShorts) : : : "memory");
}

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

int FastCos(float) __asm__("FastCos");
GAME_SECTION(FastCos) int FastCos(float)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tmfc1 $1, $f12\n"
		"\tqmtc2.ni $1, $vf15\n"
		"\tvcallms 0xc78\n"
		"\tqmfc2.i $1, $vf15\n"
		"\tjr $31\n"
		"\tmtc1 $1, $f0\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(FastCos) : : : "memory");
}

int FastSin(float) __asm__("FastSin");
GAME_SECTION(FastSin) int FastSin(float)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tmfc1 $1, $f12\n"
		"\tqmtc2.ni $1, $vf15\n"
		"\tvcallms 0xc88\n"
		"\tqmfc2.i $1, $vf15\n"
		"\tjr $31\n"
		"\tmtc1 $1, $f0\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(FastSin) : : : "memory");
}

float FastArcSin(float) __asm__("FastArcSin");
GAME_SECTION(FastArcSin) float FastArcSin(float)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlui $1, (0x3f800000 >> 16)\n"
		"\tmtc1 $0, $f13\n"
		"\tmtc1 $1, $f0\n"
		"\tnop\n"
		"\tc.lt.s $f12, $f13\n"
		"\tnop\n"
		"\tbc1f .L00453988\n"
		"\tmtc1 $1, $f10\n"
		"\tlui $1, (0xbf800000 >> 16)\n"
		"\tabs.s $f12, $f12\n"
		"\tnop\n"
		"\tmtc1 $1, $f10\n"
		".L00453988:\n"
		"\tsub.s $f1, $f0, $f12\n"
		"\taddiu $1, $28, -0x5c3f\n" /* ArcSinSeries */
		"\tmfc1 $4, $f1\n"
		"\tmul.s $f2, $f12, $f12\n"
		"\tqmtc2.ni $4, $vf15\n"
		"\tlwc1 $f5, 0x4($1)\n"
		"\tlwc1 $f4, 0x0($1)\n"
		"\tvsqrt Q, $vf15x\n"
		"\tmul.s $f3, $f12, $f2\n"
		"\tadda.s $f4, $f13\n"
		"\tmadda.s $f12, $f5\n"
		"\tlwc1 $f6, 0x8($1)\n"
		"\tlwc1 $f7, 0xc($1)\n"
		"\tmadda.s $f2, $f6\n"
		"\tmadd.s $f8, $f3, $f7\n"
		"\tvaddq.x $vf15, $vf0, Q\n"
		"\tlui $1, (0x3fc90fdb >> 16)\n"
		"\tori $1, $1, (0x3fc90fdb & 0xffff)\n"
		"\tmtc1 $1, $f2\n"
		"\tqmfc2.ni $4, $vf15\n"
		"\tmtc1 $4, $f1\n"
		"\tmul.s $f9, $f8, $f1\n"
		"\tsub.s $f11, $f2, $f9\n"
		"\tnop\n"
		"\tjr $31\n"
		"\tmul.s $f0, $f10, $f11\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(FastArcSin) : : : "memory");
}

float FastArcTan(float, float) __asm__("FastArcTan");
GAME_SECTION(FastArcTan) float FastArcTan(float, float)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlui $15, %%hi(ArcTanSeries)\n"
		"\taddiu $15, $15, %%lo(ArcTanSeries)\n"
		"\tlqc2 $vf15, 0x0($15)\n"
		"\tabs.s $f1, $f12\n"
		"\tabs.s $f2, $f13\n"
		"\tsub.s $f3, $f1, $f2\n"
		"\tmfc1 $3, $f3\n"
		"\tnop\n"
		"\tbltz $3, .L00453A20\n"
		"\tmtc1 $0, $f14\n"
		"\tabs.s $f1, $f13\n"
		"\tabs.s $f2, $f12\n"
		".L00453A20:\n"
		"\tc.le.s $f2, $f14\n"
		"\tsub.s $f3, $f1, $f2\n"
		"\tbc1t .L00453B00\n"
		"\tadd.s $f4, $f1, $f2\n"
		"\tnop\n"
		"\tnop\n"
		"\tdiv.s $f3, $f3, $f4\n"
		"\tmfc1 $1, $f12\n"
		"\tmfc1 $2, $f13\n"
		"\tlqc2 $vf16, 0x10($15)\n"
		"\tlui $4, %%hi(D_3D9EC0)\n"
		"\taddiu $4, $4, %%lo(D_3D9EC0)\n"
		"\tpref 0x00, 0x0($4)\n"
		"\tsrl $3, $3, 31\n"
		"\tsrl $2, $2, 31\n"
		"\tsrl $1, $1, 31\n"
		"\tsll $3, $3, 3\n"
		"\tsll $2, $2, 4\n"
		"\tsll $1, $1, 5\n"
		"\tadd $4, $4, $3\n"
		"\tadd $4, $4, $2\n"
		"\tadd $4, $4, $1\n"
		"\tmfc1 $1, $f3\n"
		"\tqmtc2.ni $1, $vf21\n"
		"\tlwc1 $f1, 0x0($4)\n"
		"\tlwc1 $f2, 0x4($4)\n"
		"\tvaddx.yz $vf21, $vf0, $vf21x\n"
		"\tvmulx.w $vf21, $vf0, $vf21x\n"
		"\tvmul.xyzw $vf22, $vf21, $vf21\n"
		"\tvaddw.xyz $vf25, $vf0, $vf0w\n"
		"\tvmul.xyzw $vf23, $vf22, $vf22\n"
		"\tvmul.y $vf21, $vf21, $vf22\n"
		"\tvmul.xyzw $vf24, $vf23, $vf23\n"
		"\tvmul.zw $vf21, $vf21, $vf23\n"
		"\tvmul.w $vf21, $vf21, $vf22\n"
		"\tvmul.xyzw $vf22, $vf21, $vf24\n"
		"\tvmul.xyzw $vf21, $vf21, $vf15\n"
		"\tvmul.xyzw $vf22, $vf22, $vf16\n"
		"\tvadday.x ACC, $vf21, $vf21y\n"
		"\tvmaddaz.x ACC, $vf25, $vf21z\n"
		"\tvmaddaw.x ACC, $vf25, $vf21w\n"
		"\tvmaddax.x ACC, $vf25, $vf22x\n"
		"\tvmadday.x ACC, $vf25, $vf22y\n"
		"\tvmaddaz.x ACC, $vf25, $vf22z\n"
		"\tvmaddw.x $vf21, $vf25, $vf22w\n"
		"\tlui $1, (0x3f490fdb >> 16)\n"
		"\tori $1, $1, (0x3f490fdb & 0xffff)\n"
		"\tmtc1 $1, $f3\n"
		"\tnop\n"
		"\tqmfc2.ni $1, $vf21\n"
		"\tmtc1 $1, $f4\n"
		"\tadd.s $f3, $f3, $f4\n"
		"\tmul.s $f3, $f3, $f1\n"
		"\tadd.s $f0, $f3, $f2\n"
		"\tjr $31\n"
		"\tnop\n"
		".L00453B00:\n"
		"\tjr $31\n"
		"\tmtc1 $0, $f0\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(FastArcTan) : : : "memory");
}

JUNK_ASM(func_00453B08,
	"\tsqc2 $vf15, 0x0($5)\n"
	"\tnop\n");

float FastAddRots(float, float) __asm__("FastAddRots");
GAME_SECTION(FastAddRots) float FastAddRots(float, float)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tadd.s $f0, $f12, $f13\n"
		"\tlui $1, (0x40490fdb >> 16)\n"
		"\tlui $2, (0xc0490fdb >> 16)\n"
		"\tori $1, $1, (0x40490fdb & 0xffff)\n"
		"\tori $2, $2, (0xc0490fdb & 0xffff)\n"
		"\tmtc1 $1, $f14\n"
		"\tc.lt.s $f0, $f14\n"
		"\tmtc1 $2, $f15\n"
		"\tbc1t .L00453B40\n"
		"\tc.lt.s $f0, $f15\n"
		"\tsub.s $f0, $f0, $f14\n"
		"\tsub.s $f0, $f0, $f14\n"
		".L00453B40:\n"
		"\tbc1f .L00453B50\n"
		"\tnop\n"
		"\tadd.s $f0, $f0, $f14\n"
		"\tadd.s $f0, $f0, $f14\n"
		".L00453B50:\n"
		".set at\n.set reorder" : : : "memory");
}

float FastSubRots(float, float) __asm__("FastSubRots");
GAME_SECTION(FastSubRots) float FastSubRots(float, float)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tsub.s $f0, $f12, $f13\n"
		"\tlui $1, (0x40490fdb >> 16)\n"
		"\tlui $2, (0xc0490fdb >> 16)\n"
		"\tori $1, $1, (0x40490fdb & 0xffff)\n"
		"\tori $2, $2, (0xc0490fdb & 0xffff)\n"
		"\tmtc1 $1, $f14\n"
		"\tc.lt.s $f0, $f14\n"
		"\tmtc1 $2, $f15\n"
		"\tbc1t .L00453B88\n"
		"\tc.lt.s $f0, $f15\n"
		"\tsub.s $f0, $f0, $f14\n"
		"\tsub.s $f0, $f0, $f14\n"
		".L00453B88:\n"
		"\tbc1f .L00453B98\n"
		"\tnop\n"
		"\tadd.s $f0, $f0, $f14\n"
		"\tadd.s $f0, $f0, $f14\n"
		".L00453B98:\n"
		".set at\n.set reorder" : : : "memory");
}

float FastWrapRot(float) __asm__("FastWrapRot");
GAME_SECTION(FastWrapRot) float FastWrapRot(float)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlui $1, (0x3e22f983 >> 16)\n"
		"\tori $1, $1, (0x3e22f983 & 0xffff)\n"
		"\tmtc1 $1, $f1\n"
		"\tlui $2, (0x3f000000 >> 16)\n"
		"\tmul.s $f12, $f12, $f1\n"
		"\tlui $1, (0x40c90fdb >> 16)\n"
		"\tmtc1 $2, $f2\n"
		"\tori $1, $1, (0x40c90fdb & 0xffff)\n"
		"\tadd.s $f12, $f12, $f2\n"
		"\tmtc1 $1, $f1\n"
		"\t.word 0x46006024 # cvt.w.s $f0, $f12 # 00000000 <InstrIdType: CPU_COP1_FPUS>\n"
		"\tmfc1 $1, $f12\n"
		"\tsra $1, $1, 31\n"
		"\tmfc1 $2, $f0\n"
		"\taddu $1, $1, $2\n"
		"\tnop\n"
		"\tmtc1 $1, $f0\n"
		"\tcvt.s.w $f0, $f0\n"
		"\tsub.s $f0, $f12, $f0\n"
		"\tsub.s $f0, $f0, $f2\n"
		"\tjr $31\n"
		"\tmul.s $f0, $f0, $f1\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(FastWrapRot) : : : "memory");
}

float FastDiffRots(float, float) __asm__("FastDiffRots");
GAME_SECTION(FastDiffRots) float FastDiffRots(float, float)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tsub.s $f0, $f12, $f13\n"
		"\tlui $1, (0x40490fdb >> 16)\n"
		"\tori $1, $1, (0x40490fdb & 0xffff)\n"
		"\tmtc1 $1, $f14\n"
		"\tnop\n"
		"\tabs.s $f0, $f0\n"
		"\tc.lt.s $f0, $f14\n"
		"\tnop\n"
		"\tbc1t .L00453C28\n"
		"\tnop\n"
		"\tadd.s $f1, $f14, $f14\n"
		"\tsub.s $f0, $f1, $f0\n"
		".L00453C28:\n"
		".set at\n.set reorder" : : : "memory");
}

int FastMod(float, float) __asm__("FastMod");
GAME_SECTION(FastMod) int FastMod(float, float)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tmfc1 $1, $f12\n"
		"\tmfc1 $2, $f13\n"
		"\tqmtc2.ni $1, $vf15\n"
		"\tqmtc2.ni $2, $vf16\n"
		"\tvdiv Q, $vf15x, $vf16x\n"
		"\tvwaitq\n"
		"\tvaddq.x $vf15, $vf0, Q\n"
		"\tvftoi0.x $vf17, $vf15\n"
		"\tvitof0.x $vf17, $vf17\n"
		"\tvsub.x $vf15, $vf15, $vf17\n"
		"\tvmul.x $vf15, $vf15, $vf16\n"
		"\tqmfc2.ni $1, $vf15\n"
		"\tjr $31\n"
		"\tmtc1 $1, $f0\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(FastMod) : : : "memory");
}

void FastTweenColor(int, int, float) __asm__("FastTweenColor");
GAME_SECTION(FastTweenColor) void FastTweenColor(int, int, float)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tpextlb $4, $0, $4\n"
		"\tmfc1 $1, $f12\n"
		"\tpextlh $4, $0, $4\n"
		"\tpextlb $5, $0, $5\n"
		"\tpextlh $5, $0, $5\n"
		"\tqmtc2.ni $1, $vf15\n"
		"\tqmtc2.ni $4, $vf16\n"
		"\tqmtc2.ni $5, $vf17\n"
		"\tvsubx.w $vf15, $vf0, $vf15x\n"
		"\tvitof0.xyzw $vf16, $vf16\n"
		"\tvitof0.xyzw $vf17, $vf17\n"
		"\tvmulaw.xyzw ACC, $vf16, $vf15w\n"
		"\tvmaddx.xyzw $vf15, $vf17, $vf15x\n"
		"\tvftoi0.xyzw $vf15, $vf15\n"
		"\tqmfc2.ni $2, $vf15\n"
		"\tppach $2, $0, $2\n"
		"\tjr $31\n"
		"\tppacb $2, $0, $2\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(FastTweenColor) : : : "memory");
}

void FastBsphereCheck(void *, float) __asm__("FastBsphereCheck");
GAME_SECTION(FastBsphereCheck) void FastBsphereCheck(void *, float)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlqc2 $vf15, 0x0($4)\n"
		"\tlui $1, %%hi(VC + 0x280)\n"
		"\taddiu $1, $1, %%lo(VC + 0x280)\n"
		"\tmfc1 $2, $f12\n"
		"\tlqc2 $vf24, 0x30($1)\n"
		"\tlqc2 $vf25, 0x0($1)\n"
		"\tlqc2 $vf26, 0x10($1)\n"
		"\tlqc2 $vf27, 0x20($1)\n"
		"\tvadd.x $vf19, $vf0, $vf0\n"
		"\tvmulw.xyzw $vf15, $vf15, $vf24w\n"
		"\tlqc2 $vf20, 0x40($1)\n"
		"\tlqc2 $vf21, 0x50($1)\n"
		"\tlqc2 $vf22, 0x60($1)\n"
		"\tlqc2 $vf23, 0x70($1)\n"
		"\tdsll32 $2, $2, 0\n"
		"\tnop\n"
		"\tvsub.xyz $vf16, $vf15, $vf24\n"
		"\tvaddw.x $vf17, $vf0, $vf15w\n"
		"\tqmtc2.ni $2, $vf18\n"
		"\tvsubw.y $vf17, $vf0, $vf15w\n"
		"\tvmulax.xyz ACC, $vf25, $vf16x\n"
		"\tvmadday.xyz ACC, $vf26, $vf16y\n"
		"\tvmaddz.xyz $vf16, $vf27, $vf16z\n"
		"\tvmulw.y $vf19, $vf18, $vf24w\n"
		"\tvmulw.xy $vf25, $vf22, $vf15w\n"
		"\tvaddz.xy $vf15, $vf17, $vf16z\n"
		"\tvmulz.xy $vf26, $vf20, $vf16z\n"
		"\tvabs.xy $vf16, $vf16\n"
		"\tvmulz.xy $vf27, $vf25, $vf22z\n"
		"\tvsub.xy $vf17, $vf19, $vf15\n"
		"\tvmul.xy $vf24, $vf26, $vf21\n"
		"\tvsub.xy $vf20, $vf16, $vf25\n"
		"\tvadd.xy $vf25, $vf16, $vf27\n"
		"\tvsub.xy $vf18, $vf15, $vf23\n"
		"\tqmfc2.ni $1, $vf17\n"
		"\tlui $5, (0x40000000 >> 16)\n"
		"\tvsub.xy $vf27, $vf26, $vf20\n"
		"\tnop\n"
		"\tvsub.xy $vf25, $vf24, $vf25\n"
		"\tdsll32 $2, $1, 0\n"
		"\tbltz $1, .L00453DA0\n"
		"\tqmfc2.ni $4, $vf18\n"
		"\tbgez $2, .L00453DA0\n"
		"\tnop\n"
		"\tqmfc2.ni $2, $vf27\n"
		"\tdaddu $5, $5, $5\n"
		"\tqmfc2.ni $3, $vf25\n"
		"\txor $4, $4, $5\n"
		"\tbltz $2, .L00453DA0\n"
		"\tdsll32 $2, $2, 0\n"
		"\tbltz $2, .L00453DA0\n"
		"\tor $3, $3, $4\n"
		"\tbltz $3, .L00453D98\n"
		"\tdsll32 $3, $3, 0\n"
		"\tbltz $3, .L00453D98\n"
		"\tnop\n"
		"\tjr $31\n"
		"\taddi $2, $0, 0x1\n"
		".L00453D98:\n"
		"\tjr $31\n"
		"\taddi $2, $0, 0x0\n"
		".L00453DA0:\n"
		"\tjr $31\n"
		"\taddi $2, $0, -0x1\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(FastBsphereCheck) : : : "memory");
}

void FastBsphereCheck___dupe2(void) __asm__("FastBsphereCheck___dupe2");
GAME_SECTION(FastBsphereCheck___dupe2) void FastBsphereCheck___dupe2(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlqc2 $vf15, 0x0($4)\n"
		"\tlui $1, %%hi(VC + 0x280)\n"
		"\taddiu $1, $1, %%lo(VC + 0x280)\n"
		"\tmfc1 $2, $f12\n"
		"\tlqc2 $vf24, 0x30($5)\n"
		"\tlqc2 $vf25, 0x0($5)\n"
		"\tlqc2 $vf26, 0x10($5)\n"
		"\tlqc2 $vf27, 0x20($5)\n"
		"\tlqc2 $vf20, 0x40($1)\n"
		"\tlqc2 $vf21, 0x50($1)\n"
		"\tlqc2 $vf22, 0x60($1)\n"
		"\tdsll32 $2, $2, 0\n"
		"\tlqc2 $vf23, 0x70($1)\n"
		"\tlui $3, (0x3a800000 >> 16)\n"
		"\tqmtc2.ni $3, $vf18\n"
		"\tvsub.xyz $vf16, $vf15, $vf24\n"
		"\tvaddw.x $vf17, $vf0, $vf15w\n"
		"\tvmulx.xy $vf23, $vf23, $vf18x\n"
		"\tqmtc2.ni $2, $vf19\n"
		"\tvsubw.y $vf17, $vf0, $vf15w\n"
		"\tvmulax.xyz ACC, $vf25, $vf16x\n"
		"\tvmadday.xyz ACC, $vf26, $vf16y\n"
		"\tvmaddz.xyz $vf16, $vf27, $vf16z\n"
		"\tnop\n"
		"\tvmulw.xy $vf25, $vf22, $vf15w\n"
		"\tvaddz.xy $vf15, $vf17, $vf16z\n"
		"\tvmulz.xy $vf26, $vf20, $vf16z\n"
		"\tvabs.xy $vf16, $vf16\n"
		"\tvmulz.xy $vf27, $vf25, $vf22z\n"
		"\tvsub.xy $vf17, $vf19, $vf15\n"
		"\tvmul.xy $vf24, $vf26, $vf21\n"
		"\tvsub.xy $vf20, $vf16, $vf25\n"
		"\tqmfc2.ni $2, $vf16\n"
		"\tlui $5, (0x40000000 >> 16)\n"
		"\tvadd.xy $vf25, $vf16, $vf27\n"
		"\tvsub.xy $vf18, $vf15, $vf23\n"
		"\tqmfc2.ni $1, $vf17\n"
		"\tpcpyud $2, $2, $0\n"
		"\tvsub.xy $vf27, $vf26, $vf20\n"
		"\tsw $2, 0x0($6)\n"
		"\tvsub.xy $vf25, $vf24, $vf25\n"
		"\tdsll32 $2, $1, 0\n"
		"\tbltz $1, .L00453EA0\n"
		"\tqmfc2.ni $4, $vf18\n"
		"\tbgez $2, .L00453EA0\n"
		"\tnop\n"
		"\tqmfc2.ni $2, $vf27\n"
		"\tdaddu $5, $5, $5\n"
		"\tqmfc2.ni $3, $vf25\n"
		"\txor $4, $4, $5\n"
		"\tbltz $2, .L00453EA0\n"
		"\tdsll32 $2, $2, 0\n"
		"\tbltz $2, .L00453EA0\n"
		"\tor $3, $3, $4\n"
		"\tbltz $3, .L00453E98\n"
		"\tdsll32 $3, $3, 0\n"
		"\tbltz $3, .L00453E98\n"
		"\tnop\n"
		"\tjr $31\n"
		"\taddi $2, $0, 0x1\n"
		".L00453E98:\n"
		"\tjr $31\n"
		"\taddi $2, $0, 0x0\n"
		".L00453EA0:\n"
		"\tjr $31\n"
		"\taddi $2, $0, -0x1\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(FastBsphereCheck___dupe2) : : : "memory");
}

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

void FastPointInCuboid(void *, void *, void *) __asm__("FastPointInCuboid");
GAME_SECTION(FastPointInCuboid) void FastPointInCuboid(void *, void *, void *)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlqc2 $vf24, 0x30($4)\n"
		"\tnop\n"
		"\tlqc2 $vf25, 0x0($5)\n"
		"\tnop\n"
		"\tvsub.xyzw $vf26, $vf25, $vf24\n"
		"\tnop\n"
		"\tlqc2 $vf21, 0x40($4)\n"
		"\tnop\n"
		"\tlqc2 $vf22, 0x50($4)\n"
		"\tnop\n"
		"\tlqc2 $vf23, 0x60($4)\n"
		"\tnop\n"
		"\tvmulax.xyzw ACC, $vf21, $vf26x\n"
		"\tctc2.ni $0, $vi18\n"
		"\tvmadday.xyzw ACC, $vf22, $vf26y\n"
		"\tnop\n"
		"\tvmaddz.xyzw $vf27, $vf23, $vf26z\n"
		"\tnop\n"
		"\tnop\n"
		"\tnop\n"
		"\tnop\n"
		"\tnop\n"
		"\tnop\n"
		"\tnop\n"
		"\tvclipw.xyz $vf27, $vf0w\n"
		"\tnop\n"
		"\tbgtzl $6, .L00453F60\n"
		"\tsqc2 $vf27, 0x0($6)\n"
		".L00453F60:\n"
		"\tnop\n"
		"\tnop\n"
		"\tnop\n"
		"\tnop\n"
		"\tnop\n"
		"\tnop\n"
		"\tcfc2.ni $8, $vi18\n"
		"\tadd $2, $0, $0\n"
		"\tbeql $8, $0, .L00453F88\n"
		"\tori $2, $2, 0x1\n"
		".L00453F88:\n"
		".set at\n.set reorder" : : : "memory");
}
