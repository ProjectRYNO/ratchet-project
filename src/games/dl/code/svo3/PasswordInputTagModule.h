#ifndef PASSWORDINPUTTAGMODULE_H
#define PASSWORDINPUTTAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe12(SVTagModuleState *module, iks *xml);
void BuildTag___dupe13(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe14(void);
void FreeResources___dupe25(SVTagModuleState *module);
}
#endif
