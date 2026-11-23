#include "common.h"
#include "game_section.h"
#include "fonts.h"

void Gui_DrawRC1_Help_Decorator(float, float, float, float, int, int) __asm__("Gui_DrawRC1_Help_Decorator");


void Gui_DrawDecoratedWindow(FontWindow &, int, char *, int, bool, int, bool, char *, char *, bool) __asm__("Gui_DrawDecoratedWindow");
int FontPrintWindow(FontWindow *, unsigned long, char *, int, float, float, unsigned long) __asm__("FUN_00455e78");
extern "C" int strlen(const char *);

GAME_SECTION(Gui_DrawRC1_Help_Decorator) void Gui_DrawRC1_Help_Decorator(float lowerY, float higherY, float lowerX, float higherX, int alpha, int rgb)
{
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/menu", Gui_DrawDecoratedWindow);

JUNK_ASM(func_00469798,
	"\tsw $2, 0x0($28)\n"
	"\tnop\n"
	"\taddiu $29, $29, 0xf0\n"
	"\tnop\n");
