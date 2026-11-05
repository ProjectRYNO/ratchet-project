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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw2d", writeSetupBlock);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw2d", writeGSHeader);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw2d", ScisAndRender);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw2d", FastDrawStrip);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/draw2d", FasterDrawStrip);
