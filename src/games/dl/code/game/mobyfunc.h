#ifndef MOBYFUNC_H
#define MOBYFUNC_H

#include "vector.h"

struct MobySeq;
struct SoundDef;

struct MobyClass { // 0x50
	/* 0x00 */ void *packets;
	/* 0x04 */ unsigned char packet_cnt_0;
	/* 0x05 */ unsigned char packet_cnt_1;
	/* 0x06 */ unsigned char metal_cnt;
	/* 0x07 */ unsigned char metal_ofs;
	/* 0x08 */ unsigned char joint_cnt;
	/* 0x09 */ unsigned char pad;
	/* 0x0a */ unsigned char packet_cnt_2;
	/* 0x0b */ unsigned char team_texs;
	/* 0x0c */ unsigned char seq_cnt;
	/* 0x0d */ unsigned char sound_cnt;
	/* 0x0e */ unsigned char lod_trans;
	/* 0x0f */ unsigned char shadow;
	/* 0x10 */ short *collision;
	/* 0x14 */ void *skeleton;
	/* 0x18 */ void *common_trans;
	/* 0x1c */ void *anim_joints;
	/* 0x20 */ void *gif_usage;
	/* 0x24 */ float gScale;
	/* 0x28 */ SoundDef *sound_defs;
	/* 0x2c */ unsigned char bangles;
	/* 0x2d */ unsigned char mip_dist;
	/* 0x2e */ short corncob;
	/* 0x30 */ BSphere bSphere;
	/* 0x40 */ int glow_rgba;
	/* 0x44 */ short mode_bits;
	/* 0x46 */ unsigned char type;
	/* 0x47 */ unsigned char mode_bits2;
	/* 0x48 */ MobySeq *seqs[0];
};

#endif
