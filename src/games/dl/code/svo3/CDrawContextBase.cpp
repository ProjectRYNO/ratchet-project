#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_CDrawContextBase_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "CDrawContextBase.h"
#include "UTF8_Util.h"
#include <string.h>
#include <stdio.h>

extern "C" {



extern unsigned int svoDrawThrobberCount;
extern const char svoDrawDownloading[] __attribute__((aligned(8)));
extern char svoDrawDot[];
extern char svoDrawTwoDots[];
extern char svoDrawThreeDots[];
extern char svoDrawThrobberClass[];
extern char svoDrawImageLineClass[];
extern char svoDrawImageText[];
extern char svoDrawImageTextClass[];
extern char svoDrawStaticImageFormat[];
#define SECTION(name) __attribute__((section(".svo_CDrawContextBase_" #name)))

SECTION(RenderAssert) int RenderAssert(void *self, void *context)
{
    return 0;
}

SECTION(TransitionPageOff) int TransitionPageOff(void *self)
{
    return 1;
}

SECTION(TransitionPageOn) int TransitionPageOn(void *self)
{
    return 1;
}

SECTION(TransitionPopupPageOff) int TransitionPopupPageOff(void *self)
{
    return 1;
}

SECTION(TransitionPopupPageOn) int TransitionPopupPageOn(void *self)
{
    return 1;
}

SECTION(DrawVKB) void DrawVKB(CDrawContextBase *draw)
{
    // Retail has no default virtual keyboard renderer.
}

}

extern "C" SECTION(DrawButton) void DrawButton(CDrawContextBase *draw, unsigned int id, float x, float y, float z, float width, float height, unsigned int lineColor, unsigned int fillColor, unsigned int textColor, int selected, char *text, int textLen, int fontSize, int alignment, char *tagClass, int border)
{
    draw->vtable->SVDrawText(draw, id, x, y, textColor, text, textLen, fontSize, alignment, tagClass);
}

extern "C" SECTION(DrawDownloadThrobber) void DrawDownloadThrobber(CDrawContextBase *draw, unsigned int id, float x, float y, float width, float height, char *tagClass)
{
    char text[32] __attribute__((aligned(8)));
    unsigned int lo = 15, mid = 30, hi = 45, top = 60;
    ++svoDrawThrobberCount;
    memcpy(text, svoDrawDownloading, 12);
    if (svoDrawThrobberCount > lo && svoDrawThrobberCount < mid) strcat(text, svoDrawDot);
    else if (svoDrawThrobberCount > mid && svoDrawThrobberCount < hi) strcat(text, svoDrawTwoDots);
    else if (svoDrawThrobberCount > hi && svoDrawThrobberCount < top) strcat(text, svoDrawThreeDots);
    else if (svoDrawThrobberCount > top) svoDrawThrobberCount = 0;
    draw->vtable->DrawRectangle(draw, id, x, y, width, height, 0xFF000000, 0xFF0000FF, 2, 0, 0, 1000000.0f, svoDrawThrobberClass);
    draw->vtable->SVDrawText(draw, id, x + 5.0f, y + 5.0f, 0xFFBBBBBB, text, 14, 12, 0, svoDrawThrobberClass);
}

extern "C" SECTION(DrawGenericListboxFrame) void DrawGenericListboxFrame(CDrawContextBase *draw, unsigned int id, float x, float y, float width, float height, unsigned int lineColor, unsigned int fillColor, int maxVisibleItems, float scrollBarPercentage, char *tagClass)
{
    draw->vtable->DrawRectangle(draw, id, x, y, width, height, lineColor, fillColor, 1, 0, 0, 100000.0f, 0);
}

extern "C" SECTION(DrawGridBorder) void DrawGridBorder(CDrawContextBase *draw, unsigned int id, float x, float y, float z, float width, float height, unsigned int lineColor, unsigned int fillColor, char *tagClass)
{
    draw->vtable->DrawRectangle(draw, id, x, y, width, height, lineColor, fillColor, 1, 0, 0, z, tagClass);
}

extern "C" SECTION(DrawGridCell) void DrawGridCell(CDrawContextBase *draw, unsigned int id, float x, float y, float z, float width, float height, unsigned int lineColor, unsigned int fillColor, unsigned int textColor, int selected, char *text, int textLen, int fontSize, int alignment, char *tagClass)
{
    draw->vtable->DrawButton(draw, id, x, y, z, width, height, lineColor, fillColor, textColor, selected, text, textLen, fontSize, alignment, tagClass, 1);
}

