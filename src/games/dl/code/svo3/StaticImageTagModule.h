#ifndef STATICIMAGETAGMODULE_H
#define STATICIMAGETAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe9(SVTagModuleState *module, iks *xml);
void BuildTag___dupe10(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe11(void);
void FreeResources___dupe19(SVTagModuleState *module);
}
#endif
