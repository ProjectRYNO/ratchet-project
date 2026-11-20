#include "common.h"
#include "game_section.h"
#include "mobyutil.h"

struct part;
part *CreatePart(int) __asm__("CreatePart");
void SpawnPart_097_Main(part *, vec4f &, vec4f &, int, int, int, int, int, float, float, float, int) __asm__("SpawnPart_097_Main");
part *SpawnPart_097(vec4f &pos, vec4f &vel, int frames, int rgb, int rotSp, int initAlpha, int endAlpha, float initScale, float endScale, float gravity, int texID) __asm__("SpawnPart_097");

void SpawnPart_002_Main(part *, vec4 &, vec4 &, vec4 &, int, int, int, int, int, int) __asm__("SpawnPart_002_Main");
part *SpawnPart_002(vec4 &pos, vec4 &initVel, vec4 &finalVel, int initRGBA, int finalRGBA, int shootTimer, int slowTimer, int fadeTimer, int textureType) __asm__("SpawnPart_002");
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
	/* 0x10 */ s128 pos;
	/* 0x20 */ int update[8];
};
struct Part004 {
	/* 0x00 */ s128 vel;
	/* 0x10 */ int beginColor;
	/* 0x14 */ int endColor;
	/* 0x18 */ short maxScale;
	/* 0x1a */ short startScale;
	/* 0x1c */ int lifeSpan;
};
extern unsigned char *PartClassTexs[128] __asm__("PartClassTexs");
extern "C" int rand();
part *SpawnPart_004(vec4 &pos, vec4 &vel, int beginColor, int endColor, int lifeSpan, int startScale, int maxScale, int additive) __asm__("SpawnPart_004");
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
	/* 0x10 */ s128 pos;
	/* 0x20 */ char vars[0x20];
};
struct Part021Vars {
	/* 0x00 */ s128 vel;
	/* 0x10 */ int beginRGBA;
	/* 0x14 */ int endRGBA;
	/* 0x18 */ short numFrames;
	/* 0x1a */ short master;
	/* 0x1c */ float maxScale;
};
part *SpawnPart_021(vec4 &pos, vec4 &vel, int beginRGBA, int endRGBA, float maxScale, int numFrames, int master) __asm__("SpawnPart_021");

struct Part035 {
	/* 0x00 */ s128 vel;
	/* 0x10 */ int type;
	/* 0x14 */ int lifespan;
	/* 0x18 */ float z;
	/* 0x1c */ float rate;
};
float MB_randRange(float, float) __asm__("MB_randRange");
part *SpawnPart_035(vec4 &pos, vec4 &vel, int type, int lifespan) __asm__("SpawnPart_035");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_002_Main);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_002);

JUNK_ASM(func_00491B80,
	"\taddiu $29, $29, 0x60\n"
	"\tnop\n");

