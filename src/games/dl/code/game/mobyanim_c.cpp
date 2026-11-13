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
	/* 0x28 */ char unk28[0x31 - 0x28];
	/* 0x31 */ unsigned char drawn;
	/* 0x32 */ char unk32[0x34 - 0x32];
	/* 0x34 */ unsigned short state;
	/* 0x36 */ char unk36[0x40 - 0x36];
	/* 0x40 */ struct MobySeq *animSeq;
	/* 0x44 */ float animSeqT;
	/* 0x48 */ float animSpeed;
	/* 0x4c */ unsigned short animIScale;
	/* 0x4e */ short poseCacheEntryIndex;
	/* 0x50 */ struct MobyAnimLayer *pLayers;
	/* 0x54 */ char unk54;
	/* 0x55 */ unsigned char animFlags;
	/* 0x56 */ char unk56;
	/* 0x57 */ unsigned char jointCnt;
	/* 0x58 */ char *pJoints;
	/* 0x5c */ void *pManipulator;
	/* 0x60 */ char unk60[0x6c - 0x60];
	/* 0x6c */ unsigned char soundTrigger;
	/* 0x6d */ unsigned char soundDesired;
	/* 0x6e */ char unk6e[0xbc - 0x6e];
	/* 0xbc */ short oClass;
	/* 0xbe */ char unkbe[0x100 - 0xbe];
};
struct PoseCacheEntry {
	/* 0x00 */ short cacheIndex;
	/* 0x02 */ short jointCnt;
	/* 0x04 */ unsigned char used;
	/* 0x05 */ unsigned char nextIndex;
	/* 0x06 */ char unk06[2];
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
	/* 0x00 */ struct MobySeq *animSeq;
	/* 0x04 */ float animSeqT;
	/* 0x08 */ float animSpeed;
	/* 0x0c */ unsigned short animIScale;
	/* 0x0e */ char unk0e[2];
	/* 0x10 */ MobyAnimLayer *next;
	/* 0x14 */ char unk14;
	/* 0x15 */ unsigned char flags;
	/* 0x16 */ char animJointIndexA;
	/* 0x17 */ char animJointIndexB;
	/* 0x18 */ float blendWeight;
	/* 0x1c */ float blendFade;
};
extern unsigned char MobyAnimLayerCacheUsed[] __asm__("D_266F00");
extern MobyAnimLayer MobyAnimLayerCache[] __asm__("D_266B00");
void AnimEvaluate(moby *, int) __asm__("AnimEvaluate");
void AnimResolveMats(char *, int, int) __asm__("AnimResolveMats");
void FastMemZero16(void *, int) __asm__("FastMemZero16");
void AnimEvaluateResolve(moby *) __asm__("AnimEvaluateResolve");
void CleanupAnimLayers(moby *) __asm__("CleanupAnimLayers");
void MobyFreeAnimLayer(MobyAnimLayer *) __asm__("MobyFreeAnimLayer");


struct JointCacheEntry {
	/* 0x00 */ moby *pMoby;
	/* 0x04 */ unsigned short jointIndex;
	/* 0x06 */ char unk06;
	/* 0x07 */ unsigned char deleted;
};
extern moby *AnimLayerCacheMobys[] __asm__("AnimLayerCacheMobys");
extern int PoseGarbageIndex __asm__("PoseGarbageIndex");
extern int PoseHeadIndex __asm__("PoseHeadIndex");
void RebuildMobyJointCache() __asm__("RebuildMobyJointCache");
MobyAnimLayer *MobyAllocAnimLayer(moby *) __asm__("MobyAllocAnimLayer");
struct MobySeqFrame {
	/* 0x00 */ unsigned short iscale;
	/* 0x02 */ short unk02;
};
struct MobySeq {
	/* 0x00 */ char unk00[0x10];
	/* 0x10 */ unsigned char frameCnt;
	/* 0x11 */ unsigned char sound;
	/* 0x12 */ unsigned char trigsCnt;
	/* 0x13 */ char unk13[0x1c - 0x13];
	/* 0x1c */ unsigned char *frameData;
	/* 0x20 */ MobySeqFrame frames[1];
};
struct AnimMobyClass {
	/* 0x00 */ char unk00[8];
	/* 0x08 */ unsigned char jointCnt;
};
MobyAnimLayer *MobyAttachAnimLayer(moby *, MobySeq *, int, float, int, int, int) __asm__("MobyAttachAnimLayer");
void MobyDetachAnimLayer(moby *, MobyAnimLayer *, int) __asm__("MobyDetachAnimLayer");
void JointCacheMarkDeleted(moby *) __asm__("JointCacheMarkDeleted");

