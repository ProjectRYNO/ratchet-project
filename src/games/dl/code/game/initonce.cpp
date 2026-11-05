#include "common.h"
#include "game_section.h"



void *g_pNoNetHeapAlloc __asm__("g_pNoNetHeapAlloc") GAME_GP_DATA = 0;
extern "C" void free(void *);
void DeinitNoNetHeap() __asm__("DeinitNoNetHeap");

void FontInitialize() __asm__("FUN_00454298");
void *LoadFont(void *addr) __asm__("LoadFont");
extern "C" int sceCdMmode(int);
void SetMediaMode() __asm__("SetMediaMode");

extern int Level __asm__("Level");
extern char D_C2900[] __asm__("D_C2900");
extern "C" void *malloc(unsigned int);
/* Memory map at D_0023AB00; names come from the prototype's debug data. */
typedef struct memSlots {
	/* 0x00 */ void *os;
	/* 0x04 */ void *code;
	/* 0x08 */ char *base;
	/* 0x0c */ char *vu1_chain[2];
	/* 0x14 */ char *tie_cache;
	/* 0x18 */ void *moby_joint_cache;
	/* 0x1c */ char *joint_cache_entry_list;
	/* 0x20 */ char *level_base;
	/* 0x24 */ char unk24[0x84];
	/* 0xa8 */ char *level_end;
	/* 0xac */ char *perm_base;
	/* 0xb0 */ char *perm_armor;
	/* 0xb4 */ char *perm_armor2;
	/* 0xb8 */ char *perm_skin;
	/* 0xbc */ char *perm_patch;
	/* 0xc0 */ char *hud;
	/* 0xc4 */ char *gui;
	/* 0xc8 */ char *net_overlay;
	/* 0xcc */ char *heap;
	/* 0xd0 */ char *stack;
	/* 0xd4 */ void *occl_points;
	/* 0xd8 */ void *occl_grids;
	/* 0xdc */ void *profile;
	/* 0xe0 */ void *debug;
} memSlots_t;
typedef struct nwInfo {
	/* 0x00 */ int onlyLocalPlayers;
	/* 0x04 */ char unk04[0x100];
} nwInfo_t;
extern memSlots_t MemSlots __asm__("D_0023AB00");
extern nwInfo_t g_nwInfo __asm__("D_1723B8");
extern int vu1_bufSize __asm__("vu1_bufSize");
extern char D_5566FF[] __asm__("D_5566FF");
extern char D_54E6D7[] __asm__("D_54E6D7");
extern char D_1FFC000[] __asm__("D_1FFC000");
extern char D_1F38000[] __asm__("D_1F38000");
extern char ezNetCnfInit[] __asm__("ezNetCnfInit");
extern void *g_DownloadPatchData __asm__("D_21DD74");
extern void *g_PatchData __asm__("g_PatchData");
extern "C" void *memset(void *, int, unsigned int);
void InitMemSlots() __asm__("InitMemSlots");
void InitNoNetHeap() __asm__("InitNoNetHeap");
inline int isNoNetLevel()
{
	int r = 0;
	if (Level == 0) r = 1;
	else if (Level >= 0x28) r = 1;
	return r;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/initonce", InitMemSlots);

GAME_SECTION(SetMediaMode) void SetMediaMode()
{
	sceCdMmode(2);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/initonce", InitOnce);

GAME_SECTION(LoadFont) void *LoadFont(void *addr)
{
	FontInitialize();
	return addr;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/initonce", InitNoNetHeap);

GAME_SECTION(DeinitNoNetHeap) void DeinitNoNetHeap()
{
	if (g_pNoNetHeapAlloc) {
		free(g_pNoNetHeapAlloc);
		g_pNoNetHeapAlloc = 0;
	}
}
