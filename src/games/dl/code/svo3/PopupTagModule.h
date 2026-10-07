#ifndef POPUPTAGMODULE_H
#define POPUPTAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe19(SVTagModuleState *module, iks *xml);
void BuildTag___dupe20(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe21(void);
void FreeResources___dupe39(SVTagModuleState *module);
}
#endif
