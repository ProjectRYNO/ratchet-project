#ifndef CAUDIOCONTEXTBASE_H
#define CAUDIOCONTEXTBASE_H

// A separate type name keeps the original unmangled constructor entry callable.
typedef struct { // 0x04
    /* 0x00 */ const void *vtable;
} CAudioContextBaseState;

extern "C" const void *CAudioContextBase(CAudioContextBaseState *context);

#endif
