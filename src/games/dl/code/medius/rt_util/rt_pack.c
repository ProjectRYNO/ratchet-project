#include "common.h"
#include "rt_pack.h"

#define MEDIUS_PACK_SECTION(name) __attribute__((section(".medius_pack_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME)     __asm__(".section .medius_pack_" #NAME ",\"ax\",@progbits
"             ".set noat
.set noreorder
"             ".include \"" FOLDER "/" #NAME ".s\"
"             ".set reorder
.set at
.text
")
#endif

extern void *memcpy(void *destination, const void *source, unsigned int size);

int MEDIUS_PACK_SECTION(rt_init_pack_buffer) rt_init_pack_buffer(RT_PACK_BUFFER *buffer, char *begin, char *end)
{
    if (!buffer) return 0;
    buffer->lastError = 0;
    buffer->begin = begin;
    buffer->cursor = begin;
    buffer->end = end;
    buffer->bitOffset = 0;
    if (!begin) {
        buffer->lastError = RT_INVALID_PARAM;
        return 0;
    }
    if (!end || begin >= end) {
        buffer->lastError = RT_INVALID_PARAM;
        return 0;
    }
    return 1;
}

int MEDIUS_PACK_SECTION(rt_pack_anything) rt_pack_anything(int mode, RT_PACK_BUFFER *buffer, void *data, unsigned int size)
{
    if (mode == RT_PACK && buffer->lastError) return 0;
    if (buffer->end <= buffer->cursor) {
        buffer->lastError = RT_INVALID_PARAM;
        return 0;
    }
    if (!buffer->cursor) {
        buffer->lastError = RT_INVALID_PARAM;
        return 0;
    }
    if (!data) {
        buffer->lastError = RT_INVALID_PARAM;
        return 0;
    }
    if ((unsigned int)(buffer->end - buffer->cursor) < size) {
        buffer->lastError = RT_NO_SPC;
        return 0;
    }
    if (mode == RT_PACK)
        memcpy(buffer->cursor, data, size);
    else if (mode == RT_UNPACK)
        memcpy(data, buffer->cursor, size);
    buffer->cursor += size;
    return 1;
}

int MEDIUS_PACK_SECTION(rt_pack_1byte) rt_pack_1byte(int mode, RT_PACK_BUFFER *buffer, char *value)
{
    if (buffer->lastError) return 0;
    if (buffer->end <= buffer->cursor) {
        buffer->lastError = RT_INVALID_PARAM;
        return 0;
    }
    if (!buffer->cursor) {
        buffer->lastError = RT_INVALID_PARAM;
        return 0;
    }
    if ((unsigned int)(buffer->end - buffer->cursor) < 1) {
        buffer->lastError = RT_NO_SPC;
        return 0;
    }
    if (mode == RT_PACK)
        *buffer->cursor = *value;
    else if (mode == RT_UNPACK)
        *value = *buffer->cursor;
    buffer->cursor++;
    return 1;
}

int MEDIUS_PACK_SECTION(rt_pack_cu2byte) rt_pack_cu2byte(int mode, RT_PACK_BUFFER *buffer, unsigned short *value)
{
    unsigned char byte;

    if (buffer->lastError) return 0;
    if (buffer->end <= buffer->cursor) {
        buffer->lastError = RT_INVALID_PARAM;
        return 0;
    }
    if (!buffer->cursor) {
        buffer->lastError = RT_INVALID_PARAM;
        return 0;
    }
    if ((unsigned int)(buffer->end - buffer->cursor) < 4) {
        buffer->lastError = RT_NO_SPC;
        return 0;
    }
    if (mode == RT_PACK) {
        if (*value >= 0x7FFF) {
            buffer->lastError = RT_INVALID_PARAM;
            return 0;
        }
        if (*value >= 0x80) {
            *buffer->cursor = (*value >> 8) | 0x80;
            buffer->cursor++;
        }
        *buffer->cursor = *value;
    } else if (mode == RT_UNPACK) {
        byte = *buffer->cursor;
        *value = byte;
        if (byte & 0x80) {
            buffer->cursor++;
            *value = (byte << 8) & 0x7FFF;
            *value |= (unsigned char)*buffer->cursor;
        }
        if (*value >= 0x7FFF) {
            buffer->lastError = RT_INVALID_PARAM;
            return 0;
        }
    }
    buffer->cursor++;
    return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_pack", rt_pack_cstring);
