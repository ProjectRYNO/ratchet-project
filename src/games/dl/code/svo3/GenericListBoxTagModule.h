#ifndef GENERICLISTBOXTAGMODULE_H
#define GENERICLISTBOXTAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe27(SVTagModuleState *module, iks *xml);
void BuildTag___dupe27(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe29(void);
void FreeResources___dupe57(SVTagModuleState *module);
}
#endif
