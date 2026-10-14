


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
int ClearRows(GridTagState *);
void FreeResources___dupe36(GridTagState *);
void ResetIndexArray(GridTagState *);

}
extern "C" {
extern char svoGridRowsName[];
extern char svoGridColumnsName[];
extern char svoGridRowName[];
extern char svoGridRecordRowName[];
extern char svoGridColumnName[];
int GetCurrentSelectedCell(GridTagState *, SVGridCell **);
void HandleColumnShuffling(GridTagState *, int);
void AlignVisibleColumns(GridTagState *);
void CalculateGridHeight(GridTagState *);
void initSVGridRow(GridTagState *, SVGridRow *);
int ParseRows(GridTagState *, iks *);
int ParseColumns(GridTagState *, iks *);
int ParseSingleRow(GridTagState *, iks *, int);
int ParseSingleColumn(GridTagState *, iks *);
int ParseGridHeader(GridTagState *, iks *);

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
int ParseSingleCell(GridTagState *, iks *, SVGridCell *);

}
extern "C" {
extern char svoGridTagName[];
}
extern "C" {
int Navigate(SVTag *, CInputContextBaseState *, CDrawContextBase *, iks *, CPage *);
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
extern "C" {
extern char svoGridSelectableAttribute[];
extern char svoGridFalseValue[];
extern char svoGridNumColsAttribute[];
extern char svoGridNumTotalColsAttribute[];
extern char svoGridNumVisColsAttribute[];
extern char svoGridNumLockedColsAttribute[];
extern char svoGridNumVisRowsAttribute[];
extern char svoGridNumTotalRowsAttribute[];
extern char svoGridVerticalWrapAttribute[];
extern char svoGridSideWrapAttribute[];
extern char svoGridTooltipTagNameAttribute[];
extern char svoGridCellFontSizeAttribute[];
extern char svoGridCellAlignAttribute[];
extern char svoGridBorderWidthAttribute[];
extern char svoGridBorderHeightAttribute[];
extern char svoGridBorderLineAttribute[];
extern char svoGridBorderFillAttribute[];
extern char svoGridBorderHighlightLineAttribute[];
extern char svoGridBorderHighlightFillAttribute[];
extern char svoGridBorderClassAttribute[];
extern char svoGridVerticalScrollbarWidthAttribute[];
extern char svoGridHorizontalScrollbarHeightAttribute[];
extern char svoGridScrollbarClassAttribute[];
extern char svoGridIsModalAttribute[];
void DefaultInit___dupe18(GridTagState *);
void CreateAndInitColumnIndexArray(GridTagState *);
int InitGridCells(GridTagState *);
int InitRowsAndColumns(GridTagState *);
int FindAndSetSelectedCell(GridTagState *);
}
#define SECTION(name) __attribute__((section(".svo_GridTag_" #name)))

extern "C" SECTION(ClearRows) int ClearRows(GridTagState *tag)
{
    tag->base.m_bSelectable = 0;
    for (int i = 0; i < tag->m_numTotalRows; ++i)
        svFreeSafe(tag->base.m_contexts->memoryContext, tag->m_cells[i]);
    if (tag->m_numTotalRows > 0) {
        svFreeSafe(tag->base.m_contexts->memoryContext, tag->m_cells);
        tag->m_cells = 0;
        svFreeSafe(tag->base.m_contexts->memoryContext, tag->m_rows);
        tag->m_rows = 0;
        tag->m_numTotalRows = 0;
        tag->m_numVisRowsWithCells = 0;
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
    if (tag->m_pTimer) {
        _SVChronograph(tag->m_pTimer, 3);
        return;
    }
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
    if (flags & 1) { SVTagDelete(&tag->base); return; }
}

extern "C" SECTION(GridTag) void GridTag(GridTagState *tag, iks *xml, CAllContextData *contexts)
{
    SVTagConstruct(&tag->base, xml, contexts);
    tag->base.vtable = &svoGridTagVtable;
    DefaultInit___dupe18(tag);
    char *selectable = 0;
    getStringAttrib(tag->base.m_xml, svoGridSelectableAttribute, &selectable);
    if (selectable && !strcmp(selectable, svoGridFalseValue)) tag->base.m_bSelectable = 0;
    getIntAttrib(tag->base.m_xml, svoGridNumColsAttribute, &tag->m_numTotalColumns);
    if (!tag->m_numTotalColumns) getIntAttrib(tag->base.m_xml, svoGridNumTotalColsAttribute, &tag->m_numTotalColumns);
    if (tag->m_numTotalColumns < 1) __SVO_Assert_Handler(svoGridTagSource, 0xE5);
    getIntAttrib(tag->base.m_xml, svoGridNumVisColsAttribute, &tag->m_numVisColumns);
    getIntAttrib(tag->base.m_xml, svoGridNumLockedColsAttribute, &tag->m_numLockedColumns);
    if (tag->m_numVisColumns <= 0 || tag->m_numVisColumns > tag->m_numTotalColumns) tag->m_numVisColumns = tag->m_numTotalColumns;
    if (tag->m_numVisColumns < 1 || tag->m_numTotalColumns < 1) __SVO_Assert_Handler(svoGridTagSource, 0xF2);
    CreateAndInitColumnIndexArray(tag);
    if (!tag->m_columnIndexes) __SVO_Assert_Handler(svoGridTagSource, 0xF8);
    getIntAttrib(tag->base.m_xml, svoGridNumVisRowsAttribute, &tag->m_origNumVisRows);
    getIntAttrib(tag->base.m_xml, svoGridNumTotalRowsAttribute, &tag->m_numTotalRows);
    tag->m_numVisRowsWithCells = tag->m_origNumVisRows < tag->m_numTotalRows ? tag->m_origNumVisRows : tag->m_numTotalRows;
    if (tag->m_numVisRowsWithCells < 0) __SVO_Assert_Handler(svoGridTagSource, 0x109);
    if (!getBoolAttrib(tag->base.m_xml, svoGridVerticalWrapAttribute, &tag->m_bVerticalWrapAllowed)) tag->m_bVerticalWrapAllowed = 0;
    if (!getBoolAttrib(tag->base.m_xml, svoGridSideWrapAttribute, &tag->m_bSideWrapAllowed)) tag->m_bSideWrapAllowed = 0;
    getStringAttrib(tag->base.m_xml, svoGridClassAttribute, &tag->base.m_tagClass);
    tag->base.m_toolTipTagName = iks_find_attrib(tag->base.m_xml, svoGridTooltipTagNameAttribute);
    tag->base.m_toolTip = iks_find_attrib(tag->base.m_xml, svoGridTooltipAttribute);
    getFloatAttrib(tag->base.m_xml, svoGridColWidthAttribute, &tag->m_defaultColWidth);
    if (tag->m_defaultColWidth <= 0.0f) __SVO_Assert_Handler(svoGridTagSource, 0x122);
    getFloatAttrib(tag->base.m_xml, svoGridRowHeightAttribute, &tag->m_defaultRowHeight);
    if (tag->m_defaultRowHeight <= 0.0f) __SVO_Assert_Handler(svoGridTagSource, 0x125);
    getIntAttrib(tag->base.m_xml, svoGridCellFontSizeAttribute, &tag->m_defCellFontSize);
    getAlignAttrib(tag->base.m_xml, svoGridCellAlignAttribute, &tag->m_defCellAlign);
    getColorAttrib(tag->base.m_xml, svoGridTextColorAttribute, &tag->m_defCellTextColor);
    getColorAttrib(tag->base.m_xml, svoGridLineColorAttribute, &tag->m_defCellLineColor);
    getColorAttrib(tag->base.m_xml, svoGridFillColorAttribute, &tag->m_defCellFillColor);
    getColorAttrib(tag->base.m_xml, svoGridHighlightTextAttribute, &tag->m_highlightCellTextColor);
    getColorAttrib(tag->base.m_xml, svoGridHighlightLineAttribute, &tag->m_highlightCellLineColor);
    getColorAttrib(tag->base.m_xml, svoGridHighlightFillAttribute, &tag->m_highlightCellFillColor);
    getIntAttrib(tag->base.m_xml, svoGridBorderWidthAttribute, &tag->m_borderWidth);
    getIntAttrib(tag->base.m_xml, svoGridBorderHeightAttribute, &tag->m_borderHeight);
    getColorAttrib(tag->base.m_xml, svoGridBorderLineAttribute, &tag->m_borderOutlineColor);
    getColorAttrib(tag->base.m_xml, svoGridBorderFillAttribute, &tag->m_borderFillColor);
    getColorAttrib(tag->base.m_xml, svoGridBorderHighlightLineAttribute, &tag->m_borderHighlightOutlineColor);
    getColorAttrib(tag->base.m_xml, svoGridBorderHighlightFillAttribute, &tag->m_borderHighlightFillColor);
    getStringAttrib(tag->base.m_xml, svoGridBorderClassAttribute, &tag->m_borderClass);
    tag->m_header_tagID = svoNextTagId++;
    getFloatAttrib(tag->base.m_xml, svoGridVerticalScrollbarWidthAttribute, &tag->m_vert_sb_width);
    getFloatAttrib(tag->base.m_xml, svoGridHorizontalScrollbarHeightAttribute, &tag->m_horz_sb_height);
    getStringAttrib(tag->base.m_xml, svoGridScrollbarClassAttribute, &tag->m_scrollbar_class);
    InitGridCells(tag);
    InitRowsAndColumns(tag);
    FindAndSetSelectedCell(tag);
    if (tag->m_currCellColNum < 0 || tag->m_currCellColNum > tag->m_numTotalColumns) tag->m_currCellColNum = 0;
    if (!getBoolAttrib(tag->base.m_xml, svoGridIsModalAttribute, &tag->m_bIsModalGrid)) tag->m_bIsModalGrid = 0;
    if (!tag->m_bIsModalGrid) tag->m_bIsClickedIn = 1;
}

extern "C" SECTION(HasNavigationOccured) int HasNavigationOccured(GridTagState *tag, CPage *page)
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
    if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_LEFT)) { ChangeSelectedCell(tag, -2); return 0; }
    if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_RIGHT)) { ChangeSelectedCell(tag, 2); return 0; }
    if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_UP)) { ChangeSelectedCell(tag, -1); return 0; }
    if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_DOWN)) { ChangeSelectedCell(tag, 1); return 0; }
    if (HasActionOccurred(input, 0x11, SV_ACTION_ACTIVATE)) { FollowLink(tag, page); return 0; }
    if (HasActionOccurred(input, 0x11, SV_ACTION_SCROLL_DOWN)) { AdvanceCurrTopRow(tag, 1, 1); return 0; }
    if (HasActionOccurred(input, 0x11, SV_ACTION_SCROLL_UP)) { AdvanceCurrTopRow(tag, -1, 1); return 0; }
    return 1;
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
            if (action > 0) ChangeSelectedCell(tag, 2);
            else ChangeSelectedCell(tag, -2);
            return 0;
        }
    }
    action = HasActionOccurred(input, 0x11, SV_ACTION_SELECT_UP);
    if (!action) action = HasActionOccurred(input, 0x11, SV_ACTION_SELECT_DOWN);
    if (action && ElapsedMS(tag->m_pTimer) > 250) {
        int magnitude = action < 0 ? -action : action;
        if (magnitude > 45) {
            Reset___dupe5(tag->m_pTimer);
            if (action < 0) ChangeSelectedCell(tag, -1);
            else ChangeSelectedCell(tag, 1);
            return 0;
        }
    }
    if (HasActionOccurred(input, 0x11, SV_ACTION_ACTIVATE)) { FollowLink(tag, page); return 0; }
    if (HasActionOccurred(input, 0x11, SV_ACTION_SCROLL_DOWN)) { AdvanceCurrTopRow(tag, 1, 1); return 0; }
    if (HasActionOccurred(input, 0x11, SV_ACTION_SCROLL_UP)) { AdvanceCurrTopRow(tag, -1, 1); return 0; }
    return 1;
}

