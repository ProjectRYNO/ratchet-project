# Select control slot blockers (2026-10-09)

Original slots preserved; candidates below were not integrated.

The Draw candidate's `SelectDrawVtable` is a scratch prefix with DrawSelect at
0x20. Its callback takes `(CDrawContextBase *, unsigned int, float, float, float,
float, float, unsigned int, unsigned int, unsigned int, int, char *, int, int,
int, char *)`. Recover that field in CDrawContextVtablePrefix only when integrating
a fitting candidate. Alphabet navigation uses the existing character table at
0x00191F01 and select-direction globals at 0x0016E580/0x0016E584.

## Draw___dupe13

Compiled 0x108; slot 0x100. Two extra floating-compare pipeline NOPs; correct callback banks and full args recovered; no slot widening. DrawSelect0x20 is not needed until this fits.

```cpp
extern "C" SECTION(Draw___dupe13) void Draw___dupe13(SelectTagState *tag)
{
    SVTag *base = &tag->base;
    CDrawContextBase *draw = base->m_contexts->drawContext;
    tag->m_text = getCurrOptionStrPtr(tag);
    decodeEntityText(tag->m_text);
    int length = strlen(tag->m_text);
    unsigned int text = tag->m_textColor;
    unsigned int line = base->m_lineColor;
    unsigned int fill = base->m_fillColor;
    if (base->m_bSelected) {
        text = tag->m_highlightTextColor;
        line = tag->m_highlightLineColor;
        fill = tag->m_highlightFillColor;
    }
    if (tag->m_displayLength > 0) length = TrimToFitDisplaySize(draw, tag->m_text, tag->m_displayLength, tag->m_fontSize);
    ((SelectDrawVtable *)draw->vtable)->DrawSelect(draw, base->m_tagid, base->m_x, base->m_y, base->m_z, base->m_width, base->m_height, text, line, fill, base->m_bSelected, tag->m_text, length, tag->m_fontSize, tag->m_align, base->m_tagClass);
}
```

## changeCurOptionToNextLetterInAlphabet

Compiled 0x154; slot 0x148. Preserves signed-char narrowing of starting letter but not each candidate letter (retail behavior), ctype base0x00191F01, direction globals; 12byte overrun retained ASM.

```cpp
extern "C" SECTION(changeCurOptionToNextLetterInAlphabet) void changeCurOptionToNextLetterInAlphabet(SelectTagState *tag, int direction)
{
    char initial = *getCurrOptionStrPtr(tag);
    int start = tag->m_currOptionIdx;
    if (svoCharacterTypes[(int)initial] & 1) initial += 32;
    for (;;) {
        advanceCurrOption(tag, direction);
        if (tag->m_currOptionIdx == start) {
            advanceCurrOption(tag, direction);
            return;
        }
        int letter = *getCurrOptionStrPtr(tag);
        if (svoCharacterTypes[letter] & 1) letter += 32;
        if (initial != letter) break;
    }
    if (direction == svoSelectPreviousDirection) {
        initial = *getCurrOptionStrPtr(tag);
        if (svoCharacterTypes[(int)initial] & 1) initial += 32;
        int letter;
        do {
            advanceCurrOption(tag, svoSelectPreviousDirection);
            letter = *getCurrOptionStrPtr(tag);
            if (svoCharacterTypes[letter] & 1) letter += 32;
        } while (initial == letter);
        advanceCurrOption(tag, svoSelectNextDirection);
    }
}
```
