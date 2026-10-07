#ifndef TAGUTILS_H
#define TAGUTILS_H
#include "SVTagModule.h"
extern "C" {
long getIntAttrib(iks *xml, char *name, int *value);
long getFloatAttrib(iks *xml, char *name, float *value);
long getColorAttrib(iks *xml, char *name, unsigned int *color);
long getStringAttrib(iks *xml, char *name, char **value);
}
#endif
