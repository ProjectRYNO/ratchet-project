#ifndef TAGUTILS_H
#define TAGUTILS_H
#include "SVTagModule.h"
struct SVTag;
struct CPage;
extern "C" {
int getBoolAttrib(iks *xml, char *name, int *value);
int getAlignAttrib(iks *xml, char *name, int *align);
int getLinkOptionAttrib(iks *xml, char *name, unsigned int *option);
SVTag *getTagByName(char *name, CPage *page);
iks *getChildIksStruct(iks *xml, char *name);
int getChildIksStructList(iks *xml, char *name, iks **list, int size);
int getIntAttrib(iks *xml, char *name, int *value);
int getFloatAttrib(iks *xml, char *name, float *value);
int getColorAttrib(iks *xml, char *name, unsigned int *color);
int getStringAttrib(iks *xml, char *name, char **value);
}
#endif
