#ifndef LISTBOXTAG_H
#define LISTBOXTAG_H
#include "SVTag.h"
#include "SVChronograph.h"

typedef struct { // 0x1C
    /* 0x00 */ char *displayStr;
    /* 0x04 */ char *h_ref;
    /* 0x08 */ unsigned int linkOption;
    /* 0x0C */ char *tagClass;
    /* 0x10 */ char *name;
    /* 0x14 */ char *info;
    /* 0x18 */ unsigned int tagid;
} ListBoxItem;

typedef struct { // 0x288
    /* 0x000 */ SVTag base;
    /* 0x0B4 */ int m_fontSize;
    /* 0x0B8 */ int m_align;
    /* 0x0BC */ float m_displayLength;
    /* 0x0C0 */ ListBoxItem *m_items[100];
    /* 0x250 */ int m_maxNumItems;
    /* 0x254 */ int m_maxVisibleItems;
    /* 0x258 */ int m_numItems;
    /* 0x25C */ int m_selectedIndex;
    /* 0x260 */ int m_topVisibleIndex;
    /* 0x264 */ int m_bPopulatedByPage;
    /* 0x268 */ unsigned int m_selectedItemColor;
    /* 0x26C */ unsigned int m_defaultItemColor;
    /* 0x270 */ float m_lineSpacing;
    /* 0x274 */ float m_buttonHeight;
    /* 0x278 */ float m_scrollBarPercentage;
    /* 0x27C */ SVChronographState *m_pTimer;
    /* 0x280 */ int m_turnOffDraw;
    /* 0x284 */ int m_selectFocusAreaMode;
} ListBoxTagState;
#endif
