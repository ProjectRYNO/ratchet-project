

#include "CInputContextBase.h"
#include "CPage.h"
#include "CAudioContextBase.h"
#include "SVOString.h"
#include "HttpUtils.h"
#include "GridTag.h"
#include "TagUtils.h"
#include "string.h"
#include "CMemoryContextBase.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_GridTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern "C" {
CMemoryContextBaseState *GetMemoryContext(void);
extern char svoGridTagSource[];
extern const SVTagVtablePrefix svoGridTagVtable;
extern unsigned int svoNextTagId;
long ClearRows(GridTagState *);
void FreeResources___dupe36(GridTagState *);
void ResetIndexArray(GridTagState *);

}
extern "C" {
extern char svoGridRowsName[];
extern char svoGridColumnsName[];
extern char svoGridRowName[];
extern char svoGridRecordRowName[];
extern char svoGridColumnName[];
long GetCurrentSelectedCell(GridTagState *, SVGridCell **);
void HandleColumnShuffling(GridTagState *, int);
void AlignVisibleColumns(GridTagState *);
void CalculateGridHeight(GridTagState *);
void initSVGridRow(GridTagState *, SVGridRow *);
long ParseRows(GridTagState *, iks *);
long ParseColumns(GridTagState *, iks *);
long ParseSingleRow(GridTagState *, iks *, int);
long ParseSingleColumn(GridTagState *, iks *);
long ParseGridHeader(GridTagState *, iks *);

}
extern "C" {
extern char svoGridClassAttribute[];
extern char svoGridTooltipAttribute[];
extern char svoGridColWidthAttribute[];
extern char svoGridRowHeightAttribute[];
extern char svoGridTextColorAttribute[];
extern char svoGridLineColorAttribute[];
extern char svoGridFillColorAttribute[];
extern char svoGridHighlightTextAttribute[];
extern char svoGridHighlightLineAttribute[];
extern char svoGridHighlightFillAttribute[];
extern char svoGridRecordSpaceAttribute[];
extern char svoGridCellName[];
extern char svoGridLinkAttribute[];
extern char svoGridLinkOptionAttribute[];
extern char svoGridAlignAttribute[];
extern char svoGridHeightAttribute[];
extern char svoGridFontSizeAttribute[];
extern int g_rowNumParseCntr;
extern int g_colNumParseCntr;
long ParseSingleCell(GridTagState *, iks *, SVGridCell *);

}
extern "C" {
extern char svoGridTagName[];
}
extern "C" {
long Navigate(SVTag *, CInputContextBaseState *, CDrawContextBase *, iks *, CPage *);
CAudioContextBaseState *GetAudioContext();
extern char svoGridEmptyLink[];
extern char svoGridAudioClass[];
}
extern "C" {
void ChangeSelectedCell(GridTagState *, int);
void AdvanceCurrTopRow(GridTagState *, int, int);
}
extern "C" {
void ChangeSelectedColumn(GridTagState *, int);
}
#define SECTION(name) __attribute__((section(".svo_GridTag_" #name)))

extern "C" SECTION(ClearRows) long ClearRows(GridTagState *tag)
{
    tag->base.m_bSelectable = 0;
    for (int i = 0; i < tag->m_numTotalRows; ++i)
        svFreeSafe(tag->base.m_contexts->memoryContext, tag->m_cells[i]);
    if (tag->m_numTotalRows > 0) {
        svFreeSafe(tag->base.m_contexts->memoryContext, tag->m_cells);
        tag->m_cells = 0;
        svFreeSafe(tag->base.m_contexts->memoryContext, tag->m_rows);
        tag->m_rows = 0;
        tag->m_numVisRowsWithCells = 0;
        tag->m_numTotalRows = 0;
    }
    return 1;
}

extern "C" SECTION(FreeResources___dupe36) void FreeResources___dupe36(GridTagState *tag)
{
    ClearRows(tag);
    svFreeSafe(tag->base.m_contexts->memoryContext, tag->m_columns);
    if (tag->m_columnIndexes) svFreeSafe(tag->base.m_contexts->memoryContext, tag->m_columnIndexes);
    if (tag->m_myRecordRow) {
        if (tag->m_myRecordRow->cells) svFreeSafe(tag->base.m_contexts->memoryContext, tag->m_myRecordRow->cells);
        svFreeSafe(tag->base.m_contexts->memoryContext, tag->m_myRecordRow);
    }
    if (tag->m_pTimer) _SVChronograph(tag->m_pTimer, 3);
}

