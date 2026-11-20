#include "common.h"
#include "game_section.h"
#include "game_vu0.h"
#include "mobyutil.h"


int CS_RodType_Move(MobyInstance *pMoby) __asm__("CS_RodType_Move");
int CS_BallsType_Move(MobyInstance *pMoby) __asm__("CS_BallsType_Move");

struct ChunkVars {
	/* 0x00 */ char unk00[0x10];
	/* 0x10 */ s128 rotVel;
	/* 0x20 */ s128 cg;
	/* 0x30 */ s128 *verts;
	/* 0x34 */ char unk34[0x54 - 0x34];
	/* 0x54 */ int collFlags;
	/* 0x58 */ char unk58;
	/* 0x59 */ unsigned char pivots[3];
	/* 0x5c */ unsigned char numPivots;
};
struct CollOutputDef {
	/* 0x00 */ char unk00[0x30];
	/* 0x30 */ s128 push;
	/* 0x40 */ char unk40[0x40];
};
extern CollOutputDef CollOutput __asm__("CollOutput");
/* CollOutput.push, addressed directly (lui/addiu of CollOutput + 0x30). */
extern s128 CollOutputPush __asm__("CollOutputPush");
int CollSphere_Fix(s128 *pos, int type, int flags, float radius) __asm__("CollSphere_Fix");
int CS_DoCollision_Sphere(MobyInstance *pMoby) __asm__("CS_DoCollision_Sphere");
void CS_RemoveUnusedPivots(MobyInstance *pMoby, int pivot, s128 &grav) __asm__("CS_RemoveUnusedPivots");
void CS_RemoveRotationAroundAxis(MobyInstance *pMoby, s128 *rotVel, s128 *axis) __asm__("CS_RemoveRotationAroundAxis");
int CS_AttachPivot(MobyInstance *pMoby, int pivot, s128 &grav) __asm__("CS_AttachPivot");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_SpawnChunk);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_InitChunk);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_UpdateChunk);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_BlockType_Move);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_SphereType_Move);

GAME_SECTION(CS_RodType_Move) int CS_RodType_Move(MobyInstance *pMoby) { return 1; }

GAME_SECTION(CS_BallsType_Move) int CS_BallsType_Move(MobyInstance *pMoby) { return 1; }

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_MoveFree);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_MoveFree_Sphere);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_MovePivot);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_DoCollision);

GAME_SECTION(CS_DoCollision_Sphere) int CS_DoCollision_Sphere(MobyInstance *pMoby)
{
	ChunkVars *pVar = (ChunkVars *)pMoby->pVar;
	s128 mobyCG;
	s128 acc;
	s128 *m = (s128 *)&pMoby->rMtx;
	register s128 a0 __asm__("vf3") = m[0];
	register s128 c __asm__("vf2") = pVar->cg;
	register s128 a1 __asm__("vf1") = m[1];
	register s128 r __asm__("vf1");
	VU0_OP("vmulax.xyzw ACC, %1, %2x" : "=j"(acc) : "j"(a0), "j"(c));
	{
		register s128 a2 __asm__("vf3") = m[2];
		VU0_OP("vmadday.xyzw ACC, %1, %2y" : "+j"(acc) : "j"(a1), "j"(c));
		VU0_OP("vmaddaz.xyzw ACC, %1, %2z" : "+j"(acc) : "j"(a2), "j"(c));
	}
	{
		register s128 p __asm__("vf4") = pMoby->pos.v;
		VU0_OP("vmaddw.xyzw %0, vf0, %1w" : "=j"(r) : "j"(c), "j"(acc));
		mobyCG = r;
		VU0_OP("vadd.xyz %0, %0, %1" : "+j"(r) : "j"(p));
	}
	mobyCG = r;
	/* Read through byte offsets: retail loads these after the mobyCG stores, which field reads do not give. */
	if (CollSphere_Fix(&mobyCG, 2, *(int *)((char *)pVar + 0x54), *(float *)((char *)pVar + 0x2c))) {
		s128 push = CollOutputPush;
		s128 pos = pMoby->pos.v;
		VU0_OP("vsub.xyz %0, %0, %1" : "+j"(push) : "j"(mobyCG));
		VU0_OP("vadd.xyz %0, %0, %1" : "+j"(pos) : "j"(push));
		pMoby->pos.v = pos;
		return 1;
	}
	return 0;
}

GAME_SECTION(CS_AttachPivot) int CS_AttachPivot(MobyInstance *pMoby, int pivot, s128 &grav)
{
	ChunkVars *pVar = (ChunkVars *)pMoby->pVar;
	pVar->pivots[pVar->numPivots] = pivot;
	pVar->numPivots++;
	CS_RemoveUnusedPivots(pMoby, pVar->numPivots - 1, grav);
	if (pVar->numPivots != 1) {
		s128 pivotAxis;
		s128 *m = (s128 *)&pMoby->rMtx;
		register s128 m0 __asm__("vf3") = m[0];
		register s128 b __asm__("vf2") = pVar->verts[pVar->pivots[1]];
		register s128 d __asm__("vf1") = pVar->verts[pVar->pivots[0]];
		s128 acc;
		register s128 r __asm__("vf2");
		VU0_OP("vsub.xyz %0, %0, %1" : "+j"(d) : "j"(b));
		pivotAxis = d;
		VU0_OP("vmulax.xyzw ACC, %1, %2x" : "=j"(acc) : "j"(m0), "j"(d) : "memory");
		{
			register s128 m1 __asm__("vf2") = m[1];
			register s128 m2 __asm__("vf3") = m[2];
			VU0_OP("vmadday.xyzw ACC, %1, %2y
	vmaddaz.xyzw ACC, %3, %2z" : "+j"(acc) : "j"(m1), "j"(d), "j"(m2));
		}
		VU0_OP("vmaddw.xyzw %0, vf0, %1w" : "=j"(r) : "j"(d), "j"(acc));
		pivotAxis = r;
		CS_RemoveRotationAroundAxis(pMoby, &pVar->rotVel, &pivotAxis);
	}
	return pVar->numPivots;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_RemoveUnusedPivots);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_AddRotationVel);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_RemoveRotationAroundAxis);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_ReflectVector);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/chunk", CS_UnPackCollData);
