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

extern "C" {
SVTagModuleState *getInstance___dupe17(void);
extern char svoTextAreaTagFormNameAttribute[];
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
long ProcessNewLine(TextAreaTagState *, int);
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
long GetVisible(SVTag *);
void PrintText(TextAreaTagState *, CDrawContextBase *);
void DrawCursor(TextAreaTagState *, CDrawContextBase *, int);
void SetScrollBarPercentage(TextAreaTagState *);
extern unsigned int svoTextAreaBlinkCount;
}
#define SECTION(name) __attribute__((section(".svo_TextAreaTag_" #name)))

SECTION(scroll___dupe2) void scroll___dupe2(TextAreaTagState *tag, signed char amount)
{
    Scroll(tag, amount, 0);
}

SECTION(GetMaxLengthUTF8Chars) long GetMaxLengthUTF8Chars(TextAreaTagState *tag)
{
    return tag->m_maxTextSize;
}

SECTION(GetMaxLengthBytes) long GetMaxLengthBytes(TextAreaTagState *tag)
{
    return tag->m_maxTextSize;
}

}

extern "C" SECTION(_TextAreaTag) void _TextAreaTag(SVTag *tag, unsigned long flags)
{
    tag->vtable = &svoTextAreaTagVtable;
    FreeResources___dupe21((TextAreaTagState *)tag);
    tag->vtable = &svoTagVtable;
    if (flags & 1) SVTagDelete(tag);
}

extern "C" SECTION(changeColorForAllLines) void changeColorForAllLines(TextAreaTagState *tag, unsigned int color)
{
    LineInfo *line = tag->m_textLines;
    for (int i = 0; i < tag->m_maxTextLines + 1; ++i, ++line) line->color = color;
}

extern "C" SECTION(CheckForLongWord) int CheckForLongWord(TextAreaTagState *tag, char *text, int startOffset, int endOffset, float maxLength)
{
    return maxLength < GetSubstringPixelWidth(tag, tag->base.m_contexts->drawContext, text, startOffset, endOffset);
}

extern "C" SECTION(DefaultInit___dupe12) void DefaultInit___dupe12(TextAreaTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoTextAreaTagName, 64);
    tag->m_maxTextLines = 300;
    tag->m_highlightFillColor = 0xFF000000;
    tag->m_highlightTextColor = 0xFFFFFF00;
    tag->m_isEditable = 1;
    tag->m_fontSize = 14;
    tag->m_obj = -1;
    tag->m_lineSpacing = 15.0f;
    tag->m_maxNumViewableLines = 2;
    tag->m_blinkCursor = 1;
    tag->m_drawCursor = 1;
    tag->base.m_fillColor = 0xFF000000;
    tag->base.m_lineColor = 0xFFFFFFFF;
    tag->m_textColor = 0xFFFFFFFF;
    tag->m_highlightLineColor = 0xFFFFFF00;
    tag->m_node = -1;
    tag->m_scrollBarWidth = 15.0f;
    tag->m_maxTextSize = 0x3000;
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
            if (!self->m_blinkCursor) {
                if (tag->m_bSelected) DrawCursor(self, draw, 1);
            } else {
                if (svoTextAreaBlinkCount % 30 == 0) self->m_drawCursor = !self->m_drawCursor;
                ++svoTextAreaBlinkCount;
                if (tag->m_bSelected) DrawCursor(self, draw, self->m_drawCursor);
            }
        }
        SetScrollBarPercentage(self);
    }
    if (self->m_curEditOffset < 0) __SVO_Assert_Handler(svoTextAreaTagSource, 0x1C8);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", DrawCursor);

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

extern "C" SECTION(GetLineNumberAtOffset) int GetLineNumberAtOffset(TextAreaTagState *tag, char *text, int offset)
{
    for (int i = 0; i < tag->m_maxTextLines; ++i) {
        LineInfo *line = &tag->m_textLines[i];
        if (line->lineStartIndex <= offset && offset <= line->lineEndIndex) {
            if (line->lineNumber > tag->m_maxTextLines - 1) line->lineNumber = tag->m_maxTextLines - 1;
            return line->lineNumber;
        }
    }
    __SVO_Assert_Handler(svoTextAreaTagSource, 0x742);
    return 0;
}

