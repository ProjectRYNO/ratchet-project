// GAME_EXTRA_FLAGS: -g0
#include "common.h"
#include "game_section.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/collproc", CollLine_Fix);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/collproc", CollSphere_Fix);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/collproc", CollMobysLine_Fix);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/collproc", CollMobysSphere_Fix);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/collproc", CollHeroLine);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/collproc", FUN_00444328);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/collproc", CollHeroSphere);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/collproc", CollCameraLine);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/collproc", CollCameraSphere);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/collproc", CollLineList);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/collproc", CollLineTriListOfs);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/collproc", CollMovingSphereVsTri);

void CollHotspot(void) __asm__("CollHotspot");
GAME_SECTION(CollHotspot) void CollHotspot(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlui $1, %%hi(CollOutput)\n"
		"\taddiu $1, $1, %%lo(CollOutput)\n"
		"\tlw $2, 0x1c($1)\n"
		"\taddi $3, $0, 0xf\n"
		"\tbltz $2, .L004454B0\n"
		"\tand $2, $2, $3\n"
		"\tbeq $2, $3, .L004454B0\n"
		"\tnop\n"
		"\tjr $31\n"
		"\tnop\n"
		".L004454B0:\n"
		"\tjr $31\n"
		"\taddi $2, $0, -0x1\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(CollHotspot) : : : "memory");
}

void CollSoundSurface(void) __asm__("CollSoundSurface");
GAME_SECTION(CollSoundSurface) void CollSoundSurface(void)
{
	__asm__ volatile(
		".set noreorder\n.set noat\n"
		"\tlui $1, %%hi(CollOutput)\n"
		"\taddiu $1, $1, %%lo(CollOutput)\n"
		"\tlw $2, 0x1c($1)\n"
		"\taddi $3, $0, 0x60\n"
		"\tbltz $2, .L004454D8\n"
		"\tand $2, $2, $3\n"
		"\tjr $31\n"
		"\tsrl $2, $2, 5\n"
		".L004454D8:\n"
		"\tjr $31\n"
		"\taddi $2, $0, -0x1\n"
		".set at\n.set reorder\n" GAME_ASM_TAIL(CollSoundSurface) : : : "memory");
}
