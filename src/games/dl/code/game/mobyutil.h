#ifndef MOBYUTIL_H
#define MOBYUTIL_H

#include "../include/game_vu0.h"
#include "vector.h"
#include "draw.h"

struct MobyClass;
struct MobySeq;
struct MobyAnimLayer;
struct Manipulator;

struct MobyInstance { // 0x100
	/* 0x00 */ BSphere bSphere;
	/* 0x10 */ vec4 pos;
	/* 0x20 */ unsigned char state;
	/* 0x21 */ unsigned char group;
	/* 0x22 */ unsigned char mClass;
	/* 0x23 */ unsigned char alpha;
	/* 0x24 */ MobyClass *pClass;
	/* 0x28 */ MobyInstance *pChain;
	/* 0x2c */ unsigned char collDamage;
	/* 0x2d */ signed char deathCnt;
	/* 0x2e */ unsigned short occlIndex;
	/* 0x30 */ unsigned char updateDist;
	/* 0x31 */ unsigned char drawn;
	/* 0x32 */ short drawDist;
	/* 0x34 */ unsigned short modeBits;
	/* 0x36 */ unsigned short modeBits2;
	/* 0x38 */ unsigned long lights;
	/* 0x40 */ MobySeq *animSeq;
	/* 0x44 */ float animSeqT;
	/* 0x48 */ float animSpeed;
	/* 0x4c */ short animIScale;
	/* 0x4e */ short poseCacheEntryIndex;
	/* 0x50 */ MobyAnimLayer *animLayers;
	/* 0x54 */ unsigned char animSeqId;
	/* 0x55 */ unsigned char animFlags;
	/* 0x56 */ unsigned char lSeq;
	/* 0x57 */ unsigned char jointCnt;
	/* 0x58 */ mtx4 *jointCache;
	/* 0x5c */ Manipulator *pManipulator;
	/* 0x60 */ int glow_rgba;
	/* 0x64 */ unsigned char lod_trans;
	/* 0x65 */ unsigned char lod_trans2;
	/* 0x66 */ unsigned char metal;
	/* 0x67 */ unsigned char subState;
	/* 0x68 */ unsigned char prevState;
	/* 0x69 */ unsigned char stateType;
	/* 0x6a */ unsigned short stateTimer;
	/* 0x6c */ unsigned char soundTrigger;
	/* 0x6d */ unsigned char soundDesired;
	/* 0x6e */ short soundChannel;
	/* 0x70 */ float scale;
	/* 0x74 */ unsigned short bangles;
	/* 0x76 */ unsigned char shadow;
	/* 0x77 */ unsigned char shadow_index;
	/* 0x78 */ float shadow_plane;
	/* 0x7c */ float shadow_range;
	/* 0x80 */ BSphere lSphere;
	/* 0x90 */ void *netObject;
	/* 0x94 */ short updateID;
	/* 0x96 */ short spad0;
	/* 0x98 */ int *collData;
	/* 0x9c */ int collActive;
	/* 0xa0 */ unsigned int collCnt;
	/* 0xa4 */ unsigned char grid_min_x;
	/* 0xa5 */ unsigned char grid_min_y;
	/* 0xa6 */ unsigned char grid_max_x;
	/* 0xa7 */ unsigned char grid_max_y;
	/* 0xa8 */ void *pUpdate;
	/* 0xac */ void *pVar;
	/* 0xb0 */ unsigned char mission;
	/* 0xb1 */ unsigned char pad;
	/* 0xb2 */ short UID;
	/* 0xb4 */ short bolts;
	/* 0xb6 */ unsigned short xp;
	/* 0xb8 */ MobyInstance *pParent;
	/* 0xbc */ short oClass;
	/* 0xbe */ unsigned char triggers;
	/* 0xbf */ unsigned char standarddeathcalled;
	/* 0xc0 */ mtx3 rMtx;
	/* 0xf0 */ vec4f rot;
};
typedef MobyInstance moby;

struct FlashVars { // 0x10
	/* 0x00 */ short timer;
	/* 0x02 */ short type;
	/* 0x04 */ int destColor;
	/* 0x08 */ int srcColor;
	/* 0x0c */ int flags;
};

struct _2legAnim { // 0x50
	/* 0x00 */ int anim;
	/* 0x04 */ float stride;
	/* 0x08 */ float frame0;
	/* 0x0c */ float frames;
	/* 0x10 */ int fromIdle;
	/* 0x14 */ int pad[3];
	/* 0x20 */ float heelRange[2];
	/* 0x28 */ float heelDown[2];
	/* 0x30 */ float heelUp[2];
	/* 0x38 */ float footRange[2];
	/* 0x40 */ float footDown[2];
	/* 0x48 */ float footUp[2];
};

struct BotAbility { // 0x10
	/* 0x00 */ short tagUCName;
	/* 0x02 */ short tagName;
	/* 0x04 */ short tagDesc;
	/* 0x06 */ short imageIndex;
	/* 0x08 */ short iconIndex;
	/* 0x0c */ int price;
};

#endif
