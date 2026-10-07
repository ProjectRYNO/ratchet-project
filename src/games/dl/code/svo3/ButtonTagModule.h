#ifndef BUTTONTAGMODULE_H
#define BUTTONTAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe2(SVTagModuleState *module, iks *xml);
void BuildTag___dupe3(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe4(void);
void FreeResources___dupe6(SVTagModuleState *module);
}
#endif
