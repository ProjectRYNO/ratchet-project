#ifndef MEDIUS_LARGEINT_H
#define MEDIUS_LARGEINT_H

// 4096-bit unsigned integers for the RSA code, least significant word first.
// Name and layout from the retail ELF debug information.
#define LINT_WORDS 128

typedef struct { // 0x200
    /* 0x000 */ unsigned int data[LINT_WORDS];
} lint;

#ifdef __cplusplus
extern "C" {
#endif

void lintSetSmallValue(lint *pI, unsigned int value);
int IsEven(lint *pI);
int IsZero(lint *pI);
void lintSetBit(lint *pI, unsigned int nBit);
void lintIncrement(lint *pI, unsigned int value);
void MOD(lint *pResult, lint *pI1, lint *pI2);
void QRMOD(lint *pX, lint *pM, lint *pQ, lint *pR);

// ps2/LargeInt platform routines (retained assembly).
unsigned int lintGetBits(lint *pI);
int IsNotSmaller(lint *pI1, lint *pI2);
void ShiftRight(lint *pI, unsigned int nBits);
void ShiftLeft(lint *pI, unsigned int nBits);
void lintSubIP(lint *pI1, lint *pI2);
void MODIP(lint *pI1, lint *pI2);

#ifdef __cplusplus
}
#endif

#endif
