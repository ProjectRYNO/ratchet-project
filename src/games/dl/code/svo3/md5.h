#ifndef MD5_H
#define MD5_H
// Retail uses 64-bit unsigned long, including the high halves of state words.
typedef struct { // 0x70
    /* 0x00 */ unsigned long total[2];
    /* 0x10 */ unsigned long state[4];
    /* 0x30 */ unsigned char buffer[64];
} md5_context;
extern "C" {
void md5_starts(md5_context *);
void md5_process(md5_context *, unsigned char *);
void md5_update(md5_context *, unsigned char *, unsigned long);
void md5_finish(md5_context *, unsigned char *);
char *md5_hex(unsigned char *, char *);
}
#endif
