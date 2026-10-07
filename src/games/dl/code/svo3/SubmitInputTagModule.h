#ifndef SUBMITINPUTTAGMODULE_H
#define SUBMITINPUTTAGMODULE_H

#include "SVTagModule.h"

extern "C" {
int IsMyTag___dupe16(SVTagModuleState *module, iks *xml);
void BuildTag___dupe17(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts);
SVTagModuleState *getInstance___dupe18(void);
void FreeResources___dupe33(SVTagModuleState *module);
}
#endif