extern "C" SECTION(DefaultInit___dupe18) void DefaultInit___dupe18(GridTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoGridTagName, 64);
    tag->m_borderOutlineColor = 0xFF000000;
    tag->m_borderFillColor = 0xFFFFFFFF;
    tag->m_borderHighlightOutlineColor = 0xFFFFFFFF;
    tag->m_borderHighlightFillColor = 0xFFFFFF00;
    tag->m_cells = 0;
    tag->m_currCellColNum = 15;
    tag->m_columns = 0;
    tag->m_rows = 0;
    tag->m_myRecordRow = 0;
    tag->base.m_width = 0;
    tag->base.m_height = 0;
    tag->m_currTopRow = 0;
    tag->base.m_bSelected = 0;
    tag->m_headerSelected = 0;
    tag->m_numTotalColumns = 0;
    tag->m_numVisColumns = 0;
    tag->m_numLockedColumns = 0;
    tag->m_columnIndexes = 0;
    tag->m_borderWidth = 0;
    tag->m_borderHeight = 0;
    tag->m_borderClass = 0;
    tag->m_currCellRowNum = 0;
    tag->m_numVisRowsWithCells = 0;
    tag->m_numTotalRows = 0;
    SVChronographState *timer = (SVChronographState *)SVChronographNew(16);
    SVChronograph(timer, 0);
    tag->m_pTimer = timer;
    Start___dupe3(timer);
    tag->m_defCellTextColor = 0xFFFFFFFF;
    tag->m_highlightCellFillColor = 0xFFFFFF00;
    tag->m_headerHighlightTextColor = 0xFFFFFFFF;
    tag->m_headerHighlightFillColor = 0xFF000000;
    tag->m_defCellFillColor = 0xFF000000;
    tag->m_highlightCellTextColor = 0xFF000000;
    tag->m_highlightCellLineColor = 0xFF000000;
    tag->m_headerTextColor = 0xFF000000;
    tag->m_headerLineColor = 0xFFFFFFFF;
    tag->m_defCellLineColor = 0xFF0000FF;
    tag->m_headerHighlightLineColor = 0xFF7F7F7F;
    tag->m_defCellFontSize = 14;
    tag->m_headerFillColor = 0xFF7F7F7F;
    tag->m_defCellAlign = 1;
    g_colNumParseCntr = 0;
    g_rowNumParseCntr = 0;
    tag->m_horz_sb_height = 15.0f;
    tag->base.m_bSelectable = 1;
    tag->m_bIsClickedIn = 0;
    tag->m_defaultColWidth = 0;
    tag->m_defaultRowHeight = 0;
    tag->m_spaceBetweenLastRowAndMyRecord = 0;
    tag->m_vert_sb_width = 15.0f;
    tag->m_scrollbar_class = 0;
    tag->m_bVerticalWrapAllowed = 0;
    tag->m_bSideWrapAllowed = 0;
    tag->m_bIsModalGrid = 0;

}

extern "C" SECTION(_GridTag) void _GridTag(GridTagState *tag, unsigned int flags)
{
    tag->base.vtable = &svoGridTagVtable;
    FreeResources___dupe36(tag);
    tag->base.vtable = &svoTagVtable;
    if (flags & 1) SVTagDelete(&tag->base);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GridTag", GridTag);

extern "C" SECTION(HasNavigationOccured) long HasNavigationOccured(GridTagState *tag, CPage *page)
{
    CInputContextBaseState *input = tag->base.m_contexts->inputContext;
    if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_UP) ||
        HasActionOccurred(input, 0x11, SV_ACTION_NAV_DOWN) ||
        HasActionOccurred(input, 0x11, SV_ACTION_NAV_RIGHT) ||
        HasActionOccurred(input, 0x11, SV_ACTION_NAV_LEFT)) {
        CDrawContextBase *draw = tag->base.m_contexts->drawContext;
        if (!draw) __SVO_Assert_Handler(svoGridTagSource, 0x16D);
        return Navigate(&tag->base, input, draw, tag->base.m_xml, page);
    }
    return 0;
}

