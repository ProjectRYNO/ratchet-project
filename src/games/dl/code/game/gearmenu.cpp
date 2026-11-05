#include "common.h"
#include "game_section.h"


extern int g_gameType __asm__("g_gameType");
extern unsigned char InFrontEnd __asm__("InFrontEnd");
extern int vu1_bufSize __asm__("vu1_bufSize");
struct gearUnk {
	/* 0x00 */ int unk00[3];
	/* 0x0c */ char *top;
};
extern gearUnk GearTop __asm__("D_0023AB00");
int PM_Malloc(unsigned int, void **) __asm__("PM_Malloc");


char *PmMemory __asm__("D_21ED90") GAME_GP_DATA = 0;
void SetPmMemory(char *) __asm__("SetPmMemory");


GAME_SECTION(PM_Malloc) int PM_Malloc(unsigned int size, void **pt1)
{
	char **p1 = (char **)pt1;
	if (size > 0x40000) {
		*p1 = 0;
		return -1;
	}
	if (g_gameType == 1 || InFrontEnd || !PmMemory) *p1 = GearTop.top + vu1_bufSize - size; else *p1 = PmMemory;
	return 0;
}

GAME_SECTION(SetPmMemory) void SetPmMemory(char *p)
{
	PmMemory = p;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/gearmenu", func_0045C6E0);
