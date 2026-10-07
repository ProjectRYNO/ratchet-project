#ifndef TICKERTAGMODULE_H
#define TICKERTAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe28(SVTagModuleState *module, iks *xml);
void BuildTag___dupe28(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe30(void);
void FreeResources___dupe58(SVTagModuleState *module);
}
#endif
