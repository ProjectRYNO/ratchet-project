#include "common.h"
#include "game_section.h"



typedef int s128 __attribute__((mode(TI)));
struct vec4 {
	/* 0x00 */ s128 q;
};
struct Cuboid {
	/* 0x00 */ char unk00[0x80];
};
extern Cuboid *Cuboids __asm__("Cuboids");
int FastPointInCuboid(Cuboid *, vec4 &, vec4 *) __asm__("FastPointInCuboid");
int MB_IsPntInCuboid(vec4 &, int, vec4 *) __asm__("MB_IsPntInCuboid");
int rand16() __asm__("rand16");
int MB_rand(int) __asm__("MB_rand");
int MB_randRangeInt(int, int) __asm__("MB_randRangeInt");
float MB_randRange(float, float) __asm__("MB_randRange");
float MB_randRange2(float, float) __asm__("MB_randRange2");
float MB_randRot() __asm__("MB_randRot");
extern char RandSphereTemp __asm__("D_222010");
s128 GetVectorSphere(vec4 *, float, float, float) __asm__("GetVectorSphere");
void MB_randSphere(vec4 &, float, float) __asm__("MB_randSphere");

struct moby {
	/* 0x00 */ char unk00[0x20];
	/* 0x20 */ unsigned char bits;
	/* 0x21 */ char unk21[0x34 - 0x21];
	/* 0x34 */ unsigned short state;
	/* 0x36 */ char unk36[0xbc - 0x36];
	/* 0xbc */ short oClass;
	/* 0xbe */ char unkbe[0x100 - 0xbe];
};
struct MobyInterface {
	/* 0x00 */ int unk00;
	/* 0x04 */ int (*check)(moby *);
};
struct MoveVars {
	/* 0x00 */ int unk00;
	/* 0x04 */ unsigned int flags;
};
MobyInterface *MobyGetInterface(int, int, int) __asm__("MobyGetInterface___dupe2");
MoveVars *MB_GetMoveVars(moby *) __asm__("MB_GetMoveVars_2");
int FUN_00472818(moby *) __asm__("FUN_00472818");

GAME_SECTION(MB_IsPntInCuboid) int MB_IsPntInCuboid(vec4 &pnt, int cuboidlink, vec4 *relative)
{
	if (cuboidlink == -1) return 0;
	return FastPointInCuboid(&Cuboids[cuboidlink], pnt, relative);
}

GAME_SECTION(MB_rand) int MB_rand(int max)
{
	return rand16() % max;
}

GAME_SECTION(MB_randRangeInt) int MB_randRangeInt(int min, int max)
{
	return rand16() % (max - min + 1) + min;
}

GAME_SECTION(MB_randRange) float MB_randRange(float min, float max)
{
	return min + (float)rand16() * (max - min) * 3.0517578e-05f;
}

GAME_SECTION(MB_randRange2) float MB_randRange2(float min, float max)
{
	int iret;
	float ret;
	iret = rand16();
	ret = min + (float)iret * (max - min) * 3.0517578e-05f;
	if (iret & 1) ret = -ret;
	return ret;
}

GAME_SECTION(MB_randRot) float MB_randRot()
{
	return (float)(rand16() - 0x4000) * 3.1415927f * 6.1035156e-05f;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/bootutil", MB_randVector);

GAME_SECTION(MB_randSphere) void MB_randSphere(vec4 &v, float minRad, float maxRad)
{
	float a = MB_randRot();
	float b = MB_randRot();
	float r = MB_randRange(minRad, maxRad);
	v.q = GetVectorSphere((vec4 *)&RandSphereTemp, r, a, b);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/bootutil", FUN_00472818);
