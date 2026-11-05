#include "common.h"
#include "game_section.h"



struct CreditMessage {
	/* 0x00 */ int text;
	/* 0x04 */ int unk04[3];
};
struct CreditDef {
	/* 0x000 */ int unk000[2];
	/* 0x008 */ unsigned int *pool;
	/* 0x00c */ CreditMessage *messages;
	/* 0x010 */ unsigned int message_count;
	/* 0x014 */ int unk014[3];
	/* 0x020 */ short unk020;
	/* 0x022 */ short page;
	/* 0x024 */ short line;
	/* 0x026 */ short unk026;
	/* 0x028 */ int unk028;
	/* 0x02c */ int timer;
	/* 0x030 */ char unk030[0x368];
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
	/* 0x0c */ char unk0c[0x40];
};
struct CreditPages {
	/* 0x0000 */ CreditPage pages[0x40];
	/* 0x1300 */ int count;
};
extern CreditPages g_CreditPages __asm__("g_CreditPages");
bool Credit_PageForLine(int line, int *pPage, int *pLine) __asm__("Credit_PageForLine");


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/credits", _mode_creditsInit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/credits", _mode_creditsUnInit);

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
