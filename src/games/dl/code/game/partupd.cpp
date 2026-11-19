#include "common.h"
#include "game_section.h"

struct vec4 { float x, y, z, w; };
struct part;
part *CreatePart(int) __asm__("CreatePart");
void SpawnPart_097_Main(part *, vec4 &, vec4 &, int, int, int, int, int, float, float, float, int) __asm__("SpawnPart_097_Main");
part *SpawnPart_097(vec4 &pos, vec4 &vel, int frames, int rgb, int rotSp, int initAlpha, int endAlpha, float initScale, float endScale, float gravity, int texID) __asm__("SpawnPart_097");

typedef unsigned int uint128 __attribute__((mode(TI)));
struct vec4Quad { uint128 m_v; };
void SpawnPart_002_Main(part *, vec4Quad &, vec4Quad &, vec4Quad &, int, int, int, int, int, int) __asm__("SpawnPart_002_Main");
part *SpawnPart_002(vec4Quad &pos, vec4Quad &initVel, vec4Quad &finalVel, int initRGBA, int finalRGBA, int shootTimer, int slowTimer, int fadeTimer, int textureType) __asm__("SpawnPart_002");
struct Part {
	/* 0x00 */ char unk00;
	/* 0x01 */ unsigned char type;
	/* 0x02 */ unsigned char tex;
	/* 0x03 */ unsigned char gs_alpha;
	/* 0x04 */ int rgba;
	/* 0x08 */ unsigned char rot;
	/* 0x09 */ unsigned char draw_dist;
	/* 0x0a */ short timer;
	/* 0x0c */ float scale;
	/* 0x10 */ uint128 pos;
	/* 0x20 */ int update[8];
};
struct Part004 {
	/* 0x00 */ uint128 vel;
	/* 0x10 */ int beginColor;
	/* 0x14 */ int endColor;
	/* 0x18 */ short maxScale;
	/* 0x1a */ short startScale;
	/* 0x1c */ int lifeSpan;
};
extern unsigned char *PartClassTexs[128] __asm__("PartClassTexs");
extern "C" int rand();
part *SpawnPart_004(vec4Quad &pos, vec4Quad &vel, int beginColor, int endColor, int lifeSpan, int startScale, int maxScale, int additive) __asm__("SpawnPart_004");
struct Part021 {
	/* 0x00 */ char unk00;
	/* 0x01 */ unsigned char b1;
	/* 0x02 */ unsigned char tex;
	/* 0x03 */ unsigned char flags;
	/* 0x04 */ int rgba;
	/* 0x08 */ unsigned char rot;
	/* 0x09 */ unsigned char b9;
	/* 0x0a */ short timer;
	/* 0x0c */ float scale;
	/* 0x10 */ uint128 pos;
	/* 0x20 */ char vars[0x20];
};
struct Part021Vars {
	/* 0x00 */ uint128 vel;
	/* 0x10 */ int beginRGBA;
	/* 0x14 */ int endRGBA;
	/* 0x18 */ short numFrames;
	/* 0x1a */ short master;
	/* 0x1c */ float maxScale;
};
part *SpawnPart_021(vec4Quad &pos, vec4Quad &vel, int beginRGBA, int endRGBA, float maxScale, int numFrames, int master) __asm__("SpawnPart_021");

struct Part035 {
	/* 0x00 */ uint128 vel;
	/* 0x10 */ int type;
	/* 0x14 */ int lifespan;
	/* 0x18 */ float z;
	/* 0x1c */ float rate;
};
float MB_randRange(float, float) __asm__("MB_randRange");
part *SpawnPart_035(vec4Quad &pos, vec4Quad &vel, int type, int lifespan) __asm__("SpawnPart_035");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_002_Main);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_002);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", func_00491B80);

GAME_SECTION(SpawnPart_004) part *SpawnPart_004(vec4Quad &pos, vec4Quad &vel, int beginColor, int endColor, int lifeSpan, int startScale, int maxScale, int additive)
{
	Part *pPart = (Part *)CreatePart(4);
	if (pPart) {
		uint128 tmp = pos.m_v;
		pPart->draw_dist = 0xa4;
		pPart->pos = tmp;
		pPart->rgba = beginColor;
		if (additive) pPart->gs_alpha = 0x48;
		else pPart->gs_alpha = 0x44;
		pPart->type = 0;
		pPart->tex = *PartClassTexs[4];
		pPart->rot = rand();
		pPart->scale = 0.0f;
		pPart->pos = pos.m_v;
		Part004 *pVar = (Part004 *)pPart->update;
		uint128 tmp2 = vel.m_v;
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

GAME_SECTION(SpawnPart_021) part *SpawnPart_021(vec4Quad &pos, vec4Quad &vel, int beginRGBA, int endRGBA, float maxScale, int numFrames, int master)
{
	Part021 *pPart;
	if (numFrames == 0) return 0;
	pPart = (Part021 *)CreatePart(0x15);
	if (pPart) {
		uint128 tmp = pos.m_v;
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
		Part021Vars *pVar = (Part021Vars *)pPart->vars;
		pVar->numFrames = numFrames;
		pVar->maxScale = maxScale;
		pVar->beginRGBA = beginRGBA;
		pVar->endRGBA = endRGBA;
		pVar->master = master;
		uint128 tmp2 = vel.m_v;
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

GAME_SECTION(SpawnPart_035) part *SpawnPart_035(vec4Quad &pos, vec4Quad &vel, int type, int lifespan)
{
	Part *pPart = (Part *)CreatePart(0x23);
	if (pPart) {
		uint128 tmp = pos.m_v;
		pPart->type = 0;
		pPart->pos = tmp;
		pPart->rgba = 0x80808080;
		pPart->draw_dist = 0x12;
		pPart->gs_alpha = 0x44;
		pPart->scale = MB_randRange(10500.0f, 16800.0f);
		Part035 *pVar = (Part035 *)pPart->update;
		pPart->tex = *PartClassTexs[0x23];
		uint128 tmp2 = vel.m_v;
		pVar->vel = tmp2;
		pVar->lifespan = lifespan;
		pVar->type = type;
		pVar->z = ((float *)&pPart->pos)[2];
		if (type == 2) pVar->z = 0.0f;
		pVar->rate = MB_randRange(0.0029166667f, 0.005f);
	}
	return (part *)pPart;
}

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
