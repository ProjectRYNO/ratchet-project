#include "common.h"
#include "game_section.h"

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


typedef unsigned int qword __attribute__((mode(TI)));
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
extern void *MobyClassUpdate[] __asm__("MobyClassUpdate");
extern void *MobyClassNullUpdate[] __asm__("MobyClassNullUpdate");
extern int MobyClassIndex __asm__("MobyClassIndex");
extern int MobyClassNullIndex __asm__("MobyClassNullIndex");
mobyfuncs *GetMobyFunctions(MobyInstance *pMoby) __asm__("GetMobyFunctions");
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

GAME_SECTION(UpdateMovieOverlay) void UpdateMovieOverlay(unsigned long *vu_ptr, bool init)
{
	vu1_bufPtr = (qwordWords *)vu_ptr;
	*(int *)vu_ptr = 0x30000009;
	(*vu1_bufPtr)[1] = (unsigned int)pAAbuff->giftagDrawSmall & 0xfffffff;
	(*vu1_bufPtr)[2] = 0;
	(*vu1_bufPtr)[3] = 0x50000009;
	vu1_bufPtr[1][0] = 0x30000025;
	vu1_bufPtr[1][1] = (int)aaMovieDisplayRegs;
	vu1_bufPtr[1][2] = 0;
	vu1_bufPtr[1][3] = 0x50000025;
	vu1_bufPtr = vu1_bufPtr + 2;
	Scene.iframe = Scene.iframe + 1;
	if (gMovieQueue.intro != 0) {
		DrawLogoAndStart();
	} else {
		DrawSubtitles();
	}
	(*vu1_bufPtr)[0] = 0x70000000;
	(*vu1_bufPtr)[1] = 0;
	vu1_bufPtr = vu1_bufPtr + 1;
}
