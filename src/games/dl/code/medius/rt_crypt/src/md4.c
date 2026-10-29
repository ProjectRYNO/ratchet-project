#include "common.h"
#include "md4.h"

#define MEDIUS_MD4_SECTION(name) __attribute__((section(".medius_md4_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_md4_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern void *memset(void *pointer, int value, unsigned int size);
extern void *memcpy(void *destination, const void *source, unsigned int size);

#define S11 3
#define S12 7
#define S13 11
#define S14 19
#define S21 3
#define S22 5
#define S23 9
#define S24 13
#define S31 3
#define S32 9
#define S33 11
#define S34 15

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (y)) | ((x) & (z)) | ((y) & (z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
#define FF(a, b, c, d, x, s) { (a) += F((b), (c), (d)) + (x); (a) = ROTATE_LEFT((a), (s)); }
#define GG(a, b, c, d, x, s) { (a) += G((b), (c), (d)) + (x) + 0x5A827999; (a) = ROTATE_LEFT((a), (s)); }
#define HH(a, b, c, d, x, s) { (a) += H((b), (c), (d)) + (x) + 0x6ED9EBA1; (a) = ROTATE_LEFT((a), (s)); }

void MEDIUS_MD4_SECTION(KM_MD4) KM_MD4(unsigned char *pMessage, unsigned int cbMessageSize, unsigned char *digest)
{
    MD4_CTX context;

    md4Init(&context);
    md4Update(&context, pMessage, cbMessageSize);
    md4Final(&context, digest);
}

void MEDIUS_MD4_SECTION(md4Init) md4Init(MD4_CTX *pMD4)
{
    pMD4->count[0] = pMD4->count[1] = 0;
    pMD4->state[0] = 0x67452301;
    pMD4->state[1] = 0xEFCDAB89;
    pMD4->state[2] = 0x98BADCFE;
    pMD4->state[3] = 0x10325476;
}

void MEDIUS_MD4_SECTION(md4Update) md4Update(MD4_CTX *pMD4, unsigned char *input, unsigned int inputLen)
{
    unsigned int i;
    unsigned int index;
    unsigned int partLen;

    index = (pMD4->count[0] >> 3) & 0x3F;
    if ((pMD4->count[0] += inputLen << 3) < (inputLen << 3)) pMD4->count[1]++;
    pMD4->count[1] += inputLen >> 29;
    partLen = 64 - index;
    if (inputLen >= partLen) {
        memcpy(&pMD4->buffer[index], input, partLen);
        md4Transform(pMD4, pMD4->buffer);
        for (i = partLen; i + 63 < inputLen; i += 64) md4Transform(pMD4, &input[i]);
        index = 0;
    } else {
        i = 0;
    }
    memcpy(&pMD4->buffer[index], &input[i], inputLen - i);
}

void MEDIUS_MD4_SECTION(md4Final) md4Final(MD4_CTX *pMD4, unsigned char *digest)
{
    unsigned char bits[8];
    unsigned int index;
    unsigned int padLen;

    Encode(bits, pMD4->count, 8);
    index = (pMD4->count[0] >> 3) & 0x3F;
    padLen = (index < 56) ? (56 - index) : (120 - index);
    md4Update(pMD4, rtCryptMd4Padding, padLen);
    md4Update(pMD4, bits, 8);
    Encode(digest, pMD4->state, 16);
    memset(pMD4, 0, sizeof(*pMD4));
}

void MEDIUS_MD4_SECTION(md4Transform) md4Transform(MD4_CTX *pMD4, unsigned char *block)
{
    unsigned int a = pMD4->state[0], b = pMD4->state[1], c = pMD4->state[2], d = pMD4->state[3], x[16];

    Decode(x, block, 64);

    FF(a, b, c, d, x[0], S11);
    FF(d, a, b, c, x[1], S12);
    FF(c, d, a, b, x[2], S13);
    FF(b, c, d, a, x[3], S14);
    FF(a, b, c, d, x[4], S11);
    FF(d, a, b, c, x[5], S12);
    FF(c, d, a, b, x[6], S13);
    FF(b, c, d, a, x[7], S14);
    FF(a, b, c, d, x[8], S11);
    FF(d, a, b, c, x[9], S12);
    FF(c, d, a, b, x[10], S13);
    FF(b, c, d, a, x[11], S14);
    FF(a, b, c, d, x[12], S11);
    FF(d, a, b, c, x[13], S12);
    FF(c, d, a, b, x[14], S13);
    FF(b, c, d, a, x[15], S14);

    GG(a, b, c, d, x[0], S21);
    GG(d, a, b, c, x[4], S22);
    GG(c, d, a, b, x[8], S23);
    GG(b, c, d, a, x[12], S24);
    GG(a, b, c, d, x[1], S21);
    GG(d, a, b, c, x[5], S22);
    GG(c, d, a, b, x[9], S23);
    GG(b, c, d, a, x[13], S24);
    GG(a, b, c, d, x[2], S21);
    GG(d, a, b, c, x[6], S22);
    GG(c, d, a, b, x[10], S23);
    GG(b, c, d, a, x[14], S24);
    GG(a, b, c, d, x[3], S21);
    GG(d, a, b, c, x[7], S22);
    GG(c, d, a, b, x[11], S23);
    GG(b, c, d, a, x[15], S24);

    HH(a, b, c, d, x[0], S31);
    HH(d, a, b, c, x[8], S32);
    HH(c, d, a, b, x[4], S33);
    HH(b, c, d, a, x[12], S34);
    HH(a, b, c, d, x[2], S31);
    HH(d, a, b, c, x[10], S32);
    HH(c, d, a, b, x[6], S33);
    HH(b, c, d, a, x[14], S34);
    HH(a, b, c, d, x[1], S31);
    HH(d, a, b, c, x[9], S32);
    HH(c, d, a, b, x[5], S33);
    HH(b, c, d, a, x[13], S34);
    HH(a, b, c, d, x[3], S31);
    HH(d, a, b, c, x[11], S32);
    HH(c, d, a, b, x[7], S33);
    HH(b, c, d, a, x[15], S34);

    pMD4->state[0] += a;
    pMD4->state[1] += b;
    pMD4->state[2] += c;
    pMD4->state[3] += d;
    memset(x, 0, sizeof(x));
}

void MEDIUS_MD4_SECTION(Encode) Encode(unsigned char *output, unsigned int *input, unsigned int len)
{
    unsigned int i, j;

    for (i = 0, j = 0; j < len; i++, j += 4) {
        output[j] = (unsigned char)(input[i] & 0xFF);
        output[j + 1] = (unsigned char)((input[i] >> 8) & 0xFF);
        output[j + 2] = (unsigned char)((input[i] >> 16) & 0xFF);
        output[j + 3] = (unsigned char)((input[i] >> 24) & 0xFF);
    }
}

void MEDIUS_MD4_SECTION(Decode) Decode(unsigned int *output, unsigned char *input, unsigned int len)
{
    unsigned int i, j;

    for (i = 0, j = 0; j < len; i++, j += 4)
        output[i] = ((unsigned int)input[j]) | (((unsigned int)input[j + 1]) << 8) |
                    (((unsigned int)input[j + 2]) << 16) | (((unsigned int)input[j + 3]) << 24);
}
