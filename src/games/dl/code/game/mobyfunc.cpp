#include "common.h"
#include "game_section.h"




struct Manipulator;
struct MobyClass {
	/* 0x00 */ char unk00[0xf];
	/* 0x0f */ unsigned char shadow;
	/* 0x10 */ char unk10[0x2e - 0x10];
	/* 0x2e */ short corncob;
};
struct MobyInstance {
	/* 0x00 */ char unk00[0x20];
	/* 0x20 */ unsigned char state;
	/* 0x21 */ unsigned char group;
	/* 0x22 */ char unk22[0x24 - 0x22];
	/* 0x24 */ MobyClass *pClass;
	/* 0x28 */ char unk28[0x2d - 0x28];
	/* 0x2d */ unsigned char deathCnt;
	/* 0x2e */ char unk2e[0x34 - 0x2e];
	/* 0x34 */ unsigned short modeBits;
	/* 0x36 */ unsigned short modeBits2;
	/* 0x38 */ char unk38[0x40 - 0x38];
	/* 0x40 */ void *animSeq;
	/* 0x44 */ float animSeqT;
	/* 0x48 */ char unk48[0x55 - 0x48];
	/* 0x55 */ unsigned char animFlags;
	/* 0x56 */ char unk56[0x5c - 0x56];
	/* 0x5c */ Manipulator *pManipulator;
	/* 0x60 */ char unk60[0x6d - 0x60];
	/* 0x6d */ unsigned char soundDesired;
	/* 0x6e */ short soundChannel;
	/* 0x70 */ char unk70[0x74 - 0x70];
	/* 0x74 */ unsigned short bangles;
	/* 0x76 */ char unk76[0xa0 - 0x76];
	/* 0xa0 */ int collCnt;
	/* 0xa4 */ char unka4[0xac - 0xa4];
	/* 0xac */ void *pVar;
	/* 0xb0 */ char unkb0[0x100 - 0xb0];
};
struct Moby2dCon {
	/* 0x00 */ MobyInstance *mobys[8];
	/* 0x20 */ int active;
	/* 0x24 */ int screen_ofs_x;
	/* 0x28 */ int screen_ofs_y;
	/* 0x2c */ int scissor_l;
	/* 0x30 */ int scissor_r;
	/* 0x34 */ int scissor_t;
	/* 0x38 */ int scissor_b;
	/* 0x3c */ int unk3c;
};
struct mobyfuncs {
	/* 0x00 */ int unk00[4];
	/* 0x10 */ void *(*getMobyInterface)(int, int, void *);
};
extern Moby2dCon g_Moby2dCon __asm__("g_Moby2dCon");
extern char g_MobyClassDistsStash[] __asm__("g_MobyClassDistsStash");
extern long _dma_1[] __asm__("D_1170D0");
void FastMemSet(void *, int, int) __asm__("FastMemSet");
void FastMemCopy16(void *, const void *, int) __asm__("FastMemCopy16");
void VU0_loadMicroProgram(long *) __asm__("VU0_loadMicroProgram");
void DeleteMoby(MobyInstance *) __asm__("DeleteMoby");
mobyfuncs *GetMobyFunctions(int) __asm__("GetMobyFunctions___dupe2");
void InitMobyClassDists() __asm__("InitMobyClassDists");
int MobyCornExists(MobyInstance *, int) __asm__("MobyCornExists");
void StashMobyClassDists() __asm__("StashMobyClassDists");
void RestoreMobyClassDists() __asm__("RestoreMobyClassDists");
MobyInstance *Moby2dGetPtr(int) __asm__("Moby2dGetPtr");
void Moby2dReset() __asm__("Moby2dReset");
void Moby2dDelete(int) __asm__("Moby2dDelete");
void *MobyGetInterface(int, int, int) __asm__("MobyGetInterface___dupe2");


