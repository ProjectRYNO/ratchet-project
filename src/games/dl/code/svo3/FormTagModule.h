#ifndef FORMTAGMODULE_H
#define FORMTAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe15(SVTagModuleState *module, iks *xml);
void BuildTag___dupe16(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe17(void);
void FreeResources___dupe31(SVTagModuleState *module);
}
#endif