void DmaToSpr(void *, int, int) __asm__("DmaToSpr");
void DmaToSprSync() __asm__("DmaToSprSync");
void AnimDecompInterp(float) __asm__("AnimDecompInterp");
void AnimDecompInterpBlend(float, float) __asm__("AnimDecompInterpBlend");
void AnimEvaluate_LowLevel(MobySeq *, float) __asm__("AnimEvaluate_LowLevel");
void AnimEvaluateBlend_LowLevel(MobySeq *, float, float) __asm__("AnimEvaluateBlend_LowLevel");
struct AK_EvalClass {
	/* 0x00 */ char unk00[8];
	/* 0x08 */ unsigned char jointCnt;
	/* 0x09 */ char unk09[0x18 - 0x9];
	/* 0x18 */ void *common_trans;
	/* 0x1c */ void **anim_joints;
};
extern char AK_PoseCache2[] __asm__("PoseCache");
void InitQSTBuffer(int) __asm__("InitQSTBuffer");
void AnimDecompCached(void *, int) __asm__("AnimDecompCached");
void AnimDecompBlendCached(void *, int, float) __asm__("AnimDecompBlendCached");
void AnimPreprocessSubskeleton(int, int, void *, void *) __asm__("AnimPreprocessSubskeleton");
void ProcessManipulators(void *) __asm__("ProcessManipulators");
void DmaFromSpr(void *, int, int) __asm__("DmaFromSpr");
void DmaFromSprSync() __asm__("DmaFromSprSync");
struct AK_SeqHdr { float bSphere[4]; char unk10[0x10]; };
void AllocPoseCacheEntry(MobyAnimLayer *, void *) __asm__("AllocPoseCacheEntry");
void MobyTransitionSequence(moby *pMoby, MobySeq *seq, int seqId, float seqT, int fadeSteps) __asm__("MobyTransitionSequence");
struct AK_PoseClass {
	/* 0x00 */ char unk00[8];
	/* 0x08 */ unsigned char jointCnt;
	/* 0x09 */ char unk09[0x18 - 0x9];
	/* 0x18 */ void *common_trans;
};
extern char AK_PoseCache[] __asm__("PoseCache");
void AnimCachePose(void *, int) __asm__("AnimCachePose");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", AnimEvaluate_LowLevel);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", AnimEvaluateBlend_LowLevel);

GAME_SECTION(AnimEvaluate) void AnimEvaluate(moby *pMoby, int QST)
{
	AK_EvalClass *pClass = (AK_EvalClass *)pMoby->pClass;
	if (!pClass->jointCnt) return;
	DmaToSpr(pClass->common_trans, pClass->jointCnt, 0x2000);
	DmaToSprSync();
	InitQSTBuffer(pClass->jointCnt);
	if (pMoby->animFlags & 4) {
		PoseCacheEntry *p_entry = &PoseCacheEntryList[pMoby->poseCacheEntryIndex];
		AnimDecompCached(AK_PoseCache2 + p_entry->cacheIndex * 0x20, p_entry->jointCnt);
	} else {
		AnimEvaluate_LowLevel(pMoby->animSeq, pMoby->animSeqT);
	}
	MobyAnimLayer *pLayer;
	for (pLayer = pMoby->pLayers; pLayer; pLayer = pLayer->next) {
		unsigned char *pFrameData = pLayer->animSeq->frameData;
		if ((unsigned char)pLayer->animJointIndexA == 0xff) {
			AnimPreprocessSubskeleton(pFrameData[6], pFrameData[7], 0, 0);
		} else if ((unsigned char)pLayer->animJointIndexB == 0xff) {
			AnimPreprocessSubskeleton(pFrameData[6], pFrameData[7], pClass->anim_joints[(unsigned char)pLayer->animJointIndexA + 1], 0);
		} else {
			AnimPreprocessSubskeleton(pFrameData[6], pFrameData[7], pClass->anim_joints[(unsigned char)pLayer->animJointIndexA + 1], pClass->anim_joints[(unsigned char)pLayer->animJointIndexB + 1]);
		}
		if (pLayer->flags & 4) {
			PoseCacheEntry *p_entry = &PoseCacheEntryList[((MobyAnimLayerCommon *)pLayer)->poseIndex];
			AnimDecompBlendCached(AK_PoseCache2 + p_entry->cacheIndex * 0x20, p_entry->jointCnt, pLayer->blendWeight);
		} else {
			AnimEvaluateBlend_LowLevel(pLayer->animSeq, pLayer->animSeqT, pLayer->blendWeight);
		}
	}
	if (pMoby->pManipulator) ProcessManipulators(pMoby->pManipulator);
	if (QST != 0x70000000) {
		DmaFromSpr((void *)QST, pClass->jointCnt * 4, 0);
		DmaFromSprSync();
	}
}