struct moby {
	/* 0x00 */ char unk00[0x38];
	/* 0x38 */ unsigned long lights;
};
extern int *MobyVarListTop __asm__("MobyVarListTop");
extern int *MobyVarList __asm__("MobyVarList");
extern int *MobyVarListNext __asm__("MobyVarListNext");
extern int *MobyVarListHead __asm__("MobyVarListHead");
extern int *MobyVarListTail __asm__("MobyVarListTail");
extern void *EngScratchPad __asm__("EngScratchPad");
extern void *SkinVertexCache __asm__("SkinVertexCache");
extern char MobyAnimMicrocode[0x800] __asm__("D_3D6860");
extern void *MobyShadowMarker __asm__("MobyShadowMarker");
extern char *MobyTeamTexPtr __asm__("MobyTeamTexPtr");
extern char MobyTeamTexList[] __asm__("MobyTeamTexList");
extern long _dma_7[] __asm__("D_117A60");
extern int MobySplitScreen __asm__("MobySplitScreen");
extern MobyInstance *MobyInstances __asm__("MobyInstances");
extern void *MobyAnimPtr __asm__("MobyAnimPtr");
extern int MobyGroupFirstDynamic __asm__("MobyGroupFirstDynamic");
struct ScrnDef {
	/* 0x00 */ int size_x;
	/* 0x04 */ int size_y;
	/* 0x08 */ int unk08[2];
};
extern ScrnDef Scrn __asm__("Scrn");
extern unsigned short *g_pLightCuboids __asm__("g_pLightCuboids");
void MobyAnimProc(void *, void *) __asm__("MobyAnimProc");
void DmaMobyTextures() __asm__("DmaMobyTextures");
void ProcessMobyShadows() __asm__("ProcessMobyShadows");
void ProcessMobyTeamTexs() __asm__("ProcessMobyTeamTexs");
void DrawMobysSetup() __asm__("DrawMobysSetup");
void *MobyProc(MobyInstance *, void *, long, int) __asm__("FUN_00470bf0");
void SetMobyLights(moby *, int, int, int, int) __asm__("SetMobyLights");
void *SetupMobyVars(int, void *) __asm__("SetupMobyVars");
void ProcessMobyAnimData() __asm__("ProcessMobyAnimData");
void DrawMobysCleanup() __asm__("DrawMobysCleanup");
void DrawMobys() __asm__("DrawMobys");
void *MobyGetInterface(int, int) __asm__("MobyGetInterface");
int MobyDynamicGroup_IsDynamicGroup(int) __asm__("MobyDynamicGroup_IsDynamicGroup");
void CollSphereFail(void *) __asm__("CollSphereFail");
void Moby2dSetWindow(int, int, int, int) __asm__("Moby2dSetWindow");
void SetMobyLightDefault(moby *) __asm__("SetMobyLightDefault");

struct Manipulator {
	/* 0x00 */ char unk00[8];
	/* 0x08 */ Manipulator *pChain;
	/* 0x0c */ char unk0c[0x34];
};
/* ===== AG additions ===== */
extern int MobyShadowList[2] __asm__("MobyShadowList");
extern int MobyShadowCnt __asm__("MobyShadowCnt");
void ShadowBuildPrimList(void *, int) __asm__("ShadowBuildPrimList");
void VU1_addGSregister(unsigned int, unsigned long, int) __asm__("VU1_addGSregister");
float MobyMayaFrame(MobyInstance *) __asm__("MobyMayaFrame");
void *GetMobyShadowVolumesAndJoints(MobyInstance *) __asm__("GetMobyShadowVolumesAndJoints");
void DrawMobyList(MobyInstance *, int, int) __asm__("DrawMobyList");
void DetachManipulator(MobyInstance *, Manipulator *) __asm__("DetachManipulator");