#include "CDrawContextBase.h"
extern "C" {
extern char svoGridEmptyCellText[];
int TrimToFitDisplaySize(CDrawContextBase *draw, char *text, float length, int fontSize);
}
extern "C" SECTION(Draw___dupe23) void Draw___dupe23(GridTagState *tag)
{
    CDrawContextBase *draw = tag->base.m_contexts->drawContext;
    int r;
    int c;
    int strLen;
    int col_num;
    float header_x;
    float header_y;
    int visiblySelected;
    float row_x;
    SVGridCell *selectedCell;
    int selected;
    char *cText;
    char *_classString;
    unsigned int fillColor;
    unsigned int lineColor;
    unsigned int textColor;
    float _grid_height;
    float _grid_width;
    float h_sb_percentage;
    float h_sb_size_percentage;
    float v_sb_percentage;
    float v_sb_size_percentage;
    if (!draw) __SVO_Assert_Handler(svoGridTagSource, 0x258);
    if (!(tag->m_currCellColNum >= 0 && tag->m_currCellColNum < tag->m_numTotalColumns))
        __SVO_Assert_Handler(svoGridTagSource, 0x259);
    if (tag->m_borderHeight > 0 && tag->m_borderWidth > 0) {
        float spaceForMyRecordRow = 0.0f;
        if (tag->m_myRecordRow)
            spaceForMyRecordRow = tag->m_myRecordRow->row.height + tag->m_spaceBetweenLastRowAndMyRecord;
        unsigned int _border_line_color = tag->m_borderOutlineColor;
        unsigned int _border_fill_color = tag->m_borderFillColor;
        if (tag->base.vtable->IsSelected(&tag->base)) {
            _border_line_color = tag->m_borderHighlightOutlineColor;
            _border_fill_color = tag->m_borderHighlightFillColor;
        }
        draw->vtable->DrawGridBorder(draw, tag->m_header_tagID, tag->base.m_x, tag->base.m_y, tag->base.m_z,
                                     tag->base.m_width + (float)(tag->m_borderWidth * 2),
                                     tag->base.m_height + (float)(tag->m_borderHeight * 2) + spaceForMyRecordRow,
                                     _border_line_color, _border_fill_color, tag->m_borderClass);
    }
    header_x = tag->base.m_x + (float)tag->m_borderWidth;
    visiblySelected = 0;
    header_y = tag->base.m_y + (float)tag->m_borderHeight;
    if (tag->m_headerSelected) visiblySelected = tag->m_bIsClickedIn != 0;
    draw->vtable->DrawGridHeader(draw, tag->m_header_tagID, header_x, header_y,
                                 tag->base.m_z, tag->base.m_width, tag->m_headerHeight,
                                 tag->m_columns[tag->m_currCellColNum].col_x + (float)tag->m_borderWidth,
                                 tag->m_columns[tag->m_currCellColNum].width,
                                 tag->m_headerLineColor, tag->m_headerFillColor, tag->m_headerClass, visiblySelected);
    for (c = 0; c < tag->m_numVisColumns; c++) {
        col_num = tag->m_columnIndexes[c];
        if (tag->m_columns[col_num].colName) {
            float _xval;
            float _yval;
            float _textSizeInPixels;
            float _smallIndentFactor;
            unsigned int _headerTextColor;
            strLen = TrimToFitDisplaySize(draw, tag->m_columns[col_num].colName, tag->m_columns[col_num].width, tag->m_headerFontSize);
            _yval = header_y + (tag->m_headerHeight - (float)tag->m_headerFontSize) * 0.5f;
            _textSizeInPixels = draw->vtable->GetStringWidth(draw, tag->m_headerFontSize, tag->m_columns[col_num].colName, strLen);
            _smallIndentFactor = 5.0f;
            switch (tag->m_columns[col_num].colAlign) {
            case 0:
                _xval = tag->m_columns[col_num].col_x + (float)tag->m_borderWidth + _smallIndentFactor;
                break;
            case 1:
                _xval = tag->m_columns[col_num].col_x + _textSizeInPixels * 0.5f + (float)tag->m_borderWidth;
                break;
            case 2:
                _xval = tag->m_columns[col_num].col_x + tag->m_columns[col_num].width + (float)tag->m_borderWidth - (_textSizeInPixels + _smallIndentFactor);
                break;
            default:
                __SVO_Assert_Handler(svoGridTagSource, 0x2A7);
                _xval = tag->m_columns[col_num].col_x + _textSizeInPixels * 0.5f + (float)tag->m_borderWidth;
                break;
            }
            if (tag->m_currCellRowNum == -1 && col_num == tag->m_currCellColNum && tag->m_bIsClickedIn)
                _headerTextColor = tag->m_headerHighlightTextColor;
            else
                _headerTextColor = tag->m_headerTextColor;
            draw->vtable->SVDrawText(draw, tag->m_header_tagID, _xval, _yval, _headerTextColor,
                                     tag->m_columns[col_num].colName, strLen, tag->m_headerFontSize, 0, tag->base.m_tagClass);
        }
    }
    row_x = tag->base.m_x + (float)tag->m_borderWidth;
    for (r = 0; r < tag->m_origNumVisRows; r++) {
        int rowNum = r + tag->m_currTopRow;
        int isCur = rowNum == tag->m_currCellRowNum;
        draw->vtable->DrawGridRow(draw, tag->m_rows[r].row_tagID, row_x, tag->m_rows[r].row_y + (float)tag->m_borderHeight,
                                  tag->base.m_z, tag->base.m_width, tag->m_rows[r].height, rowNum,
                                  isCur, tag->m_rows[r].rowClass);
    }
    if (tag->m_numTotalRows <= 0) return;
    selected = 0;
    selectedCell = 0;
    if (tag->base.vtable->IsSelected(&tag->base) && !GetCurrentSelectedCell(tag, &selectedCell))
        __SVO_Assert_Handler(svoGridTagSource, 0x2DD);
    fillColor = tag->m_defCellFillColor;
    lineColor = tag->m_defCellLineColor;
    textColor = tag->m_defCellTextColor;
    for (r = 0; r < tag->m_numVisRowsWithCells; r++) {
        for (c = 0; c < tag->m_numVisColumns; c++) {
            col_num = tag->m_columnIndexes[c];
            SVGridCell *cell = &tag->m_cells[r + tag->m_currTopRow][col_num];
            cText = cell->cell_text;
            if (!cText) cText = svoGridEmptyCellText;
            selected = selectedCell == cell;
            strLen = TrimToFitDisplaySize(draw, cText, tag->m_columns[col_num].width, tag->m_defCellFontSize);
            if (tag->m_cells[r + tag->m_currTopRow][col_num].cellClass) _classString = tag->m_cells[r + tag->m_currTopRow][col_num].cellClass;
            else _classString = tag->base.m_tagClass;
            if (selected && tag->m_bIsClickedIn) {
                fillColor = tag->m_highlightCellFillColor;
                lineColor = tag->m_highlightCellLineColor;
                textColor = tag->m_highlightCellTextColor;
            }
            draw->vtable->DrawGridCell(draw, tag->m_cells[r][col_num].cell_tagID,
                                       tag->m_columns[col_num].col_x + (float)tag->m_borderWidth,
                                       tag->m_rows[r].row_y + (float)tag->m_borderHeight, tag->base.m_z,
                                       tag->m_columns[col_num].width, tag->m_rows[r].height,
                                       lineColor, fillColor, textColor, selected, cText, strLen,
                                       tag->m_defCellFontSize, tag->m_columns[c].colAlign, _classString);
            if (selected && tag->m_bIsClickedIn) {
                fillColor = tag->m_defCellFillColor;
                lineColor = tag->m_defCellLineColor;
                textColor = tag->m_defCellTextColor;
            }
        }
    }
    if (tag->m_myRecordRow) {
        for (c = 0; c < tag->m_numVisColumns; c++) {
            col_num = tag->m_columnIndexes[c];
            cText = tag->m_myRecordRow->cells[col_num].cell_text;
            if (!cText) cText = svoGridEmptyCellText;
            strLen = TrimToFitDisplaySize(draw, cText, tag->m_columns[col_num].width, tag->m_defCellFontSize);
            if (tag->m_myRecordRow->cells[col_num].cellClass) _classString = tag->m_myRecordRow->cells[col_num].cellClass;
            else if (tag->m_myRecordRow->row.rowClass) _classString = tag->m_myRecordRow->row.rowClass;
            else _classString = tag->base.m_tagClass;
            textColor = tag->m_myRecordRow->textColor;
            fillColor = tag->m_defCellFillColor;
            lineColor = tag->m_defCellLineColor;
            draw->vtable->DrawGridCell(draw, tag->m_myRecordRow->cells[col_num].cell_tagID,
                                       tag->m_columns[col_num].col_x + (float)tag->m_borderWidth,
                                       tag->base.m_y + tag->base.m_height + (float)tag->m_borderHeight + tag->m_spaceBetweenLastRowAndMyRecord,
                                       tag->base.m_z, tag->m_columns[col_num].width, tag->m_myRecordRow->row.height,
                                       lineColor, fillColor, textColor, selected, cText, strLen,
                                       tag->m_defCellFontSize, tag->m_columns[c].colAlign, _classString);
        }
    }
    _grid_height = tag->base.m_height + (float)(tag->m_borderHeight * 2);
    _grid_width = tag->base.m_width + (float)(tag->m_borderWidth * 2);
    if (tag->m_numTotalColumns > tag->m_numVisColumns) {
        float denominator = (float)tag->m_numTotalColumns;
        float numerator = (float)tag->m_columnIndexes[tag->m_numLockedColumns] - (float)tag->m_numLockedColumns;
        if (denominator == 0.0f) __SVO_Assert_Handler(svoGridTagSource, 0x365);
        h_sb_percentage = numerator / denominator;
        h_sb_size_percentage = (float)tag->m_numVisColumns / (float)tag->m_numTotalColumns;
        if (!(h_sb_percentage + h_sb_size_percentage <= 1.01f)) __SVO_Assert_Handler(svoGridTagSource, 0x36A);
    } else {
        h_sb_percentage = 0.0f;
        h_sb_size_percentage = 1.0f;
    }
    if (tag->m_numTotalRows > tag->m_numVisRowsWithCells) {
        float denominator = (float)tag->m_numTotalRows;
        float numerator = (float)tag->m_currTopRow;
        if (denominator == 0.0f) __SVO_Assert_Handler(svoGridTagSource, 0x37C);
        v_sb_percentage = numerator / denominator;
        v_sb_size_percentage = (float)tag->m_numVisRowsWithCells / (float)tag->m_numTotalRows;
        if (!(v_sb_percentage + v_sb_size_percentage <= 1.01f)) __SVO_Assert_Handler(svoGridTagSource, 0x382);
    } else {
        v_sb_percentage = 0.0f;
        v_sb_size_percentage = 1.0f;
    }
    if (!tag->m_scrollbar_class) tag->m_scrollbar_class = tag->base.m_tagClass;
    if (tag->m_myRecordRow)
        _grid_height += tag->m_spaceBetweenLastRowAndMyRecord + tag->m_myRecordRow->row.height;
    draw->vtable->DrawGridScrollbars(draw, tag->base.m_tagid, tag->m_scrollbar_class,
                                     tag->base.m_x, tag->base.m_y, tag->base.m_z, _grid_width, _grid_height,
                                     tag->m_vert_sb_width, _grid_height, v_sb_percentage, v_sb_size_percentage,
                                     _grid_width, tag->m_horz_sb_height, h_sb_percentage, h_sb_size_percentage);
}

