#include "common.h"
#include "game_section.h"


void FontEnableColors(int) __asm__("FontEnableColors");
extern unsigned char fontColorsEnabled __asm__("D_21ECEE");
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

void FontPrintRightSmall(int, int, unsigned long, char *, int) __asm__("FontPrintRightSmall");
void FontPrintSmall(int, int, unsigned long, char *, int) __asm__("FontPrintSmall");
int FontPrintCenterSmall(int, int, unsigned long, char *, int) __asm__("FontPrintCenterSmall");
extern int Level __asm__("Level");
extern unsigned char InFrontEnd __asm__("InFrontEnd");
extern char *g_Font __asm__("g_Font");
extern char *g_FontKerning __asm__("D_21DE90");
extern char g_FontTableA[4][0x40] __asm__("D_3D7BC0");
extern char g_FontTableB[4][0x40] __asm__("D_3D7C80");
char *g_FontTableAPtr __asm__("D_21ECE4") GAME_GP_DATA = 0;
char *g_FontTableBPtr __asm__("D_21ECE8") GAME_GP_DATA = 0;

/* ===== AL additions ===== */
struct alFontMetric {
	/* 0x00 */ unsigned int w0;
	/* 0x04 */ unsigned int lo : 9;
	unsigned int height2 : 8;
	unsigned int height : 6;
	unsigned int hi : 9;
};
int FontStringHeight(char *s, int length, float scale) __asm__("FontStringHeight");

unsigned char fontClampScale __asm__("D_21ECD8") GAME_GP_DATA = 0;
int fontLastFrame __asm__("D_21ECE0") GAME_GP_DATA = 0;
int g_FontForceReload __asm__("g_FontForceReload") GAME_GP_DATA = 0;
int LoadPalToGs(void *, int) __asm__("LoadPalToGs");
int LoadTexToGs(void *, int, int, int) __asm__("LoadTexToGs");
struct alFontHeader {
	/* 0x00 */ unsigned char palCount;
	/* 0x01 */ unsigned char texCount;
	/* 0x02 */ char unk02[0x2e];
	/* 0x30 */ unsigned char palFormat[0x10];
	/* 0x40 */ unsigned char texFormat[0x10];
	/* 0x50 */ short texSize[0x10][2];
	/* 0x90 */ int palOffset[0x10];
	/* 0xd0 */ int texOffset[0x10];
};
short FontGetUnicodeCharacter(unsigned char *, int *) __asm__("FontGetUnicodeCharacter");
struct alFontMetric2 {
	/* 0x00 */ unsigned int index : 4;
	unsigned int kern : 12;
	unsigned int u : 9;
	unsigned int pre : 7;
	/* 0x04 */ unsigned int v : 9;
	unsigned int drop : 8;
	unsigned int h : 6;
	unsigned int w : 6;
	unsigned int post : 3;
};
struct alFontKerning {
	/* 0x00 */ short second;
	/* 0x02 */ signed char kern;
	/* 0x03 */ unsigned char end;
};

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

int FontGetMaxHeight(float &, float &, bool) __asm__("FontGetMaxHeight");

GAME_SECTION(FontGetMaxHeight) int FontGetMaxHeight(float &max_font_height, float &max_height_char_drop, bool capital_a_only)
{
	bool result;
	int count;
	unsigned int max_height;
	int i;

	max_font_height = 0.0f;
	max_height_char_drop = 0.0f;
	result = false;
	if (g_FontMetrics != 0) {
		if (capital_a_only) {
			max_font_height = (float)((alFontMetric *)g_FontMetrics)[0x41].height;
			max_height_char_drop = (float)((alFontMetric *)g_FontMetrics)[0x41].height2 * 0.25f;
			result = true;
		} else {
			count = FontGetCharacterCount();
			max_height = 0;
			if (count > 0) {
				for (i = 0; i < count; i++) {
					if (max_height < ((alFontMetric *)g_FontMetrics)[i].height) {
						max_height = ((alFontMetric *)g_FontMetrics)[i].height;
						max_height_char_drop = (float)((alFontMetric *)g_FontMetrics)[i].height2 * 0.25f;
					}
				}
				max_font_height = (float)max_height;
				result = true;
			}
		}
	}
	return result;
}

GAME_SECTION(FontEnableColors) void FontEnableColors(int enable)
{
	fontColorsEnabled = enable;
}

