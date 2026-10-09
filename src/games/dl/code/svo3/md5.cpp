#include "string.h"
#include "md5.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_md5_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern "C" {
extern unsigned char svoMD5Padding[];
extern char *svoMD5HexDigits;
}
#define SECTION(name) __attribute__((section(".svo_md5_" #name)))

extern "C" SECTION(md5_starts) void md5_starts(md5_context *ctx)
{
    ctx->state[0] = 0x67452301UL;
    ctx->state[3] = 0x10325476UL;
    ctx->state[1] = 0xEFCDAB89UL;
    ctx->state[2] = 0x98BADCFEUL;
    ctx->total[0] = 0;
    ctx->total[1] = 0;
}

extern "C" SECTION(md5_process) void md5_process(md5_context *ctx, unsigned char *data)
{
    unsigned long words[16];
    for (int i = 0; i < 16; ++i) {
        unsigned char *p = data + i * 4;
        words[i] = (unsigned long)p[0] | ((unsigned long)p[1] << 8) | ((unsigned long)p[2] << 16) | ((unsigned long)p[3] << 24);
    }
    unsigned long a = ctx->state[0];
    unsigned long b = ctx->state[1];
    unsigned long c = ctx->state[2];
    unsigned long d = ctx->state[3];
    a += (d ^ (b & (c ^ d))) + words[0] + 0xD76AA478UL;
    a = ((a << 7) | ((a & 0xFFFFFFFFUL) >> 25)) + b;
    d += (c ^ (a & (b ^ c))) + words[1] + 0xE8C7B756UL;
    d = ((d << 12) | ((d & 0xFFFFFFFFUL) >> 20)) + a;
    c += (b ^ (d & (a ^ b))) + words[2] + 0x242070DBUL;
    c = ((c << 17) | ((c & 0xFFFFFFFFUL) >> 15)) + d;
    b += (a ^ (c & (d ^ a))) + words[3] + 0xC1BDCEEEUL;
    b = ((b << 22) | ((b & 0xFFFFFFFFUL) >> 10)) + c;
    a += (d ^ (b & (c ^ d))) + words[4] + 0xF57C0FAFUL;
    a = ((a << 7) | ((a & 0xFFFFFFFFUL) >> 25)) + b;
    d += (c ^ (a & (b ^ c))) + words[5] + 0x4787C62AUL;
    d = ((d << 12) | ((d & 0xFFFFFFFFUL) >> 20)) + a;
    c += (b ^ (d & (a ^ b))) + words[6] + 0xA8304613UL;
    c = ((c << 17) | ((c & 0xFFFFFFFFUL) >> 15)) + d;
    b += (a ^ (c & (d ^ a))) + words[7] + 0xFD469501UL;
    b = ((b << 22) | ((b & 0xFFFFFFFFUL) >> 10)) + c;
    a += (d ^ (b & (c ^ d))) + words[8] + 0x698098D8UL;
    a = ((a << 7) | ((a & 0xFFFFFFFFUL) >> 25)) + b;
    d += (c ^ (a & (b ^ c))) + words[9] + 0x8B44F7AFUL;
    d = ((d << 12) | ((d & 0xFFFFFFFFUL) >> 20)) + a;
    c += (b ^ (d & (a ^ b))) + words[10] + 0xFFFF5BB1UL;
    c = ((c << 17) | ((c & 0xFFFFFFFFUL) >> 15)) + d;
    b += (a ^ (c & (d ^ a))) + words[11] + 0x895CD7BEUL;
    b = ((b << 22) | ((b & 0xFFFFFFFFUL) >> 10)) + c;
    a += (d ^ (b & (c ^ d))) + words[12] + 0x6B901122UL;
    a = ((a << 7) | ((a & 0xFFFFFFFFUL) >> 25)) + b;
    d += (c ^ (a & (b ^ c))) + words[13] + 0xFD987193UL;
    d = ((d << 12) | ((d & 0xFFFFFFFFUL) >> 20)) + a;
    c += (b ^ (d & (a ^ b))) + words[14] + 0xA679438EUL;
    c = ((c << 17) | ((c & 0xFFFFFFFFUL) >> 15)) + d;
    b += (a ^ (c & (d ^ a))) + words[15] + 0x49B40821UL;
    b = ((b << 22) | ((b & 0xFFFFFFFFUL) >> 10)) + c;
    a += (c ^ (d & (b ^ c))) + words[1] + 0xF61E2562UL;
    a = ((a << 5) | ((a & 0xFFFFFFFFUL) >> 27)) + b;
    d += (b ^ (c & (a ^ b))) + words[6] + 0xC040B340UL;
    d = ((d << 9) | ((d & 0xFFFFFFFFUL) >> 23)) + a;
    c += (a ^ (b & (d ^ a))) + words[11] + 0x265E5A51UL;
    c = ((c << 14) | ((c & 0xFFFFFFFFUL) >> 18)) + d;
    b += (d ^ (a & (c ^ d))) + words[0] + 0xE9B6C7AAUL;
    b = ((b << 20) | ((b & 0xFFFFFFFFUL) >> 12)) + c;
    a += (c ^ (d & (b ^ c))) + words[5] + 0xD62F105DUL;
    a = ((a << 5) | ((a & 0xFFFFFFFFUL) >> 27)) + b;
    d += (b ^ (c & (a ^ b))) + words[10] + 0x02441453UL;
    d = ((d << 9) | ((d & 0xFFFFFFFFUL) >> 23)) + a;
    c += (a ^ (b & (d ^ a))) + words[15] + 0xD8A1E681UL;
    c = ((c << 14) | ((c & 0xFFFFFFFFUL) >> 18)) + d;
    b += (d ^ (a & (c ^ d))) + words[4] + 0xE7D3FBC8UL;
    b = ((b << 20) | ((b & 0xFFFFFFFFUL) >> 12)) + c;
    a += (c ^ (d & (b ^ c))) + words[9] + 0x21E1CDE6UL;
    a = ((a << 5) | ((a & 0xFFFFFFFFUL) >> 27)) + b;
    d += (b ^ (c & (a ^ b))) + words[14] + 0xC33707D6UL;
    d = ((d << 9) | ((d & 0xFFFFFFFFUL) >> 23)) + a;
    c += (a ^ (b & (d ^ a))) + words[3] + 0xF4D50D87UL;
    c = ((c << 14) | ((c & 0xFFFFFFFFUL) >> 18)) + d;
    b += (d ^ (a & (c ^ d))) + words[8] + 0x455A14EDUL;
    b = ((b << 20) | ((b & 0xFFFFFFFFUL) >> 12)) + c;
    a += (c ^ (d & (b ^ c))) + words[13] + 0xA9E3E905UL;
    a = ((a << 5) | ((a & 0xFFFFFFFFUL) >> 27)) + b;
    d += (b ^ (c & (a ^ b))) + words[2] + 0xFCEFA3F8UL;
    d = ((d << 9) | ((d & 0xFFFFFFFFUL) >> 23)) + a;
    c += (a ^ (b & (d ^ a))) + words[7] + 0x676F02D9UL;
    c = ((c << 14) | ((c & 0xFFFFFFFFUL) >> 18)) + d;
    b += (d ^ (a & (c ^ d))) + words[12] + 0x8D2A4C8AUL;
    b = ((b << 20) | ((b & 0xFFFFFFFFUL) >> 12)) + c;
    a += (b ^ c ^ d) + words[5] + 0xFFFA3942UL;
    a = ((a << 4) | ((a & 0xFFFFFFFFUL) >> 28)) + b;
    d += (a ^ b ^ c) + words[8] + 0x8771F681UL;
    d = ((d << 11) | ((d & 0xFFFFFFFFUL) >> 21)) + a;
    c += (d ^ a ^ b) + words[11] + 0x6D9D6122UL;
    c = ((c << 16) | ((c & 0xFFFFFFFFUL) >> 16)) + d;
    b += (c ^ d ^ a) + words[14] + 0xFDE5380CUL;
    b = ((b << 23) | ((b & 0xFFFFFFFFUL) >> 9)) + c;
    a += (b ^ c ^ d) + words[1] + 0xA4BEEA44UL;
    a = ((a << 4) | ((a & 0xFFFFFFFFUL) >> 28)) + b;
    d += (a ^ b ^ c) + words[4] + 0x4BDECFA9UL;
    d = ((d << 11) | ((d & 0xFFFFFFFFUL) >> 21)) + a;
    c += (d ^ a ^ b) + words[7] + 0xF6BB4B60UL;
    c = ((c << 16) | ((c & 0xFFFFFFFFUL) >> 16)) + d;
    b += (c ^ d ^ a) + words[10] + 0xBEBFBC70UL;
    b = ((b << 23) | ((b & 0xFFFFFFFFUL) >> 9)) + c;
    a += (b ^ c ^ d) + words[13] + 0x289B7EC6UL;
    a = ((a << 4) | ((a & 0xFFFFFFFFUL) >> 28)) + b;
    d += (a ^ b ^ c) + words[0] + 0xEAA127FAUL;
    d = ((d << 11) | ((d & 0xFFFFFFFFUL) >> 21)) + a;
    c += (d ^ a ^ b) + words[3] + 0xD4EF3085UL;
    c = ((c << 16) | ((c & 0xFFFFFFFFUL) >> 16)) + d;
    b += (c ^ d ^ a) + words[6] + 0x04881D05UL;
    b = ((b << 23) | ((b & 0xFFFFFFFFUL) >> 9)) + c;
    a += (b ^ c ^ d) + words[9] + 0xD9D4D039UL;
    a = ((a << 4) | ((a & 0xFFFFFFFFUL) >> 28)) + b;
    d += (a ^ b ^ c) + words[12] + 0xE6DB99E5UL;
    d = ((d << 11) | ((d & 0xFFFFFFFFUL) >> 21)) + a;
    c += (d ^ a ^ b) + words[15] + 0x1FA27CF8UL;
    c = ((c << 16) | ((c & 0xFFFFFFFFUL) >> 16)) + d;
    b += (c ^ d ^ a) + words[2] + 0xC4AC5665UL;
    b = ((b << 23) | ((b & 0xFFFFFFFFUL) >> 9)) + c;
    a += (c ^ (b | ~d)) + words[0] + 0xF4292244UL;
    a = ((a << 6) | ((a & 0xFFFFFFFFUL) >> 26)) + b;
    d += (b ^ (a | ~c)) + words[7] + 0x432AFF97UL;
    d = ((d << 10) | ((d & 0xFFFFFFFFUL) >> 22)) + a;
    c += (a ^ (d | ~b)) + words[14] + 0xAB9423A7UL;
    c = ((c << 15) | ((c & 0xFFFFFFFFUL) >> 17)) + d;
    b += (d ^ (c | ~a)) + words[5] + 0xFC93A039UL;
    b = ((b << 21) | ((b & 0xFFFFFFFFUL) >> 11)) + c;
    a += (c ^ (b | ~d)) + words[12] + 0x655B59C3UL;
    a = ((a << 6) | ((a & 0xFFFFFFFFUL) >> 26)) + b;
    d += (b ^ (a | ~c)) + words[3] + 0x8F0CCC92UL;
    d = ((d << 10) | ((d & 0xFFFFFFFFUL) >> 22)) + a;
    c += (a ^ (d | ~b)) + words[10] + 0xFFEFF47DUL;
    c = ((c << 15) | ((c & 0xFFFFFFFFUL) >> 17)) + d;
    b += (d ^ (c | ~a)) + words[1] + 0x85845DD1UL;
    b = ((b << 21) | ((b & 0xFFFFFFFFUL) >> 11)) + c;
    a += (c ^ (b | ~d)) + words[8] + 0x6FA87E4FUL;
    a = ((a << 6) | ((a & 0xFFFFFFFFUL) >> 26)) + b;
    d += (b ^ (a | ~c)) + words[15] + 0xFE2CE6E0UL;
    d = ((d << 10) | ((d & 0xFFFFFFFFUL) >> 22)) + a;
    c += (a ^ (d | ~b)) + words[6] + 0xA3014314UL;
    c = ((c << 15) | ((c & 0xFFFFFFFFUL) >> 17)) + d;
    b += (d ^ (c | ~a)) + words[13] + 0x4E0811A1UL;
    b = ((b << 21) | ((b & 0xFFFFFFFFUL) >> 11)) + c;
    a += (c ^ (b | ~d)) + words[4] + 0xF7537E82UL;
    a = ((a << 6) | ((a & 0xFFFFFFFFUL) >> 26)) + b;
    d += (b ^ (a | ~c)) + words[11] + 0xBD3AF235UL;
    d = ((d << 10) | ((d & 0xFFFFFFFFUL) >> 22)) + a;
    c += (a ^ (d | ~b)) + words[2] + 0x2AD7D2BBUL;
    c = ((c << 15) | ((c & 0xFFFFFFFFUL) >> 17)) + d;
    b += (d ^ (c | ~a)) + words[9] + 0xEB86D391UL;
    b = ((b << 21) | ((b & 0xFFFFFFFFUL) >> 11)) + c;
    ctx->state[0] += a;
    ctx->state[3] += d;
    ctx->state[2] += c;
    ctx->state[1] += b;
}

