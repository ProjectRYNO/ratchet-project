#ifndef TIEFUNC_H
#define TIEFUNC_H

#include "vector.h"

typedef struct { // 0x8
	/* 0x0 */ short int vert_cnt;
	/* 0x2 */ short int tri_cnt;
	/* 0x4 */ short int strip_cnt;
	/* 0x6 */ short int pad;
} TieLod;

struct TieInstance { // 0x20
	/* 0x00 */ BSphere bsphere;
	/* 0x10 */ unsigned short occl_index;
	/* 0x12 */ unsigned short index;
	/* 0x14 */ unsigned short cache_loc;
	/* 0x16 */ short cache_size;
	/* 0x18 */ short dir_lights;
	/* 0x1a */ unsigned short point_lights;
	/* 0x1c */ unsigned char draw_dist;
	/* 0x1d */ unsigned char t_class;
	/* 0x1e */ unsigned char flags;
	/* 0x1f */ unsigned char cache_lod;
};

#endif
