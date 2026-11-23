#include "common.h"
#include "game_section.h"
#include "mobyutil.h"
#include "draw.h"
#include "wad.h"
#include "gameglobals.h"


struct MobyClass;
struct ArmorLoadDef {
	/* 0x00 */ int armor_index;
	/* 0x04 */ MobyClass *armor_ram_base;
	/* 0x08 */ int unk08;
	/* 0x0c */ MobyClass *armor_ratchet_class;
	/* 0x10 */ int unk10[4];
	/* 0x20 */ int armor2_index;
	/* 0x24 */ MobyClass *armor2_ram_base;
	/* 0x28 */ int unk28;
	/* 0x2c */ MobyClass *armor2_ratchet_class;
	/* 0x30 */ int unk30[4];
	/* 0x40 */ int bot_tex_index;
	/* 0x44 */ int bot_tex_cnt;
	/* 0x48 */ unsigned long bot_tex0[2];
	/* 0x58 */ int landstalker_tex_index;
	/* 0x5c */ int landstalker_tex_cnt;
	/* 0x60 */ unsigned long landstalker_tex0[2];
	/* 0x70 */ int dropship_tex_index;
	/* 0x74 */ int dropship_tex_cnt;
	/* 0x78 */ unsigned long dropship_tex0[3];
};
extern ArmorLoadDef ArmorLoad __asm__("ArmorLoad");
extern SceneDef Scene __asm__("Scene");
struct MemSlotsVu1 {
	/* 0x00 */ char *vu1_chain1;
	/* 0x04 */ int unk04[3];
};
extern MemSlotsVu1 MemSlotsChain __asm__("D_0023AB10");
extern int vu1_bufSize __asm__("vu1_bufSize");
struct LevelBankEntry {
	/* 0x00 */ int offset;
	/* 0x04 */ int size;
};
struct LevelDataHeader {
	/* 0x00 */ int unk00[8];
	/* 0x20 */ LevelBankEntry banks[1];
};
struct LevelLoadDef {
	/* 0x00 */ char *level_data;
	/* 0x04 */ int unk04[3];
};
extern LevelLoadDef LevelLoad __asm__("LevelLoad");
struct HudHeader {
	/* 0x00 */ char unk00[0x74];
	/* 0x74 */ char *bank_load[16];
};
struct HudDef {
	/* 0x00 */ int unk00[3];
	/* 0x0c */ HudHeader *header;
	/* 0x10 */ int unk10[4];
};
extern HudDef Hud __asm__("Hud");
void LoadArmor(int, int) __asm__("LoadArmor");
void RemapArmor(MobyClass *, MobyClass *) __asm__("RemapArmor");
void PopMobyStack() __asm__("PopMobyStack");
void ParseNpcChunk() __asm__("ParseNpcChunk");
int FastDecompress(char *, char *) __asm__("FastDecompress");
bool IsSceneLevel() __asm__("IsSceneLevel");
void ResetGadgetBank() __asm__("ResetGadgetBank");
void SwitchMobyToCoOpArmor(MobyInstance *) __asm__("SwitchMobyToCoOpArmor");
void SwitchArmor(int) __asm__("SwitchArmor");
void SwitchArmor2(int) __asm__("SwitchArmor2");
void UnloadNpcMobys() __asm__("UnloadNpcMobys");
void ParseSpaceSceneChunk(int) __asm__("ParseSpaceSceneChunk");
void LoadCompressedHudBank(int, char *) __asm__("LoadCompressedHudBank");

struct WadLoc {
	/* 0x0 */ int offset;
	/* 0x4 */ int length;
};
extern wadinfo g_wad __asm__("D_001C2040");
extern char g_fsLoadQueue[] __asm__("D_001CFAF8");
void Sync(int) __asm__("Sync");
void Load(int, void *, int, int, void *, void *, void *) __asm__("Load");
void LoadAsync(int, void *, int, int, void *, void *, void *) __asm__("LoadAsync");
int LoadNpcMobys(int, int) __asm__("LoadNpcMobys");
int LoadNpcSubtitles(int, int) __asm__("LoadNpcSubtitles");
int PreLoadNpcChunk(int) __asm__("PreLoadNpcChunk");
extern GSMEM GSmem __asm__("GSmem");
extern int vu1_bufId __asm__("vu1_bufId");
extern void *vu1_DmaBuffers[2] __asm__("vu1_DmaBuffers");
void VU1_syncChain(int) __asm__("VU1_syncChain");
int music_Sync(int) __asm__("music_Sync");
void AttachPaintJobTextures(int, int, void *, int *, unsigned long *) __asm__("AttachPaintJobTextures");
void LoadBotTextures(int) __asm__("LoadBotTextures");
void LoadLandStalkerTextures(int) __asm__("LoadLandStalkerTextures");
void LoadDropshipTextures(int) __asm__("LoadDropshipTextures");

