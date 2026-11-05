#include "common.h"
#include "game_section.h"

/* mobyupd */
struct mobyfuncs {
	/* 0x00 */ void *funcs[8];
};
struct MobyInstance {
	/* 0x00 */ char unk00[0x22];
	/* 0x22 */ unsigned char mClass;
	/* 0x23 */ char unk23[0xbc - 0x23];
	/* 0xbc */ short oClass;
};
struct mobyVtblEntry {
	/* 0x00 */ int oClass;
	/* 0x04 */ void *update;
	/* 0x08 */ mobyfuncs *funcs;
};
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


typedef unsigned int qword __attribute__((mode(TI)));
/* movieoverlay */
struct fsAABuff {
	/* 0x00 */ char unk00[0xc0];
	/* 0xc0 */ char giftagDrawSmall[0x10];
};
struct SceneDef {
	/* 0x00 */ char unk00[0x74];
	/* 0x74 */ int iframe;
	/* 0x78 */ char unk78[0x100];
};
struct MovieQueue {
	/* 0x00 */ int intro;
	/* 0x04 */ int unk04[3];
};
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
struct StashInfo {
	/* 0x00 */ char *base;
	/* 0x04 */ int size;
	/* 0x08 */ int unk08[10];
	/* 0x30 */ char *free;
	/* 0x34 */ int block;
	/* 0x38 */ char *gadgetram;
};
struct StashBlock {
	/* 0x00 */ char *ram;
	/* 0x04 */ int qwc;
	/* 0x08 */ const char *comment;
	/* 0x0c */ int pad;
};
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
struct GSmemDef {
	/* 0x00 */ int unk00[5];
	/* 0x14 */ int perm_debug_font;
	/* 0x18 */ int unk18[13];
	/* 0x4c */ int stash_font;
};
struct PifHeader;
extern wadMisc g_wad __asm__("D_001C2040");
extern GSmemDef GSmem __asm__("GSmem");
extern char MobyGrids[] __asm__("MobyGrids");
extern unsigned long DebugFontTex0 __asm__("DebugFontTex0");
struct Fs {
	static void Sync(unsigned int) __asm__("Sync");
	static int Load(int, unsigned int, unsigned int, unsigned int, unsigned int, void *, void *) __asm__("Load");
};
void LoadPifAsPSMT8H(PifHeader *pPif, unsigned long *gsRegs, int tex_loc, int pal_loc) __asm__("LoadPifAsPSMT8H");
void LoadDebugFont() __asm__("LoadDebugFont");

/* tiefunc */
struct TieInstance {
	/* 0x00 */ char unk00[0x14];
	/* 0x14 */ unsigned short cache_loc;
	/* 0x16 */ short cache_size;
	/* 0x18 */ short unk18;
	/* 0x1a */ unsigned short lights;
	/* 0x1c */ char unk1c[3];
	/* 0x1f */ unsigned char cache_lod;
};
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
struct PointLight {
	/* 0x00 */ char unk00[0x20];
};
struct PL_Data {
	/* 0x00 */ short tie_offset;
	/* 0x02 */ short tie_count;
	/* 0x04 */ short shrub_offset;
	/* 0x06 */ short shrub_count;
	/* 0x08 */ short tfrag_offset;
	/* 0x0a */ short tfrag_count;
	/* 0x0c */ short *list;
	/* 0x10 */ char unk10[0x20];
};
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
struct TfragPatch {
	/* 0x00 */ int *ptr;
	/* 0x04 */ int count;
};
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
