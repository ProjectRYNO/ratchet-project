#include "CPage.h"
#include "SVBrowser.h"
#include "TextEditableTag.h"
#include "CDrawContextBase.h"
#include "UTF8_Util.h"
#include "SVOString.h"
#include "string.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_TextInputTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "TextInputTag.h"

extern "C" {
void DrawImpl(TextInputTagState *tag, char *text);

extern "C" {
SVTagModuleState *getInstance___dupe17(void);
extern char svoTextInputTagFormNameAttribute[];
void AddTextElement(FormTag *form, TextInputTagState *tag);
extern char svoTextInputTagSource[];

}
extern "C" {
float getSubstringPixelWidthImpl(TextInputTagState *tag, char *text, int left, int right);
void setText(TextInputTagState *tag, char *text, unsigned int length);
}
extern "C" {
void resetTextInput(TextInputTagState *);
void InitialiseFromXml(TextInputTagState *, iks *, SVTag **, CAllContextData *);
extern char svoTextInputTagName[];
extern const SVTagVtablePrefix svoTextInputTagVtable;
}
extern "C" {

}
int Navigate(SVTag *, CInputContextBaseState *, CDrawContextBase *, iks *, CPage *);
void ShowVKB(SVBrowserPrefix *, SVTag *);
long GetVisible(SVTag *);
void drawCursor(TextInputTagState *, CDrawContextBase *, int);
void handleSpecialKeys___dupe2(TextInputTagState *, unsigned char);
void scrollTextLeftToFillWindow(TextInputTagState *);
void DumpSubstring(char *, float, int, int, char *);
extern unsigned int svoTextInputBlinkCount;
extern int svoTextInputJumpScroll;
extern char svoTextInputCursorGlyph[];
extern char svoTextInputJumpPart1[];
extern char svoTextInputJumpPart2[];
extern char svoTextInputSmoothScroll[];

void SignalPluginEvent(SVBrowserPrefix *, int, SVTag *);
void scrollTextRightToFillWindow(TextInputTagState *);
#define SECTION(name) __attribute__((section(".svo_TextInputTag_" #name)))

SECTION(FreeResources___dupe23) void FreeResources___dupe23(SVTag *tag)
{
    FreeContexts(tag);
}

SECTION(Draw___dupe17) void Draw___dupe17(TextInputTagState *tag)
{
    DrawImpl(tag, tag->m_text);
}

SECTION(GetMaxLengthUTF8Chars___dupe2) long GetMaxLengthUTF8Chars___dupe2(TextInputTagState *tag)
{
    return tag->m_maxLengthUTF8Chars;
}

SECTION(GetMaxLengthBytes___dupe2) long GetMaxLengthBytes___dupe2(TextInputTagState *tag)
{
    return 0x200;
}

}

extern "C" SECTION(defaultInit) void defaultInit(TextInputTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoTextInputTagName, 64);
    resetTextInput(tag);
    tag->m_numKeyboards = 0;
    tag->m_opacity = 1.0f;
    tag->m_fontSize = 14;
    tag->m_textColor = 0xFFFFFFFF;
    tag->m_highlightFillColor = 0xFF000000;
    tag->m_highlightTextColor = 0xFFFFFF00;
    tag->m_maxWrap = tag->base.m_width - 10.0f;
    tag->base.m_bSelectable = 1;
    tag->m_bRequiredForSubmit = 0;
    tag->m_upRightOffset = 0;
    tag->m_upLeftOffset = 0;
    tag->m_maxLengthUTF8Chars = 0;
    tag->m_node = -1;
    tag->m_obj = -1;
    tag->m_nx = 0;
    tag->m_ny = 0;
    tag->m_blinkCursor = 1;
    tag->m_drawCursor = 1;
    tag->base.m_fillColor = 0xFF000000;
    tag->base.m_lineColor = 0xFFFFFFFF;
    tag->m_highlightLineColor = 0xFFFFFF00;
    tag->base.m_isDefTextEntry = 0;
    tag->m_bEditable = 1;
    tag->m_bSubmitAsEncryped = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", drawCursor);

