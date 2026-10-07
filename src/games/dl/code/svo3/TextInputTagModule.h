#ifndef TEXTINPUTTAGMODULE_H
#define TEXTINPUTTAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe11(SVTagModuleState *module, iks *xml);
void BuildTag___dupe12(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe13(void);
void FreeResources___dupe24(SVTagModuleState *module);
}
#endif