extern "C" SECTION(InitGridCells) int InitGridCells(GridTagState *tag)
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

extern "C" SECTION(FindAndSetSelectedCell) int FindAndSetSelectedCell(GridTagState *tag)
{
    int r;
    int c;
    int col;
    for (r = 0; r < tag->m_numVisRowsWithCells; r++) {
        for (c = 0; c < tag->m_numVisColumns; c++) {
            if (tag->m_cells[r][c].cell_link) {
                tag->m_currCellRowNum = r;
                tag->m_currCellColNum = c;
                return tag->base.m_bSelectable = 1;
            }
        }
    }
    for (col = 0; col < tag->m_numVisColumns; col++) {
        if (tag->m_columns[col].colHdrLink) {
            tag->m_currCellRowNum = -1;
            tag->m_currCellColNum = col;
            return tag->base.m_bSelectable = 1;
        }
    }
    return tag->base.m_bSelectable = 0;
}

extern "C" SECTION(InitRowsAndColumns) int InitRowsAndColumns(GridTagState *tag)
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

extern "C" SECTION(CalculateGridHeight) void CalculateGridHeight(GridTagState *tag)
{
    float temp_y;
    int r;
    tag->base.m_height = tag->m_headerHeight;
    temp_y = tag->base.m_y + tag->m_headerHeight;
    for (r = 0; r < tag->m_origNumVisRows; r++) {
        tag->m_rows[r].row_y = temp_y;
        tag->base.m_height += tag->m_rows[r].height;
        temp_y += tag->m_rows[r].height;
        if (temp_y != tag->base.m_height + tag->base.m_y) __SVO_Assert_Handler(svoGridTagSource, 0x423);
    }
}