extern "C" SECTION(FollowLink) void FollowLink(GridTagState *tag, CPage *page)
{
    if (page->m_state) return;
    SVGridCell *cell;
    GetCurrentSelectedCell(tag, &cell);
    if (cell) {
        if (cell->cell_link && strcmp(cell->cell_link, svoGridEmptyLink)) {
            CAudioContextBaseState *audio = GetAudioContext();
            ((const CAudioContextVtablePrefix *)audio->vtable)->Play(audio, 1, svoGridAudioClass);
            followLink(page, cell->cell_link, cell->linkOption);
        }
    } else {
        char *link = tag->m_columns[tag->m_currCellColNum].colHdrLink;
        if (link && strcmp(link, svoGridEmptyLink)) {
            CAudioContextBaseState *audio = GetAudioContext();
            ((const CAudioContextVtablePrefix *)audio->vtable)->Play(audio, 1, svoGridAudioClass);
            followLink(page, tag->m_columns[tag->m_currCellColNum].colHdrLink, 0);
        }
    }
}

extern "C" SECTION(HandleModalInput) int HandleModalInput(GridTagState *tag, CPage *page)
{
    CInputContextBaseState *input = tag->base.m_contexts->inputContext;
    if (!tag->m_bIsClickedIn) {
        if (HasNavigationOccured(tag, page)) return 0;
        if (tag->m_numVisRowsWithCells < 1) return 1;
        if (HasActionOccurred(input, 0x11, SV_ACTION_ACTIVATE)) {
            tag->m_bIsClickedIn = 1;
            return 0;
        }
        return 1;
    }
    if (HasActionOccurred(input, 0x11, SV_ACTION_BACK)) {
        tag->m_bIsClickedIn = 0;
        return 0;
    }
    int direction;
    if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_LEFT)) direction = -2;
    else if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_RIGHT)) direction = 2;
    else if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_UP)) direction = -1;
    else if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_DOWN)) direction = 1;
    else {
        if (HasActionOccurred(input, 0x11, SV_ACTION_ACTIVATE)) {
            FollowLink(tag, page);
            return 0;
        }
        if (HasActionOccurred(input, 0x11, SV_ACTION_SCROLL_DOWN)) direction = 1;
        else if (HasActionOccurred(input, 0x11, SV_ACTION_SCROLL_UP)) direction = -1;
        else return 1;
        AdvanceCurrTopRow(tag, direction, 1);
        return 0;
    }
    ChangeSelectedCell(tag, direction);
    return 0;
}

