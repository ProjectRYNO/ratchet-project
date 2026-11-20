#include "common.h"
#include "game_section.h"
#include "mobyutil.h"
#include "draw.h"



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
		pMoby->modeBits |= 0x80;
		pMoby++;
test:
		;
	} while (pMoby < MobyInstanceEnd);
}

GAME_SECTION(UnInitModeGadgetPuzzle) void UnInitModeGadgetPuzzle()
{
	moby *pMoby;
	mode_pop(0, 0);
	SetBackgroundColor(VC.backR, VC.backG, VC.backB);
	/* Fake match: jumping into the loop stops GCC rotating it or hoisting the end pointer, as retail shows. */
	pMoby = MobyInstances;
	goto test;
	do {
		pMoby->modeBits &= ~0x80;
		pMoby++;
test:
		;
	} while (pMoby < MobyInstanceEnd);
}