extern "C" SECTION(initSVGridRow) void initSVGridRow(GridTagState *tag, SVGridRow *row)
{
    row->height = tag->m_defaultRowHeight;
    row->rowClass = 0;
    unsigned int id = svoNextTagId++;
    row->row_tagID = id;
}

extern "C" SECTION(ParseRows) int ParseRows(GridTagState *tag, iks *xml)
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

extern "C" SECTION(ParseSingleRow) int ParseSingleRow(GridTagState *tag, iks *xml, int record)
{
    char *child_name;
    iks *curr_child;
    SVGridRow *thisRow;
    int colNum;
    int okToParseCell;
    SVGridCell *cell;
    if (tag->m_numTotalRows > 0) {
        if (!record) thisRow = &tag->m_rows[g_rowNumParseCntr];
        else {
            thisRow = &tag->m_myRecordRow->row;
            getFloatAttrib(xml, svoGridRecordSpaceAttribute, &tag->m_spaceBetweenLastRowAndMyRecord);
            getColorAttrib(xml, svoGridTextColorAttribute, &tag->m_myRecordRow->textColor);
        }
        if (!xml) {
            __SVO_Assert_Handler(svoGridTagSource, 0x48A);
            return 0;
        } else {
            colNum = 0;
            getFloatAttrib(xml, svoGridRowHeightAttribute, &thisRow->height);
            thisRow->rowClass = iks_find_attrib(xml, svoGridClassAttribute);
            for (curr_child = iks_child(xml); curr_child; curr_child = iks_next(curr_child)) {
                child_name = iks_name(curr_child);
                if (child_name && !strcmp(child_name, svoGridCellName)) {
                    okToParseCell = 0;
                    if (record || g_rowNumParseCntr < tag->m_numTotalRows) okToParseCell = 1;
                    if (okToParseCell) {
                        if (colNum < tag->m_numTotalColumns) {
                            if (!record) cell = &tag->m_cells[g_rowNumParseCntr][colNum];
                            else cell = &tag->m_myRecordRow->cells[colNum];
                            ParseSingleCell(tag, curr_child, cell);
                            colNum++;
                        } else __SVO_Assert_Handler(svoGridTagSource, 0x4B4);
                    } else if (!record) __SVO_Assert_Handler(svoGridTagSource, 0x4BA);
                }
            }
            if (!record) g_rowNumParseCntr = (unsigned int)g_rowNumParseCntr + 1;
            return 1;
        }
    }
    return 1;
}

