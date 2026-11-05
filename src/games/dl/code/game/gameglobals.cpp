#include "common.h"
#include "game_section.h"

typedef struct profileStruct {
	/* 0x000 */ char unk00[4];
	/* 0x004 */ char normalLeftRightMode0;
	/* 0x005 */ char normalUpDownMode0;
	/* 0x008 */ int cameraSpeed0;
	/* 0x00c */ char normalLeftRightMode1;
	/* 0x00d */ char normalUpDownMode1;
	/* 0x010 */ int cameraSpeed1;
	/* 0x014 */ char normalLeftRightMode2;
	/* 0x015 */ char normalUpDownMode2;
	/* 0x018 */ int cameraSpeed2;
	/* 0x01c */ char FirstPersonModeOn;
	/* 0x020 */ char unk1d[0x20 + 3];
	/* 0x040 */ char savePassword;
	/* 0x041 */ char unk41[0x19f];
} profileStruct_t;
extern profileStruct_t mpProfiles[8] __asm__("D_001DFD70");
extern "C" void *memset(void *, int, unsigned int);
void InitMultiplayerProfiles() __asm__("InitMultiplayerProfiles");
extern int frontEndState __asm__("D_0021DE0C");
void SetFrontEndState(int state) __asm__("SetFrontEndState");
extern unsigned long GetTimerSystemTime() __asm__("GetTimerSystemTime");
unsigned long nwKbdTimerFunc() __asm__("nwKbdTimerFunc");


typedef struct cameraOption {
	/* 0x00 */ char unk00[2];
	/* 0x04 */ int unk;
} cameraOption_t;

GAME_SECTION(SetFrontEndState) void SetFrontEndState(int state)
{
	frontEndState = state;
}

GAME_SECTION(nwKbdTimerFunc) unsigned long nwKbdTimerFunc()
{
	return GetTimerSystemTime() / 0x24000;
}

GAME_SECTION(InitMultiplayerProfiles) void InitMultiplayerProfiles()
{
	profileStruct_t *p = mpProfiles;
	do {
		memset(p, 0, 0x1e0);
		p->normalLeftRightMode0 = 1;
		p->normalUpDownMode0 = 1;
		p->cameraSpeed0 = 0x32;
		p->normalLeftRightMode1 = 1;
		p->normalUpDownMode1 = 1;
		p->cameraSpeed1 = 0x32;
		p->normalLeftRightMode2 = 1;
		p->normalUpDownMode2 = 1;
		p->cameraSpeed2 = 0x32;
		p->FirstPersonModeOn = 1;
		p->savePassword = 1;
		p++;
	} while ((int)p < (int)&mpProfiles[8]);
}
