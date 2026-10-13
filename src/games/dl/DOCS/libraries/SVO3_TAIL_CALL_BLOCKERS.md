# SVO3 compiler blockers: tail calls (2026-10-12)

> **Resolved 2026-10-13.** The user chose SCE ee-gcc 2.96-ee-001003-1 for SVO3
> (DECISIONS.md K07). Every function listed below is now compiled within its slot.
> The table and bodies are kept as historical evidence for the toolchain choice.

Retail Ghidra, split instructions and EE compiler probes. Original slots retained.
No matching or gameplay claim.

## Root cause

Retail SVO3 ends many functions with a tail jump. The return address is restored
and control jumps directly to the callee, e.g. `GetEditPosition___dupe2` at 0x01EFCB84:

```text
addiu sp,sp,-0x10
addiu a0,a0,0xB8
sd    ra,0x0(sp)
ld    ra,0x0(sp)
j     strlen
addiu sp,sp,0x10   # delay slot
```

The project compiler, ps2dev `ee-gcc (GCC) 3.2.3`, never emits a MIPS sibling call.
A probe of `unsigned f(char *p) { return strlen(p + 0xB8); }` produced `jal` plus
`jr ra` under `-O2`, `-O2 -foptimize-sibling-calls`, `-Os` and `-O3`. Each tail call
therefore costs at least one extra instruction, and a wrapper can never fit its slot.
Other overruns of a few bytes come from the same compiler-generation gap
(register allocation, frame layout, branch-likely use).

The neighbouring UYA project independently concluded that Insomniac retail code was
built with SN Systems ProDG EE GCC 2.95.x (`uya_decomp_local/decomp_notes/retail_toolchain_identification.md`;
confirmed there by `sq`/`lq` callee-save frames, which 3.2.3 never emits). Whether
ProDG 2.95.x reproduces these tail jumps has **not** been tested for Deadlocked.

## Compiler probe (2026-10-12)

SVO3 retail spills callee-saved registers with `sd` and never `sq` (0 of 1,703 saves),
unlike Insomniac game code, so the ProDG 2.95 lead does not fit this library. Three
Sony EE compilers from the decomp.me archive (`decompme/compilers` releases) were run
in a throwaway i386 container on the recovered C++ bodies (`-G0 -O2 -fno-exceptions`):

| Compiler | Tail-call shape | GetEditPosition (0x18) | getSubstringPixelWidth (0x24) | getImageTypeAttrib (0x8C) |
| --- | --- | --- | --- | --- |
| ps2dev 3.2.3 (current) | no | 0x1C, no | 0x2C, no | fits, differs |
| SCE 3.2-ee-040921 | yes | identical | differs (extra move, $14/$15) | differs |
| **SCE 2.96-ee-001003-1** | **yes** | **byte-identical** | **byte-identical** | same size; prologue store order and one delay-slot fill differ with source shape |

`2.96-ee-001003-1` reproduces retail register allocation, branch-likely use and the
retained-frame tail jump. It is the leading candidate for SVO3. `3.2-ee-030926` did not
run (32-bit stat failure on its specs file). Probe sources and outputs:
`build/compiler-probe/dl/` (ignored). Adopting a compiler is a toolchain change: the
binaries are 32-bit Linux and need i386 runtime support in the build image. Do not
commit the compiler archives.

## Remaining SVO3 functions ending in a retail tail jump

| Module | Function |
| --- | --- |
| BrowserInitTag | BrowserInitTag |
| CDrawContextBase | TrimToFitDisplaySize |
| CHttp | operator.new___dupe4 |
| CPage | doPost |
| CPage | getTopOfHistory |
| CPage | operator.new___dupe3 |
| CPluginManager | CPluginManager |
| CPluginManager | operator.new___dupe11 |
| HttpSecure | HTTPS_Malloc |
| LineTag | LineTag |
| LogoutTag | LogoutTag |
| PageHistory | PageHistory |
| SVBrowser | SV_IKS_Malloc |
| SVBrowser | URIStoreFind |
| SVBrowser | ReturnFromGame |
| SVChronograph | operator.new___dupe5 |
| SVDownloadManager | operator.new___dupe13 |
| SVFileDownloadQueue | operator.new___dupe14 |
| SVSock | operator.new___dupe9 |
| SVTag | operator.new___dupe8 |
| SVTag | SVTag |
| SVTagModule | operator.new___dupe7 |
| SVTagModuleList | operator.new___dupe6 |
| SVURIStore | operator.new___dupe10 |
| SubmitInputTag | SubmitInputTag |
| TextInputTag | GetEditPosition___dupe2 |
| TextInputTag | getSubstringPixelWidth |
| URISchemeMgr | Register |
| URISchemeMgr | CURISchemeMgr |

With ee-gcc 3.2.3 these cannot fit without slot widening, which is not permitted.

## Recovered bodies retained as assembly

These bodies were written in the 2026-10-09 continuation and checked against retail
Ghidra. Each overruns its slot and stays `INCLUDE_ASM`. `HandleInput___dupe34`
is newly recorded; the rest supersede earlier candidates in the TARGET, TEXT_INPUT,
TEXT_AREA, GRID_LIST and 75 blocker documents.

