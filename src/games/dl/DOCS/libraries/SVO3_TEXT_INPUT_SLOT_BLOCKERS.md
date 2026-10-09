# Text input slot blockers (2026-10-09)

Retail Ghidra and split evidence; original slots retained. No matching or gameplay claim.

## TextInputTag::setText

Candidate `0xC8`; retail `0xBC`. Retained assembly.

```cpp
extern "C" SECTION(setText) void setText(TextInputTagState *self, char *text, unsigned int editOffset)
{
    resetTextInput(self);
    strncpy(self->m_text, text, 512);
    self->m_curEditOffset = editOffset;
    self->m_curRightOffset = editOffset;
    float width = ((const TextInputTagVtablePrefix *)self->base.vtable)->getSubstringPixelWidth(self, 0, editOffset);
    if (self->m_curEditOffset > 0 && width > self->m_maxWrap) {
        self->m_curLeftOffset = self->m_curEditOffset;
        do {
            --self->m_curLeftOffset;
            width = ((const TextInputTagVtablePrefix *)self->base.vtable)->getSubstringPixelWidth(self, self->m_curLeftOffset, self->m_curEditOffset);
        } while (width < self->m_maxWrap);
    }
}
```

## TextInputTag::scrollTextRightToFillWindow

Candidate `0x18C`; retail `0x180`. Retained assembly.

```cpp
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
```

## TextInputTag::drawCursor

Candidate `0x154`; retail `0x144`. Retained assembly.

```cpp
extern "C" SECTION(drawCursor) void drawCursor(TextInputTagState *self, CDrawContextBase *draw, int visible)
{
    if (!visible) return;
    SVTag *tag = &self->base;
    float x = tag->m_x + ((const TextInputTagVtablePrefix *)tag->vtable)->getSubstringPixelWidth(self, self->m_curLeftOffset, self->m_curEditOffset);
    unsigned int color = tag->m_bSelected ? self->m_highlightTextColor : self->m_textColor;
    float top;
    float bottom;
    float thickness;
    if (self->m_node == -1) {
        thickness = 3.0f;
        top = tag->m_y + 4.0f;
        bottom = tag->m_y + (tag->m_height - 2.0f);
        x += 6.0f;
    } else {
        float height = tag->m_height - 4.0f;
        top = tag->m_y - height * 0.5f;
        bottom = top + height;
        thickness = draw->vtable->GetStringWidth(draw, self->m_fontSize, svoTextInputCursorGlyph, 1) * 0.75f;
    }
    // Retail passes x again as the depth coordinate.
    draw->vtable->DrawLine(draw, tag->m_tagid, x, top, x, bottom, tag->m_x, thickness, color, 0);
}
```

## TextInputTag::handleSpecialKeys___dupe2

Candidate `0x300`; retail `0x2CC`. Retained assembly.

```cpp
extern "C" SECTION(handleSpecialKeys___dupe2) void handleSpecialKeys___dupe2(TextInputTagState *self, unsigned char key)
{
    size_t length = strlen(self->m_text);
    SVTag *tag = &self->base;
    CDrawContextBase *draw = tag->m_contexts->drawContext;
    CInputContextBaseState *input = tag->m_contexts->inputContext;
    if (key == 0x88 || key == 0x81 || key == 0x82) {
        int line = 0x1C0;
        if (key == 0x88) {
            SignalPluginEvent(GetInstance(), 10, tag);
            self->m_curEditOffset = UTF8_RemoveCharFromStringDELETE(self->m_text, self->m_curEditOffset);
            line = 0x187;
        }
        CPage *page = GetInstance()->m_pMainPage;
        if (!page->m_bIsActive) page = GetInstance()->m_pPopupPage;
        if (!draw) __SVO_Assert_Handler(svoTextInputTagSource, line);
        Navigate(tag, input, draw, tag->m_xml, page);
    } else if (key == 0x83 || key == 0x89) {
        if (key == 0x83) self->m_curEditOffset = UTF8_GetPrevCharIndexFromString(self->m_text, self->m_curEditOffset);
        else self->m_curEditOffset = UTF8_RemoveCharFromStringBACKSPACE(self->m_text, self->m_curEditOffset);
        scrollTextRightToFillWindow(self);
    } else if (key == 0x84 || key == 0x87) {
        if (key == 0x84) self->m_curEditOffset = UTF8_GetNextCharIndexFromString(self->m_text, self->m_curEditOffset);
        else self->m_curEditOffset = UTF8_RemoveCharFromStringDELETE(self->m_text, self->m_curEditOffset);
        scrollTextLeftToFillWindow(self);
    } else if (key == 0x85) {
        self->m_curEditOffset = 0;
        self->m_curLeftOffset = 0;
        self->m_curRightOffset = 0;
        float width;
        do {
            ++self->m_curRightOffset;
            width = ((const TextInputTagVtablePrefix *)tag->vtable)->getSubstringPixelWidth(self, 0, self->m_curRightOffset);
        } while (width < self->m_maxWrap && (long)self->m_curRightOffset < (long)length);
        while (width > self->m_maxWrap) {
            --self->m_curRightOffset;
            width = ((const TextInputTagVtablePrefix *)tag->vtable)->getSubstringPixelWidth(self, 0, self->m_curRightOffset);
        }
    } else if (key == 0x86) {
        int end = strlen(self->m_text);
        self->m_curRightOffset = end;
        self->m_curEditOffset = end;
        self->m_curLeftOffset = end;
        float width;
        do {
            --self->m_curLeftOffset;
            width = ((const TextInputTagVtablePrefix *)tag->vtable)->getSubstringPixelWidth(self, self->m_curLeftOffset, self->m_curEditOffset);
        } while (width < self->m_maxWrap && self->m_curLeftOffset > 0);
        while (width > self->m_maxWrap) {
            ++self->m_curLeftOffset;
            width = ((const TextInputTagVtablePrefix *)tag->vtable)->getSubstringPixelWidth(self, self->m_curLeftOffset, self->m_curRightOffset);
        }
    }
    input->specialKeyCode = 0;
}
```