extern "C" SECTION(DrawImpl) void DrawImpl(TextInputTagState *self, char *text)
{
    SVTag *tag = &self->base;
    if (!GetVisible(tag)) return;
    CDrawContextBase *draw = tag->m_contexts->drawContext;
    if (!draw) __SVO_Assert_Handler(svoTextInputTagSource, 0x11E);
    if (!tag->m_xml) __SVO_Assert_Handler(svoTextInputTagSource, 0x11F);
    unsigned int fill;
    unsigned int line;
    unsigned int color;
    if (tag->vtable->IsSelected(tag)) {
        fill = self->m_highlightFillColor;
        line = self->m_highlightLineColor;
        color = self->m_highlightTextColor;
    } else {
        fill = tag->m_fillColor;
        line = tag->m_lineColor;
        color = self->m_textColor;
    }
    char visibleText[128];
    memset(visibleText, 0, sizeof(visibleText));
    memcpy(visibleText, text + self->m_curLeftOffset, (int)((unsigned int)self->m_curRightOffset - self->m_curLeftOffset));
    int length = strlen(visibleText);
    draw->vtable->DrawInputBox(draw, tag->m_tagid, tag->m_x, tag->m_y, tag->m_z, tag->m_width, tag->m_height, line, fill, color, tag->m_bSelected, visibleText, length, self->m_fontSize, tag->m_tagClass);
    if (tag->vtable->IsEditable(tag) && tag->m_bSelected) {
        if (!self->m_blinkCursor) drawCursor(self, draw, 1);
        else {
            if (svoTextInputBlinkCount % 30 == 0) self->m_drawCursor = !self->m_drawCursor;
            ++svoTextInputBlinkCount;
            drawCursor(self, draw, self->m_drawCursor);
        }
    }
}

extern "C" SECTION(DumpSubstring) void DumpSubstring(char *comment, float width, int left, int right, char *text)
{
    int length = (unsigned int)right - left;
    if ((unsigned long)(long)length < 128) {
        char buffer[128];
        memset(buffer, 0, 128);
        memcpy(buffer, text + left, length);
    }
}