extern "C" SECTION(DrawGridHeader) void DrawGridHeader(CDrawContextBase *draw, unsigned int id, float x, float y, float z, float width, float height, unsigned int lineColor, unsigned int fillColor, char *tagClass, int selected, int selectedCol, float selectedX, float selectedWidth)
{
    float h = height - 1.0f;
    draw->vtable->DrawRectangle(draw, id, x, y, width, h, lineColor, fillColor, 1, 0, 0, 100000.0f, 0);
    if (selected) draw->vtable->DrawRectangle(draw, id, selectedX, y, selectedWidth, h, fillColor, lineColor, 1, 0, 0, z + 1.0f, 0);
}

extern "C" SECTION(DrawGridScrollbars) void DrawGridScrollbars(CDrawContextBase *draw, unsigned int id, float x, float y, float z, float width, float height, float vw, float vh, float vp, float vs, float hw, float hh, float hp, float hs, char *tagClass)
{
    float right = x + width + 1.0f;
    if (vp >= 0.0f) {
        draw->vtable->DrawRectangle(draw, id, right, y, vw, vh, 0xFF0000FF, 0xFFFFFFFF, 1, 0, 0, 100000.0f, 0);
        unsigned int up = 0xFF7F7F7F;
        unsigned int down = 0xFF7F7F7F;
        if (vs < 1.0f) {
            if (vp > 0.0f) up = 0xFFFF0000;
            if (vp + vs < 0.98999995f) down = 0xFFFF0000;
        }
        draw->vtable->DrawRectangle(draw, id, right, y, vw, vw, 0xFFFFFFFF, up, 1, 0, 0, 100000.0f, 0);
        float by = y + vh - vw;
        draw->vtable->DrawRectangle(draw, id, right, by, vw, vw, 0xFFFFFFFF, down, 1, 0, 0, 100000.0f, 0);
    }
    float bottom = y + height + 1.0f;
    if (hp >= 0.0f) {
        draw->vtable->DrawRectangle(draw, id, x, bottom, hw, hh, 0xFF0000FF, 0xFFFFFFFF, 1, 0, 0, 100000.0f, 0);
        unsigned int left = 0xFF7F7F7F;
        unsigned int rightColor = 0xFF7F7F7F;
        if (hs < 1.0f) {
            if (hp > 0.0f) left = 0xFFFF0000;
            if (hp + hs < 0.98999995f) rightColor = 0xFFFF0000;
        }
        draw->vtable->DrawRectangle(draw, id, x, bottom, hh, hh, 0xFFFFFFFF, left, 1, 0, 0, 100000.0f, 0);
        float bx = x + hw - hh;
        draw->vtable->DrawRectangle(draw, id, bx, bottom, hh, hh, 0xFFFFFFFF, rightColor, 1, 0, 0, 100000.0f, 0);
    }
}

extern "C" SECTION(DrawImage) void DrawImage(CDrawContextBase *draw, unsigned int id, char *buffer, int x, int y, int w, int h, float u0, float v0, int selected, unsigned int alpha)
{
    float fx = (float)x;
    float fy = (float)y;
    float fw = (float)w;
    float fh = (float)h;
    float depth = 100000.0f;
    draw->vtable->DrawRectangle(draw, id, fx, fy, fw, fh, 0xFFFFFF00, 0xFF000000, 1, 0, 0, depth, 0);
    draw->vtable->DrawLine(draw, id, fx, fy, fx + fw, fy + fh, depth, 2.0f, 0xFFFFFF00, svoDrawImageLineClass);
    char text[24];
    memcpy(text, svoDrawImageText, 24);
    draw->vtable->SVDrawText(draw, id, fx + (float)(w / 2), fy + (float)(h / 2), 0xFFFFFFFF, text, strlen(text), 12, 1, svoDrawImageTextClass);
}

extern "C" SECTION(DrawInputBox) void DrawInputBox(CDrawContextBase *draw, unsigned int id, float x, float y, float z, float width, float height, unsigned int lineColor, unsigned int fillColor, unsigned int textColor, int selected, char *text, int textLen, int fontSize, char *tagClass)
{
    draw->vtable->SVDrawText(draw, id, x, y, textColor, text, textLen, fontSize, 0, tagClass);
}

