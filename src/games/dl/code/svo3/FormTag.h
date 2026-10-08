#ifndef FORMTAG_H
#define FORMTAG_H
#include "SVTag.h"

struct RadioInputTagState;
struct CheckboxInputTagState;
struct TextInputTagState;
struct HiddenInputTagState;
struct SelectTagState;
struct TextAreaTagState;
struct SubmitInputTagState;
struct FormChildrenInfo_t;

typedef struct { // 0x184
    /* 0x000 */ RadioInputTagState *elements[64];
    /* 0x100 */ char name[64];
    /* 0x140 */ char value[64];
    /* 0x180 */ int numElementsInGroup;
} RadioElementGroup;

struct FormTag { // 0x69EC
    /* 0x0000 */ SVTag base;
    /* 0x00B4 */ int m_numRadioElementGroups;
    /* 0x00B8 */ int m_numCheckboxElements;
    /* 0x00BC */ int m_numTextElements;
    /* 0x00C0 */ int m_numPasswordElements;
    /* 0x00C4 */ int m_numHiddenElements;
    /* 0x00C8 */ int m_numSelectElements;
    /* 0x00CC */ int m_numTextAreaElements;
    /* 0x00D0 */ char m_url[256];
    /* 0x01D0 */ char m_encType[256];
    /* 0x02D0 */ int m_methodType;
    /* 0x02D4 */ int m_method;
    /* 0x02D8 */ int m_bEncryptionErrorOccurred;
    /* 0x02DC */ int m_bValidationSucceeded;
    /* 0x02E0 */ SVTag *m_tagThatFailedValidation;
    /* 0x02E4 */ RadioElementGroup m_radioElementGroups[64];
    /* 0x63E4 */ CheckboxInputTagState *m_checkboxElements[64];
    /* 0x64E4 */ TextInputTagState *m_textElements[64];
    /* 0x65E4 */ TextInputTagState *m_passwordElements[64];
    /* 0x66E4 */ SubmitInputTagState *m_submitElement;
    /* 0x66E8 */ HiddenInputTagState *m_hiddenElements[64];
    /* 0x67E8 */ SelectTagState *m_selectElements[64];
    /* 0x68E8 */ TextAreaTagState *m_textAreaElements[64];
    /* 0x69E8 */ FormChildrenInfo_t *m_pChildrenInfoList;
};
#endif