extern "C" SECTION(findParentForm) FormTag *findParentForm(TextInputTagState *tag, iks *parent, SVTag **tagList)
{
    if (!parent) __SVO_Assert_Handler(svoTextInputTagSource, 0x311);
    if (!tagList) __SVO_Assert_Handler(svoTextInputTagSource, 0x312);
    SVTagModuleState *module = getInstance___dupe17();
    if (!module->vtable->IsMyTag(module, parent)) return 0;
    char *formName = iks_find_attrib(parent, svoTextInputTagFormNameAttribute);
    if (!formName) __SVO_Assert_Handler(svoTextInputTagSource, 0x31F);
    for (int i = 0; i < 256; ++i) {
        SVTag *candidate = tagList[i];
        if (candidate) {
            char *name = candidate->vtable->GetTagName(candidate);
            if (!name) __SVO_Assert_Handler(svoTextInputTagSource, 0x326);
            if (!strcmp(name, formName)) return (FormTag *)tagList[i];
        }
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", GetEditPosition___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", getSubstringPixelWidth);

extern "C" SECTION(getSubstringPixelWidthImpl) float getSubstringPixelWidthImpl(TextInputTagState *tag, char *text, int start, int end)
{
    CDrawContextBase *draw = tag->base.m_contexts->drawContext;
    int length = (unsigned int)end - start;
    if (length > 511) __SVO_Assert_Handler(svoTextInputTagSource, 0x202);
    char substring[512];
    memset(substring, 0, 512);
    strncpy(substring, text + start, length);
    return draw->vtable->GetStringWidth(draw, tag->m_fontSize, substring, strlen(substring));
}

extern "C" SECTION(GetText___dupe2) char *GetText___dupe2(TextInputTagState *tag)
{
    if ((int)strlen(tag->m_text) >= 512) __SVO_Assert_Handler(svoTextInputTagSource, 0x247);
    return tag->m_text;
}

extern "C" SECTION(HandleInput___dupe44) int HandleInput___dupe44(TextInputTagState *self, CPage *page)
{
    SVTag *tag = &self->base;
    CInputContextBaseState *input = tag->m_contexts->inputContext;
    if (!tag->m_xml) __SVO_Assert_Handler(svoTextInputTagSource, 0xE2);
    if (!input) __SVO_Assert_Handler(svoTextInputTagSource, 0xE3);
    if (!page) __SVO_Assert_Handler(svoTextInputTagSource, 0xE4);
    if (!tag->vtable->IsSelected(tag)) return 1;
    SVBrowserPrefix *browser = GetInstance();
    if (!browser->m_bShowVKB) {
        for (int action = 0; action < 4; ++action) {
            if (HasActionOccurred(input, 0x11, (PadAction)action)) {
                CDrawContextBase *draw = tag->m_contexts->drawContext;
                if (!draw) __SVO_Assert_Handler(svoTextInputTagSource, 0xF2);
                return Navigate(tag, input, draw, tag->m_xml, page) == 0;
            }
        }
        if (HasActionOccurred(input, 0x11, SV_ACTION_VKB_ACTIVATE) && tag->vtable->IsEditable(tag)) ShowVKB(browser, tag);
        if (tag->vtable->IsEditable(tag)) ((const TextEditableTagVtablePrefix *)tag->vtable)->HandleTextEntry(tag, input);
    } else if (tag->vtable->IsEditable(tag)) input->vtable->HandleVKBInput(input, tag);
    return 1;
}

extern "C" SECTION(handleKeyboardInput___dupe2) void handleKeyboardInput___dupe2(TextInputTagState *self, CInputContextBaseState *input)
{
    char *text = input->vtable->GetKeyboardBuffer(input);
    size_t length = strlen(text);
    size_t oldLength = strlen(self->m_text);
    if (input->specialKeyCode) {
        handleSpecialKeys___dupe2(self, input->specialKeyCode);
        return;
    }
    if ((long)length > 0 && *text && (unsigned int)(oldLength + strlen(text)) <= 512) {
        if (UTF8_CountCharacters(self->m_text, strlen(self->m_text)) < self->m_maxLengthUTF8Chars) {
            int previous = self->m_curEditOffset;
            self->m_curEditOffset = UTF8_AddCharToString(self->m_text, 512, text, strlen(text), self->m_curEditOffset);
            if (self->m_curRightOffset < self->m_curEditOffset) self->m_curRightOffset = self->m_curEditOffset;
            else self->m_curRightOffset = (unsigned int)self->m_curRightOffset + ((unsigned int)self->m_curEditOffset - previous);
            scrollTextLeftToFillWindow(self);
        }
    }
    input->vtable->ResetKeyboardInput(input);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", handleSpecialKeys___dupe2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", InitialiseFromXml);

extern "C" SECTION(registerWithForm) void registerWithForm(TextInputTagState *tag, iks *parent, SVTag **tagList)
{
    tag->m_parentForm = findParentForm(tag, parent, tagList);
    if (tag->m_parentForm) AddTextElement(tag->m_parentForm, tag);
}

extern "C" SECTION(resetTextInput) void resetTextInput(TextInputTagState *tag)
{
    memset(tag->m_text, 0, 512);
    memset(tag->m_keyboardInput, 0, 512);
    tag->m_curEditOffset = 0;
    tag->m_curRightOffset = 0;
    tag->m_curLeftOffset = 0;
}

extern "C" SECTION(scrollTextLeftToFillWindow) void scrollTextLeftToFillWindow(TextInputTagState *tag)
{
    while (((const TextInputTagVtablePrefix *)tag->base.vtable)->getSubstringPixelWidth(tag, tag->m_curLeftOffset, tag->m_curEditOffset) > tag->m_maxWrap) {
        tag->m_curLeftOffset = UTF8_GetNextCharIndexFromString(tag->m_text, tag->m_curLeftOffset);
        tag->m_curRightOffset = UTF8_GetNextCharIndexFromString(tag->m_text, tag->m_curRightOffset);
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", scrollTextRightToFillWindow);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextInputTag", setText);

extern "C" SECTION(SetText___dupe4) void SetText___dupe4(TextInputTagState *tag, char *text)
{
    if ((int)strlen(text) >= 512) __SVO_Assert_Handler(svoTextInputTagSource, 0x240);
    setText(tag, text, strlen(text));
}

extern "C" SECTION(TextInputTag) void TextInputTag(TextInputTagState *tag, iks *xml, SVTag **tags, CAllContextData *contexts, int subclass)
{
    SVTagConstruct(&tag->base, xml, contexts);
    tag->base.vtable = &svoTextInputTagVtable;
    if (!subclass) InitialiseFromXml(tag, xml, tags, contexts);
}
