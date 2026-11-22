// GAME_EXTRA_FLAGS: -g0
#include "common.h"
#include "game_section.h"


extern unsigned int Draw2DZ __asm__("D_21EC20");
void ResetZ() __asm__("ResetZ");
void SetZ(unsigned int) __asm__("SetZ");

struct vec2 {
	/* 0x00 */ float x;
	/* 0x04 */ float y;
};
void PackQuadLTRB(vec2 *, float, float, float, float) __asm__("PackQuadLTRB");
void DrawQuad(vec2 *, unsigned int *) __asm__("DrawQuad");
void ScalePoints(vec2 *, int, float, float) __asm__("ScalePoints");
void TranslatePoints(vec2 *, int, float, float) __asm__("TranslatePoints");
float FastSin(float) __asm__("FastSin");
float FastCos(float) __asm__("FastCos");
void RotatePoints(vec2 *, int, float) __asm__("RotatePoints");


GAME_SECTION(SetZ) void SetZ(unsigned int iZ)
{
	Draw2DZ = iZ & 0xffffff;
}

GAME_SECTION(ResetZ) void ResetZ()
{
	Draw2DZ = 0xffffff;
}

GAME_SECTION(TranslatePoints) void TranslatePoints(vec2 *vPoints, int iCount, float fTransX, float fTransY)
{
	int i;
	for (i = iCount - 1; i >= 0; i--) {
		vPoints[i].x += fTransX;
		vPoints[i].y += fTransY;
	}
}

GAME_SECTION(ScalePoints) void ScalePoints(vec2 *vPoints, int iCount, float fScaleX, float fScaleY)
{
	int i;
	for (i = iCount - 1; i >= 0; i--) {
		vPoints[i].x *= fScaleX;
		vPoints[i].y *= fScaleY;
	}
}

GAME_SECTION(RotatePoints) void RotatePoints(vec2 *vPoints, int iCount, float fRot)
{
	float s = FastSin(fRot);
	int i = iCount - 1;
	float c = FastCos(fRot);
	for (; i >= 0; i--) {
		float x = vPoints[i].x;
		float y = vPoints[i].y;
		float nx = x * c + y * s; float ny = y * c - x * s; vPoints[i].y = ny; vPoints[i].x = nx;
	}
}

GAME_SECTION(PackQuadLTRB) void PackQuadLTRB(vec2 *vPoints, float fL, float fT, float fR, float fB)
{
	vPoints[0].x = fL;
	vPoints[0].y = fT;
	vPoints[1].x = fR;
	vPoints[1].y = fT;
	vPoints[2].x = fL;
	vPoints[2].y = fB;
	vPoints[3].x = fR;
	vPoints[3].y = fB;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw2d", DrawQuad);

void DrawQuad(vec2 *vPoints, unsigned int colour) __asm__("DrawQuad___dupe2");
GAME_SECTION(DrawQuad___dupe2) void DrawQuad(vec2 *vPoints, unsigned int colour)
{
	unsigned int colours[4];
	colours[0] = colour;
	colours[1] = colour;
	colours[2] = colour;
	colours[3] = colour;
	DrawQuad(vPoints, colours);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw2d", CalcMapUvs);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw2d", DrawQuadMap);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw2d", FastIntersectVert);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw2d", FastGenerateVert);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw2d", FastNearestPointOnLine3);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw2d", FastDrawQuadReal);

void writeSetupBlock(void) __asm__("writeSetupBlock");
GAME_SECTION(writeSetupBlock) void writeSetupBlock(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tpexew $31, $31\n"
		"\tqmfc2.ni $0, $vf0\n"
		"\tjal writeGSHeader\n"
		"\taddi $4, $0, 0x5\n"
		"\tlui $8, (0x24000000 >> 16)\n"
		"\tld $10, 0x70($18)\n"
		"\tdsll32 $8, $8, 0\n"
		"\tld $11, 0x78($18)\n"
		"\tori $8, $8, 0x1\n"
		"\tori $9, $0, 0x68\n"
		"\tpcpyld $10, $11, $10\n"
		"\tld $12, 0x80($18)\n"
		"\tpcpyld $8, $9, $8\n"
		"\tsq $10, 0x10($1)\n"
		"\tsq $8, 0x0($1)\n"
		"\tori $11, $0, 0x14\n"
		"\tpcpyld $12, $11, $12\n"
		"\tld $10, 0x88($18)\n"
		"\tlui $8, (0x20000000 >> 16)\n"
		"\tori $9, $0, 0xee\n"
		"\tdsll32 $8, $8, 0\n"
		"\tori $11, $0, 0x42\n"
		"\tori $8, $8, 0x8001\n"
		"\tnop\n"
		"\tpcpyld $8, $9, $8\n"
		"\tsq $12, 0x30($1)\n"
		"\tpcpyld $10, $11, $10\n"
		"\tsq $8, 0x20($1)\n"
		"\tpexew $31, $31\n"
		"\tqmfc2.ni $0, $vf0\n"
		"\tjr $31\n"
		"\tsq $10, 0x40($1)\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(writeSetupBlock) : : : "memory");
}

