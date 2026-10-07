#include "ParseXMLInfo.h"

extern "C" {
extern const unsigned char svoParseXMLInfoVtable[];
extern char svoParseXMLInfoCheckString[];
#define SECTION(name) __attribute__((section(".svo_ParseXMLInfo_" #name)))

SECTION(ParseXMLInfo) const void *ParseXMLInfo(ParseXMLState *parser)
{
    ParseXML(parser);
    parser->vtable = svoParseXMLInfoVtable;
    return svoParseXMLInfoVtable;
}

SECTION(_ParseXMLInfo) void _ParseXMLInfo(ParseXMLState *parser, int flags)
{
    parser->vtable = svoParseXMLInfoVtable;
    _ParseXML(parser, 0);
    if (flags & 1) SvoBuiltinDelete(parser);
}

SECTION(ShouldFreeResources___dupe3) int ShouldFreeResources___dupe3(ParseXMLState *parser)
{
    return 0;
}

SECTION(GetCheckString___dupe3) char *GetCheckString___dupe3(ParseXMLState *parser)
{
    return svoParseXMLInfoCheckString;
}

SECTION(CallFunction___dupe3) void CallFunction___dupe3(ParseXMLState *parser, iks *xml, CPage *page)
{
    scanObject(page, xml);
}

}
