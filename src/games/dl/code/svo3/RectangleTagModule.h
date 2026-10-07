#ifndef RECTANGLETAGMODULE_H
#define RECTANGLETAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe5(SVTagModuleState *module, iks *xml);
void BuildTag___dupe6(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe7(void);
void FreeResources___dupe11(SVTagModuleState *module);
}
#endif
