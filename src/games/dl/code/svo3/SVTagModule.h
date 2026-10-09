#ifndef SVTAGMODULE_H
#define SVTAGMODULE_H

#include "../iksemel/src/iks.h"
struct SVTag;
struct CPage;
struct CAllContextData;
struct SVTagModuleState;
#include "DownloadBinary.h"
typedef struct { // 0x08
    /* 0x00 */ int action;
    /* 0x04 */ DownloadBinaryState *download;
} SVTagScanResult;
typedef struct { // 0x30 (vtable prefix)
    /* 0x00 */ void *unknown00;
    /* 0x04 */ void *unknown04;
    /* 0x08 */ void (*destroy)(SVTagModuleState *module, int flags);
    /* 0x0C */ void (*freeResources)(SVTagModuleState *module);
    /* 0x10 */ long (*HandleInput)(SVTagModuleState *module, CPage *page);
    /* 0x14 */ void *unknown14;
    /* 0x18 */ long (*IsMyTag)(SVTagModuleState *module, iks *xml);
    /* 0x1C */ void (*InitTag)(SVTagModuleState *module, iks *xml, SVTag **tag, SVTag **tagList, CAllContextData *contexts);
    /* 0x20 */ void *unknown20;
    /* 0x24 */ void (*ScanTag)(SVTagModuleState *, iks *, SVTag **, CAllContextData *, SVTagScanResult *);
    /* 0x28 */ void (*LeaveCurrentPage)(SVTagModuleState *module);
    /* 0x2C */ void (*EnterNewPage)(SVTagModuleState *module);
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
