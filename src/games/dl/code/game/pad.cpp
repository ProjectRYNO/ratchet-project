#include "common.h"
#include "game_section.h"
#include "gameglobals.h"
#include "pad.h"


extern PAD Pad[8] __asm__("Pad");
void InitPadRing(PAD *pIn) __asm__("InitPadRing");
float PadRingAng(int frames, PAD *pIn) __asm__("PadRingAng");
int Pad_NonLaggedBits(PAD *pIn) __asm__("Pad_NonLaggedBits");
void UpdatePad(PAD *) __asm__("UpdatePad");
void UpdatePads() __asm__("UpdatePad___dupe2");
void Update_HudBitsRepeat() __asm__("Update_HudBitsRepeat");

extern int g_gameType __asm__("g_gameType");
int PadRingBitsOn(int bits, int frames, int *pFrame, PAD *pIn) __asm__("PadRingBitsOn");
int Pad_MappedPad(int bits, int index) __asm__("Pad_MappedPad");
void ClearPadInput(PAD &pad) __asm__("ClearPadInput");


GAME_SECTION(InitPadRing) void InitPadRing(PAD *pIn)
{
	PAD *pPad = pIn ? pIn : Pad;
	pPad->ringIndex = 0;
	pPad->ringValidSize = 0;
}

JUNK_ASM(func_0048F800,
	"\tlwc1 $f0, 0x38c($4)\n"
	"\tnop\n");

GAME_SECTION(Pad_NonLaggedBits) int Pad_NonLaggedBits(PAD *pIn)
{
	if (pIn) return pIn->bits_Lagged[(pIn->lagIndex + 6) % 7];
	return Pad[0].bits_Lagged[(Pad[0].lagIndex + 6) % 7];
}

JUNK_ASM(func_0048F868,
	"\tand $2, $4, $2\n"
	"\tnop\n"
	"\tand $2, $2, $5\n"
	"\tnop\n");

GAME_SECTION(PadRingBitsOn) int PadRingBitsOn(int bits, int frames, int *pFrame, PAD *pIn)
{
	int i;
	if (!pIn) pIn = Pad;
	if (pIn->ringValidSize < frames) frames = pIn->ringValidSize;
	for (i = 1; i < frames + 1; i++) {
		int idx = (pIn->ringIndex - i + 30) % 30;
		if (pIn->bitsOnRing[idx] & bits) {
			if (pFrame) *pFrame = i - 1;
			return pIn->bitsOnRing[idx] & bits;
		}
	}
	return 0;
}

JUNK_ASM(func_0048F908,
	"\tlwc1 $f0, 0x2d0($2)\n"
	"\tnop\n");

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

JUNK_ASM(func_004903F8,
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n");

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