struct LdCollOutput {
	/* 0x00 */ int unk00[4];
	/* 0x10 */ int call_cnt;
	/* 0x14 */ int damage_next;
	/* 0x18 */ int unk18[2];
};
extern LdCollOutput CollOutput __asm__("CollOutput");
extern char g_HeroArr[] __asm__("g_Hero");
extern char ResetLevelBlock_229A80[] __asm__("D_229A80");
extern char MobyGrids[] __asm__("MobyGrids");
extern char MobyGridAlloc[] __asm__("MobyGridAlloc");
extern float NtscPalSpeedAdjuster __asm__("NtscPalSpeedAdjuster");
extern int g_gameTypeLd __asm__("g_gameType");
void FastMemSet(void *, int, int) __asm__("FastMemSet");
void FastMemZero16(void *, int) __asm__("FastMemZero16");
void MobyResetAnimLayerCache() __asm__("MobyResetAnimLayerCache");
void InitMobyJointCache() __asm__("InitMobyJointCache");
extern "C" void srand(unsigned int);
void SetNtscPalTiming(int) __asm__("SetNtscPalTiming");
void ResetLevelData() __asm__("ResetLevelData");
struct LdMemSlots {
	/* 0x00 */ char unk00[0xac];
	/* 0xac */ char *perm_patch;
	/* 0xb0 */ int unkb0[4];
};
extern LdMemSlots LdMemSlotsV __asm__("D_0023AB10");
extern wadinfo g_wadMisc __asm__("D_001C2040");
extern char LevelDataTop[] __asm__("D_1E99F80");
extern volatile LevelLoadDef LevelLoadV __asm__("LevelLoad");
int LoadFrontData() __asm__("LoadFrontData");
struct MobyStackDef {
	/* 0x00 */ int in_use;
	/* 0x04 */ int unk04[3];
};
extern MobyStackDef MobyStack __asm__("MobyStack");
void FastMemCopyReverse16(void *, void *, int) __asm__("FastMemCopyReverse16");
void PushMobyStack(int, void *, void *, int, bool) __asm__("PushMobyStack");
void ParseNpcMobys() __asm__("ParseNpcMobys");

void SetUpVisGif(int *, short *, int, int, int, int, int) __asm__("SetUpVisGif");
void SetUpVisGifViewer(int *, int, int, int, int, int) __asm__("SetUpVisGifViewer");
void ParseMobyGifs(void *packets, short *tex_defs, char *tex_refs, int total_packet_cnt) __asm__("ParseMobyGifs");
extern char MobyClassLookup[] __asm__("MobyClassLookup");
extern int MobyClassNullIndex __asm__("MobyClassNullIndex");
extern short MobyClassNullRef[] __asm__("MobyClassNullRef");
extern int MobyClassIndex __asm__("MobyClassIndex");
extern short MobyClassRef[] __asm__("MobyClassRef");
extern MobyClass *MobyClasses[] __asm__("MobyClassPtrs");
extern unsigned int MobyMipDists[] __asm__("MobyMipDists");
void SetupMobyFunctions(int, int) __asm__("SetupMobyFunctions");
void ParseMobyClass(MobyClass *, short *, char *, int) __asm__("ParseMobyClass");
void ParseMoby(char *data, short *tex_defs, char *tex_refs, int oClass) __asm__("ParseMoby");

extern "C" {
	void FlushCache(int);
	int sceGsSetDefLoadImage(void *, short, short, short, short, short, short, short);
	int sceGsExecLoadImage(void *, void *);
	int sceGsSetDefStoreImage(void *, short, short, short, short, short, short, short);
	int sceGsExecStoreImage(void *, void *);
	int sceGsSyncPath(int, unsigned short);
}
struct sceGsLoadImageBuf {
	/* 0x00 */ unsigned long q[12];
};
struct sceGsStoreImageBuf {
	/* 0x00 */ unsigned long q[14];
};
void SwizzleTextureInPlace(char *tex_data, int tex_format, int x_size, int y_size) __asm__("SwizzleTextureInPlace");
extern MobyInstance *MobyInstances __asm__("MobyInstances");
extern MobyInstance *MobyInstanceEnd __asm__("MobyInstanceEnd");
extern int GSbase __asm__("GSbase");
extern int MobyTexCnt __asm__("MobyTexCnt");
/* LevelLoad seen as a 4-byte object here: retail loads level_data with an lw macro (lui/lw same register) */
struct LevelLoadHead { char *level_data; };
extern LevelLoadHead LevelLoadHeadView __asm__("LevelLoad");

