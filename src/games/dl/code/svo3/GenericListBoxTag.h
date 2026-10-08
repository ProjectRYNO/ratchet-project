#ifndef GENERICLISTBOXTAG_H
#define GENERICLISTBOXTAG_H
#include "SVTag.h"
#include "SVChronograph.h"

typedef unsigned int svo_listbox_handle;
struct GenericListBoxTagState;
typedef struct { // 0x84 (vtable prefix)
    /* 0x00 */ unsigned char unrecovered00[0x5C];
    /* 0x5C */ void (*clearList)(GenericListBoxTagState *tag);
    /* 0x60 */ unsigned char unrecovered60[0x20];
    /* 0x80 */ long (*getIndexOfHandle)(GenericListBoxTagState *tag, svo_listbox_handle handle);
} GenericListBoxTagVtablePrefix;

struct GenericListBoxTagState { // 0xE4
    /* 0x00 */ SVTag base;
    /* 0xB4 */ unsigned int m_highlightFillColor;
    /* 0xB8 */ unsigned int m_highlightLineColor;
    /* 0xBC */ char *m_class;
    /* 0xC0 */ svo_listbox_handle *m_handles;
    /* 0xC4 */ int m_maxNumItems;
    /* 0xC8 */ int m_maxVisibleItems;
    /* 0xCC */ int m_numItems;
    /* 0xD0 */ int m_selectedIndex;
    /* 0xD4 */ int m_topVisibleIndex;
    /* 0xD8 */ SVChronographState *m_pTimer;
    /* 0xDC */ int m_turnOffDraw;
    /* 0xE0 */ unsigned int *m_entryTagIDs;
};
#endif
