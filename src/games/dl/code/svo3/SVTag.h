#ifndef SVTAG_H
#define SVTAG_H

#include "SVTagModule.h"
#include "Navigation.h"
#include "CAllContextData.h"

struct SVTag;
typedef struct { // 0x4C (vtable prefix)
    /* 0x00 */ unsigned char unrecovered00[8];
    /* 0x08 */ void (*destroy)(SVTag *tag, unsigned int flags);
    /* 0x0C */ unsigned char unrecovered0C[8];
    /* 0x14 */ void (*Update)(SVTag *tag, CPage *page);
    /* 0x18 */ unsigned char unrecovered18[8];
    /* 0x20 */ long (*IsSelected)(SVTag *tag);
    /* 0x24 */ void *unknown24;
    /* 0x28 */ long (*IsSelectable)(SVTag *tag);
    /* 0x2C */ unsigned char unrecovered2C[0x10];
    /* 0x3C */ char *(*GetTagName)(SVTag *tag);
    /* 0x40 */ void *unknown40;
    /* 0x44 */ void *unknown44;
    /* 0x48 */ void (*SetVisible)(SVTag *tag, int visible);
} SVTagVtablePrefix;

// Retail base layout, corroborated by prototype dltypes and field accesses.
struct SVTag { // 0xB4
    /* 0x00 */ iks *m_xml;
    /* 0x04 */ unsigned int m_tagid;
    /* 0x08 */ int m_bSelected;
    /* 0x0C */ int m_bIgnoreInput;
    /* 0x10 */ int m_bSelectable;
    /* 0x14 */ int m_bOptional;
    /* 0x18 */ float m_x;
    /* 0x1C */ float m_y;
    /* 0x20 */ float m_z;
    /* 0x24 */ float m_width;
    /* 0x28 */ float m_height;
    /* 0x2C */ unsigned int m_lineColor;
    /* 0x30 */ unsigned int m_fillColor;
    /* 0x34 */ char *m_name;
    /* 0x38 */ char m_tagTypeName[64];
    /* 0x78 */ char *m_toolTip;
    /* 0x7C */ char *m_toolTipTagName;
    /* 0x80 */ CAllContextData *m_contexts;
    /* 0x84 */ CNavInfoState m_navInfo;
    /* 0x94 */ char *m_info;
    /* 0x98 */ int m_isDefTextEntry;
    /* 0x9C */ int m_isDefTextScroll;
    /* 0xA0 */ char *m_tagClass;
    /* 0xA4 */ int m_bIsVisible;
    /* 0xA8 */ int m_bNeverSelectable;
    /* 0xAC */ unsigned char m_ucType;
    /* 0xAD */ unsigned char paddingAD[3];
    /* 0xB0 */ const SVTagVtablePrefix *vtable;
};
extern "C" {
void SVTagConstruct(SVTag *tag, iks *xml, CAllContextData *contexts) __asm__("SVTag");
void SVTagDelete(SVTag *tag) __asm__("operator.delete___dupe7");
void FreeContexts(SVTag *tag);
extern const SVTagVtablePrefix svoTagVtable;
}
#endif
