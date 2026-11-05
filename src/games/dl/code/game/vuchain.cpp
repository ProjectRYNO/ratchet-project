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


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", VU0_loadMicroProgram);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", VU1_setBufSizeByLevel);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", VU1_addDataDirect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", func_004E7978);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", VU1_addGSregister);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", VU1_gsRegsNormal);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", VU1_gsRegsEffects);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", func_004E7CA8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", VU1_resetDrawContexts);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", StashGSMem);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", func_004E7E50);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", UploadGSMemLinear);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vuchain", DMAC_VIF1_Enable);

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
