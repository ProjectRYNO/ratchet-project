#include "common.h"
#include "game_section.h"



typedef unsigned long uint64;
struct FXRegistrySystemInternal {
	/* 0x00 */ unsigned char tracking;
	/* 0x01 */ char unk01[3];
	/* 0x04 */ int blendMode;
	/* 0x08 */ int clampMode;
	/* 0x0c */ int fogMode;
	/* 0x10 */ int fogDirty;
	/* 0x14 */ char unk14[4];
	/* 0x18 */ uint64 alpha;
	/* 0x20 */ uint64 clamp;
	/* 0x28 */ uint64 fogCol;
	/* 0x30 */ uint64 test;
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


extern int FXRG_FogModesForBlendModes[] __asm__("FXRG_FogModesForBlendModes");
extern uint64 FXRG_fogModeRegisterSettings[][4] __asm__("FXRG_fogModeRegisterSettings");
void SetFogMode(FXRegistrySystemInternal *, int) __asm__("SetFogMode");
extern uint64 FXRG_clampModeRegisterSettings[][4] __asm__("FXRG_clampModeRegisterSettings");
extern uint64 FXRG_prepEffectsRegisterSettings[] __asm__("FXRG_prepEffectsRegisterSettings");
struct alGsMemDef {
	/* 0x00 */ int unk00[2];
	/* 0x08 */ int zbuf;
};
extern alGsMemDef GSmem __asm__("GSmem");
struct alViewContext {
	/* 0x000 */ char unk000[0x250];
	/* 0x250 */ int fogR;
	/* 0x254 */ int fogG;
	/* 0x258 */ int fogB;
};
extern alViewContext VC __asm__("VC");
void SetTextureClamp(FXRegistrySystemInternal *, int) __asm__("SetTextureClamp");
void PrepForEffectsRendering(FXRegistrySystemInternal *) __asm__("PrepForEffectsRendering");
extern uint64 FXRG_blendModeRegisterSettings[][6] __asm__("FXRG_blendModeRegisterSettings");
unsigned char FXRG_bSetBloomFlagForBlendModes[16] __asm__("FXRG_bSetBloomFlagForBlendModes") GAME_GP_DATA = {0};
extern int g_BloomFlag __asm__("g_BloomFlag");
static inline void alAddCommandsList3(unsigned int uiCommandsList)
{
	(*vu1_bufPtr)[0] = 0x30000003;
	(*vu1_bufPtr)[1] = uiCommandsList;
	(*vu1_bufPtr)[2] = 0;
	(*vu1_bufPtr)[3] = 0x50000003;
}

extern uint64 alResetZBufSetting[] __asm__("FXRG_resetZBufRegisterSetting");
GAME_SECTION(PrepForEffectsRendering) void PrepForEffectsRendering(FXRegistrySystemInternal *self)
{
	uint64 v;

	FXRG_prepEffectsRegisterSettings[2] = (long)(GSmem.zbuf >> 13) | 0x1000000;
	alResetZBufSetting[2] = FXRG_prepEffectsRegisterSettings[2];
	(*vu1_bufPtr)[0] = 0x30000007;
	(*vu1_bufPtr)[1] = (unsigned int)FXRG_prepEffectsRegisterSettings;
	(*vu1_bufPtr)[2] = 0;
	(*vu1_bufPtr)[3] = 0x50000007;
	vu1_bufPtr = vu1_bufPtr + 1;
	self->fogMode = 3;
	self->fogDirty = 0x7c;
	self->clampMode = 1;
	self->blendMode = 0;
	self->alpha = FXRG_prepEffectsRegisterSettings[6];
	self->clamp = FXRG_prepEffectsRegisterSettings[10];
	self->fogCol = FXRG_prepEffectsRegisterSettings[12];
	self->test = FXRG_prepEffectsRegisterSettings[8];
	v = FXRG_prepEffectsRegisterSettings[4];
	self->tex0 = 0;
	self->tex1 = v;
	self->zbuf = FXRG_prepEffectsRegisterSettings[2];
	FXRG_fogModeRegisterSettings[2][2] = (long)VC.fogR | (long)VC.fogG << 8 | (long)VC.fogB << 16;
	FastDrawStripInit();
	FXReg = 0x70000000;
	FXRegB = 0x70001000;
	FXRegC = 0x70001400;
	(&FXRegC)[1] = 0x70001c00;
	self->tracking = 1;
}

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

GAME_SECTION(SetTextureClamp) void SetTextureClamp(FXRegistrySystemInternal *self, int clamp)
{
	if (!IntFXReg.tracking) {
		if (clamp != 0) {
			(*vu1_bufPtr)[0] = 0x30000002;
			(*vu1_bufPtr)[1] = (unsigned int)FXRG_clampModeRegisterSettings[clamp];
			(*vu1_bufPtr)[2] = 0;
			(*vu1_bufPtr)[3] = 0x50000002;
			vu1_bufPtr = vu1_bufPtr + 1;
			return;
		}
	} else if (clamp != 0) {
		if (IntFXReg.clampMode == clamp) {
			if (IntFXReg.clamp == FXRG_clampModeRegisterSettings[clamp][2]) {
				return;
			}
		} else if (IntFXReg.clamp == FXRG_clampModeRegisterSettings[clamp][2]) {
			IntFXReg.clampMode = clamp;
			return;
		}
		(*vu1_bufPtr)[0] = 0x30000002;
		(*vu1_bufPtr)[1] = (unsigned int)FXRG_clampModeRegisterSettings[clamp];
		(*vu1_bufPtr)[2] = 0;
		(*vu1_bufPtr)[3] = 0x50000002;
		IntFXReg.clamp = FXRG_clampModeRegisterSettings[clamp][2];
		vu1_bufPtr++;
		IntFXReg.clampMode = clamp;
	}
}

GAME_SECTION(SetFogMode) void SetFogMode(FXRegistrySystemInternal *self, int fogMode)
{
	if (IntFXReg.tracking && fogMode != 0) {
		if (fogMode == 1) {
			if (IntFXReg.blendMode == -1) {
				fogMode = 2;
			} else {
				fogMode = FXRG_FogModesForBlendModes[IntFXReg.blendMode];
			}
		}
		if (IntFXReg.fogMode == fogMode) {
			if (IntFXReg.fogCol == FXRG_fogModeRegisterSettings[fogMode][2]) {
				return;
			}
		} else if (IntFXReg.fogCol == FXRG_fogModeRegisterSettings[fogMode][2]) {
			IntFXReg.fogMode = fogMode;
			return;
		}
		(*vu1_bufPtr)[0] = 0x30000002;
		(*vu1_bufPtr)[1] = (unsigned int)FXRG_fogModeRegisterSettings[fogMode];
		(*vu1_bufPtr)[2] = 0;
		(*vu1_bufPtr)[3] = 0x50000002;
		IntFXReg.fogCol = FXRG_fogModeRegisterSettings[fogMode][2];
		vu1_bufPtr++;
		IntFXReg.fogMode = fogMode;
	}
}

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

/* ===== AL additions ===== */
GAME_SECTION(ZUpdateRegisterValue) int ZUpdateRegisterValue(FXRegistrySystemInternal *self, unsigned int reg, uint64 value)
{
	if (!IntFXReg.tracking) {
		return 1;
	}
	switch (reg) {
	case 0x42:
		if (IntFXReg.alpha == value) {
			return 0;
		}
		IntFXReg.blendMode = -1;
		IntFXReg.alpha = value;
		break;
	case 0x47:
		if (IntFXReg.test == value) {
			return 0;
		}
		IntFXReg.blendMode = -1;
		IntFXReg.test = value;
		break;
	case 8:
		if (IntFXReg.clamp == value) {
			return 0;
		}
		IntFXReg.clampMode = -1;
		IntFXReg.clamp = value;
		break;
	case 6:
		if (IntFXReg.tex0 == value) {
			return 0;
		}
		IntFXReg.fogDirty = 0x7c;
		IntFXReg.tex0 = value;
		break;
	case 0x14:
		if (IntFXReg.tex1 == value) {
			return 0;
		}
		IntFXReg.tex1 = value;
		break;
	case 0x4e:
		if (IntFXReg.zbuf == value) {
			return 0;
		}
		IntFXReg.zbuf = value;
		break;
	case 0x3d:
		if (IntFXReg.fogCol == value) {
			return 0;
		}
		IntFXReg.fogCol = value;
		break;
	}
	return 1;
}
