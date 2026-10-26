#include "TagUtils.h"
#include "HttpUtils.h"
#include "SVBrowser.h"
#include "TextEditableTag.h"
#include "UTF8_Util.h"
#include "CInputContextBase.h"
#include "CDrawContextBase.h"
#include "SVOString.h"
#include "TextAreaTag.h"
#include "CMemoryContextBase.h"
#include "SVTag.h"
#include "string.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_TextAreaTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern "C" {
void Scroll(TextAreaTagState *tag, signed char amount, int speed);
void changeColorForAllLines(TextAreaTagState *tag, unsigned int color);
void SetText___dupe3(TextAreaTagState *tag, char *text);
void RegisterWithForm___dupe2(TextAreaTagState *tag, iks *parent, SVTag **tagList);

extern "C" {
SVTagModuleState *getInstance___dupe17(void);
extern char svoTextAreaTagFormNameAttribute[];
struct SVTextAreaNewline { char text[2]; };
extern const SVTextAreaNewline svoTextAreaNewline;
void AddTextAreaElement(FormTag *form, TextAreaTagState *tag);
extern char svoTextAreaTagSource[];

}
extern "C" {
extern const SVTagVtablePrefix svoTextAreaTagVtable;
void FreeResources___dupe21(TextAreaTagState *tag);
}
extern "C" {
float GetSubstringPixelWidth(TextAreaTagState *tag, CDrawContextBase *draw, char *text, int startOffset, int endOffset);
}
extern "C" {
void ResetVariables(TextAreaTagState *);
void resetTextArea(TextAreaTagState *);
void ResetParser(TextAreaTagState *);
int ParseText(TextAreaTagState *, char *, int *);
void UpdateCursorPosition(TextAreaTagState *, CDrawContextBase *);
void SetArrowOffsets(TextAreaTagState *);
int GetLineNumberAtOffset(TextAreaTagState *, char *, int);

}
extern "C" {
extern char svoTextAreaTagName[];
}
extern "C" {

}
extern "C" {

}
extern "C" {
void handleSpecialKeys(TextAreaTagState *, unsigned char);
void UpdateAfterTextEntry(TextAreaTagState *);
int GetNextWord(TextAreaTagState *, char *, int *, int *, int *);
int CheckForLongWord(TextAreaTagState *, char *, int, int, float);
int TrimLongWord(TextAreaTagState *, char *, int, int, float);
int ProcessNewLine(TextAreaTagState *, int);
void PutBackWord(TextAreaTagState *, int, int *);
}
extern "C" {
void ProcessUpArrow(TextAreaTagState *);
void ProcessDownArrow(TextAreaTagState *);
void ProcessLeftArrow(TextAreaTagState *);
void ProcessRightArrow(TextAreaTagState *);
void SignalPluginEvent(SVBrowserPrefix *, int, SVTag *);
int Navigate(SVTag *, CInputContextBaseState *, CDrawContextBase *, iks *, CPage *);
void ShowVKB(SVBrowserPrefix *, SVTag *);
int GetVisible(SVTag *);
void PrintText(TextAreaTagState *, CDrawContextBase *);
void DrawCursor(TextAreaTagState *, CDrawContextBase *, int);
void SetScrollBarPercentage(TextAreaTagState *);
extern unsigned int svoTextAreaBlinkCount;
}
extern "C" {
extern char svoTextAreaFillColorAttribute[];
extern char svoTextAreaLineColorAttribute[];
extern char svoTextAreaTextColorAttribute[];
extern char svoTextAreaHighlightFillColorAttribute[];
extern char svoTextAreaHighlightLineColorAttribute[];
extern char svoTextAreaHighlightTextColorAttribute[];
extern char svoTextAreaFontSizeAttribute[];
extern char svoTextAreaLineSpacingAttribute[];
extern char svoTextAreaLeftPadValueAttribute[];
extern char svoTextAreaTopPadValueAttribute[];
extern char svoTextAreaScrollBarWidthAttribute[];
extern char svoTextAreaScrollBarHeightAttribute[];
extern char svoTextAreaLinesVisibleAttribute[];
extern char svoTextAreaMaxLengthAttribute[];
extern char svoTextAreaMaxLinesAttribute[];
extern char svoTextAreaReadOnlyAttribute[];
extern char svoTextAreaEditableAttribute[];
extern char svoTextAreaFalseValue[];
extern char svoTextAreaTrueValue[];
extern char svoTextAreaBlinkCursorAttribute[];
extern char svoTextAreaLinkAttribute[];
extern char svoTextAreaDefaultTextEntryAttribute[];
extern char svoTextAreaClassAttribute[];
extern char svoTextAreaSubmitAsEncryptedAttribute[];
extern char svoTextAreaRequiredForPostAttribute[];
extern char svoTextAreaMultiColorTextAreaAttribute[];
}
#define SECTION(name) __attribute__((section(".svo_TextAreaTag_" #name)))




}


