extern "C" SECTION(GetNextWord) int GetNextWord(TextAreaTagState *tag, char *text, int *start, int *end, int *offset)
{
    if (!offset) offset = &tag->m_curParseOffset;
    *start = *offset;
    *end = *start;
    int result = 1;
    for (;;) {
        int current = *offset;
        char c = text[current];
        if (!c || current == tag->m_maxTextSize - 1) {
            result = 0;
            break;
        }
        if (c == ' ' && current != *start) break;
        if (c == '\n' || c == '\r') {
            result = 2;
            break;
        }
        *offset = current + 1;
    }
    if (CheckForLongWord(tag, text, *start, *offset, tag->m_maxLineLength)) {
        *offset = TrimLongWord(tag, text, *start, *offset, tag->m_maxLineLength);
        result = 3;
    } else {
        if (result == 0) result = *offset != *start;
        tag->m_textLines[tag->m_curParseLine].lineEndIndex = *offset;
    }
    *end = *offset;
    return result;
}

extern "C" SECTION(GetSubstringPixelWidth) float GetSubstringPixelWidth(TextAreaTagState *tag, CDrawContextBase *unused, char *text, int start, int end)
{
    int length = (unsigned int)end - start;
    if (length <= 0) return 0;
    if (length >= tag->m_maxTextSize) __SVO_Assert_Handler(svoTextAreaTagSource, 0x65D);
    CDrawContextBase *draw = tag->base.m_contexts->drawContext;
    char substring[12288];
    memset(substring, 0, 12288);
    memcpy(substring, text + start, length);
    substring[length] = 0;
    tag->m_tmpCallsToGSW = (unsigned int)tag->m_tmpCallsToGSW + 1;
    return draw->vtable->GetStringWidth(draw, tag->m_fontSize, substring, strlen(substring));
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
    if (browser->m_bShowVKB) input->vtable->HandleVKBInput(input, tag);
    else {
        for (int action = 0; action < 4; ++action) {
            if (HasActionOccurred(input, 0x11, (PadAction)action)) {
                CDrawContextBase *draw = tag->m_contexts->drawContext;
                if (!draw) __SVO_Assert_Handler(svoTextAreaTagSource, 0x155);
                return Navigate(tag, input, draw, tag->m_xml, page) == 0;
            }
        }
        if (HasActionOccurred(input, 0x11, SV_ACTION_SCROLL_LEFT)) ProcessLeftArrow(self);
        if (HasActionOccurred(input, 0x11, SV_ACTION_SCROLL_RIGHT)) ProcessRightArrow(self);
        if (tag->vtable->IsEditable(tag)) {
            if (HasActionOccurred(input, 0x11, SV_ACTION_VKB_ACTIVATE)) ShowVKB(browser, tag);
            ((const TextEditableTagVtablePrefix *)tag->vtable)->HandleTextEntry(tag, input);
        }
    }
    return 1;
}

extern "C" SECTION(handleKeyboardInput) void handleKeyboardInput(TextAreaTagState *tag, CInputContextBaseState *input)
{
    char *text = input->vtable->GetKeyboardBuffer(input);
    size_t length = strlen(text);
    size_t oldLength = strlen(tag->m_text);
    char last[16];
    last[0] = (long)length < 1 ? 0 : text[(int)length - 1];
    last[1] = 0;
    if (input->specialKeyCode) handleSpecialKeys(tag, input->specialKeyCode);
    else if ((long)length > 0 && (long)oldLength < tag->m_maxTextSize - 1 && tag->m_curLine < tag->m_maxTextLines) {
        tag->m_curEditOffset = UTF8_AddCharToString(tag->m_text, tag->m_maxTextSize, last, strlen(last), tag->m_curEditOffset);
        UpdateAfterTextEntry(tag);
        UpdateCursorPosition(tag, tag->base.m_contexts->drawContext);
    }
    input->vtable->ResetKeyboardInput(input);
}

