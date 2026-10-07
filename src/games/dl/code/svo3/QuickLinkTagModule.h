#ifndef QUICKLINKTAGMODULE_H
#define QUICKLINKTAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe6(SVTagModuleState *module, iks *xml);
void BuildTag___dupe7(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe8(void);
void FreeResources___dupe14(SVTagModuleState *module);
}
#endif
