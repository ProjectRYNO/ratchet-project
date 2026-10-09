#ifndef PARSEXML_H
#define PARSEXML_H
#include "SVTagModule.h"
struct CPage;
struct ParseXMLState;
typedef struct { // 0x18 (vtable prefix)
    /* 0x00 */ unsigned char unrecovered00[0x0C];
    /* 0x0C */ long (*ShouldFreeResources)(ParseXMLState *parser);
    /* 0x10 */ char *(*GetCheckString)(ParseXMLState *parser);
    /* 0x14 */ void (*CallFunction)(ParseXMLState *parser, iks *xml, CPage *page);
} ParseXMLVtablePrefix;
typedef struct ParseXMLState { // 0x04
    /* 0x00 */ const void *vtable;
} ParseXMLState;
extern "C" {
const void *ParseXML(ParseXMLState *parser);
void _ParseXML(ParseXMLState *parser, int flags);
void SvoBuiltinDelete(void *memory) __asm__("__builtin_delete");
void addObject(CPage *page, iks *xml);
void scanObject(CPage *page, iks *xml);
extern const unsigned char svoParseXMLVtable[];
}
#endif
