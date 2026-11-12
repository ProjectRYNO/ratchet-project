#include "common.h"
#include "game_section.h"



struct CreditMessage {
	/* 0x00 */ int text;
	/* 0x04 */ int unk04[3];
};
struct CreditDef {
	/* 0x000 */ void *pHeap[2];
	/* 0x008 */ unsigned int *pool;
	/* 0x00c */ CreditMessage *messages;
	/* 0x010 */ unsigned int message_count;
	/* 0x014 */ int heapSize;
	/* 0x018 */ int oldGSbase;
	/* 0x01c */ int unk01c;
	/* 0x020 */ short unk020;
	/* 0x022 */ short page;
	/* 0x024 */ short line;
	/* 0x026 */ short unk026;
	/* 0x028 */ short state;
	/* 0x02a */ short unk02a;
	/* 0x02c */ int timer;
	/* 0x030 */ int timerMax;
	/* 0x034 */ int currentPage;
	/* 0x038 */ char unk038[0x340];
	/* 0x378 */ int ts1_LineTimeGap;
	/* 0x37c */ int ts1_OneLineTime;
	/* 0x380 */ char unk380[0x18];
};
extern CreditDef Credit __asm__("Credit");
int FastDecTimer(int &) __asm__("FastDecTimer");
int Credit_SequenceTrigger() __asm__("Credit_SequenceTrigger");
void setArrayContents(int *theArray, int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9, int n10) __asm__("setArrayContents");
void Credit_InitializeMessagePool() __asm__("Credit_InitializeMessagePool");
struct CreditPage {
	/* 0x00 */ int unk00;
	/* 0x04 */ int first;
	/* 0x08 */ int last;
	/* 0x0c */ int unk0c[3];
	/* 0x18 */ int textScrollMode;
	/* 0x1c */ int numLinesOnScreen;
	/* 0x20 */ int unk20[10];
	/* 0x48 */ int timeOnScreen;
};
struct CreditPages {
	/* 0x0000 */ CreditPage pages[0x40];
	/* 0x1300 */ int count;
};
extern CreditPages g_CreditPages __asm__("g_CreditPages");
bool Credit_PageForLine(int line, int *pPage, int *pLine) __asm__("Credit_PageForLine");


struct MemSlotsChains {
	/* 0x00 */ int unk00[3];
	/* 0x0c */ char *vu1_chain[2];
	/* 0x14 */ int unk14[3];
};
extern MemSlotsChains MemSlots __asm__("D_0023AB00");
extern int gsFrame __asm__("gsFrame");
extern int vu1_bufSize __asm__("vu1_bufSize");
extern int EngScratchPadSize __asm__("EngScratchPadSize");
extern int GSbase __asm__("GSbase");
extern float ScreenFade0 __asm__("ScreenFade");
extern unsigned int g_credits_stream_handle __asm__("D_21EB28");
struct StreamInterface {
	unsigned int Stop(unsigned int, float) __asm__("Stop");
};
extern StreamInterface StreamSys __asm__("StreamSys");
struct UberSound {
	static void Stop(unsigned int) __asm__("Stop___dupe2");
};
extern "C" int sceGsSyncV(int);
void VU1_syncChain(int) __asm__("VU1_syncChain");
void VU1_setBufSizeByLevel() __asm__("VU1_setBufSizeByLevel");
void VU1_initChain() __asm__("VU1_initChain");
void FadeToBlack(int, unsigned int) __asm__("FadeToBlack");
bool Credit_SeekNextLines() __asm__("Credit_SeekNextLines");
void _mode_creditsInit() __asm__("_mode_creditsInit");
void _mode_creditsUnInit() __asm__("_mode_creditsUnInit");
void Credit_AdvancePage() __asm__("Credit_AdvancePage");

GAME_SECTION(_mode_creditsInit) void _mode_creditsInit()
{
	VU1_syncChain(1);
	sceGsSyncV(0);
	gsFrame++;
	Credit.heapSize = vu1_bufSize - 0x60000;
	Credit.pHeap[0] = MemSlots.vu1_chain[0] + 0x60000;
	Credit.pHeap[1] = MemSlots.vu1_chain[1] + 0x60000;
	Credit.pool = (unsigned int *)((char *)Credit.pHeap[0] + 0xd0800);
	EngScratchPadSize = 0x2000;
	vu1_bufSize = 0x60000;
	VU1_initChain();
	UberSound::Stop(1);
	Credit.oldGSbase = GSbase;
	ScreenFade0 = 1.0f;
}

GAME_SECTION(_mode_creditsUnInit) void _mode_creditsUnInit()
{
	VU1_syncChain(1);
	VU1_setBufSizeByLevel();
	VU1_initChain();
	ScreenFade0 = 0.0f;
	GSbase = Credit.oldGSbase;
	FadeToBlack(0x1e, 0);
}

GAME_SECTION(setArrayContents) void setArrayContents(int *theArray, int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9, int n10)
{
	theArray[0] = n1;
	theArray[1] = n2;
	theArray[2] = n3;
	theArray[3] = n4;
	theArray[4] = n5;
	theArray[5] = n6;
	theArray[6] = n7;
	theArray[7] = n8;
	theArray[8] = n9;
	theArray[9] = n10;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/credits", _credits_update);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/credits", Credit_AddSequence);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/credits", func_00446968);

GAME_SECTION(Credit_InitializeMessagePool) void Credit_InitializeMessagePool()
{
	int i;
	Credit.messages = (CreditMessage *)Credit.pool;
	Credit.message_count = *Credit.pool >> 4;
	for (i = 0; i < (int)Credit.message_count; i++) {
		Credit.messages[i].text += (int)Credit.messages;
	}
}

GAME_SECTION(Credit_PageForLine) bool Credit_PageForLine(int line, int *pPage, int *pLine)
{
	*pPage = Credit.page;
	*pLine = Credit.line + line;
	if (*pPage >= 0 && *pPage < g_CreditPages.count) {
		return g_CreditPages.pages[*pPage].first + *pLine <= g_CreditPages.pages[*pPage].last;
	}
	return false;
}

GAME_SECTION(Credit_SequenceTrigger) int Credit_SequenceTrigger()
{
	return FastDecTimer(Credit.timer);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/credits", Credit_AdvancePage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/credits", Credit_SeekNextLines);