extern "C" SECTION(handleSpecialKeys) void handleSpecialKeys(TextAreaTagState *tag, unsigned char key)
{
    CAllContextData *contexts = tag->base.m_contexts;
    CInputContextBaseState *input = contexts->inputContext;
    char newline[16];
    newline[0] = '\n';
    newline[1] = 0;
    if (key == 0x81) ProcessUpArrow(tag);
    else if (key == 0x82) ProcessDownArrow(tag);
    else if (key == 0x83) ProcessLeftArrow(tag);
    else if (key == 0x84) ProcessRightArrow(tag);
    else if (key == 0x85) {
        tag->m_curEditOffset = 0;
        tag->m_curLine = 0;
        tag->m_minDisplayLine = 0;
        UpdateCursorPosition(tag, contexts->drawContext);
    } else if (key == 0x86) {
        tag->m_curLine = tag->m_textEndLine;
        int first = tag->m_textEndLine - tag->m_maxNumViewableLines + 1;
        tag->m_curEditOffset = tag->m_textEndOffset;
        if (first < 0) first = 0;
        tag->m_minDisplayLine = first;
        UpdateCursorPosition(tag, contexts->drawContext);
    } else if (key == 0x87) {
        tag->m_curEditOffset = UTF8_RemoveCharFromStringDELETE(tag->m_text, tag->m_curEditOffset);
        UpdateAfterTextEntry(tag);
    } else if (key == 0x88) {
        SignalPluginEvent(GetInstance(), 10, &tag->base);
        if (tag->m_curLine < tag->m_maxTextLines - 1 && (int)strlen(tag->m_text) + 2 < tag->m_maxTextSize) {
            tag->m_curEditOffset = UTF8_AddCharToString(tag->m_text, tag->m_maxTextSize, newline, strlen(newline), tag->m_curEditOffset);
            ++tag->m_curLine;
            UpdateAfterTextEntry(tag);
        }
    } else if (key == 0x89 && tag->m_curEditOffset > 0) {
        tag->m_curEditOffset = UTF8_RemoveCharFromStringBACKSPACE(tag->m_text, tag->m_curEditOffset);
        UpdateAfterTextEntry(tag);
    }
    input->specialKeyCode = 0;
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
        width = tag->m_overallLength + width;
        if (width > tag->m_maxLineLength) {
            PutBackWord(tag, start, offset);
            if (!ProcessNewLine(tag, *offset)) break;
            ++lines;
        } else if ((unsigned int)result - 2 < 2) {
            if (!ProcessNewLine(tag, *offset)) break;
            if (result != 3) ++*offset;
            if (text[*offset]) ++lines;
        } else tag->m_overallLength = width;
    }
    tag->m_textEndOffset = *offset;
    return lines;
}

extern "C" SECTION(PrintText) void PrintText(TextAreaTagState *tag, CDrawContextBase *draw)
{
    for (int i = 0; i < tag->m_numLinesInDisplay; ++i) {
        LineInfo *line = &tag->m_textLines[tag->m_minDisplayLine + i];
        if (line->lineStartIndex == -1) break;
        int length = (int)line->lineEndIndex - line->lineStartIndex;
        if ((unsigned long)(long)length > 127) __SVO_Assert_Handler(svoTextAreaTagSource, 0x55B);
        if (length > 0) {
            char text[128];
            memset(text, 0, 128);
            memcpy(text, tag->m_text + tag->m_textLines[tag->m_minDisplayLine + i].lineStartIndex, length);
            text[length] = 0;
            draw->vtable->SVDrawText(draw, tag->base.m_tagid, tag->base.m_x + tag->m_xAxisPadValue, tag->base.m_y + (float)i * tag->m_lineSpacing + tag->m_yAxisPadValue, tag->m_textLines[tag->m_minDisplayLine + i].color, text, length, tag->m_fontSize, 0, 0);
        }
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
    }
    UpdateCursorPosition(tag, tag->base.m_contexts->drawContext);
}

extern "C" SECTION(ProcessNewLine) long ProcessNewLine(TextAreaTagState *tag, int offset)
{
    int line = tag->m_curParseLine;
    if (line >= tag->m_maxTextLines) return 0;
    LineInfo *lines = tag->m_textLines;
    int total = tag->m_numTotalLines;
    char *text = tag->m_text;
    lines[line].lineEndIndex = offset;
    int shown = tag->m_numLinesInDisplay;
    int end = tag->m_textEndLine;
    int maximum = tag->m_maxNumViewableLines;
    lines[line + 1].lineStartIndex = offset + (text[offset] == ' ' || text[offset] == 10);
    tag->m_numTotalLines = total + 1;
    lines[line + 1].lineNumber = tag->m_numTotalLines;
    if (shown < maximum) tag->m_numLinesInDisplay = shown + 1;
    else ++tag->m_minDisplayLine;
    tag->m_curParseLine = line + 1;
    tag->m_textEndLine = end + 1;
    tag->m_overallLength = 0;
    return 1;
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
    }
    UpdateCursorPosition(tag, tag->base.m_contexts->drawContext);
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

extern "C" SECTION(PutBackWord) void PutBackWord(TextAreaTagState *tag, int startIndex, int *parseOffset)
{
    if (startIndex < 0) startIndex = 0;
    int *offset = parseOffset ? parseOffset : &tag->m_curParseOffset;
    *offset = startIndex;
    tag->m_textLines[tag->m_curParseLine].lineEndIndex = (short)*offset;
}

