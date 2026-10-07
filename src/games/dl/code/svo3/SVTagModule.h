#ifndef SVTAGMODULE_H
#define SVTAGMODULE_H

#include "../iksemel/src/iks.h"
struct SVTag;
struct CAllContextData;
struct SVTagModuleState;
typedef struct { // 0x10 (vtable prefix)
    /* 0x00 */ void *unknown00;
    /* 0x04 */ void *unknown04;
    /* 0x08 */ void (*destroy)(SVTagModuleState *module, int flags);
    /* 0x0C */ void (*freeResources)(SVTagModuleState *module);
} SVTagModuleVtablePrefix;

struct SVTagModuleState { // 0x04
    /* 0x00 */ const SVTagModuleVtablePrefix *vtable;
};

extern "C" {
void *SVTagModuleNew(unsigned int size) __asm__("operator.new___dupe7");
void *SVTagNew(unsigned int size) __asm__("operator.new___dupe8");
char *iks_find_attrib(iks *node, const char *name);
void __SVO_Assert_Handler(const char *file, int line);
}
#endif
