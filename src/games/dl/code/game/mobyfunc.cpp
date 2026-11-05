#include "common.h"
#include "game_section.h"


struct MobyClass {
	/* 0x00 */ char unk00[0x2e];
	/* 0x2e */ short corncob;
};
struct MobyInstance {
	/* 0x00 */ char unk00[0x24];
	/* 0x24 */ MobyClass *pClass;
};
struct Moby2dCon {
	/* 0x00 */ MobyInstance *mobys[8];
	/* 0x20 */ int active;
	/* 0x24 */ int unk24[3];
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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", ProcessMobyAnimData);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", DrawMobysCleanup);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", DrawMobys);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", MobyGetInterface);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", MobyDynamicGroup_IsDynamicGroup);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", func_0046D5B0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", CollSphereFail);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", Moby2dSetWindow);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/mobyfunc", SetMobyLightDefault);
