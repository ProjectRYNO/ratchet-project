#include "common.h"
#include "game_section.h"
#include "game_vu0.h"
#include "mobyutil.h"



struct FXU_CubicPoint {
	/* 0x00 */ char unk00[9];
	/* 0x09 */ unsigned char style;
	/* 0x0a */ unsigned char count;
	/* 0x0b */ unsigned char bDisabled;
	/* 0x0c */ int iNumSkipPoints;
	/* 0x10 */ vec4 pos;
	/* 0x20 */ vec4 vTangent;
	/* 0x30 */ vec4 vTangentOccQuat;
};
struct FXU_CubicLineSet_t {
	/* 0x00 */ int unk00[4];
	/* 0x10 */ FXU_CubicPoint *lines[0x20];
	/* 0x90 */ float fFadeTypeScale;
	/* 0x94 */ float fFadeScale;
	/* 0x98 */ float fFadeShift;
	/* 0x9c */ float fFadeMinValue;
	/* 0xa0 */ float fFadeMaxValue;
	/* 0xa4 */ int count;
	/* 0xa8 */ int iSetInitFrame;
	/* 0xac */ int bDeactivating;
	/* 0xb0 */ int iMinStartSkipPoints;
	/* 0xb4 */ int iMaxStartSkipPoints;
	/* 0xb8 */ int iMinEndSkipPoints;
	/* 0xbc */ int iMaxEndSkipPoints;
};
void CubicLineSet_SetEndPointPos(void *, FXU_CubicLineSet_t &, int, vec4 &) __asm__("CubicLineSet_SetEndPointPos");
void CubicLineSet_SetStyle(void *, FXU_CubicLineSet_t &, void *, int) __asm__("CubicLineSet_SetStyle");
struct MobyAttachInterface {
	/* 0x00 */ int (*attach)(void *, vec4 &, vec4 &, int, int, int);
};
MobyAttachInterface *MobyGetInterface(int, int, int) __asm__("MobyGetInterface___dupe2");
int AttachPointToJoint(void *, void *, vec4 &, vec4 &, unsigned char, short, int) __asm__("AttachPointToJoint");


extern int worldUpdateTime __asm__("worldUpdateTime");
void CubicLine_Init(void *, FXU_CubicPoint *, int, void *, int) __asm__("CubicLine_Init");
void CubicLine_Draw(void *, FXU_CubicPoint *, int, void *, float) __asm__("CubicLine_Draw");
float CalcCycleFade(void *, float, int) __asm__("CalcCycleFade");
void CubicLineSet_Init(void *, FXU_CubicLineSet_t &, int, void *, int, bool) __asm__("CubicLineSet_Init");
void CubicLineSet_Draw(void *, FXU_CubicLineSet_t &, void *) __asm__("CubicLineSet_Draw");
int MB_randRangeInt(int, int) __asm__("MB_randRangeInt");
void CubicLine_Update(void *, FXU_CubicPoint *, int) __asm__("CubicLine_Update");
void CubicLineSet_Update(void *, FXU_CubicLineSet_t &, void *) __asm__("CubicLineSet_Update");

int FastTweenColor(int, int, float) __asm__("FastTweenColor");
float MB_randRange(float, float) __asm__("MB_randRange");
void CubicLineSet_InitAsLightning(void *, FXU_CubicLineSet_t &, int, int, int, int, int) __asm__("CubicLineSet_InitAsLightning");
float FastSin(float) __asm__("FastSin");
float FastCos(float) __asm__("FastCos");


GAME_SECTION(CalcCycleFade) float CalcCycleFade(void *self, float fCycleFrac, int fadeType)
{
	float fAlpha = 0.0f;

	if (fCycleFrac < 0.0f || 1.0f < fCycleFrac) {
		fCycleFrac -= (float)(int)fCycleFrac;
		if (fCycleFrac < 0.0f) {
			fCycleFrac += 1.0f;
		}
	}
	switch (fadeType) {
	case 0:
		fAlpha = 1.0f;
		break;
	case 1:
		fAlpha = fCycleFrac;
		break;
	case 2:
		fAlpha = 1.0f - fCycleFrac;
		break;
	case 3:
		fAlpha = FastSin((fCycleFrac - 0.5f) * 2.0f * 3.1415927f) * 0.5f + 0.5f;
		break;
	case 4:
		fAlpha = FastCos((fCycleFrac - 0.5f) * 2.0f * 3.1415927f) * 0.5f + 0.5f;
		break;
	case 5:
		if (fCycleFrac < 0.5f) {
			fAlpha = 1.0f;
		} else {
			fAlpha = 0.0f;
		}
		break;
	case 6:
		if (fCycleFrac < 0.5f) {
			fAlpha = fCycleFrac * 2.0f;
		} else {
			fAlpha = (0.5f - (fCycleFrac - 0.5f)) * 2.0f;
		}
		break;
	case 7:
		if (0.5f < fCycleFrac) {
			fAlpha = 0.0f;
		} else if (fCycleFrac < 0.25f) {
			fAlpha = fCycleFrac * 4.0f;
		} else {
			fAlpha = (0.25f - (fCycleFrac - 0.25f)) * 4.0f;
		}
		break;
	case 8:
		if (fCycleFrac < 0.5f) {
			fAlpha = 0.0f;
		} else if (fCycleFrac < 0.75f) {
			fAlpha = (fCycleFrac - 0.5f) * 4.0f;
		} else {
			fAlpha = (0.25f - (fCycleFrac - 0.75f)) * 4.0f;
		}
		break;
	}
	return fAlpha;
}

