#ifndef LISTBOXTAGMODULE_H
#define LISTBOXTAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe23(SVTagModuleState *module, iks *xml);
void BuildTag___dupe24(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe25(void);
void FreeResources___dupe49(SVTagModuleState *module);
}
#endif
