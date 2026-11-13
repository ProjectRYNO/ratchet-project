#include "common.h"
#include "game_section.h"

struct vec4 { float x, y, z, w; };
struct part;
part *CreatePart(int) __asm__("CreatePart");
void SpawnPart_097_Main(part *, vec4 &, vec4 &, int, int, int, int, int, float, float, float, int) __asm__("SpawnPart_097_Main");
part *SpawnPart_097(vec4 &pos, vec4 &vel, int frames, int rgb, int rotSp, int initAlpha, int endAlpha, float initScale, float endScale, float gravity, int texID) __asm__("SpawnPart_097");

typedef unsigned int AK_s128 __attribute__((mode(TI)));
struct AK_vec4 { AK_s128 m_v; };
void SpawnPart_002_Main(part *, AK_vec4 &, AK_vec4 &, AK_vec4 &, int, int, int, int, int, int) __asm__("SpawnPart_002_Main");
part *SpawnPart_002(AK_vec4 &pos, AK_vec4 &initVel, AK_vec4 &finalVel, int initRGBA, int finalRGBA, int shootTimer, int slowTimer, int fadeTimer, int textureType) __asm__("SpawnPart_002");
struct AK_Part {
	/* 0x00 */ char unk00;
	/* 0x01 */ unsigned char type;
	/* 0x02 */ unsigned char tex;
	/* 0x03 */ unsigned char gs_alpha;
	/* 0x04 */ int rgba;
	/* 0x08 */ unsigned char rot;
	/* 0x09 */ unsigned char draw_dist;
	/* 0x0a */ short timer;
	/* 0x0c */ float scale;
	/* 0x10 */ AK_s128 pos;
	/* 0x20 */ int update[8];
};
struct AK_Part004 {
	/* 0x00 */ AK_s128 vel;
	/* 0x10 */ int beginColor;
	/* 0x14 */ int endColor;
	/* 0x18 */ short maxScale;
	/* 0x1a */ short startScale;
	/* 0x1c */ int lifeSpan;
};
extern unsigned char *AK_PartClassTexs[128] __asm__("PartClassTexs");
extern "C" int rand();
part *SpawnPart_004(AK_vec4 &pos, AK_vec4 &vel, int beginColor, int endColor, int lifeSpan, int startScale, int maxScale, int additive) __asm__("SpawnPart_004");
struct AK_Part021 {
	/* 0x00 */ char unk00;
	/* 0x01 */ unsigned char b1;
	/* 0x02 */ unsigned char tex;
	/* 0x03 */ unsigned char flags;
	/* 0x04 */ int rgba;
	/* 0x08 */ unsigned char rot;
	/* 0x09 */ unsigned char b9;
	/* 0x0a */ short timer;
	/* 0x0c */ float scale;
	/* 0x10 */ AK_s128 pos;
	/* 0x20 */ char vars[0x20];
};
struct AK_Part021Vars {
	/* 0x00 */ AK_s128 vel;
	/* 0x10 */ int beginRGBA;
	/* 0x14 */ int endRGBA;
	/* 0x18 */ short numFrames;
	/* 0x1a */ short master;
	/* 0x1c */ float maxScale;
};
extern unsigned char *PartClassTexs[128] __asm__("PartClassTexs");
part *SpawnPart_021(AK_vec4 &pos, AK_vec4 &vel, int beginRGBA, int endRGBA, float maxScale, int numFrames, int master) __asm__("SpawnPart_021");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_002_Main);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_002);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00491B80);

GAME_SECTION(SpawnPart_004) part *SpawnPart_004(AK_vec4 &pos, AK_vec4 &vel, int beginColor, int endColor, int lifeSpan, int startScale, int maxScale, int additive)
{
	AK_Part *pPart = (AK_Part *)CreatePart(4);
	if (pPart) {
		AK_s128 tmp = pos.m_v;
		pPart->draw_dist = 0xa4;
		pPart->pos = tmp;
		pPart->rgba = beginColor;
		if (additive) pPart->gs_alpha = 0x48;
		else pPart->gs_alpha = 0x44;
		pPart->type = 0;
		pPart->tex = *AK_PartClassTexs[4];
		pPart->rot = rand();
		pPart->scale = 0.0f;
		pPart->pos = pos.m_v;
		AK_Part004 *pVar = (AK_Part004 *)pPart->update;
		AK_s128 tmp2 = vel.m_v;
		pPart->timer = lifeSpan;
		pVar->vel = tmp2;
		pVar->lifeSpan = lifeSpan;
		pVar->beginColor = beginColor;
		pVar->endColor = endColor;
		pVar->maxScale = maxScale;
		pVar->startScale = startScale;
	}
	return (part *)pPart;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00491C88);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_011);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00491FA8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_015);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00492130);

GAME_SECTION(SpawnPart_021) part *SpawnPart_021(AK_vec4 &pos, AK_vec4 &vel, int beginRGBA, int endRGBA, float maxScale, int numFrames, int master)
{
	AK_Part021 *pPart;
	if (numFrames == 0) return 0;
	pPart = (AK_Part021 *)CreatePart(0x15);
	if (pPart) {
		AK_s128 tmp = pos.m_v;
		pPart->rgba = beginRGBA;
		pPart->b1 = 0;
		pPart->scale = maxScale;
		pPart->b9 = 0xa4;
		pPart->flags = 0x48;
		pPart->pos = tmp;
		pPart->rot = rand();
		unsigned char tex = *PartClassTexs[0x15];
		pPart->timer = numFrames;
		pPart->tex = tex;
		AK_Part021Vars *pVar = (AK_Part021Vars *)pPart->vars;
		pVar->numFrames = numFrames;
		pVar->maxScale = maxScale;
		pVar->beginRGBA = beginRGBA;
		pVar->endRGBA = endRGBA;
		pVar->master = master;
		AK_s128 tmp2 = vel.m_v;
		pVar->vel = tmp2;
	}
	return (part *)pPart;
}

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
