#include "common.h"
#include "game_section.h"



typedef int s128 __attribute__((mode(TI)));
struct vec4 {
	/* 0x00 */ s128 q;
};
struct FXU_CubicPoint {
	/* 0x00 */ char unk00[9];
	/* 0x09 */ unsigned char style;
	/* 0x0a */ unsigned char count;
	/* 0x0b */ unsigned char bDisabled;
	/* 0x0c */ int iNumSkipPoints;
	/* 0x10 */ vec4 pos;
	/* 0x20 */ char unk20[0x20];
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


/* ===== AL additions ===== */
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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", func_0044F930);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", DrawShellEdgeFaded);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", func_00450210);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", DrawAlphaMaskPoly);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", CubicLine_Update);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", func_00451530);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", func_00452A90);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", func_00452D70);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", IsDrawOK);
