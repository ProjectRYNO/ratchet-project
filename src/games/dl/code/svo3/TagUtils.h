#ifndef TAGUTILS_H
#define TAGUTILS_H
#include "SVTagModule.h"
struct SVTag;
struct CPage;
extern "C" {
long getBoolAttrib(iks *xml, char *name, int *value);
long getAlignAttrib(iks *xml, char *name, int *align);
long getLinkOptionAttrib(iks *xml, char *name, unsigned int *option);
SVTag *getTagByName(char *name, CPage *page);
iks *getChildIksStruct(iks *xml, char *name);
int getChildIksStructList(iks *xml, char *name, iks **list, int size);
long getIntAttrib(iks *xml, char *name, int *value);
long getFloatAttrib(iks *xml, char *name, float *value);
long getColorAttrib(iks *xml, char *name, unsigned int *color);
long getStringAttrib(iks *xml, char *name, char **value);
}
#endif
