#include "common.h"
#include "game_section.h"

struct SettingsDef {
	/* 0x00 */ int PalMode;
	/* 0x04 */ char unk04[0xfc];
};
extern SettingsDef bootSettings __asm__("bootSettings");
extern int progressiveScan __asm__("progressiveScan");
extern "C" {
	void sceGsResetPath();
	int sceGsResetGraph(short, short, short, short);
	int sceGsPutDispEnv(void *);
}
void SetVideoMode() __asm__("SetVideoMode");
struct fsAABuff {
	/* 0x00 */ char unk00[0xc0];
	/* 0xc0 */ char giftagDrawSmall[0x10];
};
extern fsAABuff *pAAbuff __asm__("pAAbuff");
void PutDispBuffer() __asm__("PutDispBuffer");
extern long aaClearRegs[] __asm__("aaClearRegs");
void SetBackgroundColor(int r, int g, int b) __asm__("SetBackgroundColor");

typedef int qwordWords[4];
extern qwordWords *vu1_bufPtr __asm__("vu1_bufPtr");
extern long aaBlurRegs[] __asm__("aaBlurRegs");
void AA_BlurPass() __asm__("AA_BlurPass");
void PutDrawBufferSmall() __asm__("PutDrawBufferSmall");


GAME_SECTION(SetVideoMode) void SetVideoMode()
{
	sceGsResetPath();
	if (bootSettings.PalMode != 0) {
		progressiveScan = 0;
	}
	if (progressiveScan != 0) {
		sceGsResetGraph(0, 0, 0x50, 1);
	} else {
		sceGsResetGraph(0, 1, bootSettings.PalMode == 1 ? 3 : 2, 0);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/framebuf", func_004586E0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/framebuf", SetMovieDrawSmallVIFChain);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/framebuf", SetupFS_AA_buffer);

GAME_SECTION(SetBackgroundColor) void SetBackgroundColor(int r, int g, int b)
{
	aaClearRegs[7] = (long)r | ((long)g << 8) | ((long)b << 16) | 0x80000000L;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/framebuf", func_00459400);

GAME_SECTION(PutDispBuffer) void PutDispBuffer()
{
	sceGsPutDispEnv(pAAbuff);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/framebuf", PutDrawBufferLarge);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/framebuf", ClearDrawBufferLarge);

GAME_SECTION(PutDrawBufferSmall) void PutDrawBufferSmall()
{
	(*vu1_bufPtr)[0] = 0x30000009;
	(*vu1_bufPtr)[1] = (unsigned int)pAAbuff->giftagDrawSmall & 0xfffffff;
	(*vu1_bufPtr)[2] = 0;
	(*vu1_bufPtr)[3] = 0x50000009;
	vu1_bufPtr = vu1_bufPtr + 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/framebuf", func_00459750);

GAME_SECTION(AA_BlurPass) void AA_BlurPass()
{
	(*vu1_bufPtr)[0] = 0x30000026;
	(*vu1_bufPtr)[1] = (int)aaBlurRegs;
	(*vu1_bufPtr)[2] = 0;
	(*vu1_bufPtr)[3] = 0x50000026;
	vu1_bufPtr = vu1_bufPtr + 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/framebuf", AA_DisplayPass);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/framebuf", func_004598D8);
