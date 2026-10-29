#include "common.h"
#include "md5.h"

#define MEDIUS_MD5_SECTION(name) __attribute__((section(".medius_md5_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_md5_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern void *memset(void *pointer, int value, unsigned int size);
extern void *memcpy(void *destination, const void *source, unsigned int size);

void MEDIUS_MD5_SECTION(KM_MD5) KM_MD5(unsigned char *pMessage, unsigned int cbMessageSize, unsigned char *digest)
{
    MD5_CTX context;

    md5Init(&context);
    md5Update(&context, pMessage, cbMessageSize);
    md5Final(digest, &context);
}

void MEDIUS_MD5_SECTION(KM_Salted_MD5) KM_Salted_MD5(unsigned char *pSalt, unsigned int cbSaltSize, unsigned char *pMessage, unsigned int cbMessageSize,
                   unsigned char *Digest)
{
    MD5_CTX context;

    md5Init(&context);
    if (pSalt && cbSaltSize) md5Update(&context, pSalt, cbSaltSize);
    md5Update(&context, pMessage, cbMessageSize);
    md5Final(Digest, &context);
}

void MEDIUS_MD5_SECTION(md5Init) md5Init(MD5_CTX *context)
{
    context->count[0] = context->count[1] = 0;
    context->state[0] = 0x67452301;
    context->state[1] = 0xEFCDAB89;
    context->state[2] = 0x98BADCFE;
    context->state[3] = 0x10325476;
}

void MEDIUS_MD5_SECTION(md5Update) md5Update(MD5_CTX *context, unsigned char *input, unsigned int inputLen)
{
    unsigned int index;
    unsigned int partLen;

    index = context->count[0] & 0x3F;
    if ((context->count[0] += inputLen) < inputLen) context->count[1]++;
    partLen = 64 - index;
    if (inputLen >= partLen) {
        memcpy(&context->buffer[index], input, partLen);
        index = 0;
        md5Transform(context);
        inputLen -= partLen;
        input += partLen;
        while (inputLen >= 64) {
            *(MD5_BLOCK *)context->buffer = *(MD5_BLOCK *)input;
            inputLen -= 64;
            input += 64;
            md5Transform(context);
        }
    }
    memcpy(&context->buffer[index], input, inputLen);
}

void MEDIUS_MD5_SECTION(md5Final) md5Final(unsigned char *digest, MD5_CTX *context)
{
    unsigned char bits[16];
    unsigned int count[2];
    unsigned int index;
    unsigned int padLen;

    count[0] = context->count[0];
    count[1] = context->count[1];
    index = count[0] & 0x3F;
    padLen = (index < 56) ? (56 - index) : (120 - index);
    md5Update(context, rtCryptMd5Padding, padLen);
    count[1] = (count[1] << 3) + (count[0] >> 29);
    count[0] <<= 3;
    md5Encode(bits, count, 8);
    md5Update(context, bits, 8);
    md5Encode(digest, context->state, 16);
    memset(context, 0, sizeof(*context));
}