extern "C" SECTION(ParseColumns) int ParseColumns(GridTagState *tag, iks *xml)
{
    CMemoryContextBaseState *memory = GetMemoryContext();
    SVGridColumn *column = (SVGridColumn *)svAllocSafe(memory, (unsigned int)tag->m_numTotalColumns * 32, 0, 0x4D5, svoGridTagSource);
    tag->m_columns = column;
    for (int i = 0; i < tag->m_numTotalColumns; ++i, ++column) {
        column->colAlign = tag->m_defCellAlign;
        column->width = tag->m_defaultColWidth;
        column->colName = 0;
        *(void **)&column->linkOption = 0;
    }
    ParseGridHeader(tag, xml);
    if (!iks_has_children(xml)) __SVO_Assert_Handler(svoGridTagSource, 0x4E3);
    for (iks *child = iks_child(xml); child; child = iks_next(child)) {
        char *name = iks_name(child);
        if (name && !strcmp(name, svoGridColumnName)) ParseSingleColumn(tag, child);
    }
    return 1;
}

extern "C" SECTION(ParseSingleColumn) int ParseSingleColumn(GridTagState *tag, iks *xml)
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

extern "C" SECTION(ParseGridHeader) int ParseGridHeader(GridTagState *tag, iks *xml)
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
    unsigned int id = svoNextTagId++;
    tag->m_header_tagID = id;
    return 1;
}

