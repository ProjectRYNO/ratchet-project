# Text-area slot blockers (2026-10-09)

Retail Ghidra and split evidence; original slots retained. No matching or gameplay claim.

## TextAreaTag::DrawCursor

Candidate `0x74`; retail `0x6C`. Retained assembly.

```cpp
extern "C" SECTION(DrawCursor) void DrawCursor(TextAreaTagState *tag, CDrawContextBase *draw, int visible)
{
    if (visible) {
        unsigned int color = tag->base.m_bSelected ? tag->m_highlightTextColor : tag->m_textColor;
        float y = tag->m_cursorY + tag->m_yAxisPadValue;
        draw->vtable->DrawLine(draw, tag->base.m_tagid, tag->m_cursorX, y, tag->m_cursorX, y + tag->m_lineSpacing, tag->base.m_x, 2.0f, color, 0);
    }
}
```

## TextAreaTag::UpdateCursorPosition

Candidate `0xDC`; retail `0xD4`. Retained assembly.

```cpp
extern "C" SECTION(UpdateCursorPosition) void UpdateCursorPosition(TextAreaTagState *tag, CDrawContextBase *draw)
{
    tag->m_cursorY = tag->base.m_y + (float)(tag->m_curLine - tag->m_minDisplayLine) * tag->m_lineSpacing - 2.0f;
    if (tag->m_curEditOffset > tag->m_maxTextSize) {
        if (tag->m_curLine < 0) tag->m_curLine = 0;
        tag->m_curEditOffset = tag->m_textLines[tag->m_curLine].lineEndIndex;
    }
    tag->m_cursorX = tag->base.m_x + GetSubstringPixelWidth(tag, draw, tag->m_text, tag->m_textLines[tag->m_curLine].lineStartIndex, tag->m_curEditOffset) + 7.0f;
    SetArrowOffsets(tag);
}
```