extern "C" SECTION(HandleInput___dupe50) int HandleInput___dupe50(GridTagState *tag, CPage *page)
{
    CInputContextBaseState *input = tag->base.m_contexts->inputContext;
    if (!tag->base.m_xml) __SVO_Assert_Handler(svoGridTagSource, 0x1F4);
    if (!input) __SVO_Assert_Handler(svoGridTagSource, 0x1F5);
    if (!page) __SVO_Assert_Handler(svoGridTagSource, 0x1F6);
    if (!tag->base.vtable->IsSelected(&tag->base)) return 1;
    if (tag->m_bIsModalGrid) return HandleModalInput(tag, page);
    if (HasNavigationOccured(tag, page)) return 0;
    if (tag->m_numVisRowsWithCells < 1) return 1;
    int action = HasActionOccurred(input, 0x11, SV_ACTION_SELECT_LEFT);
    if (!action) action = HasActionOccurred(input, 0x11, SV_ACTION_SELECT_RIGHT);
    if (action && ElapsedMS(tag->m_pTimer) > 250) {
        int magnitude = action < 0 ? -action : action;
        if (magnitude > 45) {
            Reset___dupe5(tag->m_pTimer);
            ChangeSelectedCell(tag, action > 0 ? 2 : -2);
            return 0;
        }
    }
    action = HasActionOccurred(input, 0x11, SV_ACTION_SELECT_UP);
    if (!action) action = HasActionOccurred(input, 0x11, SV_ACTION_SELECT_DOWN);
    if (action && ElapsedMS(tag->m_pTimer) > 250) {
        int magnitude = action < 0 ? -action : action;
        if (magnitude > 45) {
            Reset___dupe5(tag->m_pTimer);
            ChangeSelectedCell(tag, action < 0 ? -1 : 1);
            return 0;
        }
    }
    if (HasActionOccurred(input, 0x11, SV_ACTION_ACTIVATE)) FollowLink(tag, page);
    else {
        int direction;
        if (HasActionOccurred(input, 0x11, SV_ACTION_SCROLL_DOWN)) direction = 1;
        else if (HasActionOccurred(input, 0x11, SV_ACTION_SCROLL_UP)) direction = -1;
        else return 1;
        AdvanceCurrTopRow(tag, direction, 1);
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GridTag", Draw___dupe23);

extern "C" SECTION(InitGridCells) long InitGridCells(GridTagState *tag)
{
    if (tag->m_cells) __SVO_Assert_Handler(svoGridTagSource, 0x3A5);
    if (tag->m_numTotalRows <= 0) return 1;
    CMemoryContextBaseState *memory = GetMemoryContext();
    tag->m_cells = (SVGridCell **)svAllocSafe(memory, (unsigned int)tag->m_numTotalRows * 4, 0, 0x3AE, svoGridTagSource);
    if (!tag->m_cells) { __SVO_Assert_Handler(svoGridTagSource, 0x3B1); return 0; }
    for (int i = 0; i < tag->m_numTotalRows; ++i) {
        memory = GetMemoryContext();
        SVGridCell *row = (SVGridCell *)svAllocSafe(memory, (unsigned int)tag->m_numTotalColumns * 0x18, 0, 0x3B8, svoGridTagSource);
        tag->m_cells[i] = row;
        if (!row) { __SVO_Assert_Handler(svoGridTagSource, 0x3BB); return 0; }
        memset(row, 0, tag->m_numTotalColumns * 0x18);
    }
    return 1;
}

extern "C" SECTION(FindAndSetSelectedCell) long FindAndSetSelectedCell(GridTagState *tag)
{
    for (int row = 0; row < tag->m_numVisRowsWithCells; ++row) {
        for (int col = 0; col < tag->m_numVisColumns; ++col) {
            if (tag->m_cells[row][col].cell_link) {
                tag->m_currCellRowNum = row;
                tag->base.m_bSelectable = 1;
                tag->m_currCellColNum = col;
                return 1;
            }
        }
    }
    for (int col = 0; col < tag->m_numVisColumns; ++col) {
        if (tag->m_columns[col].colHdrLink) {
            tag->base.m_bSelectable = 1;
            tag->m_currCellRowNum = -1;
            tag->m_currCellColNum = col;
            return 1;
        }
    }
    tag->base.m_bSelectable = 0;
    return 0;
}

extern "C" SECTION(InitRowsAndColumns) long InitRowsAndColumns(GridTagState *tag)
{
    if (!iks_has_children(tag->base.m_xml)) __SVO_Assert_Handler(svoGridTagSource, 0x3F0);
    for (iks *child = iks_child(tag->base.m_xml); child; child = iks_next(child)) {
        char *name = iks_name(child);
        if (!name) continue;
        if (!strcmp(name, svoGridRowsName)) {
            if (tag->m_numTotalRows > 0 || tag->m_origNumVisRows > 0) ParseRows(tag, child);
        } else if (!strcmp(name, svoGridColumnsName)) ParseColumns(tag, child);
        else __SVO_Assert_Handler(svoGridTagSource, 0x409);
    }
    CalculateGridHeight(tag);
    AlignVisibleColumns(tag);
    return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GridTag", CalculateGridHeight);

extern "C" SECTION(initSVGridRow) void initSVGridRow(GridTagState *tag, SVGridRow *row)
{
    row->height = tag->m_defaultRowHeight;
    unsigned int id = svoNextTagId;
    row->rowClass = 0;
    svoNextTagId = id + 1;
    row->row_tagID = id;
}

extern "C" SECTION(ParseRows) long ParseRows(GridTagState *tag, iks *xml)
{
    int count = tag->m_origNumVisRows;
    if (count < tag->m_numTotalRows) count = tag->m_numTotalRows;
    if (count > 0) {
        tag->m_rows = (SVGridRow *)svAllocSafe(GetMemoryContext(), (unsigned int)count * 16, 0, 0x439, svoGridTagSource);
        for (int i = 0; i < count; ++i) initSVGridRow(tag, &tag->m_rows[i]);
    }
    if (!iks_has_children(xml)) __SVO_Assert_Handler(svoGridTagSource, 0x442);
    for (iks *child = iks_child(xml); child; child = iks_next(child)) {
        char *name = iks_name(child);
        if (!name) continue;
        if (!strcmp(name, svoGridRowName)) ParseSingleRow(tag, child, 0);
        else if (!strcmp(name, svoGridRecordRowName)) {
            if (tag->m_myRecordRow) {
                svFreeSafe(tag->base.m_contexts->memoryContext, tag->m_myRecordRow->cells);
                svFreeSafe(tag->base.m_contexts->memoryContext, tag->m_myRecordRow);
                __SVO_Assert_Handler(svoGridTagSource, 0x458);
            }
            tag->m_myRecordRow = (SVMyRecordRow *)svAllocSafe(GetMemoryContext(), 0x18, 0, 0x45C, svoGridTagSource);
            CMemoryContextBaseState *memory = GetMemoryContext();
            SVGridCell *cells = (SVGridCell *)svAllocSafe(memory, (unsigned int)tag->m_numTotalColumns * 0x18, 0, 0x45F, svoGridTagSource);
            tag->m_myRecordRow->textColor = 0xFFFFFFFF;
            tag->m_myRecordRow->cells = cells;
            tag->m_myRecordRow->row.height = tag->m_defaultRowHeight;
            tag->m_myRecordRow->row.rowClass = 0;
            ParseSingleRow(tag, child, 1);
        }
    }
    return 1;
}

extern "C" SECTION(ParseSingleRow) long ParseSingleRow(GridTagState *tag, iks *xml, int record)
{
    if (tag->m_numTotalRows <= 0) return 1;
    SVGridRow *row;
    if (!record) row = &tag->m_rows[g_rowNumParseCntr];
    else {
        row = &tag->m_myRecordRow->row;
        getFloatAttrib(xml, svoGridRecordSpaceAttribute, &tag->m_spaceBetweenLastRowAndMyRecord);
        getColorAttrib(xml, svoGridTextColorAttribute, &tag->m_myRecordRow->textColor);
    }
    if (!xml) { __SVO_Assert_Handler(svoGridTagSource, 0x48A); return 0; }
    int col = 0;
    getFloatAttrib(xml, svoGridRowHeightAttribute, &row->height);
    row->rowClass = iks_find_attrib(xml, svoGridClassAttribute);
    for (iks *child = iks_child(xml); child; child = iks_next(child)) {
        char *name = iks_name(child);
        if (!name || strcmp(name, svoGridCellName)) continue;
        if (record || g_rowNumParseCntr < tag->m_numTotalRows) {
            if (col < tag->m_numTotalColumns) {
                SVGridCell *cells = record ? tag->m_myRecordRow->cells : tag->m_cells[g_rowNumParseCntr];
                ParseSingleCell(tag, child, &cells[col++]);
            } else __SVO_Assert_Handler(svoGridTagSource, 0x4B4);
        } else if (!record) __SVO_Assert_Handler(svoGridTagSource, 0x4BA);
    }
    if (!record) g_rowNumParseCntr = (unsigned int)g_rowNumParseCntr + 1;
    return 1;
}

extern "C" SECTION(ParseColumns) long ParseColumns(GridTagState *tag, iks *xml)
{
    CMemoryContextBaseState *memory = GetMemoryContext();
    SVGridColumn *column = (SVGridColumn *)svAllocSafe(memory, (unsigned int)tag->m_numTotalColumns * 32, 0, 0x4D5, svoGridTagSource);
    tag->m_columns = column;
    for (int i = 0; i < tag->m_numTotalColumns; ++i, ++column) {
        column->colAlign = tag->m_defCellAlign;
        column->width = tag->m_defaultColWidth;
        column->colName = 0;
        column->linkOption = 0;
    }
    ParseGridHeader(tag, xml);
    if (!iks_has_children(xml)) __SVO_Assert_Handler(svoGridTagSource, 0x4E3);
    for (iks *child = iks_child(xml); child; child = iks_next(child)) {
        char *name = iks_name(child);
        if (name && !strcmp(name, svoGridColumnName)) ParseSingleColumn(tag, child);
    }
    return 1;
}

extern "C" SECTION(ParseSingleColumn) long ParseSingleColumn(GridTagState *tag, iks *xml)
{
    if (!xml) { __SVO_Assert_Handler(svoGridTagSource, 0x503); return 0; }
    getFloatAttrib(xml, svoGridColWidthAttribute, &tag->m_columns[g_colNumParseCntr].width);
    char *text = iks_cdata(iks_child(xml));
    tag->m_columns[g_colNumParseCntr].colName = text;
    tag->m_columns[g_colNumParseCntr].colHdrLink = 0;
    char *link = iks_find_attrib(xml, svoGridLinkAttribute);
    tag->m_columns[g_colNumParseCntr].colHdrLink = link;
    unsigned int option;
    getLinkOptionAttrib(xml, svoGridLinkOptionAttribute, &option);
    tag->m_columns[g_colNumParseCntr].linkOption = option;
    tag->m_columns[g_colNumParseCntr].isSelectable = tag->m_columns[g_colNumParseCntr].colHdrLink != 0;
    char *tooltip = iks_find_attrib(xml, svoGridTooltipAttribute);
    tag->m_columns[g_colNumParseCntr].colTooltip = tooltip;
    getAlignAttrib(xml, svoGridAlignAttribute, &tag->m_columns[g_colNumParseCntr].colAlign);
    if (tag->m_columns[g_colNumParseCntr].isSelectable) {
        decodeEntityText(tag->m_columns[g_colNumParseCntr].colHdrLink);
        if (g_colNumParseCntr < tag->m_currCellColNum) tag->m_currCellColNum = g_colNumParseCntr;
    }
    g_colNumParseCntr = (unsigned int)g_colNumParseCntr + 1;
    return 1;
}

extern "C" SECTION(ParseGridHeader) long ParseGridHeader(GridTagState *tag, iks *xml)
{
    if (!xml) { __SVO_Assert_Handler(svoGridTagSource, 0x530); return 0; }
    getFloatAttrib(xml, svoGridHeightAttribute, &tag->m_headerHeight);
    getIntAttrib(xml, svoGridFontSizeAttribute, &tag->m_headerFontSize);
    getColorAttrib(xml, svoGridLineColorAttribute, &tag->m_headerLineColor);
    getColorAttrib(xml, svoGridHighlightLineAttribute, &tag->m_headerHighlightLineColor);
    getColorAttrib(xml, svoGridTextColorAttribute, &tag->m_headerTextColor);
    getColorAttrib(xml, svoGridHighlightTextAttribute, &tag->m_headerHighlightTextColor);
    getColorAttrib(xml, svoGridFillColorAttribute, &tag->m_headerFillColor);
    // Retail writes highlightFillColor into the highlight-line field too.
    getColorAttrib(xml, svoGridHighlightFillAttribute, &tag->m_headerHighlightLineColor);
    tag->m_headerClass = iks_find_attrib(xml, svoGridClassAttribute);
    unsigned int id = svoNextTagId;
    svoNextTagId = id + 1;
    tag->m_header_tagID = id;
    return 1;
}

extern "C" SECTION(ParseSingleCell) long ParseSingleCell(GridTagState *tag, iks *xml, SVGridCell *cell)
{
    if (!xml || !cell) {
        __SVO_Assert_Handler(svoGridTagSource, 0x549);
        return 0;
    }
    cell->cell_tagID = svoNextTagId++;
    cell->cellClass = iks_find_attrib(xml, svoGridClassAttribute);
    if (iks_has_children(xml)) {
        if (iks_has_children(xml)) cell->cell_text = iks_cdata(iks_child(xml));
        else cell->cell_text = 0;
        cell->cell_link = iks_find_attrib(xml, svoGridLinkAttribute);
        if (tag->base.m_toolTipTagName) cell->cell_tooltip = iks_find_attrib(xml, svoGridTooltipAttribute);
        if (cell->cell_link) decodeEntityText(cell->cell_link);
        char *tagClass = iks_find_attrib(xml, svoGridClassAttribute);
        cell->linkOption = 0;
        cell->cellClass = tagClass;
        getLinkOptionAttrib(xml, svoGridLinkOptionAttribute, (unsigned int *)&cell->linkOption);
    }
    return 1;
}

extern "C" SECTION(AdvanceCurrTopRow) void AdvanceCurrTopRow(GridTagState *tag, int direction, int records)
{
    if (direction == -1) {
        int top = tag->m_currTopRow - records;
        tag->m_currTopRow = top < 0 ? 0 : top;
    } else if (direction == 1) {
        int top = tag->m_currTopRow + records;
        int limit = tag->m_numTotalRows - tag->m_numVisRowsWithCells;
        tag->m_currTopRow = top < limit ? top : limit;
    }
}

extern "C" SECTION(GetCurrentSelectedCell) long GetCurrentSelectedCell(GridTagState *tag, SVGridCell **cell)
{
    if (!tag->m_cells) __SVO_Assert_Handler(svoGridTagSource, 0x597);
    if (tag->m_currCellColNum < 0 || tag->m_currCellColNum >= tag->m_numTotalColumns)
        __SVO_Assert_Handler(svoGridTagSource, 0x598);
    if (tag->m_currCellRowNum < -1 || tag->m_currCellRowNum >= tag->m_numTotalRows)
        __SVO_Assert_Handler(svoGridTagSource, 0x599);
    *cell = tag->m_currCellRowNum == -1 ? 0 : &tag->m_cells[tag->m_currCellRowNum][tag->m_currCellColNum];
    return 1;
}

extern "C" SECTION(ChangeSelectedCell) void ChangeSelectedCell(GridTagState *tag, int direction)
{
    switch (direction) {
    case -1: {
        tag->m_headerSelected = 0;
        if (tag->m_bVerticalWrapAllowed && tag->m_currCellRowNum == -1) {
            AdvanceCurrTopRow(tag, 1, tag->m_numTotalRows - tag->m_numVisRowsWithCells);
            tag->m_currCellRowNum = tag->m_numTotalRows;
        }
        int previous = tag->m_currCellRowNum;
        for (int row = previous - 1; row >= 0; --row) {
            if (tag->m_cells[row][tag->m_currCellColNum].cell_link) {
                if (row < tag->m_currTopRow) AdvanceCurrTopRow(tag, -1, tag->m_currTopRow - row);
                tag->m_currCellRowNum = row;
                return;
            }
        }
        if (tag->m_columns[tag->m_currCellColNum].colHdrLink) {
            tag->m_headerSelected = 1;
            if (tag->m_numVisRowsWithCells < previous + 1) AdvanceCurrTopRow(tag, -1, tag->m_currTopRow);
            tag->m_currCellRowNum = -1;
        } else if (tag->m_bVerticalWrapAllowed) {
            AdvanceCurrTopRow(tag, 1, tag->m_numTotalRows - tag->m_numVisRowsWithCells);
            tag->m_currCellRowNum = tag->m_numTotalRows - 1;
        }
        return;
    }
    case 1: {
        int previous = tag->m_currCellRowNum;
        for (int row = previous + 1; row < tag->m_numTotalRows; ++row) {
            if (tag->m_cells[row][tag->m_currCellColNum].cell_link) {
                if (row >= tag->m_currTopRow + tag->m_numVisRowsWithCells)
                    AdvanceCurrTopRow(tag, 1, row - tag->m_currTopRow - tag->m_numVisRowsWithCells + 1);
                tag->m_currCellRowNum = row;
                tag->m_headerSelected = 0;
                return;
            }
        }
        if (tag->m_bVerticalWrapAllowed) {
            for (int row = 0; row < previous; ++row) {
                if (tag->m_cells[row][tag->m_currCellColNum].cell_link) {
                    if (row < tag->m_currTopRow) AdvanceCurrTopRow(tag, -1, tag->m_currTopRow - row);
                    tag->m_currCellRowNum = row;
                    tag->m_headerSelected = 0;
                    return;
                }
            }
        }
        return;
    }
    case -2:
    case 2: {
        int step = direction < 0 ? -1 : 1;
        int offset = step;
        for (int tried = 1; tried < tag->m_numTotalColumns; ++tried, offset += step) {
            int previous = tag->m_currCellColNum;
            int column = (previous + tag->m_numTotalColumns + offset) % tag->m_numTotalColumns;
            if (!tag->m_bSideWrapAllowed) {
                if (direction == -2 && previous < column) return;
                if (direction == 2 && column < previous) return;
            }
            char *link;
            if (tag->m_currCellRowNum == -1) link = tag->m_columns[column].colHdrLink;
            else link = tag->m_cells[tag->m_currCellRowNum][column].cell_link;
            if (link) {
                ChangeSelectedColumn(tag, column);
                return;
            }
        }
        return;
    }
    default:
        __SVO_Assert_Handler(svoGridTagSource, 0x62C);
    }
}

extern "C" SECTION(GetToolTipText___dupe2) char * GetToolTipText___dupe2(GridTagState *tag)
{
    SVGridCell *cell = 0;
    if (tag->m_bIsModalGrid && !tag->m_bIsClickedIn) return tag->base.m_toolTip;
    if (tag->m_currCellRowNum == -1) {
        int col = tag->m_currCellColNum;
        // Retail accepts col == total here, unlike GetCurrentSelectedCell.
        if (col >= 0 && col <= tag->m_numTotalColumns) return tag->m_columns[col].colTooltip;
        __SVO_Assert_Handler(svoGridTagSource, 0x643);
    } else {
        if (!tag->m_cells) return 0;
        GetCurrentSelectedCell(tag, &cell);
        if (cell) return cell->cell_tooltip;
        __SVO_Assert_Handler(svoGridTagSource, 0x658);
    }
    return 0;
}

extern "C" SECTION(CreateAndInitColumnIndexArray) void CreateAndInitColumnIndexArray(GridTagState *tag)
{
    CMemoryContextBaseState *memory = GetMemoryContext();
    tag->m_columnIndexes = (int *)svAllocSafe(memory, (unsigned int)tag->m_numVisColumns * 4, 0, 0x665, svoGridTagSource);
    if (!tag->m_columnIndexes) __SVO_Assert_Handler(svoGridTagSource, 0x668);
    ResetIndexArray(tag);
}

extern "C" SECTION(ResetIndexArray) void ResetIndexArray(GridTagState *tag)
{
    int *index = tag->m_columnIndexes;
    for (int i = 0; i < tag->m_numVisColumns; ++i) *index++ = i;
}

extern "C" SECTION(AlignVisibleColumns) void AlignVisibleColumns(GridTagState *tag)
{
    int count = tag->m_numVisColumns;
    tag->base.m_width = 0;
    SVGridColumn *columns = tag->m_columns;
    int *indexes = tag->m_columnIndexes;
    for (int i = 0; i < count; ++i) {
        SVGridColumn *col = &columns[*indexes++];
        col->col_x = tag->base.m_x + tag->base.m_width;
        tag->base.m_width += col->width;
    }
}

extern "C" SECTION(ChangeSelectedColumn) void ChangeSelectedColumn(GridTagState *tag, int selected)
{
    if (selected < 0 || selected >= tag->m_numTotalColumns)
        __SVO_Assert_Handler(svoGridTagSource, 0x689);
    int locked = tag->m_numLockedColumns;
    tag->m_currCellColNum = selected;
    int leftmost;
    if (locked < 1) {
        if (selected < tag->m_columnIndexes[0]) leftmost = selected;
        else if (selected >= tag->m_columnIndexes[0] + tag->m_numVisColumns)
            leftmost = selected - tag->m_numVisColumns + 1;
        else return;
    } else {
        if (selected < locked) {
            if (selected < 0) __SVO_Assert_Handler(svoGridTagSource, 0x6AA);
            leftmost = locked;
        } else if (selected < tag->m_columnIndexes[locked]) leftmost = selected;
        else if (selected > tag->m_columnIndexes[tag->m_numVisColumns - 1])
            leftmost = selected + locked - tag->m_numVisColumns + 1;
        else return;
    }
    HandleColumnShuffling(tag, leftmost);
    AlignVisibleColumns(tag);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GridTag", HandleColumnShuffling);