volatile unsigned char g_PreventCountMobyGridUsageAndValidateMobyGridsFromBeingStripped __asm__("g_PreventCountMobyGridUsageAndValidateMobyGridsFromBeingStripped") GAME_GP_DATA = 0;
extern int numSpawnableMobys __asm__("numSpawnableMobys");
void *AllocMobyVar(int) __asm__("AllocMobyVar");
void InitMobyInstance(MobyInstance *, int, int) __asm__("InitMobyInstance");
void CountMobyGridUsage() __asm__("CountMobyGridUsage");
void ValidateMobyGrids() __asm__("ValidateMobyGrids");
extern MobyInstance *MobyInstanceEnd __asm__("MobyInstanceEnd");
extern MobyInstance *MobyInstancePermEnd __asm__("MobyInstancePermEnd");
extern int worldUpdateTime __asm__("worldUpdateTime");
MobyInstance *CreateMoby(int mClass, int var_size) __asm__("CreateMoby");
extern char *MobyVars __asm__("MobyVars");
extern int MobyVarsBlockCnt __asm__("MobyVarsBlockCnt");
void FreeMobyVar(void *) __asm__("FreeMobyVar");
void UpdateMobyGrids(MobyInstance *, int) __asm__("UpdateMobyGrids");
void JointCacheMarkDeleted(MobyInstance *) __asm__("JointCacheMarkDeleted");
void CleanupAnimLayers(MobyInstance *) __asm__("CleanupAnimLayers");
int MobyDynamicGroup_RemoveMoby(int, MobyInstance *) __asm__("MobyDynamicGroup_RemoveMoby");
struct SoundData {
	/* 0x00 */ char unk00[0xa];
	/* 0x0a */ short id;
	/* 0x0c */ char unk0c[0x10 - 0xc];
	/* 0x10 */ unsigned char active;
	/* 0x11 */ char unk11[0x1c - 0x11];
	/* 0x1c */ MobyInstance *pMoby;
};
extern int AK_g_gameType __asm__("g_gameType");
int GB_IsMobyAHero(MobyInstance *) __asm__("GB_IsMobyAHero");
SoundData *sound_GetChannelFromHandle(short) __asm__("sound_GetChannelFromHandle");
void sound_Kill(int) __asm__("sound_Kill");
short sound_MobyPlay(unsigned int, unsigned int, MobyInstance *) __asm__("sound_MobyPlay");
static inline int AK_sound_IsMobyPlaying(MobyInstance *pMoby)
{
	int ret = 0;
	SoundData *channel = sound_GetChannelFromHandle(pMoby->soundChannel);
	if (channel && pMoby == channel->pMoby) ret = channel->active != 0;
	return ret;
}
void MobyPlayDesiredSound(MobyInstance *pMoby) __asm__("MobyPlayDesiredSound");
typedef int AK_qword[4];
extern AK_qword *vu1_bufPtr __asm__("vu1_bufPtr");
extern AK_qword *MobyVu1Marker __asm__("MobyVu1Marker");
extern int GSloc __asm__("GSloc");
int BuildMobyTextureDma(int) __asm__("BuildMobyTextureDma");
void VU1_texFlush() __asm__("VU1_texFlush");
extern int MobyClassRectify[] __asm__("MobyClassRectify");
extern char *AK_MobyClasses[] __asm__("MobyClassPtrs");
extern short MobyGsLocStash[] __asm__("MobyGsLocStash");
void PatchMobyGifs() __asm__("PatchMobyGifs");
extern unsigned short AK_vis_mpg_size __asm__("D_110920");
extern char AK_vis_mpg[] __asm__("D_110930");
extern long AK_moby_mpg[] __asm__("D_100080");
extern int active_vu1_mpg __asm__("active_vu1_mpg");
extern int FXReg __asm__("FXReg");
extern int vu1_bufId __asm__("vu1_bufId");
extern int vu1_maxUseBeforeMobys __asm__("vu1_maxUseBeforeMobys");
extern int vu1_useBeforeMobys __asm__("vu1_useBeforeMobys");
extern AK_qword *vu1_bufLimit __asm__("vu1_bufLimit");
extern char *vu1_DmaBuffers[2] __asm__("vu1_DmaBuffers");
extern int GSbase __asm__("GSbase");
void VU1_addDataRef(void *, int) __asm__("VU1_addDataRef");
void ZAddGSRegister(void *, unsigned int, unsigned long, int) __asm__("ZAddGSRegister");
extern void *MobyGroupData[] __asm__("MobyGroupData");
extern short MobyGroupDynamicDataChunk[][24] __asm__("MobyGroupDynamicDataChunk");
extern int MobyGrids[0x1000] __asm__("MobyGrids");