GAME_SECTION(AnimEvaluateResolve) void AnimEvaluateResolve(moby *pMoby)
{
	if (pMoby && pMoby->pJoints) {
		AnimEvaluate(pMoby, 0x70000000);
		AnimResolveMats(pMoby->pJoints, pMoby->jointCnt, 0x70000000);
		pMoby->animFlags &= 0xdf;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", ProcessManipulators);

GAME_SECTION(MobyAllocAnimLayer) MobyAnimLayer *MobyAllocAnimLayer(moby *pMoby)
{
	int i;
	if (!pMoby->drawn || (pMoby->bits & 0x80)) return 0;
	for (i = 0; i < 0x20; i++) {
		if (!MobyAnimLayerCacheUsed[i]) {
			MobyAnimLayerCacheUsed[i] = 1;
			AnimLayerCacheMobys[i] = pMoby;
			return &MobyAnimLayerCache[i];
		}
	}
	return 0;
}

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

GAME_SECTION(MobyAttachAnimLayer) MobyAnimLayer *MobyAttachAnimLayer(moby *pMoby, MobySeq *seq, int seqId, float seqT, int fadeSteps, int jointIdA, int jointIdB)
{
	MobyAnimLayer *pNewLayer = MobyAllocAnimLayer(pMoby);
	if (pNewLayer) {
		MobyAnimLayer **ppNewLayer;
		pNewLayer->animJointIndexA = jointIdA;
		pNewLayer->animJointIndexB = jointIdB;
		pNewLayer->unk14 = seqId;
		pNewLayer->animSeq = seq;
		pNewLayer->animSeqT = seqT;
		pNewLayer->flags = 0;
		pNewLayer->animIScale = seq->frames[(int)seqT].iscale;
		pNewLayer->animSpeed = 1.0f;
		pNewLayer->blendFade = 0.0f;
		if (fadeSteps > 0) pNewLayer->blendFade = -1.0f / (float)fadeSteps;
		pNewLayer->blendWeight = -pNewLayer->blendFade;
		ppNewLayer = &pMoby->pLayers;
		while (*ppNewLayer) ppNewLayer = &(*ppNewLayer)->next;
		*ppNewLayer = pNewLayer;
		pNewLayer->next = 0;
	}
	return pNewLayer;
}

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

GAME_SECTION(RebuildMobyJointCache) void RebuildMobyJointCache()
{
	int i;
	for (i = 0; i < JointCacheNumEntries; i++) {
		if (!((JointCacheEntry *)JointCacheEntryList)[i].deleted) AnimEvaluateResolve(((JointCacheEntry *)JointCacheEntryList)[i].pMoby);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", AllocJointCache);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", JointCacheMarkDeleted);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyanim_c", JointCacheCleanup);

GAME_SECTION(ResetPoseCache) void ResetPoseCache()
{
	int i;
	PoseCacheEntryList[0].jointCnt = 0x200;
	PoseCacheEntryList[0].nextIndex = 0xff;
	PoseGarbageIndex = 1;
	PoseHeadIndex = 0;
	PoseCacheEntryList[0].used = 0;
	PoseCacheEntryList[0].cacheIndex = 0;
	for (i = 1; i < 0x1f; i++) PoseCacheEntryList[i].nextIndex = i + 1;
	PoseCacheEntryList[i].nextIndex = 0xff;
}

GAME_SECTION(AllocPoseCacheEntry) void AllocPoseCacheEntry(MobyAnimLayer *pLayer, void *pClass_)
{
	AK_PoseClass *pClass = (AK_PoseClass *)pClass_;
	int garbage = PoseGarbageIndex;
	int joint_cnt = pClass->jointCnt;
	if (garbage == 0xff) return;
	int index = PoseHeadIndex;
	if (index == 0xff) return;
	PoseCacheEntry *pEntry = &PoseCacheEntryList[index];
	while (pEntry->used || pEntry->jointCnt < joint_cnt) {
		index = pEntry->nextIndex;
		if (index == 0xff) return;
		pEntry = &PoseCacheEntryList[index];
	}
	if (index == 0xff) return;
	if (joint_cnt < pEntry->jointCnt) {
		PoseCacheEntry *pNewEntry = &PoseCacheEntryList[garbage];
		PoseGarbageIndex = pNewEntry->nextIndex;
		pNewEntry->nextIndex = pEntry->nextIndex;
		pEntry->nextIndex = garbage;
		pNewEntry->used = 0;
		pNewEntry->cacheIndex = pEntry->cacheIndex + joint_cnt;
		pNewEntry->jointCnt = pEntry->jointCnt - joint_cnt;
	}
	pEntry->jointCnt = joint_cnt;
	pEntry->used = 1;
	DmaToSpr(pClass->common_trans, joint_cnt, 0x2000);
	DmaToSprSync();
	InitQSTBuffer(joint_cnt);
	AnimEvaluate_LowLevel(pLayer->animSeq, pLayer->animSeqT);
	AnimCachePose(AK_PoseCache + pEntry->cacheIndex * 0x20, joint_cnt);
	((MobyAnimLayerCommon *)pLayer)->poseIndex = index;
	pLayer->flags |= 4;
}

GAME_SECTION(FreePoseCacheEntry) void FreePoseCacheEntry(MobyAnimLayerCommon *pLayer)
{
	PoseCacheEntryList[pLayer->poseIndex].used = 0;
}