extern unsigned long ViewerGsRegs[] __asm__("ViewerGsRegs");
extern unsigned long GlassGsRegs[] __asm__("GlassGsRegs");
extern unsigned long ChromeGsRegs[] __asm__("D_00241CE0");

GAME_SECTION(IsSceneLevel) bool IsSceneLevel()
{
	return false;
}

JUNK_ASM(func_00461438,
	"\taddiu $29, $29, 0x110\n"
	"\tnop\n");

GAME_SECTION(SwizzleTextureInPlace) void SwizzleTextureInPlace(char *tex_data, int tex_format, int x_size, int y_size)
{
	int dbp = (0x400000 - x_size * y_size) >> 8;
	{
		int tbw = x_size >> 6;
		sceGsLoadImageBuf image;
		if (tbw < 1) tbw = 1;
		sceGsSetDefLoadImage(&image, dbp, tbw, 0x13, 0, 0, x_size, y_size);
		FlushCache(0);
		sceGsExecLoadImage(&image, tex_data);
		sceGsSyncPath(0, 0);
	}
	{
		int tbw = x_size >> 7;
		sceGsStoreImageBuf image;
		if (tbw < 1) tbw = 1;
		sceGsSetDefStoreImage(&image, dbp, tbw, 0, 0, 0, x_size >> 1, y_size >> 1);
		FlushCache(0);
		sceGsExecStoreImage(&image, tex_data);
		sceGsSyncPath(0, 0);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", ParseParticleTexs);

void ParseEffectTexs(int *, int) __asm__("ParseEffectTexs");
GAME_SECTION(ParseEffectTexs) void ParseEffectTexs(int *, int)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlui $2, %%hi(EffectTexs)\n"
		"\tdaddu $6, $4, $0\n"
		"\taddiu $8, $2, %%lo(EffectTexs)\n"
		"\tblez $5, .L00461738\n"
		"\tsw $0, -0x4777($28)\n" /* EffectTexCnt */
		"\taddiu $11, $0, 0x13\n"
		"\taddiu $10, $0, 0x14\n"
		"\taddiu $9, $0, 0x1e\n"
		".L004616B0:\n"
		"\tlw $2, 0x0($6)\n"
		"\taddiu $6, $6, 0x4\n"
		"\tlw $3, 0x0($6)\n"
		"\tsra $2, $2, 6\n"
		"\taddiu $6, $6, 0x4\n"
		"\tlw $4, 0x0($6)\n"
		"\tsra $3, $3, 6\n"
		"\taddiu $6, $6, 0x4\n"
		"\tlw $7, 0x0($6)\n"
		"\tsh $2, 0xa($8)\n"
		"\taddiu $6, $6, 0x4\n"
		"\tsh $3, 0x8($8)\n"
		"\tbgez $4, .L004616FC\n"
		"\tsh $11, 0xe($8)\n"
		"\tsh $10, 0xe($8)\n"
		"\tblezl $4, .L004616F4\n"
		"\tneg $4, $4\n"
		".L004616F4:\n"
		"\tblezl $7, .L004616FC\n"
		"\tneg $7, $7\n"
		".L004616FC:\n"
		"\tplzcw $2, $4\n"
		"\tplzcw $3, $7\n"
		"\tlui $4, %%hi(EffectTexCnt)\n"
		"\tlw $4, %%lo(EffectTexCnt)($4)\n"
		"\tsubu $2, $9, $2\n"
		"\tsubu $3, $9, $3\n"
		"\tsb $2, 0xc($8)\n"
		"\taddiu $4, $4, 0x1\n"
		"\tsb $3, 0xd($8)\n"
		"\tsd $0, 0x0($8)\n"
		"\tslt $2, $4, $5\n"
		"\tlui $1, %%hi(EffectTexCnt)\n"
		"\tsw $4, %%lo(EffectTexCnt)($1)\n"
		"\tbnez $2, .L004616B0\n"
		"\taddiu $8, $8, 0x10\n"
		".L00461738:\n"
		".set at\n.set reorder" : : : "memory");
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", ParseSky);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", LoadArmor);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", RemapArmor);

