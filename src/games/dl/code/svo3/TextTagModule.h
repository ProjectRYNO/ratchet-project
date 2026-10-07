#ifndef TEXTTAGMODULE_H
#define TEXTTAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag(SVTagModuleState *module, iks *xml);
void BuildTag___dupe2(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe2(void);
void FreeResources___dupe3(SVTagModuleState *module);
}
#endif
