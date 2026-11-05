#include "common.h"
#include "game_section.h"

struct moby {
	/* 0x00 */ char unk00[0x34];
	/* 0x34 */ unsigned short state;
	/* 0x36 */ char unk36[0x100 - 0x36];
};
struct ViewContext {
	/* 0x000 */ char unk000[0x25c];
	/* 0x25c */ int bgR;
	/* 0x260 */ int bgG;
	/* 0x264 */ int bgB;
};


moby *PuzzleMaster __asm__("D_21FC90") GAME_GP_DATA = 0;
int PuzzleType __asm__("D_21FC94") GAME_GP_DATA = 0;
int mode_requestChange(int, int, int, int, char *) __asm__("mode_requestChange");
void CleanRegisteredDraws() __asm__("CleanRegisteredDraws");
void InitModeGadgetPuzzle(moby *, int) __asm__("InitModeGadgetPuzzle");
extern moby *MobyInstances __asm__("MobyInstances");
extern moby *MobyInstanceEnd __asm__("MobyInstanceEnd");
extern ViewContext VC __asm__("VC");
int mode_pop(int, int) __asm__("mode_pop");
void SetBackgroundColor(int, int, int) __asm__("SetBackgroundColor");
void UnInitModeGadgetPuzzle() __asm__("UnInitModeGadgetPuzzle");


GAME_SECTION(InitModeGadgetPuzzle) void InitModeGadgetPuzzle(moby *pMaster, int puzzleType)
{
	moby *pMoby;
	mode_requestChange(7, 1, 0, 0, 0);
	PuzzleType = puzzleType;
	PuzzleMaster = pMaster;
	CleanRegisteredDraws();
	SetBackgroundColor(0, 0, 0);
	/* Fake match: jumping into the loop stops GCC rotating it or hoisting the end pointer, as retail shows. */
	pMoby = MobyInstances;
	goto test;
	do {
		pMoby->state |= 0x80;
		pMoby++;
test:
		;
	} while (pMoby < MobyInstanceEnd);
}

GAME_SECTION(UnInitModeGadgetPuzzle) void UnInitModeGadgetPuzzle()
{
	moby *pMoby;
	mode_pop(0, 0);
	SetBackgroundColor(VC.bgR, VC.bgG, VC.bgB);
	/* Fake match: jumping into the loop stops GCC rotating it or hoisting the end pointer, as retail shows. */
	pMoby = MobyInstances;
	goto test;
	do {
		pMoby->state &= ~0x80;
		pMoby++;
test:
		;
	} while (pMoby < MobyInstanceEnd);
}
