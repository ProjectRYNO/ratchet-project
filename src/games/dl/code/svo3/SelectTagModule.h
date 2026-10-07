#ifndef SELECTTAGMODULE_H
#define SELECTTAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe7(SVTagModuleState *module, iks *xml);
void BuildTag___dupe8(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe9(void);
void FreeResources___dupe16(SVTagModuleState *module);
}
#endif