extern "C" SECTION(DefaultInit___dupe12) void DefaultInit___dupe12(TextAreaTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoTextAreaTagName, 64);
    tag->m_maxTextSize = 0x3000;
    tag->m_maxTextLines = 300;
    tag->m_blinkCursor = 1;
    tag->m_drawCursor = 1;
    tag->base.m_fillColor = 0xFF000000;
    tag->base.m_lineColor = 0xFFFFFFFF;
    tag->m_highlightFillColor = 0xFF000000;
    tag->m_textColor = 0xFFFFFFFF;
    tag->m_highlightLineColor = 0xFFFFFF00;
    tag->m_highlightTextColor = 0xFFFFFF00;
    tag->m_isEditable = 1;
    tag->m_fontSize = 14;
    tag->m_node = -1;
    tag->m_scrollBarWidth = 15.0f;
    tag->m_obj = -1;
    tag->m_lineSpacing = 15.0f;
    tag->m_maxNumViewableLines = 2;
    tag->m_text = 0;
    tag->m_link = 0;
    tag->m_scrollBarNode = 0;
    tag->m_scrollBarHeight = 0;
    tag->m_maxScrollBarNodeTranslate = 0;
    tag->m_scrollBarPercentage = 0;
    tag->m_xAxisPadValue = 0;
    tag->m_yAxisPadValue = 0;
    tag->m_opacity = 0;
    tag->m_nx = 0;
    tag->m_ny = 0;
    tag->base.m_isDefTextEntry = 0;
    tag->m_parentForm = 0;
    tag->m_tmpCallsToGSW = 0;
    tag->m_bSubmitAsEncryped = 0;
    tag->m_bRequiredForSubmit = 0;
    tag->m_bMultiColorTextArea = 0;
    tag->m_bSelectedLastFrame = 0;
    ResetVariables(tag);
}
extern "C" SECTION(TextAreaTag) void TextAreaTag(TextAreaTagState *tag, iks *xml, SVTag **tagList, CAllContextData *contexts)
{
    SVTagConstruct(&tag->base, xml, contexts);
    tag->base.vtable = &svoTextAreaTagVtable;
    if (!xml || !tagList) __SVO_Assert_Handler(svoTextAreaTagSource, 0x5B);
    DefaultInit___dupe12(tag);
    getColorAttrib(tag->base.m_xml, svoTextAreaFillColorAttribute, &tag->base.m_fillColor);
    getColorAttrib(tag->base.m_xml, svoTextAreaLineColorAttribute, &tag->base.m_lineColor);
    getColorAttrib(tag->base.m_xml, svoTextAreaTextColorAttribute, &tag->m_textColor);
    getColorAttrib(tag->base.m_xml, svoTextAreaHighlightFillColorAttribute, &tag->m_highlightFillColor);
    getColorAttrib(tag->base.m_xml, svoTextAreaHighlightLineColorAttribute, &tag->m_highlightLineColor);
    getColorAttrib(tag->base.m_xml, svoTextAreaHighlightTextColorAttribute, &tag->m_highlightTextColor);
    getIntAttrib(tag->base.m_xml, svoTextAreaFontSizeAttribute, &tag->m_fontSize);
    getFloatAttrib(tag->base.m_xml, svoTextAreaLineSpacingAttribute, &tag->m_lineSpacing);
    getFloatAttrib(tag->base.m_xml, svoTextAreaLeftPadValueAttribute, &tag->m_xAxisPadValue);
    getFloatAttrib(tag->base.m_xml, svoTextAreaTopPadValueAttribute, &tag->m_yAxisPadValue);
    getFloatAttrib(tag->base.m_xml, svoTextAreaScrollBarWidthAttribute, &tag->m_scrollBarWidth);
    tag->m_maxLineLength = ((tag->base.m_width - tag->m_scrollBarWidth) - 10.0f) - tag->m_xAxisPadValue;
    getFloatAttrib(tag->base.m_xml, svoTextAreaScrollBarHeightAttribute, &tag->m_scrollBarHeight);
    getIntAttrib(tag->base.m_xml, svoTextAreaLinesVisibleAttribute, &tag->m_maxNumViewableLines);
    getIntAttrib(tag->base.m_xml, svoTextAreaMaxLengthAttribute, &tag->m_maxTextSize);
    getIntAttrib(tag->base.m_xml, svoTextAreaMaxLinesAttribute, &tag->m_maxTextLines);
    ++tag->m_maxTextSize;
    tag->m_text = (char *)svAllocSafe(tag->base.m_contexts->memoryContext, tag->m_maxTextSize, 0, 0x85, svoTextAreaTagSource);
    if (!tag->m_text) __SVO_Assert_Handler(svoTextAreaTagSource, 0x86);
    memset(tag->m_text, 0, tag->m_maxTextSize);
    tag->m_textLines = (LineInfo *)svAllocSafe(tag->base.m_contexts->memoryContext, tag->m_maxTextLines * 12 + 12, 0, 0x8A, svoTextAreaTagSource);
    if (!tag->m_textLines) __SVO_Assert_Handler(svoTextAreaTagSource, 0x8B);
    resetTextArea(tag);
    char *readOnly = iks_find_attrib(xml, svoTextAreaReadOnlyAttribute);
    char *editable = iks_find_attrib(xml, svoTextAreaEditableAttribute);
    if (readOnly) {
        if (editable) __SVO_Assert_Handler(svoTextAreaTagSource, 0x96);
        if (!strcmp(readOnly, svoTextAreaFalseValue)) {
            tag->m_isEditable = 1;
            tag->base.m_bSelectable = 1;
        } else tag->m_isEditable = 0;
    } else if (editable) {
        if (!strcmp(editable, svoTextAreaTrueValue)) {
            tag->m_isEditable = 1;
            tag->base.m_bSelectable = 1;
        } else tag->m_isEditable = 0;
    }
    char *blink = iks_find_attrib(xml, svoTextAreaBlinkCursorAttribute);
    if (blink) {
        if (!strcmp(blink, svoTextAreaTrueValue)) tag->m_blinkCursor = 1;
        else tag->m_blinkCursor = 0;
    }
    tag->m_link = iks_find_attrib(tag->base.m_xml, svoTextAreaLinkAttribute);
    if (tag->m_link) decodeEntityText(tag->m_link);
    if (iks_has_children(tag->base.m_xml)) SetText___dupe3(tag, iks_cdata(iks_child(tag->base.m_xml)));
    if (!tag->m_isEditable) {
        tag->m_curEditOffset = 0;
        tag->m_curLine = 0;
        tag->m_minDisplayLine = 0;
        UpdateCursorPosition(tag, tag->base.m_contexts->drawContext);
    }
    if (!tag->m_text) __SVO_Assert_Handler(svoTextAreaTagSource, 0xE1);
    decodeEntityText(tag->m_text);
    getBoolAttrib(tag->base.m_xml, svoTextAreaDefaultTextEntryAttribute, &tag->base.m_isDefTextEntry);
    getStringAttrib(tag->base.m_xml, svoTextAreaClassAttribute, &tag->base.m_tagClass);
    SignalPluginEvent(GetInstance(), 13, &tag->base);
    tag->m_scrollBarHeight = tag->base.m_height;
    if (!getBoolAttrib(tag->base.m_xml, svoTextAreaSubmitAsEncryptedAttribute, &tag->m_bSubmitAsEncryped)) tag->m_bSubmitAsEncryped = 0;
    if (!getBoolAttrib(tag->base.m_xml, svoTextAreaRequiredForPostAttribute, &tag->m_bRequiredForSubmit)) tag->m_bRequiredForSubmit = 0;
    if (!getBoolAttrib(tag->base.m_xml, svoTextAreaMultiColorTextAreaAttribute, &tag->m_bMultiColorTextArea)) tag->m_bMultiColorTextArea = 0;
    RegisterWithForm___dupe2(tag, iks_parent(tag->base.m_xml), tagList);
    return;
}
extern "C" SECTION(_TextAreaTag) void _TextAreaTag(SVTag *tag, int flags)
{
    tag->vtable = &svoTextAreaTagVtable;
    FreeResources___dupe21((TextAreaTagState *)tag);
    tag->vtable = &svoTagVtable;
    if (flags & 1) { SVTagDelete(tag); return; }
}
extern "C" SECTION(FreeResources___dupe21) void FreeResources___dupe21(TextAreaTagState *tag)
{
    if (tag->m_text) {
        svFreeSafe(tag->base.m_contexts->memoryContext, tag->m_text);
        tag->m_text = 0;
    }
    if (tag->m_textLines) {
        svFreeSafe(tag->base.m_contexts->memoryContext, tag->m_textLines);
        tag->m_textLines = 0;
    }
}
extern "C" SECTION(HandleInput___dupe43) int HandleInput___dupe43(TextAreaTagState *self, CPage *page)
{
    SVTag *tag = &self->base;
    if (!self->m_bMultiColorTextArea) {
        if (tag->vtable->IsSelected(tag) && !self->m_bSelectedLastFrame) {
            self->m_bSelectedLastFrame = 1;
            changeColorForAllLines(self, self->m_highlightTextColor);
        } else if (!tag->vtable->IsSelected(tag) && self->m_bSelectedLastFrame) {
            self->m_bSelectedLastFrame = 0;
            changeColorForAllLines(self, self->m_textColor);
        }
    }
    if (!tag->vtable->IsSelected(tag)) return 1;
    SVBrowserPrefix *browser = GetInstance();
    CInputContextBaseState *input = tag->m_contexts->inputContext;
    if (!tag->m_xml) __SVO_Assert_Handler(svoTextAreaTagSource, 0x13C);
    if (!input) __SVO_Assert_Handler(svoTextAreaTagSource, 0x13D);
    if (!page) __SVO_Assert_Handler(svoTextAreaTagSource, 0x13E);
    int scroll = HasActionOccurred(input, 0x11, SV_ACTION_SCROLL_UP);
    if (scroll || (scroll = HasActionOccurred(input, 0x11, SV_ACTION_SCROLL_DOWN))) Scroll(self, scroll, 0);
    if (!browser->m_bShowVKB) {
        if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_UP) || HasActionOccurred(input, 0x11, SV_ACTION_NAV_DOWN)
            || HasActionOccurred(input, 0x11, SV_ACTION_NAV_LEFT) || HasActionOccurred(input, 0x11, SV_ACTION_NAV_RIGHT)) {
            CDrawContextBase *draw = tag->m_contexts->drawContext;
            if (!draw) __SVO_Assert_Handler(svoTextAreaTagSource, 0x155);
            return Navigate(tag, input, draw, tag->m_xml, page) == 0;
        }
        if (HasActionOccurred(input, 0x11, SV_ACTION_SCROLL_LEFT)) ProcessLeftArrow(self);
        if (HasActionOccurred(input, 0x11, SV_ACTION_SCROLL_RIGHT)) ProcessRightArrow(self);
        if (tag->vtable->IsEditable(tag)) {
            if (HasActionOccurred(input, 0x11, SV_ACTION_VKB_ACTIVATE)) ShowVKB(browser, tag);
            ((const TextEditableTagVtablePrefix *)tag->vtable)->HandleTextEntry(tag, input);
        }
    } else input->vtable->HandleVKBInput(input, tag);
    return 1;
}
extern "C" SECTION(Draw___dupe16) void Draw___dupe16(TextAreaTagState *self)
{
    SVTag *tag = &self->base;
    if (GetVisible(tag)) {
        CDrawContextBase *draw = tag->m_contexts->drawContext;
        if (!draw) __SVO_Assert_Handler(svoTextAreaTagSource, 0x182);
        if (!tag->m_xml || !self->m_text) __SVO_Assert_Handler(svoTextAreaTagSource, 0x183);
        unsigned int fill;
        unsigned int line;
        unsigned int color;
        char unused[16]; // Retail reserves an unused 16-byte local in this frame.
        if (tag->vtable->IsSelected(tag)) {
            fill = self->m_highlightFillColor;
            line = self->m_highlightLineColor;
            color = self->m_highlightTextColor;
        } else {
            fill = tag->m_fillColor;
            line = tag->m_lineColor;
            color = self->m_textColor;
        }
        draw->vtable->DrawTextArea(draw, tag->m_tagid, tag->m_x, tag->m_y, tag->m_z, tag->m_width, tag->m_height, line, fill, color, tag->m_bSelected, self->m_scrollBarWidth, self->m_scrollBarHeight, self->m_scrollBarPercentage, tag->m_tagClass, self->m_canScrollUp, self->m_canScrollDown);
        PrintText(self, draw);
        if (tag->vtable->IsEditable(tag)) {
            if (self->m_blinkCursor) {
                if (svoTextAreaBlinkCount % 30 == 0) self->m_drawCursor = !self->m_drawCursor;
                ++svoTextAreaBlinkCount;
                if (tag->m_bSelected) DrawCursor(self, draw, self->m_drawCursor);
            } else {
                if (tag->m_bSelected) DrawCursor(self, draw, 1);
            }
        }
        SetScrollBarPercentage(self);
    }
    if (self->m_curEditOffset < 0) __SVO_Assert_Handler(svoTextAreaTagSource, 0x1C8);
}
extern "C" SECTION(resetTextArea) void resetTextArea(TextAreaTagState *tag)
{
    memset(tag->m_text, 0, tag->m_maxTextSize);
    if (!tag->m_textLines) __SVO_Assert_Handler(svoTextAreaTagSource, 0x1D2);
    for (int i = 0; i < tag->m_maxTextLines + 1; ++i) {
        unsigned int color = tag->m_textColor;
        if (i == 0) tag->m_textLines[0].lineStartIndex = 0;
        else tag->m_textLines[i].lineStartIndex = -1;
        tag->m_textLines[i].color = color;
        tag->m_textLines[i].lineNumber = i;
        tag->m_textLines[i].lineEndIndex = 0;
    }
    ResetVariables(tag);
}
extern "C" SECTION(changeColorForAllLines) void changeColorForAllLines(TextAreaTagState *tag, unsigned int color)
{
    for (int i = 0; i < tag->m_maxTextLines + 1; i++) tag->m_textLines[i].color = color;
}
extern "C" SECTION(ResetVariables) void ResetVariables(TextAreaTagState *tag)
{
    tag->m_canScrollDown = 0;
    tag->m_scrollFrame = 0;
    tag->m_cursorX = tag->base.m_x + 7.0f;
    tag->m_curEditOffset = 0;
    tag->m_cursorY = tag->base.m_y - 2.0f;
    tag->m_textEndOffset = 0;
    tag->m_curParseOffset = 0;
    tag->m_curParseLine = 0;
    tag->m_curLine = 0;
    tag->m_textEndLine = 0;
    tag->m_minDisplayLine = 0;
    tag->m_numLinesInDisplay = 1;
    tag->m_overallLength = 0.0f;
    tag->m_upArrowOffset = 0;
    tag->m_downArrowOffset = 0;
    tag->m_leftArrowOffset = 0;
    tag->m_rightArrowOffset = 0;
    tag->m_numTotalLines = 0;
    tag->m_canScrollUp = 0;
    tag->m_firstAppendToChat = 1;
}
extern "C" SECTION(handleSpecialKeys) void handleSpecialKeys(TextAreaTagState *tag, unsigned char key)
{
    CAllContextData *contexts = tag->base.m_contexts;
    CInputContextBaseState *input = contexts->inputContext;
    char newline[16];
    int first;
    *(SVTextAreaNewline *)newline = svoTextAreaNewline;
    switch (key) {
    case 0x89:
        if (tag->m_curEditOffset > 0) {
            tag->m_curEditOffset = UTF8_RemoveCharFromStringBACKSPACE(tag->m_text, tag->m_curEditOffset);
            UpdateAfterTextEntry(tag);
        }
        break;
    case 0x87:
        tag->m_curEditOffset = UTF8_RemoveCharFromStringDELETE(tag->m_text, tag->m_curEditOffset);
        UpdateAfterTextEntry(tag);
        break;
    case 0x83:
        ProcessLeftArrow(tag);
        break;
    case 0x84:
        ProcessRightArrow(tag);
        break;
    case 0x81:
        ProcessUpArrow(tag);
        break;
    case 0x82:
        ProcessDownArrow(tag);
        break;
    case 0x86:
        tag->m_curLine = tag->m_textEndLine;
        tag->m_curEditOffset = tag->m_textEndOffset;
        first = tag->m_textEndLine - tag->m_maxNumViewableLines + 1;
        if (first < 0) first = 0;
        tag->m_minDisplayLine = first;
        UpdateCursorPosition(tag, contexts->drawContext);
        break;
    case 0x85:
        tag->m_curEditOffset = 0;
        tag->m_curLine = 0;
        tag->m_minDisplayLine = 0;
        UpdateCursorPosition(tag, contexts->drawContext);
        break;
    case 0x88:
        SignalPluginEvent(GetInstance(), 10, &tag->base);
        if (tag->m_curLine < tag->m_maxTextLines - 1 && (int)strlen(tag->m_text) + 2 < tag->m_maxTextSize) {
            tag->m_curEditOffset = UTF8_AddCharToString(tag->m_text, tag->m_maxTextSize, newline, strlen(newline), tag->m_curEditOffset);
            ++tag->m_curLine;
            UpdateAfterTextEntry(tag);
        }
        break;
    }
    input->specialKeyCode = 0;
}
extern "C" SECTION(SetScrollBarPercentage) void SetScrollBarPercentage(TextAreaTagState *tag)
{
    tag->m_scrollBarPercentage = 0;
    if (tag->m_minDisplayLine + tag->m_numLinesInDisplay < tag->m_minDisplayLine)
        __SVO_Assert_Handler(svoTextAreaTagSource, 0x275);
    if (tag->m_maxNumViewableLines < tag->m_numTotalLines)
        tag->m_scrollBarPercentage = (float)tag->m_curLine / (float)tag->m_numTotalLines;
    if (!tag->m_minDisplayLine) tag->m_canScrollUp = 0;
    else tag->m_canScrollUp = 1;
    if (tag->m_minDisplayLine + tag->m_maxNumViewableLines < tag->m_numTotalLines + 1) tag->m_canScrollDown = 1;
    else tag->m_canScrollDown = 0;
}
extern "C" SECTION(Scroll) void Scroll(TextAreaTagState *tag, signed char amount, int fromArrow)
{
    if (tag->m_scrollFrame++ < 3 && amount >= -120 && amount <= 120) return;
    tag->m_scrollFrame = 0;
    if (amount < 0) {
        if (tag->m_curLine > tag->m_minDisplayLine) {
            tag->m_curLine--;
            if (!fromArrow) {
                tag->m_curEditOffset = tag->m_upArrowOffset;
                if (tag->m_upArrowOffset < 0) __SVO_Assert_Handler(svoTextAreaTagSource, 0x2A3);
            }
            UpdateCursorPosition(tag, tag->base.m_contexts->drawContext);
        } else if (tag->m_minDisplayLine > 0) {
            tag->m_minDisplayLine--;
            tag->m_curLine--;
            if (!fromArrow) {
                tag->m_curEditOffset = tag->m_upArrowOffset;
                if (tag->m_upArrowOffset < 0) __SVO_Assert_Handler(svoTextAreaTagSource, 0x2B0);
            }
            UpdateCursorPosition(tag, tag->base.m_contexts->drawContext);
        }
    } else if (amount > 0) {
        if (tag->m_curLine < tag->m_minDisplayLine + tag->m_numLinesInDisplay - 1) {
            tag->m_curLine++;
            if (!fromArrow) {
                tag->m_curEditOffset = tag->m_downArrowOffset;
                if (tag->m_downArrowOffset < 0) __SVO_Assert_Handler(svoTextAreaTagSource, 0x2BF);
            }
            UpdateCursorPosition(tag, tag->base.m_contexts->drawContext);
        } else if (tag->m_curLine < tag->m_numTotalLines - 1) {
            tag->m_minDisplayLine++;
            tag->m_curLine++;
            if (!fromArrow) {
                tag->m_curEditOffset = tag->m_downArrowOffset;
                if (tag->m_downArrowOffset < 0) __SVO_Assert_Handler(svoTextAreaTagSource, 0x2CC);
            }
            UpdateCursorPosition(tag, tag->base.m_contexts->drawContext);
        }
    }
}
extern "C" SECTION(scroll___dupe2) void scroll___dupe2(TextAreaTagState *tag, signed char amount)
{
    Scroll(tag, amount, 0);
}
extern "C" SECTION(SetText___dupe3) void SetText___dupe3(TextAreaTagState *tag, char *text)
{
    resetTextArea(tag);
    int length = strlen(text);
    int maximum = tag->m_maxTextSize;
    int count = length;
    if (count >= maximum) count = maximum;
    else if (count < maximum - 1) count++;
    svsubstrncpy(tag->m_text, text, count + 1);
    ParseText(tag, tag->m_text, &tag->m_curParseOffset);
    tag->m_curEditOffset = tag->m_curParseOffset;
    tag->m_curLine = tag->m_textEndLine;
    UpdateCursorPosition(tag, tag->base.m_contexts->drawContext);
}
extern "C" SECTION(handleKeyboardInput) void handleKeyboardInput(TextAreaTagState *tag, CInputContextBaseState *input)
{
    char *text = input->vtable->GetKeyboardBuffer(input);
    size_t length = strlen(text);
    size_t oldLength = strlen(tag->m_text);
    char last[16];
    last[0] = (int)length < 1 ? 0 : text[(int)length - 1];
    last[1] = 0;
    unsigned char key = input->specialKeyCode;
    if (key) handleSpecialKeys(tag, key);
    else if ((int)length > 0 && (int)oldLength < tag->m_maxTextSize - 1 && tag->m_curLine < tag->m_maxTextLines) {
        tag->m_curEditOffset = UTF8_AddCharToString(tag->m_text, tag->m_maxTextSize, last, strlen(last), tag->m_curEditOffset);
        UpdateAfterTextEntry(tag);
        UpdateCursorPosition(tag, tag->base.m_contexts->drawContext);
    }
    input->vtable->ResetKeyboardInput(input);
}
extern "C" SECTION(FindParentForm___dupe2) FormTag *FindParentForm___dupe2(TextAreaTagState *tag, iks *parent, SVTag **tagList)
{
    if (!parent) __SVO_Assert_Handler(svoTextAreaTagSource, 0x3A8);
    if (!tagList) __SVO_Assert_Handler(svoTextAreaTagSource, 0x3A9);
    SVTagModuleState *module = getInstance___dupe17();
    while (!module->vtable->IsMyTag(module, parent)) {
        parent = iks_parent(parent);
        if (!parent) return 0;
    }
    char *formName = iks_find_attrib(parent, svoTextAreaTagFormNameAttribute);
    if (!formName) __SVO_Assert_Handler(svoTextAreaTagSource, 0x3BB);
    for (int i = 0; i < 256; ++i) {
        SVTag *candidate = tagList[i];
        if (candidate) {
            char *name = candidate->vtable->GetTagName(candidate);
            if (!name) __SVO_Assert_Handler(svoTextAreaTagSource, 0x3C2);
            if (!strcmp(name, formName)) return (FormTag *)tagList[i];
        }
    }
    return 0;
}
extern "C" SECTION(RegisterWithForm___dupe2) void RegisterWithForm___dupe2(TextAreaTagState *tag, iks *parent, SVTag **tagList)
{
    tag->m_parentForm = FindParentForm___dupe2(tag, parent, tagList);
    if (tag->m_parentForm) AddTextAreaElement(tag->m_parentForm, tag);
}
extern "C" SECTION(ParseText) int ParseText(TextAreaTagState *tag, char *text, int *offset)
{
    CDrawContextBase *draw = tag->base.m_contexts->drawContext;
    int lines = 1;
    int start = 0;
    int end = 0;
    for (;;) {
        int result = GetNextWord(tag, text, &start, &end, offset);
        if (result < 1) break;
        char word[128];
        memset(word, 0, 128);
        memcpy(word, text + start, (int)((unsigned int)end - start));
        word[(int)((unsigned int)end - start)] = 0;
        float width = GetSubstringPixelWidth(tag, draw, text, start, end);
        float total = tag->m_overallLength + width;
        if (total > tag->m_maxLineLength) {
            PutBackWord(tag, start, offset);
            if (!ProcessNewLine(tag, *offset)) break;
            ++lines;
        } else if ((unsigned int)result - 2 < 2) {
            if (ProcessNewLine(tag, *offset)) {
                if (result != 3) ++*offset;
                if (text[*offset]) ++lines;
            } else if (tag) { // fake match: permuter (register allocation)
                tag->m_textEndOffset = *offset;
                return lines;
            } else {
                tag->m_textEndOffset = *offset;
                return lines;
            }
        } else tag->m_overallLength = total;
    }
    tag->m_textEndOffset = *offset;
    return lines;
}
extern "C" SECTION(GetNextWord) int GetNextWord(TextAreaTagState *tag, char *text, int *start, int *end, int *offset)
{
    int result = 1;
    int *position;
    if (offset) {
        *start = *offset;
        position = offset;
    } else {
        *start = tag->m_curParseOffset;
        position = &tag->m_curParseOffset;
    }
    *end = *start;
    goto loop;
trim:
    result = 3;
    *position = TrimLongWord(tag, text, *start, *position, tag->m_maxLineLength);
    goto finish;
loop:
    {
        int current = *position;
        char *cursor = text + current;
        char c = *cursor;
        if (!c || current == tag->m_maxTextSize - 1) {
            if (CheckForLongWord(tag, text, *start, current, tag->m_maxLineLength)) goto trim;
            result = *position != *start;
            goto done;
        }
        if (c == ' ' && current != *start) {
            if (CheckForLongWord(tag, text, *start, current, tag->m_maxLineLength)) goto trim;
            goto done;
        }
        if (*cursor == '\n' || *cursor == '\r') {
            if (CheckForLongWord(tag, text, *start, current, tag->m_maxLineLength)) goto trim;
            result = 2;
            goto done;
        }
        *position = current + 1;
        goto loop;
    }
done:
    tag->m_textLines[tag->m_curParseLine].lineEndIndex = *position;
finish:
    *end = *position;
    return result;
}
extern "C" SECTION(PutBackWord) void PutBackWord(TextAreaTagState *tag, int startIndex, int *parseOffset)
{
    int *offset = parseOffset ? parseOffset : &tag->m_curParseOffset;
    *offset = startIndex < 0 ? 0 : startIndex;
    tag->m_textLines[tag->m_curParseLine].lineEndIndex = *offset;
}
extern "C" SECTION(ProcessNewLine) int ProcessNewLine(TextAreaTagState *tag, int offset)
{
    if (tag->m_curParseLine >= tag->m_maxTextLines) return 0;
    {
        tag->m_textLines[tag->m_curParseLine].lineEndIndex = offset;
        if (tag->m_text[offset] == ' ' || tag->m_text[offset] == 10) tag->m_textLines[tag->m_curParseLine + 1].lineStartIndex = offset + 1;
        else tag->m_textLines[tag->m_curParseLine + 1].lineStartIndex = offset;
        tag->m_numTotalLines++;
        tag->m_textLines[tag->m_curParseLine + 1].lineNumber = tag->m_numTotalLines;
        if (tag->m_numLinesInDisplay < tag->m_maxNumViewableLines) tag->m_numLinesInDisplay++;
        else tag->m_minDisplayLine++;
        tag->m_curParseLine++;
        tag->m_textEndLine++;
        tag->m_overallLength = 0;
        return 1;
    }
}
extern "C" SECTION(UpdateCursorPosition) void UpdateCursorPosition(TextAreaTagState *tag, CDrawContextBase *draw)
{
    tag->m_cursorY = (tag->base.m_y + (tag->m_curLine - tag->m_minDisplayLine) * tag->m_lineSpacing) - 2.0f;
    if (tag->m_maxTextSize < tag->m_curEditOffset) {
        if (tag->m_curLine < 0) tag->m_curLine = 0;
        tag->m_curEditOffset = tag->m_textLines[tag->m_curLine].lineEndIndex;
    }
    float width = GetSubstringPixelWidth(tag, draw, tag->m_text, tag->m_textLines[tag->m_curLine].lineStartIndex, tag->m_curEditOffset);
    tag->m_cursorX = tag->base.m_x + width + 7.0f;
    SetArrowOffsets(tag);
}
extern "C" SECTION(PrintText) void PrintText(TextAreaTagState *tag, CDrawContextBase *draw)
{
    for (int i = 0; i < tag->m_numLinesInDisplay; ++i) {
        if (tag->m_textLines[tag->m_minDisplayLine + i].lineStartIndex == -1) break;
        int length = (int)tag->m_textLines[tag->m_minDisplayLine + i].lineEndIndex - tag->m_textLines[tag->m_minDisplayLine + i].lineStartIndex;
        if ((unsigned int)(int)length > 127) __SVO_Assert_Handler(svoTextAreaTagSource, 0x55B);
        if (length > 0) {
            char text[128];
            memset(text, 0, 128);
            memcpy(text, tag->m_text + tag->m_textLines[tag->m_minDisplayLine + i].lineStartIndex, length);
            text[length] = 0;
            float y = tag->base.m_y + (float)i * tag->m_lineSpacing + tag->m_yAxisPadValue;
            float x = tag->base.m_x + tag->m_xAxisPadValue;
            draw->vtable->SVDrawText(draw, tag->base.m_tagid, x, y, tag->m_textLines[tag->m_minDisplayLine + i].color, text, length, tag->m_fontSize, 0, 0);
        }
    }
}
extern "C" SECTION(DrawCursor) void DrawCursor(TextAreaTagState *tag, CDrawContextBase *draw, int enabled)
{
    if (enabled) {
        unsigned int color = tag->base.m_bSelected ? tag->m_highlightTextColor : tag->m_textColor;
        float y = tag->m_cursorY + tag->m_yAxisPadValue;
        draw->vtable->DrawLine(draw, tag->base.m_tagid, tag->m_cursorX, y, tag->m_cursorX,
            y + tag->m_lineSpacing, tag->base.m_x, 2.0f, color, 0);
    }
}
extern "C" SECTION(SetArrowOffsets) void SetArrowOffsets(TextAreaTagState *tag)
{
    if (tag->m_curLine > 0) {
        int column = tag->m_curEditOffset - tag->m_textLines[tag->m_curLine].lineStartIndex;
        if ((int)tag->m_textLines[tag->m_curLine - 1].lineEndIndex - tag->m_textLines[tag->m_curLine - 1].lineStartIndex < column) {
            int target = tag->m_textLines[tag->m_curLine - 1].lineEndIndex;
            tag->m_upArrowOffset = target;
            if (target < 0) tag->m_upArrowOffset = 0;
        } else {
            int target = tag->m_textLines[tag->m_curLine - 1].lineStartIndex + column;
            tag->m_upArrowOffset = target;
            if (target < 0) tag->m_upArrowOffset = 0;
        }
    } else {
        tag->m_upArrowOffset = tag->m_curEditOffset;
        if (tag->m_curEditOffset < 0) __SVO_Assert_Handler(svoTextAreaTagSource, 0x5AF);
    }
    if (tag->m_curLine < tag->m_numTotalLines - 1 && tag->m_numLinesInDisplay > 1) {
        int column = tag->m_curEditOffset - tag->m_textLines[tag->m_curLine].lineStartIndex;
        if ((int)tag->m_textLines[tag->m_curLine + 1].lineEndIndex - tag->m_textLines[tag->m_curLine + 1].lineStartIndex < column) {
            int target = tag->m_textLines[tag->m_curLine + 1].lineEndIndex;
            tag->m_downArrowOffset = target;
            if (target < 0) {
                tag->m_downArrowOffset = tag->m_curEditOffset;
                if (tag->m_curEditOffset < 0) __SVO_Assert_Handler(svoTextAreaTagSource, 0x5C1);
            }
        } else {
            int target = tag->m_textLines[tag->m_curLine + 1].lineStartIndex + column;
            tag->m_downArrowOffset = target;
            if (target < 0) {
                tag->m_downArrowOffset = tag->m_curEditOffset;
                if (tag->m_curEditOffset < 0) __SVO_Assert_Handler(svoTextAreaTagSource, 0x5CB);
            }
        }
    } else {
        tag->m_downArrowOffset = tag->m_curEditOffset;
        if (tag->m_curEditOffset < 0) __SVO_Assert_Handler(svoTextAreaTagSource, 0x5D1);
    }
    if (tag->m_curEditOffset == tag->m_textLines[tag->m_curLine].lineStartIndex) {
        if (tag->m_curEditOffset > 0) {
            int target = tag->m_textLines[tag->m_curLine - 1].lineEndIndex;
            tag->m_leftArrowOffset = target;
            if (target < 0) __SVO_Assert_Handler(svoTextAreaTagSource, 0x5DA);
        } else {
            tag->m_leftArrowOffset = tag->m_curEditOffset;
            if (tag->m_curEditOffset < 0) __SVO_Assert_Handler(svoTextAreaTagSource, 0x5DF);
        }
    } else {
        int target = UTF8_GetPrevCharIndexFromString(tag->m_text, tag->m_curEditOffset);
        tag->m_leftArrowOffset = target;
        if (target < 0) __SVO_Assert_Handler(svoTextAreaTagSource, 0x5E5);
    }
    if (tag->m_curEditOffset == tag->m_textLines[tag->m_curLine].lineEndIndex) {
        if (tag->m_curLine + 1 < tag->m_minDisplayLine + tag->m_numLinesInDisplay)
            tag->m_rightArrowOffset = tag->m_textLines[tag->m_curLine + 1].lineStartIndex;
        else
            tag->m_rightArrowOffset = tag->m_curEditOffset;
    } else tag->m_rightArrowOffset = UTF8_GetNextCharIndexFromString(tag->m_text, tag->m_curEditOffset);
}
extern "C" SECTION(ProcessUpArrow) void ProcessUpArrow(TextAreaTagState *tag)
{
    int line = tag->m_curLine;
    tag->m_curEditOffset = tag->m_upArrowOffset;
    if (tag->m_upArrowOffset < tag->m_textLines[line].lineStartIndex) {
        if (line == tag->m_minDisplayLine) { Scroll(tag, -127, 1); return; }
        tag->m_curLine = line - 1;
        UpdateCursorPosition(tag, tag->base.m_contexts->drawContext);
    }
}
extern "C" SECTION(ProcessDownArrow) void ProcessDownArrow(TextAreaTagState *tag)
{
    tag->m_curEditOffset = tag->m_downArrowOffset;
    if (tag->m_downArrowOffset < 0) __SVO_Assert_Handler(svoTextAreaTagSource, 0x60F);
    int line = tag->m_curLine;
    if (tag->m_downArrowOffset > tag->m_textLines[line].lineEndIndex) {
        if (line == tag->m_minDisplayLine + tag->m_maxNumViewableLines - 1) { Scroll(tag, 127, 1); return; }
        tag->m_curLine = line + 1;
        if (line + 1 >= tag->m_maxTextLines) __SVO_Assert_Handler(svoTextAreaTagSource, 0x61A);
        UpdateCursorPosition(tag, tag->base.m_contexts->drawContext);
    }
}
extern "C" SECTION(ProcessLeftArrow) void ProcessLeftArrow(TextAreaTagState *tag)
{
    int line = tag->m_curLine;
    tag->m_curEditOffset = tag->m_leftArrowOffset;
    if (tag->m_leftArrowOffset < tag->m_textLines[line].lineStartIndex) {
        if (line <= 0) return;
        if (line == tag->m_minDisplayLine) { Scroll(tag, -127, 1); return; }
        tag->m_curLine = line - 1;
        UpdateCursorPosition(tag, tag->base.m_contexts->drawContext);
        return;
    }
    UpdateCursorPosition(tag, tag->base.m_contexts->drawContext);
}
extern "C" SECTION(ProcessRightArrow) void ProcessRightArrow(TextAreaTagState *tag)
{
    tag->m_curEditOffset = tag->m_rightArrowOffset;
    if (tag->m_rightArrowOffset < 0) __SVO_Assert_Handler(svoTextAreaTagSource, 0x63C);
    int line = tag->m_curLine;
    if (tag->m_rightArrowOffset > tag->m_textLines[line].lineEndIndex) {
        if (line >= tag->m_minDisplayLine + tag->m_numLinesInDisplay - 1) return;
        if (line == tag->m_minDisplayLine + tag->m_maxNumViewableLines) { Scroll(tag, 127, 1); return; }
        tag->m_curLine = line + 1;
        if (line + 1 >= tag->m_maxTextLines) __SVO_Assert_Handler(svoTextAreaTagSource, 0x649);
        UpdateCursorPosition(tag, tag->base.m_contexts->drawContext);
        return;
    }
    UpdateCursorPosition(tag, tag->base.m_contexts->drawContext);
}
extern "C" SECTION(GetSubstringPixelWidth) float GetSubstringPixelWidth(TextAreaTagState *tag, CDrawContextBase *unused, char *text, int start, int end)
{
    int length = (unsigned int)end - start;
    if (length > 0) {
        if (length >= tag->m_maxTextSize) __SVO_Assert_Handler(svoTextAreaTagSource, 0x65D);
        CDrawContextBase *draw = tag->base.m_contexts->drawContext;
        char substring[12288];
        memset(substring, 0, 12288);
        memcpy(substring, text + start, length);
        substring[length] = 0;
        tag->m_tmpCallsToGSW = (unsigned int)tag->m_tmpCallsToGSW + 1;
        return draw->vtable->GetStringWidth(draw, tag->m_fontSize, substring, strlen(substring));
    }
    return 0;
}
extern "C" SECTION(UpdateAfterTextEntry) void UpdateAfterTextEntry(TextAreaTagState *tag)
{
    ResetParser(tag);
    ParseText(tag, tag->m_text, &tag->m_curParseOffset);
    tag->m_curLine = GetLineNumberAtOffset(tag, tag->m_text, tag->m_curEditOffset);
    while (tag->m_curLine < tag->m_minDisplayLine) tag->m_minDisplayLine--;
    UpdateCursorPosition(tag, tag->base.m_contexts->drawContext);
}
extern "C" SECTION(ResetParser) void ResetParser(TextAreaTagState *tag)
{
    int maximum = tag->m_maxTextLines;
    tag->m_numLinesInDisplay = 1;
    tag->m_textEndOffset = 0;
    tag->m_cursorX = tag->base.m_x + 7.0f;
    tag->m_curParseOffset = 0;
    tag->m_cursorY = tag->base.m_y - 2.0f;
    tag->m_curParseLine = 0;
    tag->m_upArrowOffset = 0;
    tag->m_downArrowOffset = 0;
    tag->m_leftArrowOffset = 0;
    tag->m_rightArrowOffset = 0;
    tag->m_numTotalLines = 0;
    tag->m_minDisplayLine = 0;
    tag->m_textEndLine = 0;
    tag->m_overallLength = 0;
    for (int i = 0; i < maximum; ++i) {
        if (i == 0) tag->m_textLines[0].lineStartIndex = 0;
        else tag->m_textLines[i].lineStartIndex = -1;
        tag->m_textLines[i].lineEndIndex = 0;
    }
}
extern "C" SECTION(GetLineNumberAtOffset) int GetLineNumberAtOffset(TextAreaTagState *tag, char *text, int offset)
{
    for (int i = 0; i < tag->m_maxTextLines; ++i) {
        if (tag->m_textLines[i].lineStartIndex <= offset && offset <= tag->m_textLines[i].lineEndIndex) {
            if (tag->m_textLines[i].lineNumber > tag->m_maxTextLines - 1) tag->m_textLines[i].lineNumber = tag->m_maxTextLines - 1;
            return tag->m_textLines[i].lineNumber;
        }
    }
    __SVO_Assert_Handler(svoTextAreaTagSource, 0x742);
    return 0;
}
extern "C" SECTION(CheckForLongWord) int CheckForLongWord(TextAreaTagState *tag, char *text, int startOffset, int endOffset, float maxLength)
{
    int result = 0;
    if (maxLength < GetSubstringPixelWidth(tag, tag->base.m_contexts->drawContext, text, startOffset, endOffset)) result = 1;
    return result;
}
extern "C" SECTION(TrimLongWord) int TrimLongWord(TextAreaTagState *tag, char *text, int start, int end, float maximum)
{
    while (GetSubstringPixelWidth(tag, tag->base.m_contexts->drawContext, text, start, end) > maximum) {
        --end;
        if (end < start) __SVO_Assert_Handler(svoTextAreaTagSource, 0x7C9);
    }
    return end;
}
extern "C" SECTION(GetMaxLengthUTF8Chars) int GetMaxLengthUTF8Chars(TextAreaTagState *tag)
{
    return tag->m_maxTextSize;
}
extern "C" SECTION(GetMaxLengthBytes) int GetMaxLengthBytes(TextAreaTagState *tag)
{
    return tag->m_maxTextSize;
}
