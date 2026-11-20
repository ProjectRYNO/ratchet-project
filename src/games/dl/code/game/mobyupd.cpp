#include "common.h"
#include "game_section.h"
#include "mobyutil.h"
#include "mobyupd.h"
#include "lights.h"
#include "tiefunc.h"
#include "tfragfunc.h"
#include "gameglobals.h"
#include "stash.h"
#include "globals.h"
#include "draw.h"

/* mobyupd */
extern mobyVtblEntry mobyupdate_vtbl[] __asm__("D_003F0E80");
extern mobyfuncs empty_moby_funcs __asm__("D_3D8C70");
extern mobyfuncs default_moby_funcs[] __asm__("D_3F0E8C");
extern short MobyClassRef[] __asm__("MobyClassRef");
extern short MobyClassNullRef[] __asm__("MobyClassNullRef");
extern unsigned char MobyClassFuncsIndex[] __asm__("MobyClassFuncsIndex");
extern unsigned char MobyClassNullFuncsIndex[] __asm__("MobyClassNullFuncsIndex");
mobyfuncs *GetMobyFunctions(MobyInstance *pMoby) __asm__("GetMobyFunctions");

extern unsigned char MobyClassLookup[] __asm__("MobyClassLookup");
mobyfuncs *GetMobyFunctions(int oClass) __asm__("GetMobyFunctions___dupe2");


/* movieoverlay */
typedef int qwordWords[4];
extern qwordWords *vu1_bufPtr __asm__("vu1_bufPtr");
extern fsAABuff *pAAbuff __asm__("pAAbuff");
extern long aaMovieDisplayRegs[37] __asm__("aaMovieDisplayRegs");
extern SceneDef Scene __asm__("Scene");
extern MovieQueue gMovieQueue __asm__("gMovieQueue");
void DrawLogoAndStart() __asm__("DrawLogoAndStart");
void DrawSubtitles() __asm__("DrawSubtitles");
void UpdateMovieOverlay(unsigned long *vu_ptr, bool init) __asm__("UpdateMovieOverlay");
extern void *MobyClassUpdate[] __asm__("MobyClassUpdate");
extern void *MobyClassNullUpdate[] __asm__("MobyClassNullUpdate");
extern int MobyClassIndex __asm__("MobyClassIndex");
extern int MobyClassNullIndex __asm__("MobyClassNullIndex");
void SetupMobyFunctions(int oClass, int null_moby) __asm__("SetupMobyFunctions");
/* stash */
extern StashInfo Stash __asm__("Stash");
extern StashBlock Blocks[64] __asm__("Blocks");
extern char g_StashEEMemory[] __asm__("g_StashEEMemory");
extern char *g_StashMainMemory __asm__("D_21DD7C");
extern char *g_StashGadgetMemory __asm__("g_StashGadgetMemory");
extern int g_gameType __asm__("g_gameType");
void FastMemSet(void *, int, int) __asm__("FastMemSet");
void FastMemCopy(void *, const void *, int) __asm__("FastMemCopy");
void Stash_InitOnce() __asm__("Stash_InitOnce");
int Stash_SendData(void *src, int data_qwc, int alloc_qwc, const char *comment) __asm__("Stash_SendData");
/* bloaders */
struct wadMisc {
	/* 0x00 */ char unk00[0x64c];
	/* 0x64c */ int sector;
	/* 0x650 */ int debugfontOffset;
	/* 0x654 */ int debugfontLength;
};
struct PifHeader;
extern wadMisc g_wad __asm__("D_001C2040");
extern GSMEM GSmem __asm__("GSmem");
extern char MobyGrids[] __asm__("MobyGrids");
extern unsigned long DebugFontTex0 __asm__("DebugFontTex0");
struct Fs {
	static void Sync(unsigned int) __asm__("Sync");
	static int Load(int, unsigned int, unsigned int, unsigned int, unsigned int, void *, void *) __asm__("Load");
};
void LoadPifAsPSMT8H(PifHeader *pPif, unsigned long *gsRegs, int tex_loc, int pal_loc) __asm__("LoadPifAsPSMT8H");
void LoadDebugFont() __asm__("LoadDebugFont");

