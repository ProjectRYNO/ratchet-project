#include "TagUtils.h"
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
int GetVisible(SVTag *);
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
extern "C" {
extern char svoTextInputFillColorAttribute[];
extern char svoTextInputLineColorAttribute[];
extern char svoTextInputTextColorAttribute[];
extern char svoTextInputHighlightFillColorAttribute[];
extern char svoTextInputHighlightLineColorAttribute[];
extern char svoTextInputHighlightTextColorAttribute[];
extern char svoTextInputFontSizeAttribute[];
extern char svoTextInputClassAttribute[];
extern char svoTextInputMaxLengthAttribute[];
extern char svoTextInputValueAttribute[];
extern char svoTextInputOptionalAttribute[];
extern char svoTextInputYesValue[];
extern char svoTextInputBlinkCursorAttribute[];
extern char svoTextInputTrueValue[];
extern char svoTextInputReadOnlyAttribute[];
extern char svoTextInputEditableAttribute[];
extern char svoTextInputFalseValue[];
extern char svoTextInputSelectableAttribute[];
extern char svoTextInputDefaultTextEntryAttribute[];
extern char svoTextInputSubmitAsEncryptedAttribute[];
extern char svoTextInputRequiredForPostAttribute[];
}
#define SECTION(name) __attribute__((section(".svo_TextInputTag_" #name)))

SECTION(FreeResources___dupe23) void FreeResources___dupe23(SVTag *tag)
{
    FreeContexts(tag);
}

SECTION(Draw___dupe17) void Draw___dupe17(TextInputTagState *tag)
{
    DrawImpl(tag, tag->m_text);
}

SECTION(GetMaxLengthUTF8Chars___dupe2) int GetMaxLengthUTF8Chars___dupe2(TextInputTagState *tag)
{
    return tag->m_maxLengthUTF8Chars;
}

SECTION(GetMaxLengthBytes___dupe2) int GetMaxLengthBytes___dupe2(TextInputTagState *tag)
{
    return 0x200;
}

}

extern "C" SECTION(defaultInit) void defaultInit(TextInputTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoTextInputTagName, 64);
    resetTextInput(tag);
    tag->m_numKeyboards = 0;
    tag->m_bRequiredForSubmit = 0;
    tag->m_upRightOffset = 0;
    tag->m_upLeftOffset = 0;
    tag->m_fontSize = 14;
    tag->m_maxLengthUTF8Chars = 0;
    tag->m_node = -1;
    tag->m_obj = -1;
    tag->m_nx = 0;
    tag->m_ny = 0;
    tag->m_blinkCursor = 1;
    tag->m_drawCursor = 1;
    tag->base.m_fillColor = 0xFF000000;
    tag->base.m_lineColor = 0xFFFFFFFF;
    tag->m_textColor = 0xFFFFFFFF;
    tag->m_highlightFillColor = 0xFF000000;
    tag->m_highlightLineColor = 0xFFFFFF00;
    tag->m_highlightTextColor = 0xFFFFFF00;
    tag->m_maxWrap = tag->base.m_width - 10.0f;
    tag->base.m_isDefTextEntry = 0;
    tag->m_bEditable = 1;
    tag->base.m_bSelectable = 1;
    tag->m_bSubmitAsEncryped = 0;
    tag->m_opacity = 1.0f;
}

extern "C" SECTION(drawCursor) void drawCursor(TextInputTagState *self, CDrawContextBase *draw, int visible)
{
    if (!visible) return;
    SVTag *tag = &self->base;
    float x = tag->m_x + ((const TextInputTagVtablePrefix *)tag->vtable)->getSubstringPixelWidth(self, self->m_curLeftOffset, self->m_curEditOffset);
    int node = self->m_node;
    unsigned int color = tag->m_bSelected ? self->m_highlightTextColor : self->m_textColor;
    float y = tag->m_y;
    float height = tag->m_height;
    CDrawContextVtablePrefix *drawVtable = draw->vtable;
    float top;
    float bottom;
    float thickness;
    if (node == -1) {
        thickness = 3.0f;
        height -= 2.0f;
        top = y + 4.0f;
        bottom = y + height;
        x += 6.0f;
    } else {
        height -= 4.0f;
        top = y - height * 0.5f;
        bottom = top + height;
        thickness = drawVtable->GetStringWidth(draw, self->m_fontSize, svoTextInputCursorGlyph, 1) * 0.75f;
    }
    // Retail passes x again as the depth coordinate.
    draw->vtable->DrawLine(draw, tag->m_tagid, x, top, x, bottom, tag->m_x, thickness, color, 0);
}

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
        if (self->m_blinkCursor) {
            if (svoTextInputBlinkCount % 30 == 0) self->m_drawCursor = !self->m_drawCursor;
            ++svoTextInputBlinkCount;
            drawCursor(self, draw, self->m_drawCursor);
        } else drawCursor(self, draw, 1);
    }
}

