#ifndef GRIDTAGMODULE_H
#define GRIDTAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe18(SVTagModuleState *module, iks *xml);
void BuildTag___dupe19(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe20(void);
void FreeResources___dupe37(SVTagModuleState *module);
}
#endif
