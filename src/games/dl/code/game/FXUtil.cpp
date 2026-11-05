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
	/* 0x0b */ char unk0b[5];
	/* 0x10 */ vec4 pos;
	/* 0x20 */ char unk20[0x20];
};
struct FXU_CubicLineSet_t {
	/* 0x00 */ int unk00[4];
	/* 0x10 */ FXU_CubicPoint *lines[0x25];
	/* 0xa4 */ int count;
};
void CubicLineSet_SetEndPointPos(void *, FXU_CubicLineSet_t &, int, vec4 &) __asm__("CubicLineSet_SetEndPointPos");
void CubicLineSet_SetStyle(void *, FXU_CubicLineSet_t &, void *, int) __asm__("CubicLineSet_SetStyle");
struct MobyAttachInterface {
	/* 0x00 */ int (*attach)(void *, vec4 &, vec4 &, int, int, int);
};
MobyAttachInterface *MobyGetInterface(int, int, int) __asm__("MobyGetInterface___dupe2");
int AttachPointToJoint(void *, void *, vec4 &, vec4 &, unsigned char, short, int) __asm__("AttachPointToJoint");


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", CalcCycleFade);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", CubicLineSet_Init);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", CubicLineSet_Draw);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", func_00452A90);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", CubicLineSet_InitAsLightning);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", Contrail_Init);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", func_00452D70);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXUtil", IsDrawOK);