extern "C" SECTION(ParseSingleCell) int ParseSingleCell(GridTagState *tag, iks *xml, SVGridCell *cell)
{
    if (!xml || !cell) {
        __SVO_Assert_Handler(svoGridTagSource, 0x549);
        return 0;
    }
    unsigned int id = svoNextTagId++;
    cell->cell_tagID = id;
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
        if (top < limit) limit = top; tag->m_currTopRow = limit;
    }
}

extern "C" SECTION(GetCurrentSelectedCell) int GetCurrentSelectedCell(GridTagState *tag, SVGridCell **cell)
{
    if (!tag->m_cells) __SVO_Assert_Handler(svoGridTagSource, 0x597);
    if (tag->m_currCellColNum < 0 || tag->m_currCellColNum >= tag->m_numTotalColumns)
        __SVO_Assert_Handler(svoGridTagSource, 0x598);
    if (tag->m_currCellRowNum < -1 || tag->m_currCellRowNum >= tag->m_numTotalRows)
        __SVO_Assert_Handler(svoGridTagSource, 0x599);
    if (tag->m_currCellRowNum != -1) *cell = &tag->m_cells[tag->m_currCellRowNum][tag->m_currCellColNum];
    else *cell = 0;
    return 1;
}

extern "C" SECTION(ChangeSelectedCell) void ChangeSelectedCell(GridTagState *tag, int direction)
{
    int lrChoice = 0;
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
        lrChoice = -1;
    case 2: {
        if (!lrChoice) lrChoice = 1;
        for (int i = 1; i < tag->m_numTotalColumns; i++) {
            int previous = tag->m_currCellColNum;
            int column = (previous + tag->m_numTotalColumns + lrChoice * i) % tag->m_numTotalColumns;
            if (!tag->m_bSideWrapAllowed) {
                if (direction == -2 && previous < column) return;
                if (direction == 2 && column < previous) return;
            }
            if (tag->m_currCellRowNum != -1) {
                if (tag->m_cells[tag->m_currCellRowNum][column].cell_link) {
                    ChangeSelectedColumn(tag, column);
                    return;
                }
            } else if (tag->m_columns[column].colHdrLink) {
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
        if (col > tag->m_numTotalColumns || col < 0) {
            __SVO_Assert_Handler(svoGridTagSource, 0x643);
            return 0;
        }
        return tag->m_columns[col].colTooltip;
    }
    if (!tag->m_cells) return 0;
    GetCurrentSelectedCell(tag, &cell);
    if (!cell) {
        __SVO_Assert_Handler(svoGridTagSource, 0x658);
        return 0;
    }
    return cell->cell_tooltip;
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
    int i;
    for (i = 0; i < tag->m_numVisColumns; i++) tag->m_columnIndexes[i] = i;
}

extern "C" SECTION(AlignVisibleColumns) void AlignVisibleColumns(GridTagState *tag)
{
    int i;
    tag->base.m_width = 0;
    for (i = 0; i < tag->m_numVisColumns; i++) {
        tag->m_columns[tag->m_columnIndexes[i]].col_x = tag->base.m_x + tag->base.m_width;
        tag->base.m_width += tag->m_columns[tag->m_columnIndexes[i]].width;
    }
}

extern "C" SECTION(ChangeSelectedColumn) void ChangeSelectedColumn(GridTagState *tag, int selected)
{
    if (selected < 0 || selected >= tag->m_numTotalColumns)
        __SVO_Assert_Handler(svoGridTagSource, 0x689);
    int locked = tag->m_numLockedColumns;
    tag->m_currCellColNum = selected;
    if (locked < 1) {
        if (selected < tag->m_columnIndexes[0]) {
            HandleColumnShuffling(tag, selected);
            AlignVisibleColumns(tag);
            return;
        }
        if (selected >= tag->m_columnIndexes[0] + tag->m_numVisColumns) {
            HandleColumnShuffling(tag, selected - tag->m_numVisColumns + 1);
            AlignVisibleColumns(tag);
            return;
        }
    } else {
        int leftmost = locked;
        if (selected < leftmost) {
            if (selected < 0) __SVO_Assert_Handler(svoGridTagSource, 0x6AA);
            HandleColumnShuffling(tag, leftmost);
            AlignVisibleColumns(tag);
            return;
        }
        if (selected < tag->m_columnIndexes[leftmost]) {
            leftmost = selected;
            HandleColumnShuffling(tag, leftmost);
            AlignVisibleColumns(tag);
            return;
        }
        if (selected > tag->m_columnIndexes[tag->m_numVisColumns - 1]) {
            leftmost = selected + (locked - tag->m_numVisColumns) + 1;
            HandleColumnShuffling(tag, leftmost);
            AlignVisibleColumns(tag);
            return;
        }
    }
}

extern "C" SECTION(HandleColumnShuffling) void HandleColumnShuffling(GridTagState *tag, int leftmostCol)
{
    int i;
    if (leftmostCol < 0) __SVO_Assert_Handler(svoGridTagSource, 0x6CB);
    if (leftmostCol > tag->m_numTotalColumns - tag->m_numVisColumns + tag->m_numLockedColumns)
        __SVO_Assert_Handler(svoGridTagSource, 0x6CC);
    if (tag->m_numLockedColumns > 0) {
        for (i = 0; i < tag->m_numLockedColumns; ++i)
            if (tag->m_columnIndexes[i] != i) __SVO_Assert_Handler(svoGridTagSource, 0x6D2);
    }
    for (i = tag->m_numLockedColumns; i < tag->m_numVisColumns; ++i) {
        if (i + leftmostCol - tag->m_numLockedColumns >= tag->m_numTotalColumns)
            __SVO_Assert_Handler(svoGridTagSource, 0x6D8);
        tag->m_columnIndexes[i] = i + leftmostCol - tag->m_numLockedColumns;
    }
}
