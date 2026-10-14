#ifndef RT_CONSTRAINT_H
#define RT_CONSTRAINT_H

// Prototype dltypes.txt layouts; retail checks read lowVal/minSize at 0x0 and highVal/maxSize after it.
typedef struct { // 0x02
    /* 0x00 */ unsigned char lowVal;
    /* 0x01 */ unsigned char highVal;
} RT_U1BYTE_CONSTRAINT;

typedef struct { // 0x08
    /* 0x00 */ int lowVal;
    /* 0x04 */ int highVal;
} RT_4BYTE_CONSTRAINT;

typedef struct { // 0x08
    /* 0x00 */ unsigned int lowVal;
    /* 0x04 */ unsigned int highVal;
} RT_U4BYTE_CONSTRAINT;

typedef struct { // 0x08
    /* 0x00 */ unsigned int minSize;
    /* 0x04 */ unsigned int maxSize;
} RT_CSTRING_CONSTRAINT;

#ifdef __cplusplus
extern "C" {
#endif

int rt_constraint_check_RT_U1BYTE(unsigned char *value, RT_U1BYTE_CONSTRAINT *constraint);
int rt_constraint_check_RT_4BYTE(int *value, RT_4BYTE_CONSTRAINT *constraint);
int rt_constraint_check_RT_U4BYTE(unsigned int *value, RT_U4BYTE_CONSTRAINT *constraint);
int rt_constraint_check_RT_CSTRING(char *value, RT_CSTRING_CONSTRAINT *constraint);

#ifdef __cplusplus
}
#endif

#endif