GAME_SECTION(SwitchArmor) void SwitchArmor(int armor_index)
{
	if (armor_index != ArmorLoad.armor_index) {
		LoadArmor(armor_index, 0);
		RemapArmor(ArmorLoad.armor_ram_base, ArmorLoad.armor_ratchet_class);
	}
}

GAME_SECTION(SwitchArmor2) void SwitchArmor2(int armor_index)
{
	if (armor_index != ArmorLoad.armor2_index) {
		LoadArmor(armor_index, 1);
		RemapArmor(ArmorLoad.armor2_ram_base, ArmorLoad.armor2_ratchet_class);
	}
}

GAME_SECTION(SwitchMobyToCoOpArmor) void SwitchMobyToCoOpArmor(MobyInstance *pMoby)
{
	pMoby->pClass = ArmorLoad.armor2_ram_base;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", AttachPaintJobTextures);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", LoadBotTextures);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", LoadLandStalkerTextures);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", LoadDropshipTextures);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", LoadHudBanks);

GAME_SECTION(LoadCompressedHudBank) void LoadCompressedHudBank(int bank, char *decomp)
{
	decomp = (char *)(((unsigned int)decomp + 0xf) & ~0xf);
	if (decomp) {
		FastDecompress((char *)(((LevelDataHeader *)LevelLoadHeadView.level_data)->banks[bank + 1].offset + (int)LevelLoadHeadView.level_data), decomp);
	}
	Hud.header->bank_load[bank] = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", SetUpVisGif);

GAME_SECTION(SetUpVisGifViewer) void SetUpVisGifViewer(int *pGif, int mip_dist, int filter, int u_clamp, int v_clamp, int index)
{
	unsigned long tex_0 = ViewerGsRegs[index * 3];
	unsigned long tex_1 = ViewerGsRegs[index * 3 + 1];
	unsigned long mip_0 = ViewerGsRegs[index * 3 + 2];
	if (index >= 0) {
		*(unsigned long *)pGif = (tex_1 & 0x1c) | 0x20 | (long)filter << 6 | (long)mip_dist << 32;
		pGif += 4;
		*(unsigned long *)pGif = (long)u_clamp | (long)v_clamp << 2 | (long)index << 24;
		pGif += 4;
		((unsigned long *)pGif)[0] = tex_0;
		((unsigned long *)pGif)[2] = mip_0;
	} else if (index < -1) {
		unsigned long *src = ChromeGsRegs;
		if (index == -3) src = GlassGsRegs;
		*(unsigned long *)pGif = 0x20 | (long)filter << 6 | (long)mip_dist << 32;
		pGif += 4;
		*(unsigned long *)pGif = 5;
		pGif += 4;
		((unsigned long *)pGif)[0] = src[0];
		((unsigned long *)pGif)[2] = src[2];
	} else {
		*(unsigned long *)pGif = 0x20 | (long)filter << 6 | (long)mip_dist << 32;
		pGif += 4;
		*(unsigned long *)pGif = 5;
		pGif += 4;
		((unsigned long *)pGif)[0] = (long)((GSmem.perm_grey_tex >> 8) | 0xc004000) | 0x80000004c0000000;
		((unsigned long *)pGif)[2] = 0;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", ParsePermGsRam);

GAME_SECTION(ParseMobyGifs) void ParseMobyGifs(void *packets, short *tex_defs, char *tex_refs, int total_packet_cnt)
{
	int *pi = (int *)packets;
	int i;
	for (i = 0; i < total_packet_cnt; i++, pi += 4) {
		int gif_cnt = pi[1] >> 16;
		int *pgif;
		int j;
		pi[1] &= 0xffff;
		pgif = (int *)pi[0] + (pi[1] - gif_cnt) * 4;
		for (j = 0; j < gif_cnt; j += 4) {
			int index = pgif[8];
			if (index >= 0) index = (unsigned char)tex_refs[index];
			if (tex_defs) SetUpVisGif(pgif, tex_defs + index * 8, pgif[0], pgif[1], pgif[4], pgif[5], index);
			else SetUpVisGifViewer(pgif, pgif[0], pgif[1], pgif[4], pgif[5], index);
			pgif += 0x10;
		}
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", ParseMobyClass);

GAME_SECTION(ParseMoby) void ParseMoby(char *data, short *tex_defs, char *tex_refs, int oClass)
{
	if (!data) {
		SetupMobyFunctions(oClass, 1);
		MobyClassLookup[oClass] = MobyClassNullIndex;
		MobyClassNullRef[MobyClassNullIndex++] = oClass;
	} else {
		int index = MobyClassIndex;
		MobyClassRef[index] = oClass;
		MobyClassLookup[oClass] = MobyClassIndex;
		MobyClasses[index] = (MobyClass *)data;
		MobyMipDists[index] = ((unsigned char *)data)[0x2d] << 10;
		if (((unsigned char *)data)[0x2d] == 0xff) MobyMipDists[index] = 0x100000;
		ParseMobyClass((MobyClass *)data, tex_defs, tex_refs, oClass);
		SetupMobyFunctions(oClass, 0);
		MobyClassIndex++;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", ParseTfrag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", LoadFrontData);

JUNK_ASM(func_004636B8,
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", LoadLevelData);

GAME_SECTION(LoadNpcMobys) int LoadNpcMobys(int level_id, int scene_id)
{
	int offset;
	int size;
	int size_bytes;
	Scene.mobyload = 0;
	size = g_wad.levelscene.scenes[Scene.scene_id].mobyload.length;
	offset = g_wad.levelscene.scenes[Scene.scene_id].mobyload.offset;
	size_bytes = size * 0x800;
	if (size > 0) {
		Scene.mobyload = (char *)Scene.mem_alloc_top - size_bytes;
		offset += g_wad.levelscene.sector;
		Sync(1);
		Load(0, Scene.mobyload, offset, size, g_fsLoadQueue, 0, 0);
		return 1;
	}
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", ParseNpcMobys);

GAME_SECTION(UnloadNpcMobys) void UnloadNpcMobys()
{
	while (Scene.moby_cnt > 0) {
		PopMobyStack();
		Scene.moby_cnt--;
	}
}

GAME_SECTION(LoadNpcSubtitles) int LoadNpcSubtitles(int level_id, int scene_id)
{
	int offset;
	int size;
	Scene.subtitles = 0;
	size = g_wad.levelscene.scenes[Scene.scene_id].subtitles.length;
	offset = g_wad.levelscene.scenes[Scene.scene_id].subtitles.offset;
	if (size > 0) {
		Scene.subtitles = (Subtitle *)((char *)Scene.mem_alloc_top - size * 0x800);
		offset += g_wad.levelscene.sector;
		Scene.mem_alloc_top = (char *)Scene.subtitles;
		Sync(1);
		Load(0, Scene.subtitles, offset, size, g_fsLoadQueue, 0, 0);
		return 1;
	}
	return 0;
}

GAME_SECTION(PreLoadNpcChunk) int PreLoadNpcChunk(int chunk_id)
{
	void *dest = Scene.mem_chunk_comp;
	int offset = g_wad.levelscene.scenes[Scene.scene_id].chunks[chunk_id].offset;
	int size = g_wad.levelscene.scenes[Scene.scene_id].chunks[chunk_id + 1].offset - offset;
	if (size > 0) LoadAsync(0, dest, offset + g_wad.levelscene.sector, size, g_fsLoadQueue, 0, 0);
	return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", ParseNpcChunk);

GAME_SECTION(ParseSpaceSceneChunk) void ParseSpaceSceneChunk(int chunk_id)
{
	Scene.mem_chunk_comp = Scene.chunks[chunk_id];
	ParseNpcChunk();
	Scene.mem_chunk_comp = MemSlotsChain.vu1_chain1 + vu1_bufSize;
}

GAME_SECTION(ResetGadgetBank) void ResetGadgetBank()
{
}

JUNK_ASM(func_00464090,
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", PushMobyStack);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", PopMobyStack);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", QueuePifLoad);

GAME_SECTION(ResetLevelData) void ResetLevelData()
{
	FastMemSet(g_HeroArr, 0, 4);
	FastMemSet(ResetLevelBlock_229A80, 0, 0x1d0);
	MobyResetAnimLayerCache();
	InitMobyJointCache();
	if (g_gameTypeLd != 1) {
		srand(0x4d2);
	}
	if (bootSettings.PalMode != 0) {
		if (NtscPalSpeedAdjuster == 1.0f) {
			SetNtscPalTiming(1);
		}
	} else if (NtscPalSpeedAdjuster != 1.0f) {
		SetNtscPalTiming(0);
	}
	CollOutput.call_cnt = 0;
	CollOutput.damage_next = 0;
	FastMemZero16(MobyGrids, 0x1c000);
	FastMemZero16(MobyGridAlloc, 0xc0);
}
