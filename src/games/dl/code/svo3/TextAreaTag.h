#ifndef TEXTAREATAG_H
#define TEXTAREATAG_H
#include "SVTag.h"
#include "FormTag.h"

typedef struct { // 0x0C
    /* 0x00 */ short lineStartIndex;
    /* 0x02 */ short lineEndIndex;
    /* 0x04 */ unsigned short lineNumber;
    /* 0x06 */ unsigned short padding06;
    /* 0x08 */ unsigned int color;
} LineInfo;

struct TextAreaTagState { // 0x180 (verified prefix)
    /* 0x00 */ SVTag base;
    /* 0xB4 */ char *m_text;
    /* 0xB8 */ int m_maxTextSize;
    /* 0x0BC */ int m_maxTextLines;
    /* 0x0C0 */ unsigned char unrecoveredC0[8];
    /* 0x0C8 */ int m_scrollFrame;
    /* 0x0CC */ int m_curParseOffset;
    /* 0x0D0 */ int m_curParseLine;
    /* 0x0D4 */ int m_curEditOffset;
    /* 0x0D8 */ int m_textEndOffset;
    /* 0x0DC */ int m_upArrowOffset;
    /* 0x0E0 */ int m_downArrowOffset;
    /* 0x0E4 */ int m_leftArrowOffset;
    /* 0x0E8 */ int m_rightArrowOffset;
    /* 0x0EC */ int m_numTotalLines;
    /* 0x0F0 */ int m_minDisplayLine;
    /* 0x0F4 */ int m_curLine;
    /* 0x0F8 */ int m_textEndLine;
    /* 0x0FC */ int m_numLinesInDisplay;
    /* 0x100 */ unsigned char unrecovered100[4];
    /* 0x104 */ float m_cursorX;
    /* 0x108 */ float m_cursorY;
    /* 0x10C */ float m_overallLength;
    /* 0x110 */ unsigned char unrecovered110[4];
    /* 0x114 */ int m_firstAppendToChat;
    /* 0x118 */ LineInfo *m_textLines;
    /* 0x11C */ int m_canScrollUp;
    /* 0x120 */ int m_canScrollDown;
    /* 0x124 */ unsigned char unrecovered124[0x58];
    /* 0x17C */ FormTag *m_parentForm;
};

#endif
