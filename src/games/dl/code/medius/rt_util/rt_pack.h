#ifndef RT_PACK_H
#define RT_PACK_H

#define RT_PACK 1
#define RT_UNPACK 2
#define RT_INVALID_PARAM 2
#define RT_NO_SPC 8
#define RT_INVALID_CSTRING 9

// Prototype dltypes.txt layout; retail rt_init_pack_buffer stores all five fields.
typedef struct { // 0x14
    /* 0x00 */ char *begin;
    /* 0x04 */ char *end;
    /* 0x08 */ char *cursor;
    /* 0x0C */ int bitOffset;
    /* 0x10 */ int lastError;
} RT_PACK_BUFFER;

#ifdef __cplusplus
extern "C" {
#endif

int rt_init_pack_buffer(RT_PACK_BUFFER *buffer, char *begin, char *end);
int rt_pack_anything(int mode, RT_PACK_BUFFER *buffer, void *data, unsigned int size);
int rt_pack_1byte(int mode, RT_PACK_BUFFER *buffer, char *value);
int rt_pack_cu2byte(int mode, RT_PACK_BUFFER *buffer, unsigned short *value);
int rt_pack_cstring(int mode, RT_PACK_BUFFER *buffer, char *string);

#ifdef __cplusplus
}
#endif

#endif
