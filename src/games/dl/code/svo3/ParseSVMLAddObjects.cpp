#include "ParseSVMLAddObjects.h"

extern "C" {
extern const unsigned char svoParseSVMLAddObjectsVtable[];
extern char svoParseSVMLAddObjectsCheckString[];
#define SECTION(name) __attribute__((section(".svo_ParseSVMLAddObjects_" #name)))

SECTION(_ParseXML) void _ParseXML(ParseXMLState *parser, int flags)
{
    parser->vtable = svoParseXMLVtable;
    if (flags & 1) SvoBuiltinDelete(parser);
}

SECTION(ParseSVMLAddObjects) const void *ParseSVMLAddObjects(ParseXMLState *parser)
{
    ParseXML(parser);
    parser->vtable = svoParseSVMLAddObjectsVtable;
    return svoParseSVMLAddObjectsVtable;
}

SECTION(_ParseSVMLAddObjects) void _ParseSVMLAddObjects(ParseXMLState *parser, int flags)
{
    parser->vtable = svoParseSVMLAddObjectsVtable;
    _ParseXML(parser, 0);
    if (flags & 1) SvoBuiltinDelete(parser);
}

SECTION(ShouldFreeResources) int ShouldFreeResources(ParseXMLState *parser)
{
    return 1;
}

SECTION(GetCheckString) char *GetCheckString(ParseXMLState *parser)
{
    return svoParseSVMLAddObjectsCheckString;
}

SECTION(CallFunction) void CallFunction(ParseXMLState *parser, iks *xml, CPage *page)
{
    addObject(page, xml);
}

}