extern "C" SECTION(DumpSubstring) void DumpSubstring(char *comment, float width, int left, int right, char *text)
{
    int length = (unsigned int)right - left;
    if ((unsigned int)(int)length < 128) {
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

extern "C" SECTION(GetEditPosition___dupe2) unsigned int GetEditPosition___dupe2(TextInputTagState *tag)
{
    return strlen(tag->m_text);
}

extern "C" SECTION(getSubstringPixelWidth) float getSubstringPixelWidth(TextInputTagState *tag, int left, int right)
{
    return getSubstringPixelWidthImpl(tag, tag->m_text, left, right);
}

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
        if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_UP) || HasActionOccurred(input, 0x11, SV_ACTION_NAV_DOWN)
            || HasActionOccurred(input, 0x11, SV_ACTION_NAV_LEFT) || HasActionOccurred(input, 0x11, SV_ACTION_NAV_RIGHT)) {
            CDrawContextBase *draw = tag->m_contexts->drawContext;
            if (!draw) __SVO_Assert_Handler(svoTextInputTagSource, 0xF2);
            return Navigate(tag, input, draw, tag->m_xml, page) == 0;
        }
        if (HasActionOccurred(input, 0x11, SV_ACTION_VKB_ACTIVATE) && tag->vtable->IsEditable(tag)) ShowVKB(browser, tag);
        if (tag->vtable->IsEditable(tag)) ((const TextEditableTagVtablePrefix *)tag->vtable)->HandleTextEntry(tag, input);
    } else if (tag->vtable->IsEditable(tag)) input->vtable->HandleVKBInput(input, tag);
    return 1;
}

extern "C" SECTION(handleKeyboardInput___dupe2) void handleKeyboardInput___dupe2(TextInputTagState *self, CInputContextBaseState *input)
{
    char *text = self->m_text;
    char *kbBuffer = input->vtable->GetKeyboardBuffer(input);
    int kbLength = strlen(kbBuffer);
    int textLength = strlen(text);
    unsigned char key = input->specialKeyCode;
    if (key) {
        handleSpecialKeys___dupe2(self, key);
        return;
    }
    if (kbLength > 0 && *kbBuffer && (unsigned int)(textLength + strlen(kbBuffer)) <= 512) {
        if (UTF8_CountCharacters(text, strlen(text)) < self->m_maxLengthUTF8Chars) {
            unsigned int prevEditOffset = self->m_curEditOffset;
            self->m_curEditOffset = UTF8_AddCharToString(text, 512, kbBuffer, strlen(kbBuffer), self->m_curEditOffset);
            if (self->m_curRightOffset < self->m_curEditOffset) self->m_curRightOffset = self->m_curEditOffset;
            else self->m_curRightOffset = self->m_curRightOffset + (self->m_curEditOffset - prevEditOffset);
            scrollTextLeftToFillWindow(self);
        }
    }
    input->vtable->ResetKeyboardInput(input);
}

extern "C" SECTION(handleSpecialKeys___dupe2) void handleSpecialKeys___dupe2(TextInputTagState *self, unsigned char key)
{
    size_t length = strlen(self->m_text);
    SVTag *tag = &self->base;
    CInputContextBaseState *input = tag->m_contexts->inputContext;
    CDrawContextBase *draw = tag->m_contexts->drawContext;
    CPage *page;
    float width;
    switch (key) {
    case 0x88:
        SignalPluginEvent(GetInstance(), 10, tag);
        self->m_curEditOffset = UTF8_RemoveCharFromStringDELETE(self->m_text, self->m_curEditOffset);
        page = GetInstance()->m_pMainPage;
        if (!page->m_bIsActive) page = GetInstance()->m_pPopupPage;
        if (!draw) __SVO_Assert_Handler(svoTextInputTagSource, 0x187);
        Navigate(tag, input, draw, tag->m_xml, page);
        break;
    case 0x89:
        self->m_curEditOffset = UTF8_RemoveCharFromStringBACKSPACE(self->m_text, self->m_curEditOffset);
        scrollTextRightToFillWindow(self);
        break;
    case 0x87:
        self->m_curEditOffset = UTF8_RemoveCharFromStringDELETE(self->m_text, self->m_curEditOffset);
        scrollTextLeftToFillWindow(self);
        break;
    case 0x83:
        self->m_curEditOffset = UTF8_GetPrevCharIndexFromString(self->m_text, self->m_curEditOffset);
        scrollTextRightToFillWindow(self);
        break;
    case 0x84:
        self->m_curEditOffset = UTF8_GetNextCharIndexFromString(self->m_text, self->m_curEditOffset);
        scrollTextLeftToFillWindow(self);
        break;
    case 0x81:
    case 0x82:
        page = GetInstance()->m_pMainPage;
        if (!page->m_bIsActive) page = GetInstance()->m_pPopupPage;
        if (!draw) __SVO_Assert_Handler(svoTextInputTagSource, 0x1C0);
        Navigate(tag, input, draw, tag->m_xml, page);
        break;
    case 0x86: {
        int end = strlen(self->m_text);
        self->m_curEditOffset = end;
        self->m_curLeftOffset = end;
        self->m_curRightOffset = end;
        do {
            --self->m_curLeftOffset;
            width = ((const TextInputTagVtablePrefix *)tag->vtable)->getSubstringPixelWidth(self, self->m_curLeftOffset, self->m_curEditOffset);
        } while (width < self->m_maxWrap && self->m_curLeftOffset > 0);
        while (width > self->m_maxWrap) {
            ++self->m_curLeftOffset;
            width = ((const TextInputTagVtablePrefix *)tag->vtable)->getSubstringPixelWidth(self, self->m_curLeftOffset, self->m_curRightOffset);
        }
        break;
    }
    case 0x85:
        self->m_curEditOffset = 0;
        self->m_curLeftOffset = 0;
        self->m_curRightOffset = 0;
        do {
            ++self->m_curRightOffset;
            width = ((const TextInputTagVtablePrefix *)tag->vtable)->getSubstringPixelWidth(self, 0, self->m_curRightOffset);
        } while (width < self->m_maxWrap && (int)self->m_curRightOffset < (int)length);
        while (width > self->m_maxWrap) {
            --self->m_curRightOffset;
            width = ((const TextInputTagVtablePrefix *)tag->vtable)->getSubstringPixelWidth(self, 0, self->m_curRightOffset);
        }
        break;
    }
    input->specialKeyCode = 0;
}

