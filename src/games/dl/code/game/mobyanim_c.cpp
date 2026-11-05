#include "common.h"
#include "game_section.h"


typedef int s128 __attribute__((mode(TI)));
struct vec4 {
	/* 0x00 */ s128 q;
};
struct moby {
	/* 0x00 */ char unk00[0x10];
	/* 0x10 */ vec4 pos;
	/* 0x20 */ unsigned char bits;
	/* 0x21 */ char unk21[3];
	/* 0x24 */ void *pClass;
	/* 0x28 */ char unk28[0x34 - 0x28];
	/* 0x34 */ unsigned short state;
	/* 0x36 */ char unk36[0x50 - 0x36];
	/* 0x50 */ struct MobyAnimLayer *pLayers;
	/* 0x54 */ char unk54;
	/* 0x55 */ unsigned char animFlags;
	/* 0x56 */ char unk56;
	/* 0x57 */ unsigned char jointCnt;
	/* 0x58 */ char *pJoints;
	/* 0x5c */ char unk5c[0xbc - 0x5c];
	/* 0xbc */ short oClass;
	/* 0xbe */ char unkbe[0x100 - 0xbe];
};
struct PoseCacheEntry {
	/* 0x00 */ int unk00;
	/* 0x04 */ unsigned char used;
	/* 0x05 */ char unk05[3];
};
struct MobyAnimLayerCommon {
	/* 0x00 */ char unk00[0xe];
	/* 0x0e */ short poseIndex;
};
struct MemSlotData {
	/* 0x00 */ int unk00[6];
	/* 0x18 */ void *jointCache;
	/* 0x1c */ void *jointEntries;
	/* 0x20 */ int unk20[4];
};
extern PoseCacheEntry PoseCacheEntryList[] __asm__("PoseCacheEntryList");
extern unsigned char MobyAnimLayerCacheUsed[] __asm__("D_266F00");
extern MemSlotData MemSlotsAnim __asm__("D_0023AB00");
extern void *JointCacheEntryList __asm__("JointCacheEntryList");
extern void *MobyJointCache __asm__("MobyJointCache");
extern void *MobyJointCacheNextAvailableJoint __asm__("MobyJointCacheNextAvailableJoint");
extern int MobyJointCacheNumAvailableJoints __asm__("MobyJointCacheNumAvailableJoints");
extern int JointCache1stEntryDeleted __asm__("JointCache1stEntryDeleted");
extern int JointCacheNumEntries __asm__("JointCacheNumEntries");
extern int JointCacheNumEntriesDeleted __asm__("JointCacheNumEntriesDeleted");
extern int JointCacheNumJointsDeleted __asm__("JointCacheNumJointsDeleted");
unsigned char *AnimGetSubskeleton(int, void *) __asm__("AnimGetSubskeleton");
void ResetPoseCache() __asm__("ResetPoseCache");
void FreePoseCacheEntry(MobyAnimLayerCommon *) __asm__("FreePoseCacheEntry");
void MobyResetAnimLayerCache() __asm__("MobyResetAnimLayerCache");
void *GetMobyAnimJointMat(moby *, int) __asm__("GetMobyAnimJointMat");
void *GetMobyAnimJointOffset(moby *, int) __asm__("GetMobyAnimJointOffset");
void InitMobyJointCache() __asm__("InitMobyJointCache");
void ResetMobyJointCache() __asm__("ResetMobyJointCache");


struct JointMat {
	/* 0x00 */ char unk00[0x30];
	/* 0x30 */ vec4 offset;
};

