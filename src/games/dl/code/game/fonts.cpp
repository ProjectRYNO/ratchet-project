#include "common.h"
#include "game_section.h"


void FontEnableColors(int) __asm__("FontEnableColors");
extern unsigned char fontClampScale __asm__("D_21ECD8");
extern unsigned char fontColorsEnabled __asm__("D_21ECEE");
extern int fontLastFrame __asm__("D_21ECE0");
extern int gsFrame __asm__("gsFrame");
int FontStringLength(const char *, int, float) __asm__("FontStringLength");
int FontGetMaxHeight() __asm__("FontGetMaxHeight");
void FontLoadToGs() __asm__("FUN_00454060");
void FontClampScale(int) __asm__("FontClampScale");
int FontGetClampScale() __asm__("FontGetClampScale");
void FontForceInitialize() __asm__("FontForceInitialize");
int FontLen(const char *s, int len) __asm__("FontLen");
int FontLenScaled(const char *s, int len, float scale) __asm__("FontLenScaled");
int GetFontMaxHeight() __asm__("GetFontMaxHeight");
void LoadFontToGs() __asm__("LoadFontToGs");
void SetFontWindow(int a, int b, int c, int d, int e, int f, int g, int h, int i) __asm__("SetFontWindow");
void DisableFontColors() __asm__("DisableFontColors");
void EnableFontColors() __asm__("EnableFontColors");



typedef struct fontWindow {
	/* 0x00 */ short x;
	/* 0x02 */ short y;
	/* 0x04 */ short w;
	/* 0x06 */ short h;
	/* 0x08 */ short a;
	/* 0x0a */ short b;
	/* 0x0c */ short c;
	/* 0x0e */ short d;
	/* 0x10 */ short e;
	/* 0x12 */ short f;
	/* 0x14 */ short g;
	/* 0x16 */ short h2;
} fontWindow_t;
void FontSetWindowData(fontWindow_t *w, int a, int b, int c, int d, int e, int f, int g, int h) __asm__("FontSetWindow");
extern int *g_FontMetrics __asm__("g_FontMetrics");
int GetCharacterIndex(unsigned char *s, int pos, int *out) __asm__("GetCharacterIndex");
int FontGetCharacterCount() __asm__("FontGetCharacterCount");

struct FontWindow;
extern int g_CurrentFontName __asm__("g_CurrentFontName");
extern char *g_FontArray[4] __asm__("D_21DE98");
extern unsigned int *g_FontMetricsArray[4] __asm__("D_21DEA8");
extern char *g_FontKerningArray[4] __asm__("D_21DEB8");
void FontPrint(float, float, unsigned long, char *, int, float, float, int, bool, unsigned long, float, float) __asm__("FontPrint");
void FontSet(int) __asm__("FUN_00454350");
void FontPrintWindow(FontWindow *, unsigned long, char *, int, float, float, unsigned long) __asm__("FUN_00455e78");
void FontPrintWindowList(FontWindow *, unsigned long, char **, int, short, unsigned long, int &, int &, float) __asm__("FontPrintWindowList");
void FontPrintScaled(float, float, unsigned long, char *, int, float) __asm__("FontPrintScaled");
void FontPrintCenterScaledLarge(int, int, unsigned long, char *, int, float) __asm__("FontPrintCenterScaledLarge");
int FontPrintCenter(int, int, unsigned long, char *, int) __asm__("FontPrintCenter");
void FontPrintWindowSmall(FontWindow *, unsigned long, char *, int) __asm__("FontPrintWindowSmall");
void FontPrintWindowScaledGenericList(FontWindow *, unsigned long, char **, int, unsigned long, void *, short, unsigned long, int &, int &, float) __asm__("FontPrintWindowScaledGenericList");
void FontLoad(int, char *, char *) __asm__("FontLoad");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", FontLoad);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", FUN_00454060);

