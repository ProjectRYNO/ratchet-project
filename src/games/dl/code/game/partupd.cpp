#include "common.h"
#include "game_section.h"

struct vec4 { float x, y, z, w; };
struct part;
part *CreatePart(int) __asm__("CreatePart");
void SpawnPart_097_Main(part *, vec4 &, vec4 &, int, int, int, int, int, float, float, float, int) __asm__("SpawnPart_097_Main");
part *SpawnPart_097(vec4 &pos, vec4 &vel, int frames, int rgb, int rotSp, int initAlpha, int endAlpha, float initScale, float endScale, float gravity, int texID) __asm__("SpawnPart_097");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_002_Main);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_002);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00491B80);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_004);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00491C88);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_011);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00491FA8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_015);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00492130);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_021);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00492240);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_022);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_023);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00492530);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_025);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_004926C8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_028);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_029);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00492B70);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_034);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00492D78);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_035);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00492E88);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_044);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00493038);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_045);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_046);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_004932C8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_053);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_004934A8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_064);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00493618);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_074);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00493820);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_085);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", UpdatePart_085);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00493BD0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", UpdatePart_089);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_091);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00494208);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_092);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00494440);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_097_Main);

GAME_SECTION(SpawnPart_097) part *SpawnPart_097(vec4 &pos, vec4 &vel, int frames, int rgb, int rotSp, int initAlpha, int endAlpha, float initScale, float endScale, float gravity, int texID)
{
	part *pPart = CreatePart(0x61);
	if (pPart) SpawnPart_097_Main(pPart, pos, vel, frames, rgb, rotSp, initAlpha, endAlpha, initScale, endScale, gravity, texID);
	return pPart;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", UpdatePart_097);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00494820);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_099);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00494980);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_102);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00494B08);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_111);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00494C68);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_121);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00494E08);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_126);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_127);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", UpdatePart_127);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_128);
