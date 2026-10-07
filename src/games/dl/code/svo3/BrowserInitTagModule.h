#ifndef BROWSERINITTAGMODULE_H
#define BROWSERINITTAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe29(SVTagModuleState *module, iks *xml);
void BuildTag___dupe29(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe31(void);
void FreeResources___dupe61(SVTagModuleState *module);
}
#endif