extern "C" SECTION(RegisterWithForm___dupe2) void RegisterWithForm___dupe2(TextAreaTagState *tag, iks *parent, SVTag **tagList)
{
    tag->m_parentForm = FindParentForm___dupe2(tag, parent, tagList);
    if (tag->m_parentForm) AddTextAreaElement(tag->m_parentForm, tag);
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
        tag->m_textLines[i].lineStartIndex = i == 0 ? 0 : -1;
        tag->m_textLines[i].lineEndIndex = 0;
    }
}

extern "C" SECTION(resetTextArea) void resetTextArea(TextAreaTagState *tag)
{
    memset(tag->m_text, 0, tag->m_maxTextSize);
    if (!tag->m_textLines) __SVO_Assert_Handler(svoTextAreaTagSource, 0x1D2);
    for (int i = 0; i < tag->m_maxTextLines + 1; ++i) {
        unsigned int color = tag->m_textColor;
        tag->m_textLines[i].lineStartIndex = i == 0 ? 0 : -1;
        tag->m_textLines[i].color = color;
        tag->m_textLines[i].lineNumber = i;
        tag->m_textLines[i].lineEndIndex = 0;
    }
    ResetVariables(tag);
}

extern "C" SECTION(ResetVariables) void ResetVariables(TextAreaTagState *tag)
{
    tag->m_firstAppendToChat = 1;
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
}

extern "C" SECTION(Scroll) void Scroll(TextAreaTagState *tag, signed char amount, int fromArrow)
{
    int frame = tag->m_scrollFrame;
    tag->m_scrollFrame = (unsigned int)frame + 1;
    if (frame < 3 && amount >= -120 && amount <= 120) return;
    tag->m_scrollFrame = 0;
    int line;
    if (amount < 0) {
        if (tag->m_minDisplayLine < tag->m_curLine) { --tag->m_curLine; line = 0x2A3; }
        else {
            if (tag->m_minDisplayLine <= 0) return;
            --tag->m_minDisplayLine;
            --tag->m_curLine;
            line = 0x2B0;
        }
        if (!fromArrow) {
            tag->m_curEditOffset = tag->m_upArrowOffset;
            if (tag->m_upArrowOffset < 0) __SVO_Assert_Handler(svoTextAreaTagSource, line);
        }
    } else if (amount > 0) {
        if (tag->m_curLine < tag->m_minDisplayLine + tag->m_numLinesInDisplay - 1) {
            ++tag->m_curLine;
            line = 0x2BF;
        } else {
            if (tag->m_curLine >= tag->m_numTotalLines - 1) return;
            ++tag->m_minDisplayLine;
            ++tag->m_curLine;
            line = 0x2CC;
        }
        if (!fromArrow) {
            tag->m_curEditOffset = tag->m_downArrowOffset;
            if (tag->m_downArrowOffset < 0) __SVO_Assert_Handler(svoTextAreaTagSource, line);
        }
    } else return;
    UpdateCursorPosition(tag, tag->base.m_contexts->drawContext);
}

