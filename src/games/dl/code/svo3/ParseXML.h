#ifndef PARSEXML_H
#define PARSEXML_H
#include "SVTagModule.h"
struct CPage;
typedef struct { // 0x04
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
