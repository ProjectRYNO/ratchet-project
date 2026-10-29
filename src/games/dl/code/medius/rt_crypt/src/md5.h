#ifndef MEDIUS_MD5_H
#define MEDIUS_MD5_H

// RSA Data Security MD5 (RFC 1321) with a byte count instead of a bit count and a
// PS2-specific md5Transform/md5Encode (retained assembly in ps2/md5_platform).
// Names and layout from the retail ELF debug information.
typedef struct { // 0x60
    /* 0x00 */ unsigned int state[4];
    /* 0x10 */ unsigned int count[2];
    /* 0x18 */ unsigned char buffer[64];
    /* 0x58 */ unsigned char padding[8];
} MD5_CTX;

// A 64-byte input block; retail copies whole blocks into MD5_CTX.buffer by assignment.
typedef struct {
    unsigned char bytes[64];
} MD5_BLOCK;

#ifdef __cplusplus
extern "C" {
#endif

// RFC 1321 PADDING: 0x80 followed by zeros (core.data).
extern unsigned char rtCryptMd5Padding[];

void KM_MD5(unsigned char *pMessage, unsigned int cbMessageSize, unsigned char *digest);
void KM_Salted_MD5(unsigned char *pSalt, unsigned int cbSaltSize, unsigned char *pMessage, unsigned int cbMessageSize,
                   unsigned char *Digest);
void md5Init(MD5_CTX *context);
void md5Update(MD5_CTX *context, unsigned char *input, unsigned int inputLen);
void md5Final(unsigned char *digest, MD5_CTX *context);
void md5Transform(MD5_CTX *context);
void md5Encode(unsigned char *output, unsigned int *input, unsigned int len);

#ifdef __cplusplus
}
#endif

#endif
