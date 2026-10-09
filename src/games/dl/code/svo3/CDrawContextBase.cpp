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
extern char svoDrawDownloading[] __attribute__((aligned(8)));
extern char svoDrawDot[];
extern char svoDrawTwoDots[];
extern char svoDrawThreeDots[];
extern char svoDrawThrobberClass[];
extern char svoDrawImageLineClass[];
extern char svoDrawImageText[] __attribute__((aligned(8)));
extern char svoDrawImageTextClass[];
extern char svoDrawStaticImageFormat[];
#define SECTION(name) __attribute__((section(".svo_CDrawContextBase_" #name)))

SECTION(RenderAssert) long RenderAssert(void *self, void *context)
{
    return 0;
}

SECTION(TransitionPageOff) long TransitionPageOff(void *self)
{
    return 1;
}

SECTION(TransitionPageOn) long TransitionPageOn(void *self)
{
    return 1;
}

SECTION(TransitionPopupPageOff) long TransitionPopupPageOff(void *self)
{
    return 1;
}

SECTION(TransitionPopupPageOn) long TransitionPopupPageOn(void *self)
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
    ++svoDrawThrobberCount;
    memcpy(text, svoDrawDownloading, 12);
    if (svoDrawThrobberCount > 15 && svoDrawThrobberCount < 30) strcat(text, svoDrawDot);
    else if (svoDrawThrobberCount > 30 && svoDrawThrobberCount < 45) strcat(text, svoDrawTwoDots);
    else if (svoDrawThrobberCount > 45 && svoDrawThrobberCount < 60) strcat(text, svoDrawThreeDots);
    else if (svoDrawThrobberCount > 60) svoDrawThrobberCount = 0;
    draw->vtable->DrawRectangle(draw, id, x, y, width, height, 0xFF000000, 0xFF0000FF, 2, 0, 1000000.0f, 0, svoDrawThrobberClass);
    draw->vtable->SVDrawText(draw, id, x + 5.0f, y + 5.0f, 0xFFBBBBBB, text, 14, 12, 0, svoDrawThrobberClass);
}

extern "C" SECTION(DrawGenericListboxFrame) void DrawGenericListboxFrame(CDrawContextBase *draw, unsigned int id, float x, float y, float width, float height, unsigned int lineColor, unsigned int fillColor, int maxVisibleItems, float scrollBarPercentage, char *tagClass)
{
    draw->vtable->DrawRectangle(draw, id, x, y, width, height, lineColor, fillColor, 1, 0, 100000.0f, 0, 0);
}

extern "C" SECTION(DrawGridBorder) void DrawGridBorder(CDrawContextBase *draw, unsigned int id, float x, float y, float z, float width, float height, unsigned int lineColor, unsigned int fillColor, char *tagClass)
{
    draw->vtable->DrawRectangle(draw, id, x, y, width, height, lineColor, fillColor, 1, 0, z, 0, tagClass);
}

extern "C" SECTION(DrawGridCell) void DrawGridCell(CDrawContextBase *draw, unsigned int id, float x, float y, float z, float width, float height, unsigned int lineColor, unsigned int fillColor, unsigned int textColor, int selected, char *text, int textLen, int fontSize, int alignment, char *tagClass)
{
    draw->vtable->DrawButton(draw, id, x, y, z, width, height, lineColor, fillColor, textColor, selected, text, textLen, fontSize, alignment, tagClass, 1);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", DrawGridHeader);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", DrawGridScrollbars);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", DrawImage);

extern "C" SECTION(DrawInputBox) void DrawInputBox(CDrawContextBase *draw, unsigned int id, float x, float y, float z, float width, float height, unsigned int lineColor, unsigned int fillColor, unsigned int textColor, int selected, char *text, int textLen, int fontSize, char *tagClass)
{
    draw->vtable->SVDrawText(draw, id, x, y, textColor, text, textLen, fontSize, 0, tagClass);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", DrawListBox);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", DrawPopupBackground);

extern "C" SECTION(DrawSelect) void DrawSelect(CDrawContextBase *draw, unsigned int id, float x, float y, float z, float width, float height, unsigned int textColor, unsigned int lineColor, unsigned int fillColor, int selected, char *text, int textLen, int fontSize, int alignment, char *tagClass)
{
    draw->vtable->SVDrawText(draw, id, x, y, textColor, text, strlen(text), fontSize, alignment, tagClass);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", DrawStaticImage);

extern "C" SECTION(DrawTextArea) void DrawTextArea(CDrawContextBase *draw, unsigned int id, float x, float y, float z, float width, float height, unsigned int lineColor, unsigned int fillColor, unsigned int textColor, int selected, float scrollbarWidth, float scrollbarHeight, float scrollBarPercentage, char *tagClass, int canScrollUp, int canScrollDown)
{
    draw->vtable->DrawRectangle(draw, id, x, y, width, height, lineColor, fillColor, 1, 0, 100000.0f, 0, 0);
}

extern "C" SECTION(drawTicker) void drawTicker(CDrawContextBase *draw, unsigned int id, float x, float y, float width, float height, int fontSize, char *text, int textLen, unsigned int textColor, int type, char *tagClass)
{
    char buffer[51];
    memset(buffer, 0, sizeof(buffer));
    if (textLen < 51) strncpy(buffer, text, textLen + 1);
    else {
        memcpy(buffer, text, 50);
        textLen = 50;
        // Retail modifies the source, then renders it rather than the local copy.
        text[50] = 0;
    }
    draw->vtable->SVDrawText(draw, id, x, y, textColor, text, textLen, fontSize, 0, tagClass);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CDrawContextBase", TrimToFitDisplaySize);
