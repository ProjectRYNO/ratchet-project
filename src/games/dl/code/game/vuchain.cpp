#include "common.h"
#include "game_section.h"


typedef int qwordWords[4];
struct MemSlotsVu {
	/* 0x00 */ int unk00[3];
	/* 0x0c */ void *vu1_chain[2];
	/* 0x14 */ int unk14[0x40];
};
extern qwordWords *vu1_bufPtr __asm__("vu1_bufPtr");
extern qwordWords *vu1_DmaBuffers[2] __asm__("vu1_DmaBuffers");
extern int vu1_maxUseBeforeMobys __asm__("vu1_maxUseBeforeMobys");
extern int vu1_bufId __asm__("vu1_bufId");
extern int _dmacHandle[2] __asm__("_dmacHandle");
extern MemSlotsVu MemSlots __asm__("D_0023AB00");
extern char Gif_Tex_Flush[] __asm__("Gif_Tex_Flush");
int VifChainFlags __asm__("VifChainFlags") GAME_GP_DATA = 0;
extern "C" {
	int RemoveDmacHandler(int, int);
	int DisableDmac(int);
}
void FastSitAndSpin(int) __asm__("FastSitAndSpin");
void VU1_resetScratch() __asm__("VU1_resetScratch");
void Vif1ChainCmd(int) __asm__("Vif1ChainCmd");
void VU1_syncChain(int) __asm__("VU1_syncChain");
void VU1_addDataRef(void *, int) __asm__("VU1_addDataRef");
void VU1_initChain() __asm__("VU1_initChain");
void VU1_texFlush() __asm__("VU1_texFlush");
void DMAC_VIF1_Disable() __asm__("DMAC_VIF1_Disable");


extern int vu1_bufSize __asm__("vu1_bufSize");
extern int EngScratchPadSize __asm__("EngScratchPadSize");
extern int ShadowScratchPadSize __asm__("ShadowScratchPadSize");
extern char *EngScratchPad __asm__("EngScratchPad");
extern char *ShadowScratchPad __asm__("ShadowScratchPad");
extern char *SkinVertexCache __asm__("SkinVertexCache");
extern char gs_regs_normal[] __asm__("gs_regs_normal");
extern char gs_regs_effects[] __asm__("gs_regs_effects");
extern int vu1_buf_table[] __asm__("vu1_buf_table");
extern int Level __asm__("Level");
extern "C" {
	int AddDmacHandler(int, int (*)(int), int);
	int EnableDmac(int);
}
int DMAC_VIF1_Handler(int) __asm__("DMAC_VIF1_Handler");
int DMAC_BEIS_Handler(int) __asm__("DMAC_BEIS_Handler");
void FastMemCopy16(void *, void *, int) __asm__("FastMemCopy16");
void VU1_gsRegsNormal() __asm__("VU1_gsRegsNormal");
void VU1_gsRegsEffects() __asm__("VU1_gsRegsEffects");
void VU1_swapChain() __asm__("VU1_swapChain");
void VU1_setBufSizeByLevel() __asm__("VU1_setBufSizeByLevel");
void VU1_addDataDirect(int, void *, int) __asm__("VU1_addDataDirect");
void DMAC_VIF1_Enable() __asm__("DMAC_VIF1_Enable");