extern "C" SECTION(InitialiseFromXml) void InitialiseFromXml(TextInputTagState *tag, iks *xml, SVTag **tagList, CAllContextData *contexts)
{
    char optionalBuffer[16];
    char *optional = optionalBuffer;
    ((TextInputTagVtablePrefix *)tag->base.vtable)->defaultInit(tag, xml, tagList, contexts);
    getIntAttrib(tag->base.m_xml, svoTextInputMaxLengthAttribute, &tag->m_maxLengthUTF8Chars);
    if (tag->m_maxLengthUTF8Chars > 512) __SVO_Assert_Handler(svoTextInputTagSource, 0x5C);
    if (tag->m_maxLengthUTF8Chars < 1) {
        __SVO_Assert_Handler(svoTextInputTagSource, 0x60);
        tag->m_maxLengthUTF8Chars = 0;
    }
    getColorAttrib(tag->base.m_xml, svoTextInputFillColorAttribute, &tag->base.m_fillColor);
    getColorAttrib(tag->base.m_xml, svoTextInputLineColorAttribute, &tag->base.m_lineColor);
    getColorAttrib(tag->base.m_xml, svoTextInputTextColorAttribute, &tag->m_textColor);
    getColorAttrib(tag->base.m_xml, svoTextInputHighlightFillColorAttribute, &tag->m_highlightFillColor);
    getColorAttrib(tag->base.m_xml, svoTextInputHighlightLineColorAttribute, &tag->m_highlightLineColor);
    getColorAttrib(tag->base.m_xml, svoTextInputHighlightTextColorAttribute, &tag->m_highlightTextColor);
    getIntAttrib(tag->base.m_xml, svoTextInputFontSizeAttribute, &tag->m_fontSize);
    getStringAttrib(tag->base.m_xml, svoTextInputClassAttribute, &tag->base.m_tagClass);
    char *value = iks_find_attrib(tag->base.m_xml, svoTextInputValueAttribute);
    if (value) setText(tag, value, strlen(value));
    if (iks_find_attrib(tag->base.m_xml, svoTextInputOptionalAttribute)) {
        getStringAttrib(tag->base.m_xml, svoTextInputOptionalAttribute, &optional);
        if (!strncmp(optional, svoTextInputYesValue, 4)) tag->base.m_bOptional = 1;
    }
    char *blink = iks_find_attrib(tag->base.m_xml, svoTextInputBlinkCursorAttribute);
    if (blink) {
        if (!strcmp(blink, svoTextInputTrueValue)) tag->m_blinkCursor = 1;
        else tag->m_blinkCursor = 0;
    }
    char *readOnly = iks_find_attrib(xml, svoTextInputReadOnlyAttribute);
    char *editable = iks_find_attrib(xml, svoTextInputEditableAttribute);
    if (readOnly) {
        if (editable) __SVO_Assert_Handler(svoTextInputTagSource, 0x9E);
        if (!strcmp(readOnly, svoTextInputFalseValue)) {
            tag->m_bEditable = 1;
            tag->base.m_bSelectable = 1;
        } else tag->m_bEditable = 0;
    } else if (editable) {
        if (!strcmp(editable, svoTextInputTrueValue)) {
            tag->m_bEditable = 1;
            tag->base.m_bSelectable = 1;
        } else tag->m_bEditable = 0;
    }
    getBoolAttrib(tag->base.m_xml, svoTextInputSelectableAttribute, &tag->base.m_bSelectable);
    getBoolAttrib(tag->base.m_xml, svoTextInputDefaultTextEntryAttribute, &tag->base.m_isDefTextEntry);
    if (!getBoolAttrib(tag->base.m_xml, svoTextInputSubmitAsEncryptedAttribute, &tag->m_bSubmitAsEncryped)) tag->m_bSubmitAsEncryped = 0;
    if (!getBoolAttrib(tag->base.m_xml, svoTextInputRequiredForPostAttribute, &tag->m_bRequiredForSubmit)) tag->m_bRequiredForSubmit = 0;
    ((TextInputTagVtablePrefix *)tag->base.vtable)->registerWithForm(tag, iks_parent(tag->base.m_xml), tagList);
}

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
    tag->m_curLeftOffset = 0;
    tag->m_curRightOffset = 0;
}

