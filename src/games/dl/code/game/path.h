#ifndef PATH_H
#define PATH_H

#include "vector.h"

struct Path { // 0x10
	/* 0x00 */ int nNodes;
	/* 0x04 */ int bPathNormalized;
	/* 0x08 */ char pad[8];
	/* 0x10 */ vec4 nodes[0];
};

#endif