extern "C" SECTION(DrawListBox) void DrawListBox(CDrawContextBase *draw, unsigned int id, float x, float y, float z, float width, float height, unsigned int lineColor, unsigned int fillColor, int selected, float percent, float sizePercent, char *tagClass)
{
    float sb_width = 15.0f;
    unsigned int up_box_color;
    unsigned int down_box_color;
    draw->vtable->DrawRectangle(draw, 0, x, y, width, height, lineColor, fillColor, 2, 0, 0, 100000.0f, 0);
    draw->vtable->DrawLine(draw, 0, x, y, x + width, y + height, 10000.0f, 2.0f, lineColor, tagClass);
    draw->vtable->DrawRectangle(draw, 0, x + width, y, sb_width, height, lineColor, fillColor, 2, 0, 0, 100000.0f, 0);
    up_box_color = 0xFF7F7F7F;
    down_box_color = 0xFF7F7F7F;
    if (sizePercent < 1.0f) {
        if (percent > 0.0f) up_box_color = 0xFFFF0000;
        if (percent + sizePercent < 0.98999995f) down_box_color = 0xFFFF0000;
    }
    draw->vtable->DrawRectangle(draw, id, x + width, y, sb_width, sb_width, 0xFFFFFFFF, up_box_color, 1, 0, 0, 100000.0f, 0);
    draw->vtable->DrawRectangle(draw, id, x + width, y + height - sb_width, sb_width, sb_width, 0xFFFFFFFF, down_box_color, 1, 0, 0, 100000.0f, 0);
}

extern "C" SECTION(DrawPopupBackground) void DrawPopupBackground(CDrawContextBase *draw, float x, float y, float width, float height, unsigned int lineColor, unsigned int fillColor, char *tagClass)
{
    draw->vtable->DrawRectangle(draw, 0, x, y, width, height, lineColor, fillColor, 1, 0, 0, 200000.0f, 0);
}

extern "C" SECTION(DrawSelect) void DrawSelect(CDrawContextBase *draw, unsigned int id, float x, float y, float z, float width, float height, unsigned int textColor, unsigned int lineColor, unsigned int fillColor, int selected, char *text, int textLen, int fontSize, int alignment, char *tagClass)
{
    draw->vtable->SVDrawText(draw, id, x, y, textColor, text, strlen(text), fontSize, alignment, tagClass);
}

extern "C" SECTION(DrawStaticImage) void DrawStaticImage(CDrawContextBase *draw, unsigned int id, char *imageName, int index, int x, int y, int w, int h, float u0, float v0, int selected, unsigned int alpha)
{
    float fx = (float)x;
    float fy = (float)y;
    float fw = (float)w;
    float fh = (float)h;
    draw->vtable->DrawRectangle(draw, id, fx, fy, fw, fh, 0xFFFFFF00, 0xFF000000, 1, 0, 0, 100000.0f, 0);
    draw->vtable->DrawLine(draw, id, fx, fy, fx + fw, fy + fh, 100000.0f, 2.0f, 0xFFFFFF00, svoDrawImageLineClass);
    char text[64];
    memset(text, 0, sizeof(text));
    sprintf(text, svoDrawStaticImageFormat, index, imageName);
    draw->vtable->SVDrawText(draw, id, fx + (float)(w / 2), fy + (float)(h / 2), 0xFFFFFFFF, text, strlen(text), 12, 1, svoDrawImageTextClass);
}

extern "C" SECTION(DrawTextArea) void DrawTextArea(CDrawContextBase *draw, unsigned int id, float x, float y, float z, float width, float height, unsigned int lineColor, unsigned int fillColor, unsigned int textColor, int selected, float scrollbarWidth, float scrollbarHeight, float scrollBarPercentage, char *tagClass, int canScrollUp, int canScrollDown)
{
    draw->vtable->DrawRectangle(draw, id, x, y, width, height, lineColor, fillColor, 1, 0, 0, 100000.0f, 0);
}

extern "C" SECTION(drawTicker) void drawTicker(CDrawContextBase *draw, unsigned int id, float x, float y, float width, float height, int fontSize, char *text, int textLen, unsigned int textColor, int type, char *tagClass)
{
    char buffer[51];
    memset(buffer, 0, sizeof(buffer));
    if (textLen > 50) {
        memcpy(buffer, text, 50);
        textLen = 50;
        // Retail modifies the source, then renders it rather than the local copy.
        text[50] = 0;
    } else {
        strncpy(buffer, text, textLen + 1);
    }
    draw->vtable->SVDrawText(draw, id, x, y, textColor, text, textLen, fontSize, 0, tagClass);
}

extern "C" SECTION(TrimToFitDisplaySize) int TrimToFitDisplaySize(CDrawContextBase *draw, char *text, float length, int fontSize)
{
    return UTF8_TrimStringToFitLength(text, length, fontSize, draw);
}