extern "C" SECTION(scrollTextLeftToFillWindow) void scrollTextLeftToFillWindow(TextInputTagState *tag)
{
    float width = ((const TextInputTagVtablePrefix *)tag->base.vtable)->getSubstringPixelWidth(tag, tag->m_curLeftOffset, tag->m_curEditOffset);
    while (width > tag->m_maxWrap) {
        tag->m_curLeftOffset = UTF8_GetNextCharIndexFromString(tag->m_text, tag->m_curLeftOffset);
        tag->m_curRightOffset = UTF8_GetNextCharIndexFromString(tag->m_text, tag->m_curRightOffset);
        width = ((const TextInputTagVtablePrefix *)tag->base.vtable)->getSubstringPixelWidth(tag, tag->m_curLeftOffset, tag->m_curEditOffset);
    }
}

extern "C" SECTION(scrollTextRightToFillWindow) void scrollTextRightToFillWindow(TextInputTagState *self)
{
    if (self->m_curEditOffset != self->m_curLeftOffset || self->m_curEditOffset <= 0) return;
    if (svoTextInputJumpScroll) {
        float width;
        do {
            self->m_curLeftOffset = UTF8_GetPrevCharIndexFromString(self->m_text, self->m_curLeftOffset);
            width = ((const TextInputTagVtablePrefix *)self->base.vtable)->getSubstringPixelWidth(self, self->m_curLeftOffset, self->m_curEditOffset);
            DumpSubstring(svoTextInputJumpPart1, width, self->m_curLeftOffset, self->m_curEditOffset, self->m_text);
        } while (width < self->m_maxWrap && self->m_curLeftOffset > 0);
        do {
            self->m_curRightOffset = UTF8_GetPrevCharIndexFromString(self->m_text, self->m_curRightOffset);
            width = ((const TextInputTagVtablePrefix *)self->base.vtable)->getSubstringPixelWidth(self, self->m_curLeftOffset, self->m_curRightOffset);
            DumpSubstring(svoTextInputJumpPart2, width, self->m_curLeftOffset, self->m_curRightOffset, self->m_text);
        } while (width > self->m_maxWrap);
    } else {
        self->m_curLeftOffset = UTF8_GetPrevCharIndexFromString(self->m_text, self->m_curEditOffset);
        float width;
        do {
            self->m_curRightOffset = UTF8_GetPrevCharIndexFromString(self->m_text, self->m_curRightOffset);
            width = ((const TextInputTagVtablePrefix *)self->base.vtable)->getSubstringPixelWidth(self, self->m_curLeftOffset, self->m_curRightOffset);
            DumpSubstring(svoTextInputSmoothScroll, width, self->m_curLeftOffset, self->m_curRightOffset, self->m_text);
        } while (width > self->m_maxWrap);
    }
}

extern "C" SECTION(setText) void setText(TextInputTagState *tag, char *text, unsigned int length)
{
    resetTextInput(tag);
    strncpy(tag->m_text, text, 512);
    tag->m_curEditOffset = length;
    tag->m_curRightOffset = length;
    float width = ((TextInputTagVtablePrefix *)tag->base.vtable)->getSubstringPixelWidth(tag, 0, length);
    if (tag->m_curEditOffset > 0 && tag->m_maxWrap < width) {
        tag->m_curLeftOffset = tag->m_curEditOffset;
        do {
            --tag->m_curLeftOffset;
            width = ((TextInputTagVtablePrefix *)tag->base.vtable)->getSubstringPixelWidth(tag, tag->m_curLeftOffset, tag->m_curEditOffset);
        } while (width < tag->m_maxWrap);
    }
}

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
