#ifndef LOGOUTTAGMODULE_H
#define LOGOUTTAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe17(SVTagModuleState *module, iks *xml);
void BuildTag___dupe18(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe19(void);
void FreeResources___dupe35(SVTagModuleState *module);
}
#endif
