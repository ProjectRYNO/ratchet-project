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

struct TextAreaTagState { // 0x194
    /* 0x000 */ SVTag base;
    /* 0x0b4 */ char *m_text;
    /* 0x0b8 */ int m_maxTextSize;
    /* 0x0bc */ int m_maxTextLines;
    /* 0x0c0 */ void *m_pKBData;
    /* 0x0c4 */ int m_numKeyboards;
    /* 0x0c8 */ int m_scrollFrame;
    /* 0x0cc */ int m_curParseOffset;
    /* 0x0d0 */ int m_curParseLine;
    /* 0x0d4 */ int m_curEditOffset;
    /* 0x0d8 */ int m_textEndOffset;
    /* 0x0dc */ int m_upArrowOffset;
    /* 0x0e0 */ int m_downArrowOffset;
    /* 0x0e4 */ int m_leftArrowOffset;
    /* 0x0e8 */ int m_rightArrowOffset;
    /* 0x0ec */ int m_numTotalLines;
    /* 0x0f0 */ int m_minDisplayLine;
    /* 0x0f4 */ int m_curLine;
    /* 0x0f8 */ int m_textEndLine;
    /* 0x0fc */ int m_numLinesInDisplay;
    /* 0x100 */ int m_maxNumViewableLines;
    /* 0x104 */ float m_cursorX;
    /* 0x108 */ float m_cursorY;
    /* 0x10c */ float m_overallLength;
    /* 0x110 */ float m_maxLineLength;
    /* 0x114 */ int m_firstAppendToChat;
    /* 0x118 */ LineInfo *m_textLines;
    /* 0x11c */ int m_canScrollUp;
    /* 0x120 */ int m_canScrollDown;
    /* 0x124 */ int m_blinkCursor;
    /* 0x128 */ int m_drawCursor;
    /* 0x12c */ unsigned int m_textColor;
    /* 0x130 */ unsigned int m_highlightFillColor;
    /* 0x134 */ unsigned int m_highlightLineColor;
    /* 0x138 */ unsigned int m_highlightTextColor;
    /* 0x13c */ int m_isEditable;
    /* 0x140 */ char *m_link;
    /* 0x144 */ int m_fontSize;
    /* 0x148 */ int m_node;
    /* 0x14c */ int m_obj;
    /* 0x150 */ int m_scrollBarNode;
    /* 0x154 */ float m_maxScrollBarNodeTranslate;
    /* 0x158 */ float m_scrollBarWidth;
    /* 0x15c */ float m_scrollBarHeight;
    /* 0x160 */ float m_scrollBarPercentage;
    /* 0x164 */ float m_lineSpacing;
    /* 0x168 */ float m_opacity;
    /* 0x16c */ float m_xAxisPadValue;
    /* 0x170 */ float m_yAxisPadValue;
    /* 0x174 */ float m_nx;
    /* 0x178 */ float m_ny;
    /* 0x17c */ FormTag *m_parentForm;
    /* 0x180 */ int m_tmpCallsToGSW;
    /* 0x184 */ int m_bSubmitAsEncryped;
    /* 0x188 */ int m_bRequiredForSubmit;
    /* 0x18c */ int m_bMultiColorTextArea;
    /* 0x190 */ int m_bSelectedLastFrame;
};
#endif
