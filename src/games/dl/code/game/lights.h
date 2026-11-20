#ifndef LIGHTS_H
#define LIGHTS_H

#include "vector.h"

struct PointLight { // 0x20
	/* 0x00 */ vec4 color;
	/* 0x10 */ vec4 pos;
};

struct PL_Data { // 0x30
	/* 0x00 */ short tie_offset;
	/* 0x02 */ short tie_count;
	/* 0x04 */ short shrub_offset;
	/* 0x06 */ short shrub_count;
	/* 0x08 */ short tfrag_offset;
	/* 0x0a */ short tfrag_count;
	/* 0x0c */ short *list;
	/* 0x10 */ int state;
	/* 0x14 */ int pad[3];
	/* 0x20 */ vec4 update_pos;
};

#endif