JUNK_ASM(func_0044F930,
	"\taddiu $29, $29, 0x80\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", DrawShellEdgeFaded);

JUNK_ASM(func_00450210,
	"\taddiu $29, $29, 0xe0\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x230\n"
	"\tnop\n");

void DrawAlphaMaskPoly(void) __asm__("DrawAlphaMaskPoly");
GAME_SECTION(DrawAlphaMaskPoly) void DrawAlphaMaskPoly(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\taddiu $29, $29, -0x2b0\n"
		"\tlui $2, %%hi(Camera)\n"
		"\tsd $17, 0x240($29)\n"
		"\taddiu $2, $2, %%lo(Camera)\n"
		"\tsd $18, 0x248($29)\n"
		"\tvmaxw.xyzw $vf3, $vf0, $vf0w\n"
		"\tsd $19, 0x250($29)\n"
		"\tvmove.xyzw $vf5, $vf3\n"
		"\tsd $20, 0x258($29)\n"
		"\tdaddu $18, $6, $0\n"
		"\tswc1 $f24, 0x2a0($29)\n"
		"\tdaddu $20, $7, $0\n"
		"\tswc1 $f23, 0x298($29)\n"
		"\tdaddu $17, $8, $0\n"
		"\tswc1 $f22, 0x290($29)\n"
		"\tmov.s $f23, $f12\n"
		"\tswc1 $f21, 0x288($29)\n"
		"\tmov.s $f22, $f13\n"
		"\tswc1 $f20, 0x280($29)\n"
		"\tmov.s $f24, $f16\n"
		"\tsq $16, 0x230($29)\n"
		"\tmov.s $f20, $f15\n"
		"\tsd $21, 0x260($29)\n"
		"\tmov.s $f21, $f17\n"
		"\tsd $22, 0x268($29)\n"
		"\tdaddu $19, $9, $0\n"
		"\tsd $31, 0x270($29)\n"
		"\taddiu $3, $29, 0x160\n"
		"\tlqc2 $vf1, 0x0($2)\n"
		"\tlqc2 $vf6, 0x0($5)\n"
		"\tvsub.xyz $vf1, $vf1, $vf6\n"
		"\tlqc2 $vf4, 0x40($2)\n"
		"\tvmul.xyzw $vf2, $vf1, $vf1\n"
		"\tsqc2 $vf1, 0x160($29)\n"
		"\tvadday.x ACC, $vf2, $vf2y\n"
		"\tvmaddz.x $vf3, $vf3, $vf2z\n"
		"\tqmfc2.ni $2, $vf3\n"
		"\tnop\n"
		"\tnop\n"
		"\tvrsqrt Q, $vf0w, $vf3x\n"
		"\tbeqz $2, .L004502DC\n"
		"\tsqc2 $vf3, 0x70($29)\n"
		"\tvwaitq\n"
		"\tlqc2 $vf1, 0x0($3)\n"
		"\tvmulq.xyz $vf1, $vf1, Q\n"
		"\tb .L004502E8\n"
		"\tsqc2 $vf1, 0x0($3)\n"
		".L004502DC:\n"
		"\tvsub.xyz $vf1, $vf0, $vf0\n"
		"\tsqc2 $vf1, 0x160($29)\n"
		"\tsqc2 $vf1, 0x80($29)\n"
		".L004502E8:\n"
		"\tlqc2 $vf3, 0x160($29)\n"
		"\taddiu $3, $29, 0x170\n"
		"\tvopmula.xyz ACC, $vf4, $vf3\n"
		"\tvmove.xyzw $vf1, $vf3\n"
		"\tvopmsub.xyz $vf1, $vf1, $vf4\n"
		"\tvmul.xyzw $vf2, $vf1, $vf1\n"
		"\tsqc2 $vf1, 0x170($29)\n"
		"\tvadday.x ACC, $vf2, $vf2y\n"
		"\tvmaddz.x $vf2, $vf5, $vf2z\n"
		"\tqmfc2.ni $2, $vf2\n"
		"\tsqc2 $vf2, 0x70($29)\n"
		"\tnop\n"
		"\tnop\n"
		"\tvrsqrt Q, $vf0w, $vf2x\n"
		"\tbeqz $2, .L0045033C\n"
		"\tnop\n"
		"\tvwaitq\n"
		"\tlqc2 $vf1, 0x0($3)\n"
		"\tvmulq.xyz $vf1, $vf1, Q\n"
		"\tb .L00450348\n"
		"\tsqc2 $vf1, 0x0($3)\n"
		".L0045033C:\n"
		"\tvsub.xyz $vf1, $vf0, $vf0\n"
		"\tsqc2 $vf1, 0x170($29)\n"
		"\tsqc2 $vf1, 0x80($29)\n"
		".L00450348:\n"
		"\tlqc2 $vf1, 0x170($29)\n"
		"\tdaddu $4, $29, $0\n"
		"\tvopmula.xyz ACC, $vf3, $vf1\n"
		"\tlui $1, (0xbec90fdb >> 16)\n"
		"\tori $1, $1, (0xbec90fdb & 0xffff)\n"
		"\tmtc1 $1, $f12\n"
		"\tsqc2 $vf3, 0x30($29)\n"
		"\tsqc2 $vf1, 0x40($29)\n"
		"\tvopmsub.xyz $vf1, $vf1, $vf3\n"
		"\tsqc2 $vf6, 0x60($29)\n"
		"\tjal SetRotX___dupe2\n"
		"\tsqc2 $vf1, 0x50($29)\n"
		"\tmtc1 $0, $f0\n"
		"\tnop\n"
		"\tc.eq.s $f20, $f0\n"
		"\tnop\n"
		"\tbc1t .L00450430\n"
		"\tdaddu $3, $0, $0\n"
		"\tlui $1, (0x3f000000 >> 16)\n"
		"\tmtc1 $1, $f0\n"
		"\tvsub.xyzw $vf1, $vf0, $vf0\n"
		"\tlqc2 $vf3, 0x30($29)\n"
		"\tmul.s $f0, $f20, $f0\n"
		"\tlqc2 $vf4, 0x40($29)\n"
		"\tmfc1 $2, $f0\n"
		"\tlqc2 $vf2, 0x50($29)\n"
		"\tqmtc2.ni $2, $vf15\n"
		"\tsqc2 $vf0, 0xc0($29)\n"
		"\tvcallms 0xc60\n"
		"\tbeqz $3, .L004503DC\n"
		"\taddi $4, $3, -0x1\n"
		"\tbeqz $4, .L004503D4\n"
		"\tnop\n"
		"\tb .L004503E0\n"
		"\tvaddx.z $vf1, $vf1, $vf15x\n"
		".L004503D4:\n"
		"\tb .L004503E0\n"
		"\tvaddx.y $vf1, $vf1, $vf15x\n"
		".L004503DC:\n"
		"\tvaddx.x $vf1, $vf1, $vf15x\n"
		".L004503E0:\n"
		"\tvsuby.w $vf1, $vf1, $vf15y\n"
		"\tvmove.xyzw $vf15, $vf1\n"
		"\tqmtc2.ni $4, $vf21\n"
		"\tvcallms 0xd28\n"
		"\tvnop\n"
		"\tvmulax.xyzw ACC, $vf3, $vf27x\n"
		"\tsqc2 $vf27, 0x90($29)\n"
		"\tvmadday.xyzw ACC, $vf4, $vf27y\n"
		"\tsqc2 $vf28, 0xa0($29)\n"
		"\tvmaddz.xyzw $vf1, $vf2, $vf27z\n"
		"\tsqc2 $vf29, 0xb0($29)\n"
		"\tvmulax.xyzw ACC, $vf3, $vf28x\n"
		"\tsqc2 $vf1, 0x30($29)\n"
		"\tvmadday.xyzw ACC, $vf4, $vf28y\n"
		"\tvmaddz.xyzw $vf1, $vf2, $vf28z\n"
		"\tvmulax.xyzw ACC, $vf3, $vf29x\n"
		"\tsqc2 $vf1, 0x40($29)\n"
		"\tvmadday.xyzw ACC, $vf4, $vf29y\n"
		"\tvmaddz.xyzw $vf2, $vf2, $vf29z\n"
		"\tsqc2 $vf2, 0x50($29)\n"
		".L00450430:\n"
		"\tlui $1, (0x3f800000 >> 16)\n"
		"\tmtc1 $1, $f0\n"
		"\tmov.s $f12, $f24\n"
		"\tmfc1 $6, $f21\n"
		"\tnop\n"
		"\tnop\n"
		"\tdiv.s $f0, $f0, $f22\n"
		"\tdaddu $2, $6, $0\n"
		"\tlui $1, (0x3f000000 >> 16)\n"
		"\tmtc1 $1, $f1\n"
		"\tqmtc2.ni $2, $vf2\n"
		"\tmfc1 $7, $f23\n"
		"\tlui $3, (0x3f800000 >> 16)\n"
		"\tlui $2, (0x3f800000 >> 16)\n"
		"\tpextlw $4, $3, $2\n"
		"\tdaddu $7, $7, $0\n"
		"\tlui $3, (0xbf800000 >> 16)\n"
		"\tlui $2, (0x3f800000 >> 16)\n"
		"\tpextlw $16, $3, $2\n"
		"\tqmtc2.ni $7, $vf5\n"
		"\tpcpyld $16, $4, $16\n"
		"\taddiu $7, $0, 0x0\n"
		"\taddiu $6, $0, 0x0\n"
		"\tpextlw $5, $7, $6\n"
		"\tlqc2 $vf1, 0x30($29)\n"
		"\tmul.s $f0, $f0, $f1\n"
		"\tlui $6, (0x3f000000 >> 16)\n"
		"\taddiu $2, $0, 0x0\n"
		"\tpextlw $3, $6, $2\n"
		"\tvmulx.xyz $vf1, $vf1, $vf2x\n"
		"\tlqc2 $vf3, 0x40($29)\n"
		"\tlqc2 $vf2, 0x60($29)\n"
		"\tvmulx.xyz $vf3, $vf3, $vf5x\n"
		"\tmfc1 $2, $f0\n"
		"\tvadd.xyz $vf2, $vf2, $vf1\n"
		"\tdaddu $2, $2, $0\n"
		"\tlqc2 $vf4, 0x50($29)\n"
		"\tsq $2, 0x200($29)\n"
		"\tvmulx.xyz $vf4, $vf4, $vf5x\n"
		"\tlui $7, (0x3f800000 >> 16)\n"
		"\tlui $6, (0x3f000000 >> 16)\n"
		"\tpextlw $2, $7, $6\n"
		"\tsqc2 $vf2, 0x60($29)\n"
		"\tpcpyld $7, $4, $5\n"
		"\tpcpyld $6, $2, $3\n"
		"\tqmtc2.ni $6, $vf11\n"
		"\taddiu $4, $29, 0x70\n"
		"\tqmtc2.ni $7, $vf8\n"
		"\tsqc2 $vf3, 0x40($29)\n"
		"\tsqc2 $vf4, 0x50($29)\n"
		"\tsqc2 $vf8, 0x210($29)\n"
		"\tjal SetRotX\n"
		"\tsqc2 $vf11, 0x220($29)\n"
		"\tlqc2 $vf8, 0x210($29)\n"
		"\tlui $2, (0x80808080 >> 16)\n"
		"\tlqc2 $vf1, 0x30($29)\n"
		"\tori $2, $2, (0x80808080 & 0xffff)\n"
		"\tlqc2 $vf2, 0x40($29)\n"
		"\tvmulax.xyzw ACC, $vf1, $vf8x\n"
		"\tlqc2 $vf11, 0x220($29)\n"
		"\tvmadday.xyzw ACC, $vf2, $vf8y\n"
		"\tlqc2 $vf3, 0x50($29)\n"
		"\tlui $5, (0x80808080 >> 16)\n"
		"\tlqc2 $vf5, 0x60($29)\n"
		"\tvmaddaz.xyzw ACC, $vf3, $vf8z\n"
		"\tlqc2 $vf10, 0x200($29)\n"
		"\tvmaddw.xyzw $vf6, $vf5, $vf8w\n"
		"\tlui $4, %%hi(FXReg)\n"
		"\tlw $4, %%lo(FXReg)($4)\n"
		"\tvmove.xyzw $vf4, $vf8\n"
		"\tlui $6, %%hi(D_221278)\n"
		"\tlw $6, %%lo(D_221278)($6)\n"
		"\tvmulx.xyz $vf4, $vf4, $vf10x\n"
		"\tlui $3, %%hi(D_221274)\n"
		"\tlw $3, %%lo(D_221274)($3)\n"
		"\tqmtc2.ni $16, $vf12\n"
		"\tsqc2 $vf11, 0xa0($29)\n"
		"\taddiu $8, $6, 0x100\n"
		"\tsqc2 $vf1, 0xd0($29)\n"
		"\taddiu $7, $3, 0x80\n"
		"\tsqc2 $vf2, 0xe0($29)\n"
		"\taddiu $12, $29, 0x1a0\n"
		"\tsqc2 $vf3, 0xf0($29)\n"
		"\taddiu $11, $29, 0x1b0\n"
		"\tsqc2 $vf5, 0x100($29)\n"
		"\taddiu $10, $29, 0x1c0\n"
		"\tsqc2 $vf6, 0x150($29)\n"
		"\taddiu $9, $29, 0x1d0\n"
		"\tsqc2 $vf6, 0x0($4)\n"
		"\taddiu $13, $29, 0x1e0\n"
		"\tvmove.xyzw $vf1, $vf4\n"
		"\tsw $2, 0x0($3)\n"
		"\tsw $17, 0x80($3)\n"
		"\tvadd.xyz $vf1, $vf1, $vf11\n"
		"\tsqc2 $vf1, 0x180($29)\n"
		"\taddiu $14, $29, 0x1f0\n"
		"\tldl $15, 0x18b($29)\n"
		"\tldr $15, 0x184($29)\n"
		"\tsdl $15, 0x7($6)\n"
		"\tsdr $15, 0x0($6)\n"
		"\tvmove.xyzw $vf9, $vf11\n"
		"\taddiu $4, $4, 0x10\n"
		"\taddiu $8, $8, 0x8\n"
		"\tlqc2 $vf1, 0x70($29)\n"
		"\taddiu $3, $3, 0x4\n"
		"\tlqc2 $vf2, 0x80($29)\n"
		"\tvmulax.xyzw ACC, $vf1, $vf4x\n"
		"\tvmadday.xyzw ACC, $vf2, $vf4y\n"
		"\tlqc2 $vf3, 0x90($29)\n"
		"\tvmaddaz.xyzw ACC, $vf3, $vf4z\n"
		"\tlqc2 $vf1, 0xa0($29)\n"
		"\tvmaddw.xyzw $vf1, $vf1, $vf4w\n"
		"\taddiu $7, $7, 0x4\n"
		"\tsqc2 $vf1, 0x190($29)\n"
		"\tori $5, $5, (0x80808080 & 0xffff)\n"
		"\tsqc2 $vf1, 0xb0($29)\n"
		"\taddiu $2, $0, 0x6\n"
		"\tldl $15, 0x19b($29)\n"
		"\tldr $15, 0x194($29)\n"
		"\tsdl $15, 0x107($6)\n"
		"\tsdr $15, 0x100($6)\n"
		"\taddiu $6, $6, 0x8\n"
		"\tlqc2 $vf1, 0x0($29)\n"
		"\tvmulax.xyzw ACC, $vf1, $vf8x\n"
		"\tlqc2 $vf2, 0x10($29)\n"
		"\tvmadday.xyzw ACC, $vf2, $vf8y\n"
		"\tlqc2 $vf1, 0x20($29)\n"
		"\tvmaddaz.xyzw ACC, $vf1, $vf8z\n"
		"\tvmaddw.xyzw $vf8, $vf0, $vf8w\n"
		"\tlqc2 $vf5, 0x30($29)\n"
		".L00450638:\n"
		"\taddiu $2, $2, -0x1\n"
		"\tlqc2 $vf1, 0x40($29)\n"
		"\tvmulax.xyzw ACC, $vf5, $vf8x\n"
		"\tlqc2 $vf2, 0x50($29)\n"
		"\tvmadday.xyzw ACC, $vf1, $vf8y\n"
		"\tlqc2 $vf3, 0x60($29)\n"
		"\tvmaddaz.xyzw ACC, $vf2, $vf8z\n"
		"\tvmaddw.xyzw $vf6, $vf3, $vf8w\n"
		"\tsqc2 $vf5, 0xb0($29)\n"
		"\tsqc2 $vf1, 0xc0($29)\n"
		"\tsqc2 $vf2, 0xd0($29)\n"
		"\tsqc2 $vf3, 0xe0($29)\n"
		"\tsqc2 $vf6, 0x130($29)\n"
		"\tvmove.xyzw $vf4, $vf8\n"
		"\tsqc2 $vf6, 0x0($4)\n"
		"\tvmulx.xyz $vf4, $vf4, $vf10x\n"
		"\tsw $5, 0x0($3)\n"
		"\tvmove.xyzw $vf1, $vf4\n"
		"\tsw $17, 0x0($7)\n"
		"\tvadd.xyz $vf1, $vf1, $vf9\n"
		"\tsqc2 $vf1, 0x1a0($29)\n"
		"\taddiu $4, $4, 0x10\n"
		"\tldl $15, 0xb($12)\n"
		"\tldr $15, 0x4($12)\n"
		"\tsdl $15, 0x7($6)\n"
		"\tsdr $15, 0x0($6)\n"
		"\tvmove.xyzw $vf3, $vf8\n"
		"\tvmul.xyz $vf3, $vf3, $vf12\n"
		"\taddiu $3, $3, 0x4\n"
		"\tlqc2 $vf2, 0x70($29)\n"
		"\taddiu $7, $7, 0x4\n"
		"\tlqc2 $vf1, 0x80($29)\n"
		"\tvmulax.xyzw ACC, $vf2, $vf4x\n"
		"\tlqc2 $vf2, 0x90($29)\n"
		"\tvmadday.xyzw ACC, $vf1, $vf4y\n"
		"\tvmaddaz.xyzw ACC, $vf2, $vf4z\n"
		"\tlqc2 $vf1, 0xa0($29)\n"
		"\tvmaddw.xyzw $vf1, $vf1, $vf4w\n"
		"\tvmove.xyzw $vf6, $vf3\n"
		"\tsqc2 $vf1, 0xb0($29)\n"
		"\tvmulx.xyz $vf6, $vf6, $vf10x\n"
		"\tsqc2 $vf1, 0x1b0($29)\n"
		"\taddiu $6, $6, 0x8\n"
		"\tldl $15, 0xb($11)\n"
		"\tldr $15, 0x4($11)\n"
		"\tsdl $15, 0x7($8)\n"
		"\tsdr $15, 0x0($8)\n"
		"\tvmove.xyzw $vf7, $vf6\n"
		"\tvadd.xyz $vf7, $vf7, $vf9\n"
		"\taddiu $8, $8, 0x8\n"
		"\tlqc2 $vf5, 0x30($29)\n"
		"\tlqc2 $vf4, 0x40($29)\n"
		"\tvmulax.xyzw ACC, $vf5, $vf3x\n"
		"\tlqc2 $vf2, 0x50($29)\n"
		"\tvmadday.xyzw ACC, $vf4, $vf3y\n"
		"\tlqc2 $vf1, 0x60($29)\n"
		"\tvmaddaz.xyzw ACC, $vf2, $vf3z\n"
		"\tvmaddw.xyzw $vf3, $vf1, $vf3w\n"
		"\tsqc2 $vf5, 0xb0($29)\n"
		"\tsqc2 $vf2, 0xd0($29)\n"
		"\tsqc2 $vf1, 0xe0($29)\n"
		"\tsqc2 $vf3, 0x130($29)\n"
		"\tsqc2 $vf4, 0xc0($29)\n"
		"\tsqc2 $vf3, 0x0($4)\n"
		"\tsw $5, 0x0($3)\n"
		"\taddiu $4, $4, 0x10\n"
		"\tsw $17, 0x0($7)\n"
		"\taddiu $3, $3, 0x4\n"
		"\tsqc2 $vf7, 0x1c0($29)\n"
		"\taddiu $7, $7, 0x4\n"
		"\tldl $15, 0xb($10)\n"
		"\tldr $15, 0x4($10)\n"
		"\tsdl $15, 0x7($6)\n"
		"\tsdr $15, 0x0($6)\n"
		"\taddiu $6, $6, 0x8\n"
		"\tlqc2 $vf1, 0x70($29)\n"
		"\tlqc2 $vf2, 0x80($29)\n"
		"\tvmulax.xyzw ACC, $vf1, $vf6x\n"
		"\tvmadday.xyzw ACC, $vf2, $vf6y\n"
		"\tlqc2 $vf3, 0x90($29)\n"
		"\tvmaddaz.xyzw ACC, $vf3, $vf6z\n"
		"\tlqc2 $vf1, 0xa0($29)\n"
		"\tvmaddw.xyzw $vf1, $vf1, $vf6w\n"
		"\tsqc2 $vf1, 0x1d0($29)\n"
		"\tsqc2 $vf1, 0xb0($29)\n"
		"\tldl $15, 0xb($9)\n"
		"\tldr $15, 0x4($9)\n"
		"\tsdl $15, 0x7($8)\n"
		"\tsdr $15, 0x0($8)\n"
		"\taddiu $8, $8, 0x8\n"
		"\tlqc2 $vf1, 0x0($29)\n"
		"\tvmulax.xyzw ACC, $vf1, $vf8x\n"
		"\tlqc2 $vf2, 0x10($29)\n"
		"\tvmadday.xyzw ACC, $vf2, $vf8y\n"
		"\tlqc2 $vf1, 0x20($29)\n"
		"\tvmaddaz.xyzw ACC, $vf1, $vf8z\n"
		"\tvmaddw.xyzw $vf8, $vf0, $vf8w\n"
		"\tbgez $2, .L00450638\n"
		"\tlqc2 $vf5, 0x30($29)\n"
		"\tlqc2 $vf4, 0x30($29)\n"
		"\tlui $2, (0x80808080 >> 16)\n"
		"\tlqc2 $vf1, 0x40($29)\n"
		"\tvmulax.xyzw ACC, $vf4, $vf8x\n"
		"\tlqc2 $vf2, 0x50($29)\n"
		"\tvmadday.xyzw ACC, $vf1, $vf8y\n"
		"\tlqc2 $vf3, 0x60($29)\n"
		"\tvmaddaz.xyzw ACC, $vf2, $vf8z\n"
		"\tsqc2 $vf4, 0xb0($29)\n"
		"\tvmaddw.xyzw $vf5, $vf3, $vf8w\n"
		"\tsqc2 $vf1, 0xc0($29)\n"
		"\tori $2, $2, (0x80808080 & 0xffff)\n"
		"\tlqc2 $vf1, 0x200($29)\n"
		"\tdaddu $5, $18, $0\n"
		"\tsqc2 $vf2, 0xd0($29)\n"
		"\tsqc2 $vf3, 0xe0($29)\n"
		"\tsqc2 $vf5, 0x130($29)\n"
		"\tvmove.xyzw $vf4, $vf8\n"
		"\tsqc2 $vf5, 0x0($4)\n"
		"\tvmulx.xyz $vf4, $vf4, $vf1x\n"
		"\tsw $2, 0x0($3)\n"
		"\tvmove.xyzw $vf1, $vf4\n"
		"\tsw $17, 0x0($7)\n"
		"\tvadd.xyz $vf1, $vf1, $vf11\n"
		"\tsqc2 $vf1, 0x1e0($29)\n"
		"\tlui $4, %%hi(FXReg)\n"
		"\taddiu $4, $4, %%lo(FXReg)\n"
		"\tldl $2, 0xb($13)\n"
		"\tldr $2, 0x4($13)\n"
		"\tsdl $2, 0x7($6)\n"
		"\tsdr $2, 0x0($6)\n"
		"\tlqc2 $vf1, 0x70($29)\n"
		"\tvmulax.xyzw ACC, $vf1, $vf4x\n"
		"\tlqc2 $vf2, 0x80($29)\n"
		"\tlqc2 $vf3, 0x90($29)\n"
		"\tvmadday.xyzw ACC, $vf2, $vf4y\n"
		"\tlqc2 $vf1, 0xa0($29)\n"
		"\tvmaddaz.xyzw ACC, $vf3, $vf4z\n"
		"\tvmaddw.xyzw $vf1, $vf1, $vf4w\n"
		"\tsqc2 $vf1, 0x1f0($29)\n"
		"\tsqc2 $vf1, 0xb0($29)\n"
		"\tldl $15, 0xb($14)\n"
		"\tldr $15, 0x4($14)\n"
		"\tsdl $15, 0x7($8)\n"
		"\tsdr $15, 0x0($8)\n"
		"\tjal SetTexture\n"
		"\tnop\n"
		"\tlui $4, %%hi(FXReg)\n"
		"\taddiu $4, $4, %%lo(FXReg)\n"
		"\taddiu $5, $0, 0x8\n"
		"\taddiu $6, $0, 0x2\n"
		"\tjal SetBlendMode\n"
		"\taddiu $7, $0, 0x1\n"
		"\tlui $4, %%hi(FXReg)\n"
		"\taddiu $4, $4, %%lo(FXReg)\n"
		"\taddiu $5, $0, 0x10\n"
		"\taddiu $6, $0, 0x1\n"
		"\tjal DrawStrip\n"
		"\taddiu $7, $0, 0x1\n"
		"\tlui $4, %%hi(FXReg)\n"
		"\taddiu $4, $4, %%lo(FXReg)\n"
		"\tjal SetTexture\n"
		"\tdaddu $5, $20, $0\n"
		"\tbeqz $19, .L004508E4\n"
		"\taddiu $5, $0, 0xa\n"
		"\tlui $4, %%hi(FXReg)\n"
		"\taddiu $4, $4, %%lo(FXReg)\n"
		"\taddiu $6, $0, 0x1\n"
		"\tjal SetBlendMode\n"
		"\taddiu $7, $0, 0x1\n"
		"\tb .L004508FC\n"
		"\tnop\n"
		".L004508E4:\n"
		"\tlui $4, %%hi(FXReg)\n"
		"\taddiu $4, $4, %%lo(FXReg)\n"
		"\taddiu $5, $0, 0x9\n"
		"\taddiu $6, $0, 0x1\n"
		"\tjal SetBlendMode\n"
		"\taddiu $7, $0, 0x1\n"
		".L004508FC:\n"
		"\tlui $7, %%hi(D_221274)\n"
		"\tlw $7, %%lo(D_221274)($7)\n"
		"\tlui $4, %%hi(FXReg)\n"
		"\taddiu $4, $4, %%lo(FXReg)\n"
		"\tlui $8, %%hi(D_221278)\n"
		"\tlw $8, %%lo(D_221278)($8)\n"
		"\taddiu $5, $0, 0x10\n"
		"\tlui $6, %%hi(FXReg)\n"
		"\tlw $6, %%lo(FXReg)($6)\n"
		"\taddiu $7, $7, 0x80\n"
		"\taddiu $8, $8, 0x100\n"
		"\taddiu $9, $0, 0x1\n"
		"\tjal DrawStrip___dupe2\n"
		"\taddiu $10, $0, 0x1\n"
		"\tlq $16, 0x230($29)\n"
		"\tld $17, 0x240($29)\n"
		"\tld $18, 0x248($29)\n"
		"\tld $19, 0x250($29)\n"
		"\tld $20, 0x258($29)\n"
		"\tld $21, 0x260($29)\n"
		"\tld $22, 0x268($29)\n"
		"\tld $31, 0x270($29)\n"
		"\tlwc1 $f24, 0x2a0($29)\n"
		"\tlwc1 $f23, 0x298($29)\n"
		"\tlwc1 $f22, 0x290($29)\n"
		"\tlwc1 $f21, 0x288($29)\n"
		"\tlwc1 $f20, 0x280($29)\n"
		"\tjr $31\n"
		"\taddiu $29, $29, 0x2b0\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(DrawAlphaMaskPoly) : : : "memory");
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", DrawPinchDistort);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", FXU_SetupRingStripVerts);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", DrawLayeredRing);

