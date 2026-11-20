#ifndef DRAW_H
#define DRAW_H

#include "vector.h"

typedef struct { // 0x12
	/* 0x00 */ short int start;
	/* 0x02 */ short int stop;
	/* 0x04 */ short int text_ofs[7];
} Subtitle;

typedef struct { // 0x28
	/* 0x00 */ float scis_l;
	/* 0x04 */ float scis_r;
	/* 0x08 */ float scis_t;
	/* 0x0c */ float scis_b;
	/* 0x10 */ float size_x;
	/* 0x14 */ float size_y;
	/* 0x18 */ float center_x;
	/* 0x1c */ float center_y;
	/* 0x20 */ int splitScreenMode;
	/* 0x24 */ float xratio;
} FrustumDef;

struct SceneMonitor;
struct MobyInstance;

struct SceneDef { // 0x230
	/* 0x000 */ vec4 cam_pos_stash;
	/* 0x010 */ vec4 hero_warp_pos;
	/* 0x020 */ vec4f hero_warp_rot;
	/* 0x030 */ mtx4 transform;
	/* 0x070 */ int scene_id;
	/* 0x074 */ int iframe;
	/* 0x078 */ int cframe;
	/* 0x07c */ int ichunk;
	/* 0x080 */ short frame_cnt;
	/* 0x082 */ short chunk_cnt;
	/* 0x084 */ short actor_cnt;
	/* 0x086 */ short hero_warp_active;
	/* 0x088 */ short speech_adjust;
	/* 0x08a */ short next_chunk_size;
	/* 0x08c */ short moby_cnt;
	/* 0x08e */ short pre_init;
	/* 0x090 */ signed char ended;
	/* 0x091 */ signed char record_on;
	/* 0x092 */ short record_frame;
	/* 0x094 */ vec4 *cam_path;
	/* 0x098 */ SceneMonitor *monitor;
	/* 0x09c */ MobyInstance *ship;
	/* 0x0a0 */ void *mem_alloc_base;
	/* 0x0a4 */ void *mem_alloc_top;
	/* 0x0a8 */ void *mem_chunk_comp;
	/* 0x0ac */ void *mem_chunk_uncomp;
	/* 0x0b0 */ void *vu1_chain_stash[2];
	/* 0x0b8 */ Subtitle *subtitles;
	/* 0x0bc */ void *mobyload;
	/* 0x0c0 */ int level_fog_r;
	/* 0x0c4 */ int level_fog_g;
	/* 0x0c8 */ int level_fog_b;
	/* 0x0cc */ short biggest_chunk_uncomp;
	/* 0x0ce */ short biggest_chunk_comp;
	/* 0x0d0 */ float level_fog_near_dist;
	/* 0x0d4 */ float level_fog_far_dist;
	/* 0x0d8 */ float level_fog_near_intensity;
	/* 0x0dc */ float level_fog_far_intensity;
	/* 0x0e0 */ void *chunks[68];
	/* 0x1f0 */ MobyInstance *actors[16];
};

struct ViewContext { // 0x270
	/* 0x000 */ int headerBase[6][4];
	/* 0x060 */ u128 headerTex;
	/* 0x070 */ u128 headerTexNoFog;
	/* 0x080 */ u128 headerGr;
	/* 0x090 */ u128 headerGrNoFog;
	/* 0x0a0 */ float D;
	/* 0x0a4 */ float F;
	/* 0x0a8 */ float xclipratio;
	/* 0x0ac */ float yclipratio;
	/* 0x0b0 */ float xratio;
	/* 0x0b4 */ float yratio;
	/* 0x0b8 */ float xradpad;
	/* 0x0bc */ float yradpad;
	/* 0x0c0 */ mtx4 fMtx;
	/* 0x100 */ mtx4 nfMtx;
	/* 0x140 */ mtx4 hMtx;
	/* 0x180 */ vec4f hmgScale;
	/* 0x190 */ vec4f ihmgScale;
	/* 0x1a0 */ vec4 hvdf;
	/* 0x1b0 */ vec4f unSquish;
	/* 0x1c0 */ vec4f guard;
	/* 0x1d0 */ vec4f iguard;
	/* 0x1e0 */ vec4f sphereCheckA;
	/* 0x1f0 */ vec4f sphereCheckB;
	/* 0x200 */ vec4f sphereCheckC;
	/* 0x210 */ float xpix;
	/* 0x214 */ float ypix;
	/* 0x218 */ float xclip;
	/* 0x21c */ float yclip;
	/* 0x220 */ float fog0;
	/* 0x224 */ float fog1;
	/* 0x228 */ float fogNearDist;
	/* 0x22c */ float fogFarDist;
	/* 0x230 */ float fogMult;
	/* 0x234 */ float fogAdd;
	/* 0x238 */ float fogNearIntensity;
	/* 0x23c */ float fogFarIntensity;
	/* 0x240 */ int scis_l;
	/* 0x244 */ int scis_r;
	/* 0x248 */ int scis_t;
	/* 0x24c */ int scis_b;
	/* 0x250 */ int fogR;
	/* 0x254 */ int fogG;
	/* 0x258 */ int fogB;
	/* 0x25c */ int backR;
	/* 0x260 */ int backG;
	/* 0x264 */ int backB;
	/* 0x268 */ int splitScreenMode;
};

#endif
