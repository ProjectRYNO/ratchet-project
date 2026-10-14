#include "common.h"

#define MEDIUS_MSG_SECTION(name) __attribute__((section(".medius_msg_" #name)))
#define RT_INVALID_PARAM 2

int MEDIUS_MSG_SECTION(rt_msg_set_ubyte) rt_msg_set_ubyte(unsigned char *buffer, unsigned char value)
{
    int result = RT_INVALID_PARAM;

    if (buffer) {
        *buffer = value;
        result = 0;
    }
    return result;
}

int MEDIUS_MSG_SECTION(rt_msg_get_ubyte) rt_msg_get_ubyte(unsigned char *buffer, unsigned char *value)
{
    int result = RT_INVALID_PARAM;

    if (!buffer) return RT_INVALID_PARAM;
    if (!value) return RT_INVALID_PARAM;
    *value = *buffer;
    result = 0;
    return result;
}

int MEDIUS_MSG_SECTION(rt_msg_set_u2byte) rt_msg_set_u2byte(unsigned char *buffer, unsigned short value)
{
    int result = RT_INVALID_PARAM;

    if (buffer) {
        buffer[0] = value;
        buffer[1] = value >> 8;
        result = 0;
    }
    return result;
}

int MEDIUS_MSG_SECTION(rt_msg_get_u2byte) rt_msg_get_u2byte(unsigned char *buffer, unsigned short *value)
{
    int result = RT_INVALID_PARAM;

    if (!buffer) return RT_INVALID_PARAM;
    if (!value) return RT_INVALID_PARAM;
    *value = buffer[0];
    *value |= buffer[1] << 8;
    result = 0;
    return result;
}

int MEDIUS_MSG_SECTION(rt_msg_set_u4byte) rt_msg_set_u4byte(unsigned char *buffer, unsigned int value)
{
    int result = RT_INVALID_PARAM;

    if (buffer) {
        *buffer++ = value;
        *buffer++ = value >> 8;
        *buffer++ = value >> 16;
        *buffer = value >> 24;
        result = 0;
    }
    return result;
}

int MEDIUS_MSG_SECTION(rt_msg_get_u4byte) rt_msg_get_u4byte(unsigned char *buffer, unsigned int *value)
{
    int result = RT_INVALID_PARAM;

    if (!buffer) return RT_INVALID_PARAM;
    if (!value) return RT_INVALID_PARAM;
    *value = *buffer++;
    *value |= *buffer++ << 8;
    *value |= *buffer++ << 16;
    *value |= *buffer << 24;
    result = 0;
    return result;
}

int MEDIUS_MSG_SECTION(rt_msg_set_u2byte_be) rt_msg_set_u2byte_be(unsigned char *buffer, unsigned short value)
{
    int result = RT_INVALID_PARAM;

    if (buffer) {
        buffer[0] = value >> 8;
        buffer[1] = value;
        result = 0;
    }
    return result;
}

int MEDIUS_MSG_SECTION(rt_msg_get_u2byte_be) rt_msg_get_u2byte_be(unsigned char *buffer, unsigned short *value)
{
    int result = RT_INVALID_PARAM;

    if (!buffer) return RT_INVALID_PARAM;
    if (!value) return RT_INVALID_PARAM;
    *value = buffer[0] << 8;
    *value |= buffer[1];
    result = 0;
    return result;
}