GAME_SECTION(FontStringHeight) int FontStringHeight(char *s, int length, float scale)
{
	int character_index;
	bool search;
	float height;
	float max_height;
	int i;

	search = true;
	max_height = 0.0f;
	character_index = 0;
	for (i = 0; search && i != length; i++) {
		{
			if (((unsigned char *)s)[i] == 0) {
				search = false;
			} else {
				i += GetCharacterIndex((unsigned char *)s, i, &character_index);
				height = (float)((alFontMetric *)g_FontMetrics)[character_index].height * scale +
					(float)((alFontMetric *)g_FontMetrics)[character_index].height2 * scale * 0.25f;
				if (max_height < height) {
					max_height = height;
				}
			}
		}
	}
	return (int)max_height;
}

GAME_SECTION(FontStringLength) int FontStringLength(const char *s, int length, float scale)
{
	int character_index;
	int next_index;
	bool search;
	float kern;
	float end;
	float metrics_scale;
	int i;
	alFontMetric2 *metric;
	float pre;
	float ofs;
	int next;
	int last;
	float font_width;
	float pre2;
	float post;
	float start;

	search = true;
	metrics_scale = scale * 0.25f;
	character_index = 0;
	kern = 0.0f;
	next_index = 0;
	if (fontClampScale) {
		scale = (float)(int)(scale * 10.0f + 0.5f) / 10.0f;
	}
	end = kern;
	GetCharacterIndex((unsigned char *)s, 0, &character_index);
	i = 0;
	pre = (float)-(int)((alFontMetric2 *)g_FontMetrics)[character_index].pre * metrics_scale;
	if (length != 0) {
	last = length - 1;
	do {
		if (((unsigned char *)s)[i] == 0) {
			next = i + 1;
			search = false;
		} else {
			i += GetCharacterIndex((unsigned char *)s, i, &character_index);
			metric = &((alFontMetric2 *)g_FontMetrics)[character_index];
			font_width = (float)metric->w * scale;
			pre2 = (float)((int)(metric->pre + 2) & 0xfc) * metrics_scale;
			post = (float)((metric->post + 2) & 0xfc);
			next = i + 1;
			end += font_width - pre2;
			ofs = (kern + post) * metrics_scale;
			if (i != last) {
				GetCharacterIndex((unsigned char *)s, next, &next_index);
				if (next_index >= 0x10) {
					if (metric->kern != 0) {
						alFontKerning *kerning = (alFontKerning *)(g_FontKerning + metric->kern * 4);
						int k = 0;
						start = end + ofs;
						if (kerning) {
							alFontKerning *kerning2 = kerning;
							bool keep_searching = true;
							while (keep_searching) {
								if (kerning2->second == next_index) {
									k = kerning2->kern;
									keep_searching = false;
								}
								if (kerning2->end) {
									keep_searching = false;
								} else {
									kerning2++;
								}
							}
						}
						kern = k;
					} else {
						start = end + ofs;
						kern = 0.0f;
					}
					end = start;
				}
			}
		}
		i = next;
	} while (search && i != length);
	}
	return (int)(end - pre);
}

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

GAME_SECTION(FontPrintCenterSmall) int FontPrintCenterSmall(int xpos, int ypos, unsigned long rgba, char *s, int len)
{
	int font_name = g_CurrentFontName;
	int return_val;
	FontSet(0);
	FontPrint(xpos, ypos, rgba, s, len, 1.0f, 1.0f, 1, false, 0x80000000, 0.0f, 0.0f);
	return_val = xpos - (FontStringLength(s, len, 1.0f) >> 1);
	FontSet(font_name);
	return return_val;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/fonts", func_00457468);

GAME_SECTION(FontPrintCenterScaledLarge) void FontPrintCenterScaledLarge(int xpos, int ypos, unsigned long rgba, char *s, int len, float scale)
{
	FontPrint(xpos, ypos, rgba, s, len, scale, scale, 1, false, 0x80000000, 0.0f, 0.0f);
}

GAME_SECTION(FontPrintRightSmall) void FontPrintRightSmall(int xpos, int ypos, unsigned long rgba, char *s, int len)
{
	int font_name = g_CurrentFontName;
	FontSet(0);
	FontPrint(xpos, ypos, rgba, s, len, 1.0f, 1.0f, 2, false, 0x80000000, 0.0f, 0.0f);
	FontSet(font_name);
}

GAME_SECTION(FontPrintSmall) void FontPrintSmall(int xpos, int ypos, unsigned long rgba, char *s, int len)
{
	int font_name = g_CurrentFontName;
	FontSet(0);
	FontPrint(xpos, ypos, rgba, s, len, 1.0f, 1.0f, 0, false, 0x80000000, 0.0f, 0.0f);
	FontSet(font_name);
}

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
