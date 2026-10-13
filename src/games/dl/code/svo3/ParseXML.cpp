#include "ParseXML.h"

extern "C" {

#define SECTION(name) __attribute__((section(".svo_ParseXML_" #name)))

SECTION(ParseXML) void ParseXML(ParseXMLState *parser)
{
    parser->vtable = svoParseXMLVtable;
}

}
