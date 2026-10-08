#ifndef CAUDIOCONTEXTBASE_H
#define CAUDIOCONTEXTBASE_H

struct CAudioContextBaseState;
typedef struct { // 0x10 (vtable prefix)
    /* 0x00 */ unsigned char unrecovered00[0x0C];
    /* 0x0C */ void (*Play)(CAudioContextBaseState *context, int sound, char *tagClass);
} CAudioContextVtablePrefix;

// A separate type name keeps the original unmangled constructor entry callable.
struct CAudioContextBaseState { // 0x04
    /* 0x00 */ const void *vtable;
};

extern "C" const void *CAudioContextBase(CAudioContextBaseState *context);

#endif
