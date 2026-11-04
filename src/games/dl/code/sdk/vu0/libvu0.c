#include "common.h"

/* D18: hand-written VU0 routines, essentially all asm. Recovered from the retail boot instructions; no vendor source. */
#define VU0_SECTION(name) __attribute__((section(".vu0_" #name)))

/* _sceVu0ecossin is not recovered and stays in its own slot. */
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
	__asm__(".section .vu0_" #NAME ",\"ax\",@progbits\n" \
		".set noat\n.set noreorder\n" \
		".include \"" FOLDER "/" #NAME ".s\"\n" \
		".set reorder\n.set at\n.text\n")
#endif

#define VU0_ROT_HEAD \
	".set noreorder\n.set noat\n" \
	"\tmtc1 $0, $f0\n" \
	"\tc.lt.s $f12, $f0\n" \
	"\tlui $1, 0x3fc9\n" \
	"\tori $1, $1, 0x0fdb\n" \
	"\tmtc1 $1, $f0\n" \
	"\tbc1f 1f\n" \
	"\tnop\n" \
	"\tadd.s $f12, $f0, $f12\n" \
	"\tj 2f\n" \
	"\taddiu $7, $0, 1\n" \
	"1:\n" \
	"\tsub.s $f12, $f0, $f12\n" \
	"\tdaddu $7, $0, $0\n" \
	"2:\n" \
	"\tmfc1 $8, $f12\n" \
	"\tqmtc2.ni $8, $vf6\n" \
	"\tdaddu $6, $31, $0\n" \
	"\tjal _sceVu0ecossin\n" \
	"\tnop\n" \
	"\tdaddu $31, $6, $0\n"
#define VU0_ROT_TAIL \
	"\taddiu $7, $0, 4\n" \
	"3:\n" \
	"\tlqc2 $vf4, 0x0($5)\n" \
	"\tvmulax.xyzw ACC, $vf6, $vf4x\n" \
	"\tvmadday.xyzw ACC, $vf7, $vf4y\n" \
	"\tvmaddaz.xyzw ACC, $vf8, $vf4z\n" \
	"\tvmaddw.xyzw $vf5, $vf9, $vf4w\n" \
	"\tsqc2 $vf5, 0x0($4)\n" \
	"\taddi $7, $7, -1\n" \
	"\taddi $5, $5, 0x10\n" \
	"\tbne $0, $7, 3b\n" \
	"\taddi $4, $4, 0x10\n" \
	".set at\n.set reorder"
#define VU0_ROT_TAIL \
	"\taddiu $7, $0, 4\n" \
	"3:\n" \
	"\tlqc2 $vf4, 0x0($5)\n" \
	"\tvmulax.xyzw ACC, $vf6, $vf4x\n" \
	"\tvmadday.xyzw ACC, $vf7, $vf4y\n" \
	"\tvmaddaz.xyzw ACC, $vf8, $vf4z\n" \
	"\tvmaddw.xyzw $vf5, $vf9, $vf4w\n" \
	"\tsqc2 $vf5, 0x0($4)\n" \
	"\taddi $7, $7, -1\n" \
	"\taddi $5, $5, 0x10\n" \
	"\tbne $0, $7, 3b\n" \
	"\taddi $4, $4, 0x10\n" \
	".set at\n.set reorder"

void VU0_SECTION(sceVu0UnitMatrix) sceVu0UnitMatrix(void *m)
{
	__asm__ volatile(
		"\tvsub.xyzw $vf4, $vf0, $vf0\n"
		"\tvadd.w $vf4, $vf4, $vf0\n"
		"\tvmr32.xyzw $vf5, $vf4\n"
		"\tvmr32.xyzw $vf6, $vf5\n"
		"\tvmr32.xyzw $vf7, $vf6\n"
		"\tsqc2 $vf4, 0x30(%0)\n"
		"\tsqc2 $vf5, 0x20(%0)\n"
		"\tsqc2 $vf6, 0x10(%0)\n"
		"\tsqc2 $vf7, 0x0(%0)"
		: : "r"(m) : "memory");
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/vu0/libvu0", _sceVu0ecossin);

void VU0_SECTION(sceVu0RotMatrixZ) sceVu0RotMatrixZ(void *m0, void *m1, float rz)
{
	__asm__ volatile(VU0_ROT_HEAD
		"\tvmove.xyzw $vf6, $vf5\n"
		"\tvmove.xyzw $vf7, $vf5\n"
		"\tvmove.xyzw $vf9, $vf0\n"
		"\tvsub.xyz $vf9, $vf9, $vf9\n"
		"\tvmr32.xyzw $vf8, $vf9\n"
		"\tvsub.zw $vf4, $vf4, $vf4\n"
		"\tvaddx.y $vf6, $vf5, $vf4x\n"
		"\tvaddy.x $vf6, $vf5, $vf4y\n"
		"\tvsubx.x $vf7, $vf5, $vf4x\n"
		"\tvaddy.y $vf7, $vf5, $vf4y\n"
		VU0_ROT_TAIL);
}

void VU0_SECTION(sceVu0RotMatrixX) sceVu0RotMatrixX(void *m0, void *m1, float rx)
{
	__asm__ volatile(VU0_ROT_HEAD
		"\tvmove.xyzw $vf6, $vf5\n"
		"\tvmove.xyzw $vf7, $vf5\n"
		"\tvmove.xyzw $vf8, $vf5\n"
		"\tvmove.xyzw $vf9, $vf5\n"
		"\tvaddw.x $vf6, $vf5, $vf0w\n"
		"\tvaddw.w $vf9, $vf5, $vf0w\n"
		"\tvsub.zw $vf4, $vf4, $vf4\n"
		"\tvaddx.z $vf7, $vf5, $vf4x\n"
		"\tvaddy.y $vf7, $vf5, $vf4y\n"
		"\tvsubx.y $vf8, $vf5, $vf4x\n"
		"\tvaddy.z $vf8, $vf5, $vf4y\n"
		VU0_ROT_TAIL);
}

void VU0_SECTION(sceVu0RotMatrixY) sceVu0RotMatrixY(void *m0, void *m1, float ry)
{
	__asm__ volatile(VU0_ROT_HEAD
		"\tvmove.xyzw $vf6, $vf5\n"
		"\tvmove.xyzw $vf7, $vf5\n"
		"\tvmove.xyzw $vf8, $vf5\n"
		"\tvmove.xyzw $vf9, $vf5\n"
		"\tvaddw.y $vf7, $vf5, $vf0w\n"
		"\tvaddw.w $vf9, $vf5, $vf0w\n"
		"\tvsub.zw $vf4, $vf4, $vf4\n"
		"\tvsubx.z $vf6, $vf5, $vf4x\n"
		"\tvaddy.x $vf6, $vf5, $vf4y\n"
		"\tvaddx.x $vf8, $vf5, $vf4x\n"
		"\tvaddy.z $vf8, $vf5, $vf4y\n"
		VU0_ROT_TAIL);
}

