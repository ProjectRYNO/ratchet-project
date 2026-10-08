#ifndef GRIDTAG_H
#define GRIDTAG_H
#include "SVTag.h"
#include "SVChronograph.h"

typedef struct { // 0x18
    /* 0x00 */ char *cell_text;
    /* 0x04 */ char *cell_link;
    /* 0x08 */ char *cell_tooltip;
    /* 0x0C */ char *cellClass;
    /* 0x10 */ int linkOption;
    /* 0x14 */ unsigned int cell_tagID;
} SVGridCell;

typedef struct { // 0x20
    /* 0x00 */ char *colName;
    /* 0x04 */ char *colHdrLink;
    /* 0x08 */ char *colTooltip;
    /* 0x0C */ int isSelectable;
    /* 0x10 */ float width;
    /* 0x14 */ float col_x;
    /* 0x18 */ int linkOption;
    /* 0x1C */ int colAlign;
} SVGridColumn;

typedef struct { // 0x10
    /* 0x0 */ float height;
    /* 0x4 */ float row_y;
    /* 0x8 */ char *rowClass;
    /* 0xC */ unsigned int row_tagID;
} SVGridRow;

typedef struct { // 0x18
    /* 0x00 */ SVGridRow row;
    /* 0x10 */ SVGridCell *cells;
    /* 0x14 */ unsigned int textColor;
} SVMyRecordRow;

typedef struct { // 0x184
    /* 0x000 */ SVTag base;
    /* 0x0B4 */ int m_numVisColumns;
    /* 0x0B8 */ int m_numTotalColumns;
    /* 0x0BC */ int m_numVisRowsWithCells;
    /* 0x0C0 */ int m_origNumVisRows;
    /* 0x0C4 */ int m_numTotalRows;
    /* 0x0C8 */ int m_currTopRow;
    /* 0x0CC */ SVGridCell **m_cells;
    /* 0x0D0 */ SVGridColumn *m_columns;
    /* 0x0D4 */ SVGridRow *m_rows;
    /* 0x0D8 */ SVMyRecordRow *m_myRecordRow;
    /* 0x0DC */ float m_defaultColWidth;
    /* 0x0E0 */ float m_defaultRowHeight;
    /* 0x0E4 */ int m_currCellRowNum;
    /* 0x0E8 */ int m_currCellColNum;
    /* 0x0EC */ int m_numLockedColumns;
    /* 0x0F0 */ int *m_columnIndexes;
    /* 0x0F4 */ int m_headerFontSize;
    /* 0x0F8 */ float m_headerHeight;
    /* 0x0FC */ int m_headerSelected;
    /* 0x100 */ char *m_headerClass;
    /* 0x104 */ unsigned int m_header_tagID;
    /* 0x108 */ unsigned int m_headerTextColor;
    /* 0x10C */ unsigned int m_headerHighlightTextColor;
    /* 0x110 */ unsigned int m_headerFillColor;
    /* 0x114 */ unsigned int m_headerHighlightFillColor;
    /* 0x118 */ unsigned int m_headerLineColor;
    /* 0x11C */ unsigned int m_headerHighlightLineColor;
    /* 0x120 */ int m_defCellFontSize;
    /* 0x124 */ int m_defCellAlign;
    /* 0x128 */ unsigned int m_defCellTextColor;
    /* 0x12C */ unsigned int m_defCellLineColor;
    /* 0x130 */ unsigned int m_defCellFillColor;
    /* 0x134 */ unsigned int m_highlightCellTextColor;
    /* 0x138 */ unsigned int m_highlightCellLineColor;
    /* 0x13C */ unsigned int m_highlightCellFillColor;
    /* 0x140 */ int m_borderWidth;
    /* 0x144 */ int m_borderHeight;
    /* 0x148 */ unsigned int m_borderOutlineColor;
    /* 0x14C */ unsigned int m_borderFillColor;
    /* 0x150 */ char *m_borderClass;
    /* 0x154 */ unsigned int m_border_tagID;
    /* 0x158 */ unsigned int m_borderHighlightOutlineColor;
    /* 0x15C */ unsigned int m_borderHighlightFillColor;
    /* 0x160 */ float m_spaceBetweenLastRowAndMyRecord;
    /* 0x164 */ float m_vert_sb_width;
    /* 0x168 */ float m_horz_sb_height;
    /* 0x16C */ char *m_scrollbar_class;
    /* 0x170 */ int m_bSideWrapAllowed;
    /* 0x174 */ int m_bVerticalWrapAllowed;
    /* 0x178 */ int m_bIsModalGrid;
    /* 0x17C */ int m_bIsClickedIn;
    /* 0x180 */ SVChronographState *m_pTimer;
} GridTagState;

#endif