struct MobyAnimLayer {
	/* 0x00 */ char unk00[0x10];
	/* 0x10 */ MobyAnimLayer *next;
	/* 0x14 */ char unk14;
	/* 0x15 */ unsigned char flags;
	/* 0x16 */ char unk16[0xa];
};
extern unsigned char MobyAnimLayerCacheUsed[] __asm__("D_266F00");
extern MobyAnimLayer MobyAnimLayerCache[] __asm__("D_266B00");
void AnimEvaluate(moby *, int) __asm__("AnimEvaluate");
void AnimResolveMats(char *, int, int) __asm__("AnimResolveMats");
void FastMemZero16(void *, int) __asm__("FastMemZero16");
void AnimEvaluateResolve(moby *) __asm__("AnimEvaluateResolve");
void CleanupAnimLayers(moby *) __asm__("CleanupAnimLayers");
void MobyFreeAnimLayer(MobyAnimLayer *) __asm__("MobyFreeAnimLayer");


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", AnimEvaluate_LowLevel);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", AnimEvaluateBlend_LowLevel);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", AnimEvaluate);

GAME_SECTION(AnimEvaluateResolve) void AnimEvaluateResolve(moby *pMoby)
{
	if (pMoby && pMoby->pJoints) {
		AnimEvaluate(pMoby, 0x70000000);
		AnimResolveMats(pMoby->pJoints, pMoby->jointCnt, 0x70000000);
		pMoby->animFlags &= 0xdf;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", ProcessManipulators);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", MobyAllocAnimLayer);

GAME_SECTION(MobyFreeAnimLayer) void MobyFreeAnimLayer(MobyAnimLayer *pLayer)
{
	if (pLayer->flags & 4) FreePoseCacheEntry((MobyAnimLayerCommon *)pLayer);
	MobyAnimLayerCacheUsed[pLayer - MobyAnimLayerCache] = 0;
	FastMemZero16(pLayer, 0x20);
}

GAME_SECTION(MobyResetAnimLayerCache) void MobyResetAnimLayerCache()
{
	int i = 0x1f;
	unsigned char *p = MobyAnimLayerCacheUsed;
	p += 0x1f;
	do {
		*p = 0;
		i--;
		p--;
	} while (i >= 0);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", MobyAttachAnimLayer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", MobyDetachAnimLayer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", func_0046F2A8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", MobyTransitionSequence);

GAME_SECTION(CleanupAnimLayers) void CleanupAnimLayers(moby *pMoby)
{
	MobyAnimLayer *pLayer = pMoby->pLayers;
	while (pLayer) {
		MobyAnimLayer *pNext = pLayer->next;
		MobyFreeAnimLayer(pLayer);
		pLayer = pNext;
	}
	pMoby->pLayers = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", func_0046F4A0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", GetMobyAnimJointOffset);

GAME_SECTION(GetMobyAnimJointMat) void *GetMobyAnimJointMat(moby *pMoby, int joint_index)
{
	return pMoby->pJoints + *AnimGetSubskeleton((char)joint_index, pMoby->pClass) * 0x40;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", NewPostUpdateMobyBsphere);

GAME_SECTION(ResetMobyJointCache) void ResetMobyJointCache()
{
	MobyJointCacheNextAvailableJoint = MobyJointCache;
	MobyJointCacheNumAvailableJoints = 0x3094;
	JointCache1stEntryDeleted = 0x7fffffff;
	JointCacheNumEntries = 0;
	JointCacheNumEntriesDeleted = 0;
	JointCacheNumJointsDeleted = 0;
}

GAME_SECTION(InitMobyJointCache) void InitMobyJointCache()
{
	MobyJointCache = MemSlotsAnim.jointCache;
	JointCacheEntryList = MemSlotsAnim.jointEntries;
	ResetMobyJointCache();
	ResetPoseCache();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", RebuildMobyJointCache);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", AllocJointCache);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", JointCacheMarkDeleted);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", JointCacheCleanup);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", ResetPoseCache);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", AllocPoseCacheEntry);

GAME_SECTION(FreePoseCacheEntry) void FreePoseCacheEntry(MobyAnimLayerCommon *pLayer)
{
	PoseCacheEntryList[pLayer->poseIndex].used = 0;
}