GAME_SECTION(GetCharacterIndex) int GetCharacterIndex(unsigned char *s, int pos, int *out)
{
	int wide = 0;
	int c;
	s += pos;
	c = *s;
	*out = c;
	if (c & 0x80) {
		wide = 1;
		*out = (((c & 0x7f) << 8) | s[1]) + 0x7f;
	}
	return wide;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", FUN_00454298);

GAME_SECTION(FontForceInitialize) void FontForceInitialize()
{
	fontLastFrame = gsFrame - 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", FUN_00454350);

GAME_SECTION(FontGetCharacterCount) int FontGetCharacterCount()
{
	int count = -1;
	if (g_FontMetrics) count = g_FontMetrics[-1];
	return count;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", FontGetMaxHeight);

GAME_SECTION(FontEnableColors) void FontEnableColors(int enable)
{
	fontColorsEnabled = enable;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", FontStringHeight);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", FontStringLength);

GAME_SECTION(FontGetClampScale) int FontGetClampScale()
{
	return fontClampScale;
}

GAME_SECTION(FontClampScale) void FontClampScale(int clamp)
{
	fontClampScale = clamp;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", FontPrint);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", FontPrint___dupe2);

GAME_SECTION(FontSetWindow) void FontSetWindowData(fontWindow_t *w, int a, int b, int c, int d, int e, int f, int g, int h)
{
	w->x = a;
	w->y = b;
	w->w = c;
	w->h = d;
	w->a = e;
	w->b = f;
	w->e = g;
	w->f = h;
	w->c = 0;
	w->d = 0;
	w->g = 0;
	w->h2 = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", FUN_00455e78);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", FontPrintWindowList);

GAME_SECTION(GetFontMaxHeight) int GetFontMaxHeight()
{
	return FontGetMaxHeight();
}

GAME_SECTION(EnableFontColors) void EnableFontColors()
{
	FontEnableColors(1);
}

GAME_SECTION(DisableFontColors) void DisableFontColors()
{
	FontEnableColors(0);
}

GAME_SECTION(FontLen) int FontLen(const char *s, int len)
{
	return FontStringLength(s, len, 1.0f);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", func_00457248);

GAME_SECTION(FontLenScaled) int FontLenScaled(const char *s, int len, float scale)
{
	return FontStringLength(s, len, scale);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", func_00457298);

GAME_SECTION(FontPrintCenter) int FontPrintCenter(int xpos, int ypos, unsigned long rgba, char *s, int len)
{
	FontPrint(xpos, ypos, rgba, s, len, 1.0f, 1.0f, 1, false, 0x80000000, 0.0f, 0.0f);
	return xpos - (FontStringLength(s, len, 1.0f) >> 1);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", FontPrintCenterSmall);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", func_00457468);

GAME_SECTION(FontPrintCenterScaledLarge) void FontPrintCenterScaledLarge(int xpos, int ypos, unsigned long rgba, char *s, int len, float scale)
{
	FontPrint(xpos, ypos, rgba, s, len, scale, scale, 1, false, 0x80000000, 0.0f, 0.0f);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", FontPrintRightSmall);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", FontPrintSmall);

GAME_SECTION(FontPrintScaled) void FontPrintScaled(float xpos, float ypos, unsigned long color, char *s, int len, float scale)
{
	FontPrint(xpos, ypos, color, s, len, scale, scale, 0, false, 0x80000000, 0.0f, 0.0f);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", func_00457680);

GAME_SECTION(SetFontWindow) void SetFontWindow(int a, int b, int c, int d, int e, int f, int g, int h, int i)
{
	FontSetWindowData((fontWindow_t *)a, b, c, d, e, f, g, h, i);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", func_004576C0);

GAME_SECTION(FontPrintWindowSmall) void FontPrintWindowSmall(FontWindow *window, unsigned long rgba, char *s, int len)
{
	int font_name = g_CurrentFontName;
	FontSet(0);
	FontPrintWindow(window, rgba, s, len, 1.0f, 1.0f, 0x80000000);
	FontSet(font_name);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", func_00457770);

GAME_SECTION(FontPrintWindowScaledGenericList) void FontPrintWindowScaledGenericList(FontWindow *window, unsigned long rgba, char **ps, int sCnt, unsigned long tex0, void *font_table, short selectedIdx, unsigned long selectedRgba, int &selectedLineX, int &selectedLineY, float user_font_scale)
{
	FontPrintWindowList(window, rgba, ps, sCnt, selectedIdx, selectedRgba, selectedLineX, selectedLineY, user_font_scale);
}

GAME_SECTION(LoadFontToGs) void LoadFontToGs()
{
	FontLoadToGs();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", func_004577D0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", FontGetUnicodeCharacter);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", func_00457A28);
