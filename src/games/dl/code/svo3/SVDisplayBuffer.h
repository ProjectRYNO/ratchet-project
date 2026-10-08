#ifndef SVDISPLAYBUFFER_H
#define SVDISPLAYBUFFER_H
struct SVTag;
struct iksparser_struct;
#include "../iksemel/src/iks.h"
typedef struct { // 0x408
    /* 0x000 */ iks *xml;
    /* 0x004 */ iksparser_struct *parser;
    /* 0x008 */ SVTag *tagList[256];
} SVDisplayBufferState;
#endif