extern "C" SECTION(md5_update) void md5_update(md5_context *ctx, unsigned char *input, unsigned long length)
{
    if (!length) return;
    int left = (ctx->total[0] >> 3) & 63;
    int fill = 64 - left;
    unsigned long bits = length << 3;
    unsigned long total = (ctx->total[0] + bits) & 0xFFFFFFFFUL;
    ctx->total[1] += (length >> 29) + (total < bits);
    ctx->total[0] = total;
    if (left && length >= fill) {
        memcpy(ctx->buffer + (int)left, input, (int)fill);
        length -= fill;
        md5_process(ctx, ctx->buffer);
        input += (int)fill;
        left = 0;
    }
    while (length >= 64) {
        md5_process(ctx, input);
        input += 64;
        length -= 64;
    }
    if (length) memcpy(ctx->buffer + (int)left, input, (int)length);
}

extern "C" SECTION(md5_finish) void md5_finish(md5_context *ctx, unsigned char *digest)
{
    unsigned char bits[8];
    for (int i = 0; i < 8; ++i) bits[i] = ctx->total[i / 4] >> ((i % 4) * 8);
    unsigned long last = (ctx->total[0] >> 3) & 63;
    md5_update(ctx, svoMD5Padding, (last < 56 ? 56 : 120) - last);
    md5_update(ctx, bits, 8);
    for (int i = 0; i < 16; ++i) digest[i] = ctx->state[i / 4] >> ((i % 4) * 8);
}

extern "C" SECTION(md5_hex) char *md5_hex(unsigned char *digest, char *text)
{
    unsigned char *end = digest + 16;
    char *out = text;
    while (digest < end) {
        *out++ = svoMD5HexDigits[*digest >> 4];
        *out++ = svoMD5HexDigits[*digest++ & 15];
    }
    *out = 0;
    return text;
}
