#include "common.h"
#include "game_section.h"



typedef unsigned long uint64;
struct FXRegistrySystemInternal {
	/* 0x00 */ unsigned char tracking;
	/* 0x01 */ char unk01[0xf];
	/* 0x10 */ int fogDirty;
	/* 0x14 */ char unk14[0x24];
	/* 0x38 */ uint64 tex1;
	/* 0x40 */ uint64 tex0;
	/* 0x48 */ uint64 zbuf;
};
int IsTrackingRegisters(FXRegistrySystemInternal *) __asm__("IsTrackingRegisters");
extern int FXReg __asm__("FXReg");
extern int FXRegB __asm__("D_221274");
extern int FXRegC __asm__("D_221278");
void SetBlendMode(int *, int, int, int) __asm__("SetBlendMode");
void CleanUpAfterEffectsRendering(FXRegistrySystemInternal *) __asm__("CleanUpAfterEffectsRendering");
extern FXRegistrySystemInternal IntFXReg __asm__("IntFXReg");
void VU1_addGSregister(unsigned int, uint64, int) __asm__("VU1_addGSregister");
void SetTextureDirect(void *, uint64) __asm__("SetTextureDirect");
typedef unsigned int qword_t[4];
extern qword_t *vu1_bufPtr __asm__("vu1_bufPtr");
struct ResetRegister {
	/* 0x00 */ uint64 value;
	/* 0x08 */ uint64 addr;
};
extern ResetRegister ResetTex1 __asm__("D_3D76E0");
extern qword_t FXRG_resetTex1RegisterSetting[] __asm__("FXRG_resetTex1RegisterSetting");
void ResetRegisterTex1(FXRegistrySystemInternal *) __asm__("ResetRegisterTex1");
extern ResetRegister ResetZBuf __asm__("D_3D76D0");
extern qword_t FXRG_resetZBufRegisterSetting[] __asm__("FXRG_resetZBufRegisterSetting");
void ResetRegisterZBuf(FXRegistrySystemInternal *) __asm__("ResetRegisterZBuf");
int ZUpdateRegisterValue(FXRegistrySystemInternal *, unsigned int, uint64) __asm__("ZUpdateRegisterValue");
void ZAddGSRegister(FXRegistrySystemInternal *, unsigned int, uint64, int) __asm__("ZAddGSRegister");

extern int active_vu1_mpg __asm__("active_vu1_mpg");
struct FXStripData {
	/* 0x00 */ void *pXYZ;
	/* 0x04 */ int *pRGBA;
	/* 0x08 */ void *pST;
};
int GetIconFrame(int, int) __asm__("GetIconFrame");
uint64 GetFrameTex(int) __asm__("GetFrameTex");
uint64 GetEffectTex(int, int) __asm__("GetEffectTex");
void FastDrawStripInit() __asm__("FastDrawStripInit");
void FasterDrawStrip(int, void *, int *, void *, int, int) __asm__("FasterDrawStrip");
void SetIconTexture(void *, int, int) __asm__("SetIconTexture");
void SetTexture(void *, int) __asm__("SetTexture");
void DrawQuad(FXStripData *, int) __asm__("DrawQuad___dupe3");
void DrawStrip(FXStripData *, int, int, int) __asm__("DrawStrip");
void DrawStrip(void *, int, void *, int *, void *, int, int) __asm__("DrawStrip___dupe2");


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXRegistry", PrepForEffectsRendering);

GAME_SECTION(CleanUpAfterEffectsRendering) void CleanUpAfterEffectsRendering(FXRegistrySystemInternal *self)
{
	SetBlendMode(&FXReg, 0xe, 1, 2);
	FXReg = 0;
	FXRegB = 0;
	FXRegC = 0;
	self->tracking = 0;
}