struct sceGsStoreImage {
	/* 0x00 */ char unk00[0x70];
};
extern "C" {
	void sceGsSetDefStoreImage(sceGsStoreImage *, short, short, short, short, short, short, short);
	int sceGsExecStoreImage(sceGsStoreImage *, void *);
	int sceGsSyncPath(int, unsigned short);
	void FlushCache(int);
}
unsigned long *g_current_vu0_program __asm__("g_current_vu0_program") GAME_GP_DATA = 0;
int GSRegisterListOpen __asm__("GSRegisterListOpen") GAME_GP_DATA = 0;
void VU0_loadMicroProgram(unsigned long *) __asm__("VU0_loadMicroProgram");
void VU1_addGSregister(unsigned int, unsigned long, int) __asm__("VU1_addGSregister");
void StashGSMem(void *, int, int) __asm__("StashGSMem");
struct AABuff {
	/* 0x000 */ char unk000[0x150];
	/* 0x150 */ short drawW;
	/* 0x152 */ short drawH;
};
extern AABuff aaBuff __asm__("aaBuff");
extern char reset_gs_regs_draw[] __asm__("reset_gs_regs_draw");
extern char reset_gs_regs_scis[] __asm__("reset_gs_regs_scis");
extern int vu1_use __asm__("vu1_use");
extern int vu1_maxUse __asm__("vu1_maxUse");
struct sceDmaChan {
	/* 0x00 */ unsigned int chcr;
};
extern "C" {
	sceDmaChan *sceDmaGetChan(int);
	void sceDmaSend(sceDmaChan *, void *);
}
void FastMemCopy(void *, const void *, int) __asm__("FastMemCopy");
void ResetTieLightingCache() __asm__("ResetTieLightingCache");
void VU1_resetDrawContexts() __asm__("VU1_resetDrawContexts");
void VU1_setScissor(int, int, int, int) __asm__("VU1_setScissor");
void VU1_sendChain() __asm__("VU1_sendChain");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", VU0_loadMicroProgram);

GAME_SECTION(VU1_setBufSizeByLevel) void VU1_setBufSizeByLevel()
{
	vu1_bufSize = 0x160000;
	if (0 < Level) {
		if (Level < 20) vu1_bufSize = vu1_buf_table[Level];
		else if (Level < 40) vu1_bufSize = vu1_buf_table[Level - 20];
		else if (Level < 60) vu1_bufSize = 0x120000;
		else if (Level < 80) vu1_bufSize = 0x120000;
		else vu1_bufSize = 0x160000;
	}
	ShadowScratchPadSize = 0xf000;
	EngScratchPadSize = 0x1e000;
	VU1_resetScratch();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", VU1_resetScratch);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", VU1_initChain);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", VU1_swapChain);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", VU1_sendChain);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", VU1_syncChain);

