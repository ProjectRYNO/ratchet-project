#ifndef TEXTAREATAGMODULE_H
#define TEXTAREATAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe10(SVTagModuleState *module, iks *xml);
void BuildTag___dupe11(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe12(void);
void FreeResources___dupe22(SVTagModuleState *module);
}
#endif
