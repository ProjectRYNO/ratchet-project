#include "common.h"
#include "game_section.h"


struct PAD {
	/* 0x000 */ char unk000[0x100];
	/* 0x100 */ float analog[16];
	/* 0x140 */ float analogPrev[16];
	/* 0x180 */ char unk180[0xe];
	/* 0x18e */ short ringIndex;
	/* 0x190 */ int ringValidSize;
	/* 0x194 */ int unk194[3];
	/* 0x1a0 */ int bits;
	/* 0x1a4 */ int bitsOn;
	/* 0x1a8 */ int bitsOff;
	/* 0x1ac */ int unk1ac;
	/* 0x1b0 */ int digitalBits;
	/* 0x1b4 */ int digitalBitsOn;
	/* 0x1b8 */ int digitalBitsOff;
	/* 0x1bc */ int unk1bc;
	/* 0x1c0 */ int unk1c0;
	/* 0x1c4 */ int unk1c4;
	/* 0x1c8 */ int unk1c8;
	/* 0x1cc */ int unk1cc;
	/* 0x1d0 */ int unk1d0;
	/* 0x1d4 */ int unk1d4;
	/* 0x1d8 */ int unk1d8;
	/* 0x1dc */ int unk1dc;
	/* 0x1e0 */ int bitsRing[30];
	/* 0x258 */ float analogAngRing[30];
	/* 0x2d0 */ char unk2d0[0x34c - 0x2d0];
	/* 0x34c */ int lagIndex;
	/* 0x350 */ int lagValidSize;
	/* 0x354 */ int bits_Lagged[7];
	/* 0x370 */ int digitalBits_Lagged[7];
	/* 0x38c */ float analog_Lagged[7][16];
	/* 0x54c */ char unk54c[0x5c0 - 0x54c];
};
extern PAD Pad[8] __asm__("Pad");
void InitPadRing(PAD *pIn) __asm__("InitPadRing");
float PadRingAng(int frames, PAD *pIn) __asm__("PadRingAng");
int Pad_NonLaggedBits(PAD *pIn) __asm__("Pad_NonLaggedBits");
void UpdatePad(PAD *) __asm__("UpdatePad");
void UpdatePads() __asm__("UpdatePad___dupe2");
void Update_HudBitsRepeat() __asm__("Update_HudBitsRepeat");

struct SettingsDef {
	/* 0x00 */ char unk00[0xa8];
	/* 0xa8 */ unsigned char FirstPersonModeOn[4];
};
extern int g_gameType __asm__("g_gameType");
extern SettingsDef bootSettings __asm__("bootSettings");
int PadRingBitsOn(int bits, int frames, int *pFrame, PAD *pIn) __asm__("PadRingBitsOn");
int Pad_MappedPad(int bits, int index) __asm__("Pad_MappedPad");
void ClearPadInput(PAD &pad) __asm__("ClearPadInput");


GAME_SECTION(InitPadRing) void InitPadRing(PAD *pIn)
{
	PAD *pPad = pIn ? pIn : Pad;
	pPad->ringIndex = 0;
	pPad->ringValidSize = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/pad", func_0048F800);

GAME_SECTION(Pad_NonLaggedBits) int Pad_NonLaggedBits(PAD *pIn)
{
	if (pIn) return pIn->bits_Lagged[(pIn->lagIndex + 6) % 7];
	return Pad[0].bits_Lagged[(Pad[0].lagIndex + 6) % 7];
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/pad", func_0048F868);

GAME_SECTION(PadRingBitsOn) int PadRingBitsOn(int bits, int frames, int *pFrame, PAD *pIn)
{
	int i;
	if (!pIn) pIn = Pad;
	if (pIn->ringValidSize < frames) frames = pIn->ringValidSize;
	for (i = 1; i < frames + 1; i++) {
		int idx = (pIn->ringIndex - i + 30) % 30;
		if (pIn->bitsRing[idx] & bits) {
			if (pFrame) *pFrame = i - 1;
			return pIn->bitsRing[idx] & bits;
		}
	}
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/pad", func_0048F908);

GAME_SECTION(PadRingAng) float PadRingAng(int frames, PAD *pIn)
{
	PAD *pPad;
	if (pIn) pPad = pIn;
	else pPad = Pad;
	if (pPad->ringValidSize < frames) frames = pPad->ringValidSize;
	return pPad->analogAngRing[(pPad->ringIndex - frames + 30) % 30];
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/pad", pad_Init);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/pad", ClearPadInput);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/pad", ProcessPadInput);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/pad", func_004903F8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/pad", UpdatePad);

GAME_SECTION(UpdatePad___dupe2) void UpdatePads()
{
	PAD *p = Pad;
	PAD *end = &Pad[8];
	do {
		UpdatePad(p);
		p++;
	} while ((int)p < (int)end);
	Update_HudBitsRepeat();
}

GAME_SECTION(Pad_MappedPad) int Pad_MappedPad(int bits, int index)
{
	if (g_gameType != 1 && bits == 1) return 3;
	if (bootSettings.FirstPersonModeOn[index]) {
		switch (bits) {
		case 0x40:
			return 0x44;
		case 4:
		case 8:
			return 1;
		case 0x10:
			return 0x12;
		}
	}
	return bits;
}
