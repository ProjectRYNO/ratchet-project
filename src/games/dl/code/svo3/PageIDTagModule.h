#ifndef PAGEIDTAGMODULE_H
#define PAGEIDTAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe24(SVTagModuleState *module, iks *xml);
void BuildTag___dupe25(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe26(void);
void FreeResources___dupe50(SVTagModuleState *module);
}
#endif
