#ifndef VECTOR_H
#define VECTOR_H

#include "../include/types.h"

struct vec4 { // 0x10
	/* 0x00 */ s128 v;
};

typedef int qword[4];

struct vec2 { // 0x8
	/* 0x00 */ float x;
	/* 0x04 */ float y;
};

struct vec3 { // 0xc
	/* 0x00 */ float x;
	/* 0x04 */ float y;
	/* 0x08 */ float z;
};

struct quat { // 0x10
	/* 0x00 */ s128 q;
};

struct vec4f { // 0x10
	/* 0x00 */ float x;
	/* 0x04 */ float y;
	/* 0x08 */ float z;
	/* 0x0c */ float w;
};

struct mtx4 { // 0x40
	/* 0x00 */ vec4 m_v0;
	/* 0x10 */ vec4 m_v1;
	/* 0x20 */ vec4 m_v2;
	/* 0x30 */ vec4 m_v3;
};

struct mtx3 { // 0x30
	/* 0x00 */ vec4 m_v0;
	/* 0x10 */ vec4 m_v1;
	/* 0x20 */ vec4 m_v2;
};

struct BSphere { // 0x10
	/* 0x00 */ float x;
	/* 0x04 */ float y;
	/* 0x08 */ float z;
	/* 0x0c */ float rad;
};

#endif
