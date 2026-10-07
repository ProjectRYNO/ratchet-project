#ifndef LINETAGMODULE_H
#define LINETAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe3(SVTagModuleState *module, iks *xml);
void BuildTag___dupe4(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe5(void);
void FreeResources___dupe8(SVTagModuleState *module);
}
#endif
