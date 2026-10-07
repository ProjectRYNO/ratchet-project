#ifndef HIDDENINPUTTAGMODULE_H
#define HIDDENINPUTTAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe20(SVTagModuleState *module, iks *xml);
void BuildTag___dupe21(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe22(void);
void FreeResources___dupe41(SVTagModuleState *module);
}
#endif
