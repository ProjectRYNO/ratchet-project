#include "common.h"
#include "game_section.h"


struct MobyClass;
struct MobyInstance {
	/* 0x00 */ char unk00[0x24];
	/* 0x24 */ MobyClass *pClass;
};
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
struct SceneDef {
	/* 0x000 */ char unk000[0x70];
	/* 0x070 */ int scene_id;
	/* 0x074 */ char unk074[0x8c - 0x74];
	/* 0x08c */ short moby_cnt;
	/* 0x08e */ char unk08e[0xa0 - 0x8e];
	/* 0x0a0 */ char *mem_alloc_base;
	/* 0x0a4 */ char *mem_alloc_top;
	/* 0x0a8 */ void *mem_chunk_comp;
	/* 0x0ac */ char unk0ac[0xb8 - 0xac];
	/* 0x0b8 */ void *subtitles;
	/* 0x0bc */ void *mobyload;
	/* 0x0c0 */ char unk0c0[0xe0 - 0xc0];
	/* 0x0e0 */ void *chunks[16];
	/* 0x120 */ char unk120[0x110];
};
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

/* ===== AG additions ===== */
struct WadSceneDef {
	/* 0x000 */ int unk000[2];
	/* 0x008 */ int subtitles_offset;
	/* 0x00c */ int subtitles_length;
	/* 0x010 */ char unk010[0x30 - 0x10];
	/* 0x030 */ int mobyload_offset;
	/* 0x034 */ int mobyload_length;
	/* 0x038 */ int chunks[(0x14c - 0x38) / 4];
};
struct WadLoc {
	/* 0x0 */ int offset;
	/* 0x4 */ int length;
};
struct WadDef {
	/* 0x0000 */ char unk0000[0x9ac];
	/* 0x09ac */ int armor_sector;
	/* 0x09b0 */ char unk09b0[0xaf0 - 0x9b0];
	/* 0x0af0 */ WadLoc bot_texs[12];
	/* 0x0b50 */ WadLoc landstalker_texs[8];
	/* 0x0b90 */ WadLoc dropship_texs[8];
	/* 0x0bd0 */ char unk0bd0[0xdabc - 0xbd0];
	/* 0xdabc */ int sector;
	/* 0xdac0 */ WadSceneDef scenes[1];
};
extern WadDef g_wad __asm__("D_001C2040");
extern char g_fsLoadQueue[] __asm__("D_001CFAF8");
void Sync(int) __asm__("Sync");
void Load(int, void *, int, int, void *, void *, void *) __asm__("Load");
void LoadAsync(int, void *, int, int, void *, void *, void *) __asm__("LoadAsync");
int LoadNpcMobys(int, int) __asm__("LoadNpcMobys");
int LoadNpcSubtitles(int, int) __asm__("LoadNpcSubtitles");
int PreLoadNpcChunk(int) __asm__("PreLoadNpcChunk");
struct GSMEM {
	/* 0x00 */ int unk00[8];
	/* 0x20 */ int perm_bots;
	/* 0x24 */ int perm_landstalker;
	/* 0x28 */ int perm_dropship;
	/* 0x2c */ int perm_bank;
	/* 0x30 */ int stash_armor;
	/* 0x34 */ int stash_armor2;
	/* 0x38 */ int stash_bots;
	/* 0x3c */ int stash_landstalker;
	/* 0x40 */ int stash_dropship;
	/* 0x44 */ int unk44[5];
};
extern GSMEM GSmem __asm__("GSmem");
extern int vu1_bufId __asm__("vu1_bufId");
extern void *vu1_DmaBuffers[2] __asm__("vu1_DmaBuffers");
void VU1_syncChain(int) __asm__("VU1_syncChain");
int music_Sync(int) __asm__("music_Sync");
void AttachPaintJobTextures(int, int, void *, int *, unsigned long *) __asm__("AttachPaintJobTextures");
void LoadBotTextures(int) __asm__("LoadBotTextures");
void LoadLandStalkerTextures(int) __asm__("LoadLandStalkerTextures");
void LoadDropshipTextures(int) __asm__("LoadDropshipTextures");

/* ===== AM additions (pass 4) ===== */
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
struct LdBootSettings {
	/* 0x00 */ int PalMode;
	/* 0x04 */ int unk04[0x30];
};
extern LdBootSettings bootSettings __asm__("bootSettings");
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
struct LdWadMisc {
	/* 0x000 */ char unk000[0x64c];
	/* 0x64c */ int sector;
	/* 0x650 */ char unk650[0x18];
	/* 0x668 */ WadLoc frontbin;
};
extern LdWadMisc g_wadMisc __asm__("D_001C2040");
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

GAME_SECTION(IsSceneLevel) bool IsSceneLevel()
{
	return false;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", func_00461438);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", SwizzleTextureInPlace);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", ParseParticleTexs);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", ParseEffectTexs);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", LoadCompressedHudBank);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", SetUpVisGif);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", SetUpVisGifViewer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", ParsePermGsRam);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", ParseMobyGifs);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", ParseMobyClass);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", ParseMoby);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", ParseTfrag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", LoadFrontData);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", func_004636B8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", LoadLevelData);

GAME_SECTION(LoadNpcMobys) int LoadNpcMobys(int level_id, int scene_id)
{
	int offset;
	int size;
	int size_bytes;
	Scene.mobyload = 0;
	size = g_wad.scenes[Scene.scene_id].mobyload_length;
	offset = g_wad.scenes[Scene.scene_id].mobyload_offset;
	size_bytes = size * 0x800;
	if (size > 0) {
		Scene.mobyload = Scene.mem_alloc_top - size_bytes;
		offset += g_wad.sector;
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
	size = g_wad.scenes[Scene.scene_id].subtitles_length;
	offset = g_wad.scenes[Scene.scene_id].subtitles_offset;
	if (size > 0) {
		Scene.subtitles = Scene.mem_alloc_top - size * 0x800;
		offset += g_wad.sector;
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
	int offset = g_wad.scenes[Scene.scene_id].chunks[chunk_id];
	int size = g_wad.scenes[Scene.scene_id].chunks[chunk_id + 1] - offset;
	if (size > 0) LoadAsync(0, dest, offset + g_wad.sector, size, g_fsLoadQueue, 0, 0);
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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", func_00464090);

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