GAME_SECTION(CreateMoby) MobyInstance *CreateMoby(int mClass, int var_size)
{
	MobyInstance *pMoby = MobyInstancePermEnd;
	if (pMoby < MobyInstanceEnd) {
		do {
			if (pMoby->state >= 0xfe && (unsigned int)worldUpdateTime >= (unsigned int)pMoby->collCnt) {
				void *pVar = 0;
				if (var_size) pVar = AllocMobyVar(var_size);
				if (!pVar && var_size) break;
				if (pMoby->state == 0xff) pMoby[1].state = 0xff;
				InitMobyInstance(pMoby, mClass, 1);
				pMoby->pVar = pVar;
				if (var_size) FastMemSet(pVar, 0, var_size);
				if (numSpawnableMobys) numSpawnableMobys--;
				return pMoby;
			}
			pMoby++;
		} while (pMoby < MobyInstanceEnd);
	}
	if (g_PreventCountMobyGridUsageAndValidateMobyGridsFromBeingStripped) {
		CountMobyGridUsage();
		ValidateMobyGrids();
	}
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", InitMobyInstance);

GAME_SECTION(DeleteMoby) void DeleteMoby(MobyInstance *pMoby)
{
	pMoby->deathCnt++;
	if (pMoby < MobyInstancePermEnd) {
		pMoby->state = 0xfd;
	} else {
		pMoby->state = 0xfe;
		if (MobyDynamicGroup_IsDynamicGroup(pMoby->group)) MobyDynamicGroup_RemoveMoby(pMoby->group, pMoby);
		if (pMoby->pVar) {
			if ((int)pMoby->pVar >= (int)MobyVars && (int)pMoby->pVar < (int)(MobyVars + MobyVarsBlockCnt * 0x40)) {
				FreeMobyVar(pMoby->pVar);
				pMoby->pVar = 0;
			}
		}
		while (pMoby->pManipulator) DetachManipulator(pMoby, pMoby->pManipulator);
	}
	pMoby->collCnt = worldUpdateTime + 2;
	UpdateMobyGrids(pMoby, 0x80807f7f);
	JointCacheMarkDeleted(pMoby);
	CleanupAnimLayers(pMoby);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", SetupMobyVars);

GAME_SECTION(MobyPlayDesiredSound) void MobyPlayDesiredSound(MobyInstance *pMoby)
{
	unsigned int b_no_anim_update = 0;
	if (AK_g_gameType != 1 || !GB_IsMobyAHero(pMoby)) {
		if (pMoby->modeBits & 0x40) b_no_anim_update = 1;
	}
	if (AK_sound_IsMobyPlaying(pMoby)) {
		SoundData *channel = sound_GetChannelFromHandle(pMoby->soundChannel);
		if (channel->pMoby == pMoby) {
			if (channel->id == pMoby->soundDesired && !b_no_anim_update && !(pMoby->bangles & 0x8000)) return;
			sound_Kill(pMoby->soundChannel);
		}
		pMoby->soundChannel = -1;
	} else {
		if (pMoby->soundDesired == 0xff) return;
		if (b_no_anim_update) return;
		if (pMoby->bangles & 0x8000) return;
		if (pMoby->modeBits2 & 4) return;
		pMoby->soundChannel = sound_MobyPlay(pMoby->soundDesired, 4, pMoby);
	}
}

GAME_SECTION(MobyMayaFrame) float MobyMayaFrame(MobyInstance *pMoby)
{
	short *timestamp_table = (short *)((char *)pMoby->animSeq + 0x20);
	int key = (int)pMoby->animSeqT;
	float t = pMoby->animSeqT - (float)key;
	float step = timestamp_table[key * 2];
	float maya = timestamp_table[key * 2 + 1];
	return maya * 0.0625f + t * step * 0.5f;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", SetMobyCollPill);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", GetMobyBangleStats);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", GetMobyBangleVolume);

GAME_SECTION(MobyCornExists) int MobyCornExists(MobyInstance *pMoby, int bangle_index)
{
	if (!pMoby->pClass->corncob) return 0;
	unsigned char *corn_array = (unsigned char *)pMoby->pClass + pMoby->pClass->corncob * 16;
	return corn_array[bangle_index + 1] != 0xff;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", GetMobyCornVerts);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", GetMobyShadowVolumes);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", GetMobyShadowVolumesAndJoints);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", AttachManipulator);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", DetachManipulator);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", GetMobyJointMatrix);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", GetMobyJointWorld);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", func_0046CA08);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", GetMobyJointLocs);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", func_0046CAE0);