### TextInputTag::setText

Candidate `0xC8`; retail `0xBC`.

```cpp
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
```

### TextInputTag::GetEditPosition___dupe2

Candidate `0x1C`; retail `0x18`.

```cpp
extern "C" SECTION(GetEditPosition___dupe2) unsigned int GetEditPosition___dupe2(TextInputTagState *tag)
{
    return strlen(tag->m_text);
}
```

### TextInputTag::getSubstringPixelWidth

Candidate `0x2C`; retail `0x24`.

```cpp
extern "C" SECTION(getSubstringPixelWidth) float getSubstringPixelWidth(TextInputTagState *tag, int left, int right)
{
    return getSubstringPixelWidthImpl(tag, tag->m_text, left, right);
}
```

### TextAreaTag::UpdateCursorPosition

Candidate `0xDC`; retail `0xD4`.

```cpp
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
```

### TextAreaTag::DrawCursor

Candidate `0x74`; retail `0x6C`.

```cpp
extern "C" SECTION(DrawCursor) void DrawCursor(TextAreaTagState *tag, CDrawContextBase *draw, int enabled)
{
    if (enabled) {
        unsigned int color = tag->base.m_bSelected ? tag->m_highlightTextColor : tag->m_textColor;
        float y = tag->m_cursorY + tag->m_yAxisPadValue;
        draw->vtable->DrawLine(draw, tag->base.m_tagid, tag->m_cursorX, y, tag->m_cursorX,
            y + tag->m_lineSpacing, tag->base.m_x, 2.0f, color, 0);
    }
}
```

### TextTag::HandleInput___dupe34

Candidate `0x19C`; retail `0x190`.

```cpp
extern "C" SECTION(HandleInput___dupe34) int HandleInput___dupe34(TextTagState *tag, CPage *page)
{
    CInputContextBaseState *input = tag->base.m_contexts->inputContext;
    if (!tag->base.m_xml) __SVO_Assert_Handler(svoTextTagSource, 0x71);
    if (!input) __SVO_Assert_Handler(svoTextTagSource, 0x72);
    if (!page) __SVO_Assert_Handler(svoTextTagSource, 0x73);
    if (!tag->base.vtable->IsSelected(&tag->base)) return 1;
    if (HasActionOccurred(input, 0x11, SV_ACTION_ACTIVATE) && !page->m_state && tag->m_link && *tag->m_link) {
        followLink(page, tag->m_link, tag->m_linkOption);
        return 0;
    }
    if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_UP) ||
        HasActionOccurred(input, 0x11, SV_ACTION_NAV_DOWN) ||
        HasActionOccurred(input, 0x11, SV_ACTION_NAV_LEFT) ||
        HasActionOccurred(input, 0x11, SV_ACTION_NAV_RIGHT)) {
        CDrawContextBase *draw = tag->base.m_contexts->drawContext;
        if (!draw) __SVO_Assert_Handler(svoTextTagSource, 0x8B);
        return !Navigate(&tag->base, input, draw, tag->base.m_xml, page);
    }
    return 1;
}
```

### GridTag::CalculateGridHeight

Candidate `0xB0`; retail `0xA8`.

```cpp
extern "C" SECTION(CalculateGridHeight) void CalculateGridHeight(GridTagState *tag)
{
    float y = tag->base.m_y + tag->m_headerHeight;
    tag->base.m_height = tag->m_headerHeight;
    for (int i = 0; i < tag->m_origNumVisRows; ++i) {
        SVGridRow *row = &tag->m_rows[i];
        row->row_y = y;
        tag->base.m_height += row->height;
        y += row->height;
        if (y != tag->base.m_height + tag->base.m_y) __SVO_Assert_Handler(svoGridTagSource, 0x423);
    }
}
```

### GridTag::HandleColumnShuffling

Candidate `0x130`; retail `0x12C`.

```cpp
extern "C" SECTION(HandleColumnShuffling) void HandleColumnShuffling(GridTagState *tag, int leftmostCol)
{
    if (leftmostCol < 0) __SVO_Assert_Handler(svoGridTagSource, 0x6CB);
    if (leftmostCol > tag->m_numTotalColumns - tag->m_numVisColumns + tag->m_numLockedColumns)
        __SVO_Assert_Handler(svoGridTagSource, 0x6CC);
    for (int i = 0; i < tag->m_numLockedColumns; ++i)
        if (tag->m_columnIndexes[i] != i) __SVO_Assert_Handler(svoGridTagSource, 0x6D2);
    for (int i = tag->m_numLockedColumns; i < tag->m_numVisColumns; ++i) {
        if (i + leftmostCol - tag->m_numLockedColumns >= tag->m_numTotalColumns)
            __SVO_Assert_Handler(svoGridTagSource, 0x6D8);
        tag->m_columnIndexes[i] = i + leftmostCol - tag->m_numLockedColumns;
    }
}
```
