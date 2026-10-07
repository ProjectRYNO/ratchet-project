#ifndef REDIRECTTAGMODULE_H
#define REDIRECTTAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe21(SVTagModuleState *module, iks *xml);
void BuildTag___dupe22(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe23(void);
}
#endif
