#include "common.h"
#include "game_section.h"

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
void DetachPointLight(int index) __asm__("DetachPointLight");
void DeletePointLight(int index) __asm__("DeletePointLight");


/* mobyupd */
struct mobyfuncs {
	/* 0x00 */ void *funcs[8];
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
extern unsigned char MobyClassLookup[] __asm__("MobyClassLookup");
extern unsigned char MobyClassFuncsIndex[] __asm__("MobyClassFuncsIndex");
extern unsigned char MobyClassNullFuncsIndex[] __asm__("MobyClassNullFuncsIndex");
mobyfuncs *GetMobyFunctions(int oClass) __asm__("GetMobyFunctions___dupe2");
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
void TieDetachPointLight(short *, short *, int) __asm__("TieDetachPointLight");
void ShrubDetachPointLight(short *, short *, int) __asm__("ShrubDetachPointLight");
void TfragDetachPointLight(short *, short *, int) __asm__("TfragDetachPointLight");
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
typedef int qwordWords[4];
extern qwordWords *vu1_bufPtr __asm__("vu1_bufPtr");
extern qwordWords *TfragVu1Marker __asm__("TfragVu1Marker");
extern int TfragGsMax __asm__("TfragGsMax");
extern int GSloc __asm__("GSloc");
void ComputeTfragTextureUsage() __asm__("ComputeTfragTextureUsage");
int BuildTfragTextureDma(int) __asm__("BuildTfragTextureDma");
void VU1_texFlush() __asm__("VU1_texFlush");
void DmaTfragTextures() __asm__("DmaTfragTextures");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/lights", CreatePointLight);

GAME_SECTION(DeletePointLight) void DeletePointLight(int index)
{
	if ((unsigned int)index < 8) {
		DetachPointLight(index);
		FastMemZero16(&PointLights[index], 0x20);
		FastMemZero16(&PointLightData[index], 0x30);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/lights", func_004612A8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/lights", DetachPointLight);
