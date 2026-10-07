#include "ParseSVMLForDownloads.h"

extern "C" {
extern const unsigned char svoParseSVMLForDownloadsVtable[];
extern char svoParseSVMLForDownloadsCheckString[];
#define SECTION(name) __attribute__((section(".svo_ParseSVMLForDownloads_" #name)))

SECTION(ParseSVMLForDownloads) const void *ParseSVMLForDownloads(ParseXMLState *parser)
{
    ParseXML(parser);
    parser->vtable = svoParseSVMLForDownloadsVtable;
    return svoParseSVMLForDownloadsVtable;
}

SECTION(_ParseSVMLForDownloads) void _ParseSVMLForDownloads(ParseXMLState *parser, int flags)
{
    parser->vtable = svoParseSVMLForDownloadsVtable;
    _ParseXML(parser, 0);
    if (flags & 1) SvoBuiltinDelete(parser);
}

SECTION(ShouldFreeResources___dupe2) int ShouldFreeResources___dupe2(ParseXMLState *parser)
{
    return 0;
}

SECTION(GetCheckString___dupe2) char *GetCheckString___dupe2(ParseXMLState *parser)
{
    return svoParseSVMLForDownloadsCheckString;
}

SECTION(CallFunction___dupe2) void CallFunction___dupe2(ParseXMLState *parser, iks *xml, CPage *page)
{
    scanObject(page, xml);
}

}
