#ifndef MEDIUS_RC4_H
#define MEDIUS_RC4_H

// Names and layout from the retail ELF debug information.
typedef struct { // 0x102
    /* 0x000 */ unsigned char state[256];
    /* 0x100 */ unsigned char x;
    /* 0x101 */ unsigned char y;
} RC4_CTX;

#ifdef __cplusplus
extern "C" {
#endif

void RC4Init(RC4_CTX *pCtx, unsigned char *pKey, unsigned int nKeyLen);
void RC4Code(RC4_CTX *pCtx, unsigned char *pData, unsigned int nDataLen);

#ifdef __cplusplus
}
#endif

#endif
