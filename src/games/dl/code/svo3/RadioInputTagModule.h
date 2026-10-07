#ifndef RADIOINPUTTAGMODULE_H
#define RADIOINPUTTAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe13(SVTagModuleState *module, iks *xml);
void BuildTag___dupe14(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe15(void);
void FreeResources___dupe27(SVTagModuleState *module);
}
#endif