GAME_SECTION(DmaMobyTextures) void DmaMobyTextures()
{
	AK_qword *dmaMarker;
	dmaMarker = vu1_bufPtr++;
	(*MobyVu1Marker)[0] = 0x20000000;
	(*MobyVu1Marker)[1] = (int)vu1_bufPtr;
	(*MobyVu1Marker)[2] = 0;
	(*MobyVu1Marker)[3] = 0;
	GSloc = BuildMobyTextureDma(GSloc);
	VU1_texFlush();
	(*vu1_bufPtr)[0] = 0x20000000;
	(*vu1_bufPtr)[1] = (int)(MobyVu1Marker + 1);
	(*vu1_bufPtr)[2] = 0;
	(*vu1_bufPtr)[3] = 0;
	vu1_bufPtr++;
	(*dmaMarker)[0] = 0x20000000;
	(*dmaMarker)[1] = (int)vu1_bufPtr;
	(*dmaMarker)[2] = 0;
	(*dmaMarker)[3] = 0;
}

GAME_SECTION(PatchMobyGifs) void PatchMobyGifs()
{
	int *pClass;
	for (pClass = MobyClassRectify; *pClass >= 0; pClass++) {
		unsigned char *gifUsage = *(unsigned char **)(AK_MobyClasses[*pClass] + 0x20);
		for (;; gifUsage += 0x10) {
			unsigned int *pGif = (unsigned int *)(*(int *)(gifUsage + 0xc) & 0x7fffffff);
			unsigned char *pTex = gifUsage;
			while (*pTex != 0xff) {
				short *pLocs = &MobyGsLocStash[*pTex * 2];
				if (pLocs[0]) pGif[0xc] = (pGif[0xc] & 0xffffc000) | pLocs[0];
				if (pLocs[1]) pGif[0x10] = (pGif[0x10] & 0xffffc000) | pLocs[1];
				pTex++;
				pGif += 0x10;
			}
			if (*(int *)(gifUsage + 0xc) < 0) break;
		}
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", func_0046CCB0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", ProcessMobyShadows);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", ProcessMobyTeamTexs);

GAME_SECTION(ProcessMobyAnimData) void ProcessMobyAnimData()
{
	FlushCache(0);
	FastMemCopy16((void *)0x70003800, MobyAnimMicrocode, 0x800);
	MobyAnimProc(EngScratchPad, SkinVertexCache);
}

GAME_SECTION(InitMobyClassDists) void InitMobyClassDists()
{
	FastMemSet((void *)0x70003a00, 0x40000000, 0x3c0);
}

GAME_SECTION(StashMobyClassDists) void StashMobyClassDists()
{
	FastMemCopy16(g_MobyClassDistsStash, (void *)0x70003a00, 0x3c0);
}

GAME_SECTION(RestoreMobyClassDists) void RestoreMobyClassDists()
{
	FastMemCopy16((void *)0x70003a00, g_MobyClassDistsStash, 0x3c0);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", DrawMobysSetup);

GAME_SECTION(DrawMobyList) void DrawMobyList(MobyInstance *pMoby, int moby_cnt, int flags)
{
	VU0_loadMicroProgram(_dma_7);
	VU1_addGSregister(0x47, 0x5360b, 0);
	FlushCache(0);
	RestoreMobyClassDists();
	MobyAnimPtr = MobyProc(pMoby, MobyAnimPtr, moby_cnt, flags);
	StashMobyClassDists();
	MobyAnimPtr = (char *)MobyAnimPtr - 0x10;
}

GAME_SECTION(DrawMobysCleanup) void DrawMobysCleanup()
{
	DmaMobyTextures();
	ProcessMobyAnimData();
	if (MobyShadowMarker) ProcessMobyShadows();
	if (MobyTeamTexList < MobyTeamTexPtr) ProcessMobyTeamTexs();
}

GAME_SECTION(DrawMobys) void DrawMobys()
{
	int flags;
	DrawMobysSetup();
	VU0_loadMicroProgram(_dma_7);
	InitMobyClassDists();
	flags = 1;
	if (MobySplitScreen) {
		MobySplitScreen = 0;
		flags = 3;
	}
	MobyAnimPtr = MobyProc(MobyInstances, MobyAnimPtr, -1, flags);
	DrawMobysCleanup();
}

GAME_SECTION(MobyGetInterface) void *MobyGetInterface(int iMobyOClass, int iExpectedInterfaceSize)
{
	return MobyGetInterface(iMobyOClass, 0, iExpectedInterfaceSize);
}

GAME_SECTION(MobyGetInterface___dupe2) void *MobyGetInterface(int oClass, int id, int param)
{
	long args[2];
	mobyfuncs *funcs = GetMobyFunctions(oClass);
	if (funcs && funcs->getMobyInterface) {
		return funcs->getMobyInterface(oClass, id, args);
	}
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", func_0046D488);

GAME_SECTION(MobyDynamicGroup_RemoveMoby) int MobyDynamicGroup_RemoveMoby(int iGroup, MobyInstance *pRemoveMoby)
{
	int iMemberIndex;
	short *pDynamicGroup;
	if (!MobyGroupData[iGroup]) return 0;
	pDynamicGroup = MobyGroupDynamicDataChunk[iGroup - MobyGroupFirstDynamic];
	for (iMemberIndex = 0; iMemberIndex < 24; iMemberIndex++) {
		if ((pDynamicGroup[iMemberIndex] & 0x7fff) == pRemoveMoby - MobyInstances) {
			pRemoveMoby->group = 0xff;
			if (pDynamicGroup[iMemberIndex] & 0x8000) {
				if (iMemberIndex == 0) MobyGroupData[iGroup] = 0;
				else pDynamicGroup[iMemberIndex - 1] |= 0x8000;
			} else {
				for (; iMemberIndex < 23; iMemberIndex++) {
					pDynamicGroup[iMemberIndex] = pDynamicGroup[iMemberIndex + 1];
				}
			}
			return 1;
		}
	}
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", func_0046D588);

GAME_SECTION(MobyDynamicGroup_IsDynamicGroup) int MobyDynamicGroup_IsDynamicGroup(int iGroup)
{
	if (iGroup == 0xff) return 0;
	return !(iGroup < MobyGroupFirstDynamic);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", func_0046D5B0);

GAME_SECTION(CollSphereFail) void CollSphereFail(void *pSkip_)
{
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", CountMobyGridUsage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", ValidateMobyGrids);

GAME_SECTION(Moby2dReset) void Moby2dReset()
{
	int id;
	g_Moby2dCon.active = 0;
	for (id = 0; id < 8; id++) {
		Moby2dDelete(id);
	}
}

GAME_SECTION(Moby2dSetWindow) void Moby2dSetWindow(int left, int right, int top, int bottom)
{
	int center_x = (left + right) >> 1;
	int center_y = (top + bottom) >> 1;
	g_Moby2dCon.screen_ofs_x = (center_x - (Scrn.size_x >> 1)) * 0x10;
	g_Moby2dCon.screen_ofs_y = (center_y - (Scrn.size_y >> 1)) * 0x10;
	g_Moby2dCon.scissor_l = left;
	g_Moby2dCon.scissor_r = right;
	g_Moby2dCon.scissor_t = top;
	g_Moby2dCon.scissor_b = bottom;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", Moby2dCreate);

GAME_SECTION(Moby2dDelete) void Moby2dDelete(int id)
{
	if (g_Moby2dCon.mobys[id]) {
		DeleteMoby(g_Moby2dCon.mobys[id]);
		g_Moby2dCon.mobys[id] = 0;
	}
}

GAME_SECTION(Moby2dGetPtr) MobyInstance *Moby2dGetPtr(int id)
{
	VU0_loadMicroProgram(_dma_1);
	return g_Moby2dCon.mobys[id];
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", Moby2dDraw);

GAME_SECTION(SetMobyLightDefault) void SetMobyLightDefault(moby *pMoby_)
{
	if (g_pLightCuboids == 0) {
		pMoby_->lights = 0x40404000000000UL;
	} else {
		char *pCuboid = (char *)g_pLightCuboids + *g_pLightCuboids;
		unsigned char light = *(unsigned char *)(pCuboid + 0x4a);
		SetMobyLights(pMoby_, *(int *)(pCuboid + 0x40), light, light, 0);
	}
}