GAME_SECTION(IsTrackingRegisters) int IsTrackingRegisters(FXRegistrySystemInternal *self)
{
	return self->tracking;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXRegistry", func_0044D1B0);

GAME_SECTION(ResetRegisterZBuf) void ResetRegisterZBuf(FXRegistrySystemInternal *self)
{
	if (self->tracking && self->zbuf == ResetZBuf.value) return;
	(*vu1_bufPtr)[0] = 0x30000002;
	(*vu1_bufPtr)[1] = (unsigned int)FXRG_resetZBufRegisterSetting;
	(*vu1_bufPtr)[2] = 0;
	(*vu1_bufPtr)[3] = 0x50000002;
	vu1_bufPtr++;
}

GAME_SECTION(ResetRegisterTex1) void ResetRegisterTex1(FXRegistrySystemInternal *self)
{
	if (self->tracking && self->tex1 == ResetTex1.value) return;
	(*vu1_bufPtr)[0] = 0x30000002;
	(*vu1_bufPtr)[1] = (unsigned int)FXRG_resetTex1RegisterSetting;
	(*vu1_bufPtr)[2] = 0;
	(*vu1_bufPtr)[3] = 0x50000002;
	vu1_bufPtr++;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXRegistry", SetBlendMode);

GAME_SECTION(SetTexture) void SetTexture(void *self, int texture)
{
	if (!IntFXReg.tracking) {
		VU1_addGSregister(6, GetEffectTex(texture, 1), 0);
	} else if (IntFXReg.fogDirty != texture) {
		uint64 tex = GetEffectTex(texture, 1);
		if (IntFXReg.tex0 != tex) {
			IntFXReg.tex0 = tex;
			VU1_addGSregister(6, tex, 1);
		}
		IntFXReg.fogDirty = texture;
	}
}

GAME_SECTION(SetIconTexture) void SetIconTexture(void *self, int id, int frame)
{
	if (!IntFXReg.tracking) {
		VU1_addGSregister(6, GetFrameTex(GetIconFrame(id, frame)), 0);
	} else {
		uint64 tex = GetFrameTex(GetIconFrame(id, frame));
		if (IntFXReg.tex0 != tex) {
			IntFXReg.tex0 = tex;
			VU1_addGSregister(6, tex, 1);
			IntFXReg.fogDirty = 0x7c;
		}
	}
}

GAME_SECTION(SetTextureDirect) void SetTextureDirect(void *self, uint64 effectTexture)
{
	if (!IntFXReg.tracking) {
		VU1_addGSregister(6, effectTexture, 0);
	} else if (IntFXReg.tex0 != effectTexture) {
		IntFXReg.tex0 = effectTexture;
		VU1_addGSregister(6, effectTexture, 1);
		IntFXReg.fogDirty = 0x7c;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXRegistry", SetTextureClamp);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXRegistry", SetFogMode);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXRegistry", func_0044D930);

GAME_SECTION(DrawStrip) void DrawStrip(FXStripData *self, int iNumVerts, int clipped, int textured)
{
	if (!IntFXReg.tracking) {
		FastDrawStripInit();
	} else if (active_vu1_mpg != 8) {
		FastDrawStripInit();
		ResetRegisterZBuf(&IntFXReg);
	}
	FasterDrawStrip(iNumVerts, self->pXYZ, self->pRGBA, self->pST, clipped, textured);
}

GAME_SECTION(DrawStrip___dupe2) void DrawStrip(void *self, int iNumVerts, void *pXYZ, int *pRGBA, void *pST, int clipped, int textured)
{
	if (!IntFXReg.tracking) {
		FastDrawStripInit();
	} else if (active_vu1_mpg != 8) {
		FastDrawStripInit();
		ResetRegisterZBuf(&IntFXReg);
	}
	FasterDrawStrip(iNumVerts, pXYZ, pRGBA, pST, clipped, textured);
}

GAME_SECTION(DrawQuad___dupe3) void DrawQuad(FXStripData *self, int clipped)
{
	if (!IntFXReg.tracking) {
		FastDrawStripInit();
	} else if (active_vu1_mpg != 8) {
		FastDrawStripInit();
		ResetRegisterZBuf(&IntFXReg);
	}
	FasterDrawStrip(4, self->pXYZ, self->pRGBA, self->pST, clipped, 1);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXRegistry", func_0044DB48);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXRegistry", DrawQuad___dupe4);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXRegistry", func_0044DD98);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXRegistry", STScale);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXRegistry", func_0044DE70);

GAME_SECTION(ZAddGSRegister) void ZAddGSRegister(FXRegistrySystemInternal *self, unsigned int uiRegister, uint64 uiRegisterValue, int bForceSet)
{
	if (!IntFXReg.tracking) {
		VU1_addGSregister(uiRegister, uiRegisterValue, 0);
	} else if (ZUpdateRegisterValue(self, uiRegister, uiRegisterValue) || bForceSet) {
		VU1_addGSregister(uiRegister, uiRegisterValue, 1);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/FXRegistry", ZUpdateRegisterValue);
