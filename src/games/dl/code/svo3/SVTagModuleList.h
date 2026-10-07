#ifndef SVTAGMODULELIST_H
#define SVTAGMODULELIST_H
#include "SVTagModule.h"

typedef struct { // 0x204
    /* 0x000 */ SVTagModuleState *m_modules[128];
    /* 0x200 */ int m_nextTagUID;
} SVTagModuleListState;

extern "C" {
void *SVTagModuleList(SVTagModuleListState *list);
SVTagModuleListState *getInstance___dupe3();
void FreeResources___dupe4(SVTagModuleListState *list);
int AddTagModule(SVTagModuleListState *list, SVTagModuleState *module);
void *SVTagModuleListNew(unsigned int size) __asm__("operator.new___dupe6");
}
#endif