GAME_SECTION(AttachPointToJoint) int AttachPointToJoint(void *self, void *pTargetMoby, vec4 &vWorldSpaceResult, vec4 &vJointSpacePoint, unsigned char volumeIdx, short jointIdx, int flag)
{
	MobyAttachInterface *iface = MobyGetInterface(0x2034, 0, 4);
	int ret;
	if (iface) ret = iface->attach(pTargetMoby, vWorldSpaceResult, vJointSpacePoint, volumeIdx, jointIdx, flag);
	else ret = 0;
	return ret;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", CubicLine_Init);

GAME_SECTION(CubicLine_Update) void CubicLine_Update(void *pThis, FXU_CubicPoint *pEndPoints, int iNumEndPoints)
{
	if (iNumEndPoints == 0) iNumEndPoints = pEndPoints->count;
	if (iNumEndPoints > 0) {
		long bits = 0x3fb504f3;
		register s128 sqrt2 __asm__("vf4");
		VU0_OP("qmtc2.ni %1, %0" : "=j"(sqrt2) : "r"(bits));
		do {
			register s128 q __asm__("vf1") = pEndPoints->vTangentOccQuat.v;
			register s128 v __asm__("vf2");
			register s128 t __asm__("vf3");
			iNumEndPoints--;
			v = pEndPoints->vTangent.v;
			VU0_OP("vmulx.xyzw %0, %0, %1x" : "+j"(q) : "j"(sqrt2));
			VU0_OP("vopmula.xyz ACC, %1, %2\n\tvmaddaw.xyz ACC, %2, %1w\n\tvopmsub.xyz %0, %2, %1" : "=j"(t) : "j"(q), "j"(v));
			VU0_OP("vopmula.xyz ACC, %1, %2\n\tvmaddaw.xyz ACC, %0, vf0w\n\tvopmsub.xyz %0, %2, %1" : "+j"(v) : "j"(q), "j"(t));
			pEndPoints->vTangent.v = v;
			pEndPoints++;
		} while (iNumEndPoints != 0);
	}
}

JUNK_ASM(func_00451530,
	"\tsqc2 $vf1, 0x0($4)\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", FXU_BuildCubicLineGeometry);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", CubicLine_Draw);

GAME_SECTION(CubicLineSet_Init) void CubicLineSet_Init(void *self, FXU_CubicLineSet_t &lineSet, int iNumLineEndPoints, void *pStyle, int preMadeStyle, bool bAutoSetFadeSettings)
{
	int iLine;
	FXU_CubicPoint **pp;

	lineSet.iSetInitFrame = worldUpdateTime;
	lineSet.bDeactivating = 0;
	iLine = 0;
	if (lineSet.lines[0] != 0) {
		do {
			FXU_CubicPoint *pCurrLine = lineSet.lines[iLine];
			CubicLine_Init(self, pCurrLine, iNumLineEndPoints, pStyle, preMadeStyle);
			iLine++;
			pCurrLine->bDisabled = 1;
		} while (iLine < 0x20 && lineSet.lines[iLine] != 0);
	}
	lineSet.count = iLine;
	if (bAutoSetFadeSettings) {
		lineSet.fFadeTypeScale = 1.0f;
		lineSet.fFadeScale = 1.0f;
		lineSet.fFadeShift = 0.0f;
		lineSet.fFadeMinValue = 0.0f;
		lineSet.fFadeMaxValue = 1.0f;
	}
}

GAME_SECTION(CubicLineSet_SetEndPointPos) void CubicLineSet_SetEndPointPos(void *self, FXU_CubicLineSet_t &lineSet, int iEndPoint, vec4 &vPos)
{
	int i;
	for (i = 0; i < lineSet.count; i++) lineSet.lines[i][iEndPoint].pos = vPos;
}

GAME_SECTION(CubicLineSet_SetStyle) void CubicLineSet_SetStyle(void *self, FXU_CubicLineSet_t &lineSet, void *pStatic, int style)
{
	int i, j;
	for (i = 0; i < lineSet.count; i++) {
		FXU_CubicPoint *line = lineSet.lines[i];
		if (pStatic) {
			for (j = 0; j < line->count; j++) line[j].style = 0;
		} else {
			line->style = style;
			for (j = 1; j < line->count; j++) line[j].style = 0;
		}
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", CubicLineSet_Update);

GAME_SECTION(CubicLineSet_Draw) void CubicLineSet_Draw(void *self, FXU_CubicLineSet_t &lineSet, void *pStyle)
{
	int iLine;
	int iCycleStep;
	float fLineAlpha;
	int ofs;
	FXU_CubicPoint **pp;

	iCycleStep = lineSet.unk00[0] / lineSet.count;
	for (iLine = 0; iLine < lineSet.count; iLine++) {
		FXU_CubicPoint *pCurrLine = lineSet.lines[iLine];
		if (!pCurrLine->bDisabled) {
			fLineAlpha = CalcCycleFade(self, ((float)((worldUpdateTime + lineSet.unk00[1] + iLine * iCycleStep) % lineSet.unk00[0]) / (float)lineSet.unk00[0]) * lineSet.fFadeTypeScale, lineSet.unk00[2]);
			CubicLine_Draw(self, pCurrLine, 0, pStyle, (fLineAlpha * lineSet.fFadeScale + lineSet.fFadeShift <? lineSet.fFadeMaxValue) >? lineSet.fFadeMinValue);
		}
	}
}

JUNK_ASM(func_00452A90,
	"\tdaddu $2, $0, $0\n"
	"\tnop\n");

GAME_SECTION(CubicLineSet_InitAsLightning) void CubicLineSet_InitAsLightning(void *self, FXU_CubicLineSet_t &lineSet, int iNumLineEndPoints, int iStartCoreColor, int iStartGlowColor, int iEndCoreColor, int iEndGlowColor)
{
	float fColorLerp;
	int iLine;
	int iEndPoint;
	int iCurrCoreColor;
	int iCurrGlowColor;
	FXU_CubicPoint *pCurrLine;

	lineSet.unk00[0] = 0x32;
	lineSet.unk00[1] = MB_randRangeInt(0, 0x32);
	lineSet.unk00[2] = 3;
	lineSet.fFadeTypeScale = 2.0f;
	lineSet.unk00[3] = 0;
	lineSet.fFadeScale = 1.1f;
	lineSet.fFadeMaxValue = 1.1f;
	lineSet.fFadeShift = 0.0f;
	lineSet.fFadeMinValue = 0.0f;
	for (iLine = 0; iLine < lineSet.count; iLine++) {
		pCurrLine = lineSet.lines[iLine];
		for (iEndPoint = 0; iEndPoint < iNumLineEndPoints; iEndPoint++) {
			fColorLerp = (float)iEndPoint / (float)(iNumLineEndPoints - 1);
			iCurrCoreColor = FastTweenColor(iStartCoreColor, iEndCoreColor, fColorLerp);
			iCurrGlowColor = FastTweenColor(iStartGlowColor, iEndGlowColor, fColorLerp);
			*(int *)&pCurrLine[iEndPoint].unk00[0] = FastTweenColor(iCurrCoreColor & 0xff000000, iCurrCoreColor, MB_randRange(1.0f, 1.15f));
			*(int *)&pCurrLine[iEndPoint].unk00[4] = FastTweenColor(iCurrGlowColor & 0xff000000, iCurrGlowColor, MB_randRange(1.0f, 1.15f));
			pCurrLine[iEndPoint].unk00[8] = 1;
			pCurrLine[iEndPoint].iNumSkipPoints = 0;
		}
	}
	CubicLineSet_Init(self, lineSet, iNumLineEndPoints, 0, 1, false);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", Contrail_Init);

JUNK_ASM(func_00452D70,
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\tsqc2 $vf2, 0x10($5)\n"
	"\tnop\n"
	"\tnop\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x120\n"
	"\tnop\n"
	"\tswc1 $f0, 0x50($6)\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", IsDrawOK);
