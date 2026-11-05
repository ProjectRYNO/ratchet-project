#include "common.h"
#include "game_section.h"


struct HelpMsg {
	/* 0x00 */ char *text;
	/* 0x04 */ short id;
	/* 0x06 */ short shortid;
	/* 0x08 */ int unk08[2];
};
struct HelpDataMessage {
	/* 0x00 */ unsigned short timesUsed;
	/* 0x02 */ short unk02;
	/* 0x04 */ int unk04;
	/* 0x08 */ unsigned int level_die;
};
struct HelpDef {
	/* 0x00 */ int state;
	/* 0x04 */ int counter;
	/* 0x08 */ int message_id;
	/* 0x0c */ int message_index;
	/* 0x10 */ int unk10;
	/* 0x14 */ int message_flg;
	/* 0x18 */ int num_message;
	/* 0x1c */ unsigned int streamHandle;
	/* 0x20 */ short ready_timer;
	/* 0x22 */ short text_time;
	/* 0x24 */ short suspend_timer;
	/* 0x26 */ unsigned char ready;
	/* 0x27 */ unsigned char suspend;
};
struct Help_QueueData {
	/* 0x00 */ short head;
	/* 0x02 */ short tail;
	/* 0x04 */ short count;
	/* 0x06 */ short unk06[5];
};
struct StreamInterface {
	/* 0x00 */ char unk00[0x100];
	unsigned int Stop(unsigned int, float) __asm__("Stop");
};
struct MathUtilities {
	int WrapValue(int value, int low, int high) __asm__("WrapValue");
};
struct PADtap {
	/* 0x000 */ char unk000[0x550];
	/* 0x550 */ unsigned char multi_tap_connected;
};
extern HelpDef Help __asm__("Help");
extern Help_QueueData HelpQueue __asm__("HelpQueue");
extern HelpMsg *HelpMsgs __asm__("HelpMsgs");
extern HelpDataMessage HelpDataMessages[] __asm__("HelpDataMessages");
extern StreamInterface StreamSys __asm__("StreamSys");
extern unsigned int Menu_voStream __asm__("Menu_voStream");
extern MathUtilities MU __asm__("D_222010");
extern PADtap *pPad0 __asm__("pPad0");
void Help_SetState(int) __asm__("Help_SetState");
int Help_FindIndex(int) __asm__("Help_FindIndex");
char *msg_string(int) __asm__("msg_string");
char *msg_string_mtap(int) __asm__("msg_string_mtap");
bool Help_CheckIfEmptyText(int) __asm__("Help_CheckIfEmptyText");
void HelpQueue_Advance() __asm__("HelpQueue_Advance");
int HelpQueue_GetNextIndex() __asm__("HelpQueue_GetNextIndex");
void Help_ClearUsedSinceDeath() __asm__("Help_ClearUsedSinceDeath");
bool Help_KillMenuMessage() __asm__("Help_KillMenuMessage");
void Help_Kill() __asm__("Help_Kill");
bool Help_QueueMessageRepeatDelay(short, short, unsigned int, int) __asm__("Help_QueueMessageRepeatDelay");
bool Help_QueueMessageDelay(short, short, unsigned int, int) __asm__("Help_QueueMessageDelay");
void Help_ShutDown() __asm__("Help_ShutDown");
void Help_StopVoice() __asm__("Help_StopVoice");
void Help_Reset() __asm__("Help_Reset");


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", Help_Reset);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", Help_Update);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", func_0045D7A8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", Help_QueueMessage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", Help_IsMessageInQueue);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", Help_QueueMessageOnce);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", Help_QueueMessageOncePerLevel);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", func_0045DA60);

GAME_SECTION(Help_QueueMessageDelay) bool Help_QueueMessageDelay(short id, short flag, unsigned int time, int priority)
{
	if (HelpDataMessages[flag].timesUsed == 0) return Help_QueueMessageRepeatDelay(id, flag, time, priority);
	return false;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", Help_QueueMessageRepeatDelay);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", Help_QueueMessageEveryNTimes);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", Help_QueueMenuMessage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", Help_KillMenuMessage);

GAME_SECTION(Help_ShutDown) void Help_ShutDown()
{
	Help_StopVoice();
	Help.message_id = -1;
	Help.message_index = -1;
	if (Help.suspend) Help_SetState(2);
	else Help_SetState(0);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", Help_Kill);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", func_0045DED8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", Help_Resume);

GAME_SECTION(Help_ClearUsedSinceDeath) void Help_ClearUsedSinceDeath()
{
	int i;
	for (i = 0; i < 0x827; i++) {
		HelpDataMessages[i].level_die &= 0x7fffffff;
	}
}

GAME_SECTION(Help_CheckIfEmptyText) bool Help_CheckIfEmptyText(int id)
{
	return msg_string(id) == (char *)HelpMsgs;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", FUN_0045df58);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", Help_DoAddToHelpLogException);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", msg_string);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", func_0045E078);

GAME_SECTION(msg_string_mtap) char *msg_string_mtap(int tag)
{
	int shortid = HelpMsgs[Help_FindIndex(tag)].shortid;
	if (shortid > 0 && pPad0->multi_tap_connected) tag = shortid;
	return msg_string(tag);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", Help_MessageCancelled);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", Help_MessageCompleted);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", Help_SetState);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", Help_StopVoice);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", Help_AddToLog);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", Help_FindIndex);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", HelpQueue_Insert);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", HelpQueue_GetInsertIndex);

GAME_SECTION(HelpQueue_Advance) void HelpQueue_Advance()
{
	HelpQueue.head = HelpQueue_GetNextIndex();
	HelpQueue.count--;
}

GAME_SECTION(HelpQueue_GetNextIndex) int HelpQueue_GetNextIndex()
{
	return MU.WrapValue(HelpQueue.head + 1, 0, 0xf);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/help", HelpQueue_IsEmpty);