GAME_SECTION(SpawnPart_004) part *SpawnPart_004(vec4 &pos, vec4 &vel, int beginColor, int endColor, int lifeSpan, int startScale, int maxScale, int additive)
{
	Part *pPart = (Part *)CreatePart(4);
	if (pPart) {
		s128 tmp = pos.v;
		pPart->draw_dist = 0xa4;
		pPart->pos = tmp;
		pPart->rgba = beginColor;
		if (additive) pPart->gs_alpha = 0x48;
		else pPart->gs_alpha = 0x44;
		pPart->type = 0;
		pPart->tex = *PartClassTexs[4];
		pPart->rot = rand();
		pPart->scale = 0.0f;
		pPart->pos = pos.v;
		Part004 *pVar = (Part004 *)pPart->update;
		s128 tmp2 = vel.v;
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

JUNK_ASM(func_00491C88,
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0xd0\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_011);

JUNK_ASM(func_00491FA8,
	"\taddiu $29, $29, 0x80\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x70\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_015);

JUNK_ASM(func_00492130,
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x70\n"
	"\tnop\n"
	"\taddiu $29, $29, 0xb0\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n");

GAME_SECTION(SpawnPart_021) part *SpawnPart_021(vec4 &pos, vec4 &vel, int beginRGBA, int endRGBA, float maxScale, int numFrames, int master)
{
	Part021 *pPart;
	if (numFrames == 0) return 0;
	pPart = (Part021 *)CreatePart(0x15);
	if (pPart) {
		s128 tmp = pos.v;
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
		s128 tmp2 = vel.v;
		pVar->vel = tmp2;
	}
	return (part *)pPart;
}

JUNK_ASM(func_00492240,
	"\taddiu $29, $29, 0x80\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_022);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_023);

JUNK_ASM(func_00492530,
	"\taddiu $29, $29, 0x60\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_025);

JUNK_ASM(func_004926C8,
	"\taddiu $29, $29, 0x70\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_028);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_029);

JUNK_ASM(func_00492B70,
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_034);

JUNK_ASM(func_00492D78,
	"\taddiu $29, $29, 0x70\n"
	"\tnop\n");

GAME_SECTION(SpawnPart_035) part *SpawnPart_035(vec4 &pos, vec4 &vel, int type, int lifespan)
{
	Part *pPart = (Part *)CreatePart(0x23);
	if (pPart) {
		s128 tmp = pos.v;
		pPart->type = 0;
		pPart->pos = tmp;
		pPart->rgba = 0x80808080;
		pPart->draw_dist = 0x12;
		pPart->gs_alpha = 0x44;
		pPart->scale = MB_randRange(10500.0f, 16800.0f);
		Part035 *pVar = (Part035 *)pPart->update;
		pPart->tex = *PartClassTexs[0x23];
		s128 tmp2 = vel.v;
		pVar->vel = tmp2;
		pVar->lifespan = lifespan;
		pVar->type = type;
		pVar->z = ((float *)&pPart->pos)[2];
		if (type == 2) pVar->z = 0.0f;
		pVar->rate = MB_randRange(0.0029166667f, 0.005f);
	}
	return (part *)pPart;
}

JUNK_ASM(func_00492E88,
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x60\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_044);

JUNK_ASM(func_00493038,
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_045);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_046);

JUNK_ASM(func_004932C8,
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_053);

JUNK_ASM(func_004934A8,
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x60\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x70\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x60\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_064);

JUNK_ASM(func_00493618,
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0xa0\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0xb0\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x60\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_074);

JUNK_ASM(func_00493820,
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x80\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x80\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\taddiu $29, $29, 0xe0\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_085);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", UpdatePart_085);

JUNK_ASM(func_00493BD0,
	"\taddiu $29, $29, 0x70\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x70\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0xb0\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", UpdatePart_089);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_091);

JUNK_ASM(func_00494208,
	"\taddiu $29, $29, 0x80\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_092);

JUNK_ASM(func_00494440,
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_097_Main);

GAME_SECTION(SpawnPart_097) part *SpawnPart_097(vec4f &pos, vec4f &vel, int frames, int rgb, int rotSp, int initAlpha, int endAlpha, float initScale, float endScale, float gravity, int texID)
{
	part *pPart = CreatePart(0x61);
	if (pPart) SpawnPart_097_Main(pPart, pos, vel, frames, rgb, rotSp, initAlpha, endAlpha, initScale, endScale, gravity, texID);
	return pPart;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", UpdatePart_097);

JUNK_ASM(func_00494820,
	"\taddiu $29, $29, 0x70\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_099);

JUNK_ASM(func_00494980,
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_102);

JUNK_ASM(func_00494B08,
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x70\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_111);

JUNK_ASM(func_00494C68,
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\taddiu $29, $29, 0xc0\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x80\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x80\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_121);

JUNK_ASM(func_00494E08,
	"\taddiu $29, $29, 0x130\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x80\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x70\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_126);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_127);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", UpdatePart_127);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/partupd", SpawnPart_128);
