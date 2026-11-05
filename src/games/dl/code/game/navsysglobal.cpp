#include "common.h"
#include "game_section.h"


typedef struct navgWp {
	/* 0x00 */ int unk00[3];
	/* 0x0c */ unsigned int node:16;
	unsigned int nodePad:16;
} navgWp_t;
void NAVG_WpSetPos(void *, int, int) __asm__("NAVG_WpSetPos");
int NAVG_WpGetNode(navgWp_t *wp) __asm__("NAVG_WpGetNode");
void NAVG_ResetNavigationVars(char *vars, int a, int b) __asm__("NAVG_ResetNavigationVars");
char *navg_AllocMemory(int size, char **ptr, char *end) __asm__("navg_AllocMemory");


typedef struct navNode {
	/* 0x00 */ unsigned short type;
	/* 0x02 */ char unk02[0x1e];
} navNode_t;
typedef struct navEdge {
	/* 0x00 */ unsigned short type;
	/* 0x02 */ char unk02[6];
} navEdge_t;
typedef struct navSys {
	/* 0x0000 */ char unk00[0x3014];
	/* 0x3014 */ int nodeMax;
	/* 0x3018 */ navNode_t *nodes;
	/* 0x301c */ char unk301c[8];
	/* 0x3024 */ int edgeMax;
	/* 0x3028 */ navEdge_t *edges;
} navSys_t;
extern navSys_t *g_navSys __asm__("g_navSys");
int NAVG_NodeGetType(unsigned short node) __asm__("NAVG_NodeGetType");
int NAVG_EdgeGetType(unsigned short edge) __asm__("NAVG_EdgeGetType");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_CollideLineSegmentBoxLocalZeroVec);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_CollideLineSegmentSphereLocal);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", func_0048B1C0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_CollideLineSegmentCylinderLocal);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", func_0048B468);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_CollideLineSegmentPath);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", func_0048B560);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_NodeGetDistSqr);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_TestInside);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", func_0048B800);

GAME_SECTION(navg_AllocMemory) char *navg_AllocMemory(int size, char **ptr, char *end)
{
	char *mem = *ptr;
	char *next = mem + ((size + 0xf) & -0x10);
	*ptr = next;
	if (next >= end) mem = 0;
	return mem;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_LoadClusters);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_LoadNodes);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_LoadNeighbors);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_LoadEdges);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_LoadClusterPaths);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_LoadPaths);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_LoadClusterPathLists);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_LoadPathLists);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_LoadCuboids);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_LoadSpheres);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_LoadCylinders);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_LoadBoundPaths);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_LoadPartitions);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_LoadSectors);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_LoadFile);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", func_0048D028);

GAME_SECTION(NAVG_ResetNavigationVars) void NAVG_ResetNavigationVars(char *vars, int a, int b)
{
	NAVG_WpSetPos(vars + 0x10, a, b);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", func_0048D058);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_FindClosestNode);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", func_0048D220);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_FindBestIntraClusterPath);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_FindBestInterClusterPath);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_FindBestInterSectorPathStep);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_FindBestInterSectorPath);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_UpdateNavigationWpEasy);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_SetTargetWp);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_UpdateMe);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_UpdateNavigation);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", func_0048E650);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_NodeFindClosestNode);

GAME_SECTION(NAVG_NodeGetType) int NAVG_NodeGetType(unsigned short node)
{
	if (!g_navSys || g_navSys->nodeMax < node) return -1;
	return g_navSys->nodes[node].type;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_NodeGetTraversalFlags);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_NodeGetCenter);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", func_0048EAB0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_NodeGet3DSpline);

GAME_SECTION(NAVG_EdgeGetType) int NAVG_EdgeGetType(unsigned short edge)
{
	if (!g_navSys || g_navSys->edgeMax < edge) return -1;
	return g_navSys->edges[edge].type;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_EdgeGetCliffSpline);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_WpSet);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_WpSetPos);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_WpMovePos);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", func_0048EC58);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_WpGetNode);
