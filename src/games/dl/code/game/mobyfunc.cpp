#include "common.h"
#include "game_section.h"


struct MobyClass {
	/* 0x00 */ char unk00[0x2e];
	/* 0x2e */ short corncob;
};
struct MobyInstance {
	/* 0x00 */ char unk00[0x24];
	/* 0x24 */ MobyClass *pClass;
	/* 0x28 */ char unk28[0xd8];
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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", CreateMoby);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", InitMobyInstance);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", DeleteMoby);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", SetupMobyVars);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", MobyPlayDesiredSound);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", MobyMayaFrame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", SetMobyCollPill);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", GetMobyBangleStats);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", GetMobyBangleVolume);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", MobyCornExists);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", DmaMobyTextures);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", PatchMobyGifs);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", DrawMobyList);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", MobyDynamicGroup_RemoveMoby);

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