/* tiefunc */
struct MemSlotsDef {
	/* 0x00 */ int unk00[1];
	/* 0x04 */ void *tie_cache;
	/* 0x08 */ int unk08[0x40];
};
extern MemSlotsDef MemSlots __asm__("D_0023AB10");
extern char TieCacheListBuf[] __asm__("TieCacheListBuf");
extern TieInstance *TieInstances __asm__("TieInstances");
extern TieInstance *TieInstanceEnd __asm__("TieInstanceEnd");
extern void *TieCache __asm__("TieCache");
extern char *TieCacheList __asm__("TieCacheList");
extern int TieCacheListHead __asm__("TieCacheListHead");
extern int TieCacheListTail __asm__("TieCacheListTail");
extern int TieCacheListTop __asm__("TieCacheListTop");
extern TieInstance *SS_TieInstances[4] __asm__("SS_TieInstances");
extern TieInstance *SS_TieInstanceEnd[4] __asm__("SS_TieInstanceEnd");
extern int SS_TieCacheListHead[4] __asm__("SS_TieCacheListHead");
extern int SS_TieCacheListTail[4] __asm__("SS_TieCacheListTail");
extern int SS_TieCacheListTop[4] __asm__("SS_TieCacheListTop");
extern int *gNumLocalHeroes __asm__("gNumLocalHeroes");
void ResetTieLightingCache() __asm__("ResetTieLightingCache");
/* lights */
extern PointLight PointLights[] __asm__("PointLights");
extern PL_Data PointLightData[] __asm__("PointLightData");
void FastMemZero16(void *, int) __asm__("FastMemZero16");
void TieDetachPointLight(short *, short *, int) __asm__("TieDetachPointLight");
void ShrubDetachPointLight(short *, short *, int) __asm__("ShrubDetachPointLight");
void TfragDetachPointLight(short *, short *, int) __asm__("TfragDetachPointLight");
void DetachPointLight(int index) __asm__("DetachPointLight");
void DeletePointLight(int index) __asm__("DeletePointLight");
/* path */
struct Path {
	/* 0x00 */ int nNodes;
};
int StepPathNode(Path *pPath, int curNode, int step, int wrap) __asm__("StepPathNode");
/* tfragfunc */
extern TfragPatch TfragGifRectify[] __asm__("TfragGifRectify");
extern short TfragGsLocStash[][2] __asm__("TfragGsLocStash");
void PatchTfragGifs() __asm__("PatchTfragGifs");
extern qwordWords *TfragVu1Marker __asm__("TfragVu1Marker");
extern int TfragGsMax __asm__("TfragGsMax");
extern int GSloc __asm__("GSloc");
void ComputeTfragTextureUsage() __asm__("ComputeTfragTextureUsage");
int BuildTfragTextureDma(int) __asm__("BuildTfragTextureDma");
void VU1_texFlush() __asm__("VU1_texFlush");
void DmaTfragTextures() __asm__("DmaTfragTextures");

GAME_SECTION(SetupMobyFunctions) void SetupMobyFunctions(int oClass, int null_moby)
{
	int i;
	for (i = 0; mobyupdate_vtbl[i].oClass != -1 && mobyupdate_vtbl[i].oClass != oClass; i++) {
	}
	if (null_moby) {
		MobyClassNullUpdate[MobyClassNullIndex] = mobyupdate_vtbl[i].update;
		MobyClassNullFuncsIndex[MobyClassNullIndex] = mobyupdate_vtbl[i].funcs - default_moby_funcs;
	} else {
		MobyClassUpdate[MobyClassIndex] = mobyupdate_vtbl[i].update;
		MobyClassFuncsIndex[MobyClassIndex] = mobyupdate_vtbl[i].funcs - default_moby_funcs;
	}
}

GAME_SECTION(GetMobyFunctions) mobyfuncs *GetMobyFunctions(MobyInstance *pMoby)
{
	unsigned int mClass;
	if (mobyupdate_vtbl[0].oClass == -1) return &empty_moby_funcs;
	mClass = pMoby->mClass;
	if (MobyClassRef[mClass] != pMoby->oClass) {
		if (MobyClassNullRef[mClass] != pMoby->oClass) return default_moby_funcs;
		return &default_moby_funcs[MobyClassNullFuncsIndex[mClass]];
	}
	return &default_moby_funcs[MobyClassFuncsIndex[mClass]];
}

GAME_SECTION(GetMobyFunctions___dupe2) mobyfuncs *GetMobyFunctions(int oClass)
{
	int mClass;
	if (mobyupdate_vtbl[0].oClass == -1) return &empty_moby_funcs;
	mClass = MobyClassLookup[oClass];
	if (mClass == 0xff) return default_moby_funcs;
	if (MobyClassRef[mClass] != oClass) return &default_moby_funcs[MobyClassNullFuncsIndex[mClass]];
	return &default_moby_funcs[MobyClassFuncsIndex[mClass]];
}