void writeGSHeader(void) __asm__("writeGSHeader");
GAME_SECTION(writeGSHeader) void writeGSHeader(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tsll $25, $4, 4\n"
		"\tnop\n"
		"\tlw $1, -0x3b5f($28)\n" /* vu1_bufPtr */
		"\tlui $8, (0x10000000 >> 16)\n"
		"\taddi $25, $25, 0x10\n"
		"\tor $8, $8, $4\n"
		"\tsq $0, 0x0($1)\n"
		"\tlui $9, (0x40000000 >> 16)\n"
		"\tsw $8, 0x0($1)\n"
		"\tor $8, $8, $9\n"
		"\tsw $8, 0xc($1)\n"
		"\tadd $10, $1, $25\n"
		"\taddi $1, $1, 0x10\n"
		"\tnop\n"
		"\tjr $31\n"
		"\tsw $10, -0x3b5f($28)\n" /* vu1_bufPtr */
		".set at\n.set reorder\n" GAME_ASM_TAIL(writeGSHeader) : : : "memory");
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw2d", ScisAndRender);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw2d", FastDrawStrip);

void FasterDrawStrip(void) __asm__("FasterDrawStrip");
GAME_SECTION(FasterDrawStrip) void FasterDrawStrip(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tpcpyld $31, $31, $0\n"
		"\tlw $10, -0x3b5f($28)\n" /* vu1_bufPtr */
		"\taddiu $13, $8, 0xd\n"
		"\tlui $25, (0x15000000 >> 16)\n"
		"\tdaddu $1, $10, $0\n"
		"\tsll $24, $9, 3\n"
		"\tlui $11, %%hi(stripvif_head)\n"
		"\taddiu $3, $0, 0x50\n"
		"\tjal FUN_0044cfa8\n"
		"\taddiu $11, $11, %%lo(stripvif_head)\n"
		"\tori $2, $24, 0x3036\n"
		"\tandi $13, $13, 0xe\n"
		"\tsh $2, -0x3a($1)\n"
		"\tsh $2, -0x26($1)\n"
		"\tlq $2, -0x539f($28)\n" /* stripvif_SThead */
		"\tdaddu $11, $7, $0\n"
		"\tsb $4, -0x40($1)\n"
		"\tsll $3, $4, 3\n"
		"\tsq $2, 0x0($1)\n"
		"\taddiu $1, $1, 0x10\n"
		"\tjal FUN_0044cec8\n"
		"\tsb $4, -0x2($1)\n"
		"\tlq $2, -0x537f($28)\n" /* stripvif_RGBAhead */
		"\tor $13, $25, $13\n"
		"\tdaddu $11, $6, $0\n"
		"\tsll $3, $4, 2\n"
		"\tsq $2, 0x0($1)\n"
		"\taddiu $1, $1, 0x10\n"
		"\tjal FUN_0044cec8\n"
		"\tsb $4, -0x2($1)\n"
		"\tlq $2, -0x533f($28)\n" /* stripvif_XYZWhead */
		"\tlui $25, (0x11000000 >> 16)\n"
		"\tdaddu $11, $5, $0\n"
		"\tsll $3, $4, 4\n"
		"\tsq $2, 0x0($1)\n"
		"\taddiu $1, $1, 0x10\n"
		"\tjal FUN_0044cfa8\n"
		"\tsb $4, -0x2($1)\n"
		"\tsw $13, 0x0($1)\n"
		"\tsub $2, $1, $10\n"
		"\tsw $25, 0x4($1)\n"
		"\tsrl $2, $2, 4\n"
		"\tsd $0, 0x8($1)\n"
		"\taddiu $1, $1, 0x10\n"
		"\tpcpyud $31, $31, $0\n"
		"\tsh $2, 0x0($10)\n"
		"\tjr $31\n"
		"\tsw $1, -0x3b5f($28)\n" /* vu1_bufPtr */
		".set at\n.set reorder\n" GAME_ASM_TAIL(FasterDrawStrip) : : : "memory");
}