extern "C" SECTION(SetArrowOffsets) void SetArrowOffsets(TextAreaTagState *tag)
{
    int edit = tag->m_curEditOffset;
    if (tag->m_curLine < 1) {
        tag->m_upArrowOffset = edit;
        if (edit < 0) __SVO_Assert_Handler(svoTextAreaTagSource, 0x5AF);
    } else {
        LineInfo *line = &tag->m_textLines[tag->m_curLine];
        int column = edit - line->lineStartIndex;
        int previousLength = (int)line[-1].lineEndIndex - line[-1].lineStartIndex;
        int target = previousLength < column ? line[-1].lineEndIndex : line[-1].lineStartIndex + column;
        tag->m_upArrowOffset = target;
        if (target < 0) tag->m_upArrowOffset = 0;
    }
    edit = tag->m_curEditOffset;
    if (tag->m_curLine < tag->m_numTotalLines - 1 && tag->m_numLinesInDisplay > 1) {
        LineInfo *line = &tag->m_textLines[tag->m_curLine];
        int column = edit - line->lineStartIndex;
        int nextLength = (int)line[1].lineEndIndex - line[1].lineStartIndex;
        if (nextLength < column) {
            tag->m_downArrowOffset = line[1].lineEndIndex;
            if (tag->m_downArrowOffset < 0) {
                tag->m_downArrowOffset = edit;
                if (edit < 0) __SVO_Assert_Handler(svoTextAreaTagSource, 0x5C1);
            }
        } else {
            tag->m_downArrowOffset = line[1].lineStartIndex + column;
            if (tag->m_downArrowOffset < 0) {
                tag->m_downArrowOffset = edit;
                if (edit < 0) __SVO_Assert_Handler(svoTextAreaTagSource, 0x5CB);
            }
        }
    } else {
        tag->m_downArrowOffset = edit;
        if (edit < 0) __SVO_Assert_Handler(svoTextAreaTagSource, 0x5D1);
    }
    edit = tag->m_curEditOffset;
    if (edit == tag->m_textLines[tag->m_curLine].lineStartIndex) {
        if (edit > 0) {
            tag->m_leftArrowOffset = tag->m_textLines[tag->m_curLine - 1].lineEndIndex;
            if (tag->m_leftArrowOffset < 0) __SVO_Assert_Handler(svoTextAreaTagSource, 0x5DA);
        } else {
            tag->m_leftArrowOffset = edit;
            if (edit < 0) __SVO_Assert_Handler(svoTextAreaTagSource, 0x5DF);
        }
    } else {
        tag->m_leftArrowOffset = UTF8_GetPrevCharIndexFromString(tag->m_text, edit);
        if (tag->m_leftArrowOffset < 0) __SVO_Assert_Handler(svoTextAreaTagSource, 0x5E5);
    }
    edit = tag->m_curEditOffset;
    if (edit == tag->m_textLines[tag->m_curLine].lineEndIndex) {
        if (tag->m_minDisplayLine + tag->m_numLinesInDisplay <= tag->m_curLine + 1) {
            tag->m_rightArrowOffset = edit;
            return;
        }
        tag->m_rightArrowOffset = tag->m_textLines[tag->m_curLine + 1].lineStartIndex;
    } else tag->m_rightArrowOffset = UTF8_GetNextCharIndexFromString(tag->m_text, edit);
}

extern "C" SECTION(SetScrollBarPercentage) void SetScrollBarPercentage(TextAreaTagState *tag)
{
    tag->m_scrollBarPercentage = 0;
    if ((int)((unsigned int)tag->m_minDisplayLine + tag->m_numLinesInDisplay) < tag->m_minDisplayLine)
        __SVO_Assert_Handler(svoTextAreaTagSource, 0x275);
    int maximum = tag->m_maxNumViewableLines;
    int total = tag->m_numTotalLines;
    if (maximum < total) tag->m_scrollBarPercentage = (float)tag->m_curLine / (float)total;
    int first = tag->m_minDisplayLine;
    tag->m_canScrollUp = first != 0;
    tag->m_canScrollDown = first + maximum < total + 1;
}

extern "C" SECTION(SetText___dupe3) void SetText___dupe3(TextAreaTagState *tag, char *text)
{
    resetTextArea(tag);
    long length = strlen(text);
    int maximum = tag->m_maxTextSize;
    int count = (int)length + (length < maximum - 1);
    if (length >= maximum) count = maximum;
    svsubstrncpy(tag->m_text, text, count + 1);
    ParseText(tag, tag->m_text, &tag->m_curParseOffset);
    tag->m_curEditOffset = tag->m_curParseOffset;
    tag->m_curLine = tag->m_textEndLine;
    UpdateCursorPosition(tag, tag->base.m_contexts->drawContext);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", TextAreaTag);

extern "C" SECTION(TrimLongWord) int TrimLongWord(TextAreaTagState *tag, char *text, int start, int end, float maximum)
{
    while (GetSubstringPixelWidth(tag, tag->base.m_contexts->drawContext, text, start, end) > maximum) {
        --end;
        if (end < start) __SVO_Assert_Handler(svoTextAreaTagSource, 0x7C9);
    }
    return end;
}

extern "C" SECTION(UpdateAfterTextEntry) void UpdateAfterTextEntry(TextAreaTagState *tag)
{
    ResetParser(tag);
    ParseText(tag, tag->m_text, &tag->m_curParseOffset);
    int line = GetLineNumberAtOffset(tag, tag->m_text, tag->m_curEditOffset);
    tag->m_curLine = line;
    if (line < tag->m_minDisplayLine) tag->m_minDisplayLine = line;
    UpdateCursorPosition(tag, tag->base.m_contexts->drawContext);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TextAreaTag", UpdateCursorPosition);