GAME_SECTION(VU1_addDataRef) void VU1_addDataRef(void *data, int qcnt)
{
	(*vu1_bufPtr)[0] = qcnt | 0x30000000;
	(*vu1_bufPtr)[1] = (int)data;
	(*vu1_bufPtr)[2] = 0;
	(*vu1_bufPtr)[3] = 0;
	vu1_bufPtr = vu1_bufPtr + 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", func_004E78C8);

GAME_SECTION(VU1_addDataDirect) void VU1_addDataDirect(int addr, void *data, int qcnt)
{
	(*vu1_bufPtr)[0] = qcnt | 0x10000000;
	(*vu1_bufPtr)[1] = 0;
	(*vu1_bufPtr)[2] = 0x1000404;
	(*vu1_bufPtr)[3] = addr | qcnt << 16 | 0x6c000000;
	vu1_bufPtr = vu1_bufPtr + 1;
	FastMemCopy16(vu1_bufPtr, data, qcnt * 16);
	vu1_bufPtr = vu1_bufPtr + qcnt;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", func_004E7978);

GAME_SECTION(VU1_addGSregister) void VU1_addGSregister(unsigned int reg, unsigned long rval, int bFXRegTrackingAcknowledged)
{
	if (GSRegisterListOpen == 0) {
		(*vu1_bufPtr)[0] = 0x10000002;
		(*vu1_bufPtr)[1] = 0;
		(*vu1_bufPtr)[2] = 0;
		(*vu1_bufPtr)[3] = 0x50000002;
		vu1_bufPtr[1][0] = 0x8001;
		vu1_bufPtr[1][1] = 0x10000000;
		vu1_bufPtr[1][2] = 0xe;
		vu1_bufPtr[1][3] = 0;
		vu1_bufPtr = vu1_bufPtr + 2;
	}
	*(unsigned long *)*vu1_bufPtr = rval;
	(*vu1_bufPtr)[2] = reg;
	(*vu1_bufPtr)[3] = 0;
	vu1_bufPtr = vu1_bufPtr + 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", func_004E7A68);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", VU1_setScissor);

GAME_SECTION(VU1_texFlush) void VU1_texFlush()
{
	(*vu1_bufPtr)[0] = 0x30000003;
	(*vu1_bufPtr)[1] = (int)Gif_Tex_Flush;
	(*vu1_bufPtr)[2] = 0;
	(*vu1_bufPtr)[3] = 0x50000003;
	vu1_bufPtr = vu1_bufPtr + 1;
}

GAME_SECTION(VU1_gsRegsNormal) void VU1_gsRegsNormal()
{
	(*vu1_bufPtr)[0] = 0x30000003;
	(*vu1_bufPtr)[1] = (int)gs_regs_normal;
	(*vu1_bufPtr)[2] = 0;
	(*vu1_bufPtr)[3] = 0x50000003;
	vu1_bufPtr = vu1_bufPtr + 1;
}

GAME_SECTION(VU1_gsRegsEffects) void VU1_gsRegsEffects()
{
	(*vu1_bufPtr)[0] = 0x30000004;
	(*vu1_bufPtr)[1] = (int)gs_regs_effects;
	(*vu1_bufPtr)[2] = 0;
	(*vu1_bufPtr)[3] = 0x50000004;
	vu1_bufPtr = vu1_bufPtr + 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", func_004E7CA8);

GAME_SECTION(VU1_resetDrawContexts) void VU1_resetDrawContexts()
{
	(*vu1_bufPtr)[0] = 0x30000009;
	(*vu1_bufPtr)[1] = (int)reset_gs_regs_draw;
	(*vu1_bufPtr)[2] = 0;
	(*vu1_bufPtr)[3] = 0x50000009;
	vu1_bufPtr = vu1_bufPtr + 1;
	(*vu1_bufPtr)[0] = 0x10000003;
	(*vu1_bufPtr)[1] = 0;
	(*vu1_bufPtr)[2] = 0;
	(*vu1_bufPtr)[3] = 0x50000003;
	vu1_bufPtr = vu1_bufPtr + 1;
	FastMemCopy(vu1_bufPtr, reset_gs_regs_scis, 0x30);
	vu1_bufPtr = vu1_bufPtr + 3;
}

GAME_SECTION(StashGSMem) void StashGSMem(void *ram, int gs_start, int size)
{
	sceGsStoreImage image;
	int gs_pos = 0;
	int ram_pos = 0;
	int left = size + 0x3fff & -0x4000;
	for (; left > 0; left -= 0x4000) {
		sceGsSetDefStoreImage(&image, (gs_start + gs_pos) >> 8, 1, 1, 0, 0, 0x40, 0x40);
		gs_pos += 0x4000;
		FlushCache(0);
		sceGsExecStoreImage(&image, (char *)ram + ram_pos);
		ram_pos += 0x3000;
		sceGsSyncPath(0, 0);
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", func_004E7E50);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", UploadGSMemLinear);

GAME_SECTION(DMAC_VIF1_Enable) void DMAC_VIF1_Enable()
{
	if (_dmacHandle[0] == 0 && _dmacHandle[1] == 0) {
		unsigned int d_stat = *(volatile unsigned int *)0x1000e010;
		if ((d_stat & 0x20000) == 0) *(unsigned int *)0x1000e010 = 0x20000;
		_dmacHandle[0] = AddDmacHandler(1, DMAC_VIF1_Handler, 0);
		_dmacHandle[1] = AddDmacHandler(0xf, DMAC_BEIS_Handler, 0);
		EnableDmac(1);
	}
}

GAME_SECTION(DMAC_VIF1_Disable) void DMAC_VIF1_Disable()
{
	if (*(volatile unsigned int *)0x1000e010 & 0x20000) {
		*(volatile unsigned int *)0x1000e010 = 0x20000;
	}
	RemoveDmacHandler(1, _dmacHandle[0]);
	RemoveDmacHandler(0xf, _dmacHandle[1]);
	DisableDmac(1);
	_dmacHandle[0] = 0;
	_dmacHandle[1] = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", DMAC_VIF1_Handler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", DMAC_BEIS_Handler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", Vif1ChainCmd);
