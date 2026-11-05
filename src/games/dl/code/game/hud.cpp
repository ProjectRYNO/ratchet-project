#include "common.h"
#include "game_section.h"

/* Recovered from the retail boot instructions, using names from the prototype's debug data. */
typedef struct hudIcon {
	/* 0x00 */ unsigned short id;
	/* 0x02 */ unsigned short len;
	/* 0x04 */ unsigned short start;
	/* 0x06 */ char unk06[2];
} hudIcon_t;
typedef struct hudFrame {
	/* 0x00 */ short hPal;
	/* 0x02 */ short hTex;
} hudFrame_t;
typedef struct hudRam {
	/* 0x00 */ int ram;
	/* 0x04 */ int unk04;
} hudRam_t;
typedef struct hudState {
	/* 0x00 */ int unk00;
	/* 0x04 */ char *heapPtr;
	/* 0x08 */ char *heapEnd;
	/* 0x0c */ struct hudHeader *header;
	/* 0x10 */ hudIcon_t *icons;
	/* 0x14 */ hudFrame_t *frames;
	/* 0x18 */ hudRam_t *texs;
	/* 0x1c */ hudRam_t *pals;
	/* 0x20 */ char unk20[0x100];
} hudState_t;
typedef struct hudGlobals {
	/* 0x00 */ char unk00[0xb0];
	/* 0xb0 */ char *heapBase;
} hudGlobals_t;

extern hudGlobals_t hudGlobals __asm__("D_0023AB10");
unsigned char disable_icon_fetching __asm__("D_21EEF4") GAME_GP_DATA = 0;
int GetIconFrame(int icon, int frame) __asm__("GetIconFrame");
int Hud_GetIconIndex(int id) __asm__("Hud_GetIconIndex");
extern hudState_t Hud __asm__("Hud");
void Hud_HeapReset() __asm__("Hud_HeapReset");
void *Hud_HeapAlloc(int size) __asm__("Hud_HeapAlloc");
unsigned int Hud_GS_Max_Location __asm__("D_21EEF0") GAME_GP_DATA = 0;
int Hud_GsStashFreeRam() __asm__("Hud_GsStashFreeRam");

typedef struct hudHeader {
	/* 0x00 */ char unk00[0x14];
	/* 0x14 */ int pal_count[8];
	/* 0x34 */ int tex_count[16];
	/* 0x74 */ int bank_load[8];
} hudHeader_t;
typedef struct gsMem {
	/* 0x00 */ char unk00[0x48];
	/* 0x48 */ int stash_hud;
	/* 0x4c */ char unk4c[0x100];
} gsMem_t;
extern gsMem_t GSmem __asm__("GSmem");
extern int *vu1_bufPtr __asm__("vu1_bufPtr");
extern "C" void FlushCache(int);
extern "C" int sceGsSetDefLoadImage(void *, short, short, short, short, short, short, short);
extern "C" int sceGsExecLoadImage(void *, void *);
void LinkHudBank(int bank, char *ram) __asm__("LinkHudBank");
void Hud_sendTexture(char *ram, int gsaddr, int psm, int uLog, int vLog, int immediate) __asm__("Hud_sendTexture");
void Hud_SendResidentBank(int bank, char *ram, int immediate) __asm__("Hud_SendResidentBank");


GAME_SECTION(Hud_HeapAlloc) void *Hud_HeapAlloc(int size)
{
	void *result;
	hudState_t *hud = &Hud;
	if (!hud->heapPtr) Hud_HeapReset();
	if (hud->heapEnd - hud->heapPtr < size) return 0; result = hud->heapPtr; size = (size + 0xf) & 0xfffffff0; hud->heapPtr += size;
	return result;
}

GAME_SECTION(Hud_HeapReset) void Hud_HeapReset()
{
	char *base = hudGlobals.heapBase;
	Hud.heapPtr = base;
	Hud.heapEnd = base + 0x4b000;
}

GAME_SECTION(Hud_GsStashFreeRam) int Hud_GsStashFreeRam()
{
	int remain = 0;
	if (Hud_GS_Max_Location < 0x1d0000) remain = (0x1d0000 - Hud_GS_Max_Location) >> 2;
	return remain;
}

GAME_SECTION(LinkHudBank) void LinkHudBank(int bank, char *ram)
{
	int low;
	int high;
	int i;
	if (Hud.header->bank_load[bank] == 0) {
		ram = (char *)(((unsigned int)ram + 0xf) & 0xfffffff0);
		Hud.header->bank_load[bank] = (int)ram;
		low = bank ? Hud.header->pal_count[bank - 1] : 0;
		high = Hud.header->pal_count[bank];
		for (i = low; i < high; i++) {
			Hud.pals[i].ram &= 0x7fffffff;
			Hud.pals[i].ram += (int)ram;
		}
		low = bank ? Hud.header->tex_count[bank - 1 - 8 + 8] : 0;
		high = Hud.header->tex_count[bank];
		for (i = low; i < high; i++) {
			Hud.texs[i].ram &= 0x7fffffff;
			Hud.texs[i].ram += (int)ram;
		}
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/hud", func_0045E9C0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/hud", Hud_SendResidentBank);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/hud", Hud_GetIconIndex);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/hud", GetIconFrame);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/hud", GetFrameTex);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/hud", func_0045EE68);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/hud", Hud_DrawRotatedSprite16);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/hud", func_0045F1E8);

GAME_SECTION(Hud_sendTexture) void Hud_sendTexture(char *ram, int gsaddr, int psm, int uLog, int vLog, int immediate)
{
	char local[0x60];
	int dbw = (1 << uLog) >> 6;
	int qwc = 1 << (uLog + vLog - 4);
	char *image;
	if (dbw <= 0) dbw = 1;
	if (!immediate) {
		vu1_bufPtr[0] = 0x10000006;
		vu1_bufPtr[1] = 0;
		vu1_bufPtr[2] = 0;
		vu1_bufPtr[3] = 0x50000006;
		image = (char *)(vu1_bufPtr + 4);
		vu1_bufPtr += 0x1c;
	} else {
		image = local;
	}
	sceGsSetDefLoadImage(image, gsaddr, dbw, psm, 0, 0, 1 << uLog, 1 << vLog);
	if (!immediate) {
		vu1_bufPtr[0] = qwc | 0x30000000;
		vu1_bufPtr[1] = (int)ram;
		vu1_bufPtr[2] = 0;
		vu1_bufPtr[3] = qwc | 0x50000000;
		vu1_bufPtr += 4;
	} else {
		FlushCache(0);
		sceGsExecLoadImage(image, ram);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/hud", func_0045F370);
