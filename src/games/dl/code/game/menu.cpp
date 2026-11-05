#include "common.h"
#include "game_section.h"

void Gui_DrawRC1_Help_Decorator(float, float, float, float, int, int) __asm__("Gui_DrawRC1_Help_Decorator");


struct FontWindow {
	/* 0x00 */ short win_top;
	/* 0x02 */ short win_bot;
	/* 0x04 */ short win_left;
	/* 0x06 */ short win_right;
	/* 0x08 */ short text_x;
	/* 0x0a */ short text_y;
	/* 0x0c */ short max_width;
	/* 0x0e */ short max_height;
	/* 0x10 */ short line_spacing;
	/* 0x12 */ short flags;
	/* 0x14 */ short sub_pixel_x;
	/* 0x16 */ short sub_pixel_y;
	/* 0x18 */ short drop_shadow_offset_x;
	/* 0x1a */ short drop_shadow_offset_y;
};
void Gui_DrawDecoratedWindow(FontWindow &, int, char *, int, bool, int, bool, char *, char *, bool) __asm__("Gui_DrawDecoratedWindow");
int FontPrintWindow(FontWindow *, unsigned long, char *, int, float, float, unsigned long) __asm__("FUN_00455e78");
extern "C" int strlen(const char *);

GAME_SECTION(Gui_DrawRC1_Help_Decorator) void Gui_DrawRC1_Help_Decorator(float lowerY, float higherY, float lowerX, float higherX, int alpha, int rgb)
{
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/menu", Gui_DrawDecoratedWindow);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/menu", func_00469798);
