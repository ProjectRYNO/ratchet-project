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
};
extern ArmorLoadDef ArmorLoad __asm__("ArmorLoad");
struct SceneDef {
	/* 0x000 */ char unk000[0x8c];
	/* 0x08c */ short moby_cnt;
	/* 0x08e */ char unk08e[0x1a];
	/* 0x0a8 */ void *mem_chunk_comp;
	/* 0x0ac */ char unk0ac[0x34];
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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", LoadNpcMobys);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", ParseNpcMobys);

GAME_SECTION(UnloadNpcMobys) void UnloadNpcMobys()
{
	while (Scene.moby_cnt > 0) {
		PopMobyStack();
		Scene.moby_cnt--;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", LoadNpcSubtitles);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", PreLoadNpcChunk);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/loaders", ResetLevelData);
