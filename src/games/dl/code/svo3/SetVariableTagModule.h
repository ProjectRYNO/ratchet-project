#ifndef SETVARIABLETAGMODULE_H
#define SETVARIABLETAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe4(SVTagModuleState *module, iks *xml);
void BuildTag___dupe5(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe6(void);
void FreeResources___dupe10(SVTagModuleState *module);
}
#endif
