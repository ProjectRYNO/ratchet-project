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
	/* 0x02 */ char unk02[8];
	/* 0x0a */ unsigned short traversalFlags;
	/* 0x0c */ int infolink;
	/* 0x10 */ char unk10[0x10];
} navNode_t;
typedef struct navEdge {
	/* 0x00 */ unsigned short type;
	/* 0x02 */ char unk02[6];
} navEdge_t;
typedef struct navElem4 {
	/* 0x00 */ int data;
} navElem4_t;
typedef struct navElem8 {
	/* 0x00 */ int data[2];
} navElem8_t;
typedef struct navSys {
	/* 0x0000 */ char unk00[0x300c];
	/* 0x300c */ int numClusters;
	/* 0x3010 */ void *clusters;
	/* 0x3014 */ int nodeMax;
	/* 0x3018 */ navNode_t *nodes;
	/* 0x301c */ int numNeighbors;
	/* 0x3020 */ navElem8_t *neighbors;
	/* 0x3024 */ int edgeMax;
	/* 0x3028 */ navEdge_t *edges;
	/* 0x302c */ int unk302c[4];
	/* 0x303c */ int numClusterPaths;
	/* 0x3040 */ void *clusterPaths;
	/* 0x3044 */ int numPaths;
	/* 0x3048 */ navElem8_t *paths;
	/* 0x304c */ int unk304c[4];
	/* 0x305c */ int numCuboids;
	/* 0x3060 */ navElem4_t *cuboids;
	/* 0x3064 */ int numSpheres;
	/* 0x3068 */ navElem4_t *spheres;
	/* 0x306c */ int numCylinders;
	/* 0x3070 */ navElem4_t *cylinders;
	/* 0x3074 */ int numBoundPaths;
	/* 0x3078 */ navElem4_t *boundPaths;
} navSys_t;
extern navSys_t *g_navSys __asm__("g_navSys");
int NAVG_NodeGetType(unsigned short node) __asm__("NAVG_NodeGetType");
int NAVG_EdgeGetType(unsigned short edge) __asm__("NAVG_EdgeGetType");

/* Retail re-reads g_navSys and the new array pointer after storing it, before the null test. A
 * volatile store reproduces that reload; a plain store lets GCC test the returned value directly. */
#define NAVG_STORE(type, field) (*(type * volatile *)&g_navSys->field)
void FastMemCopy(void *, const void *, int) __asm__("FastMemCopy");
int navg_LoadNodes(char *, char *&, void *) __asm__("navg_LoadNodes");
int navg_LoadNeighbors(char *, char *&, void *) __asm__("navg_LoadNeighbors");
int navg_LoadEdges(char *, char *&, void *) __asm__("navg_LoadEdges");
int navg_LoadPaths(char *, char *&, void *) __asm__("navg_LoadPaths");
int navg_LoadCuboids(char *, char *&, void *) __asm__("navg_LoadCuboids");
int navg_LoadSpheres(char *, char *&, void *) __asm__("navg_LoadSpheres");
int navg_LoadCylinders(char *, char *&, void *) __asm__("navg_LoadCylinders");
int navg_LoadBoundPaths(char *, char *&, void *) __asm__("navg_LoadBoundPaths");
int NAVG_NodeGetTraversalFlags(unsigned short) __asm__("NAVG_NodeGetTraversalFlags");
int NAVG_NodeGet3DSpline(unsigned short) __asm__("NAVG_NodeGet3DSpline");

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

GAME_SECTION(navg_LoadNodes) int navg_LoadNodes(char *fileData, char *&dataMem, void *endMemory)
{
	int i;
	FastMemCopy(&g_navSys->nodeMax, fileData, 4);
	fileData += 4;
	NAVG_STORE(navNode_t, nodes) = (navNode_t *)navg_AllocMemory(g_navSys->nodeMax << 5, &dataMem, (char *)endMemory);
	if (g_navSys->nodes == 0) return 1;
	for (i = 0; i < g_navSys->nodeMax; i++) {
		FastMemCopy(&g_navSys->nodes[i], fileData, 32);
		fileData += 32;
	}
	return 0;
}

GAME_SECTION(navg_LoadNeighbors) int navg_LoadNeighbors(char *fileData, char *&dataMem, void *endMemory)
{
	int i;
	FastMemCopy(&g_navSys->numNeighbors, fileData, 4);
	fileData += 4;
	NAVG_STORE(navElem8_t, neighbors) = (navElem8_t *)navg_AllocMemory(g_navSys->numNeighbors << 3, &dataMem, (char *)endMemory);
	if (g_navSys->neighbors == 0) return 1;
	for (i = 0; i < g_navSys->numNeighbors; i++) {
		FastMemCopy(&g_navSys->neighbors[i], fileData, 8);
		fileData += 8;
	}
	return 0;
}

GAME_SECTION(navg_LoadEdges) int navg_LoadEdges(char *fileData, char *&dataMem, void *endMemory)
{
	int i;
	FastMemCopy(&g_navSys->edgeMax, fileData, 4);
	fileData += 4;
	NAVG_STORE(navEdge_t, edges) = (navEdge_t *)navg_AllocMemory(g_navSys->edgeMax << 3, &dataMem, (char *)endMemory);
	if (g_navSys->edges == 0) return 1;
	for (i = 0; i < g_navSys->edgeMax; i++) {
		FastMemCopy(&g_navSys->edges[i], fileData, 8);
		fileData += 8;
	}
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_LoadClusterPaths);

GAME_SECTION(navg_LoadPaths) int navg_LoadPaths(char *fileData, char *&dataMem, void *endMemory)
{
	int i;
	FastMemCopy(&g_navSys->numPaths, fileData, 4);
	fileData += 4;
	NAVG_STORE(navElem8_t, paths) = (navElem8_t *)navg_AllocMemory(g_navSys->numPaths << 3, &dataMem, (char *)endMemory);
	if (g_navSys->paths == 0) return 1;
	for (i = 0; i < g_navSys->numPaths; i++) {
		FastMemCopy(&g_navSys->paths[i], fileData, 8);
		fileData += 8;
	}
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_LoadClusterPathLists);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_LoadPathLists);

GAME_SECTION(navg_LoadCuboids) int navg_LoadCuboids(char *fileData, char *&dataMem, void *endMemory)
{
	int i;
	FastMemCopy(&g_navSys->numCuboids, fileData, 4);
	fileData += 4;
	NAVG_STORE(navElem4_t, cuboids) = (navElem4_t *)navg_AllocMemory(g_navSys->numCuboids << 2, &dataMem, (char *)endMemory);
	if (g_navSys->cuboids == 0) return 1;
	for (i = 0; i < g_navSys->numCuboids; i++) {
		FastMemCopy(&g_navSys->cuboids[i], fileData, 4);
		fileData += 4;
	}
	return 0;
}

GAME_SECTION(navg_LoadSpheres) int navg_LoadSpheres(char *fileData, char *&dataMem, void *endMemory)
{
	int i;
	FastMemCopy(&g_navSys->numSpheres, fileData, 4);
	fileData += 4;
	NAVG_STORE(navElem4_t, spheres) = (navElem4_t *)navg_AllocMemory(g_navSys->numSpheres << 2, &dataMem, (char *)endMemory);
	if (g_navSys->spheres == 0) return 1;
	for (i = 0; i < g_navSys->numSpheres; i++) {
		FastMemCopy(&g_navSys->spheres[i], fileData, 4);
		fileData += 4;
	}
	return 0;
}

GAME_SECTION(navg_LoadCylinders) int navg_LoadCylinders(char *fileData, char *&dataMem, void *endMemory)
{
	int i;
	FastMemCopy(&g_navSys->numCylinders, fileData, 4);
	fileData += 4;
	NAVG_STORE(navElem4_t, cylinders) = (navElem4_t *)navg_AllocMemory(g_navSys->numCylinders << 2, &dataMem, (char *)endMemory);
	if (g_navSys->cylinders == 0) return 1;
	for (i = 0; i < g_navSys->numCylinders; i++) {
		FastMemCopy(&g_navSys->cylinders[i], fileData, 4);
		fileData += 4;
	}
	return 0;
}

GAME_SECTION(navg_LoadBoundPaths) int navg_LoadBoundPaths(char *fileData, char *&dataMem, void *endMemory)
{
	int i;
	FastMemCopy(&g_navSys->numBoundPaths, fileData, 4);
	fileData += 4;
	NAVG_STORE(navElem4_t, boundPaths) = (navElem4_t *)navg_AllocMemory(g_navSys->numBoundPaths << 2, &dataMem, (char *)endMemory);
	if (g_navSys->boundPaths == 0) return 1;
	for (i = 0; i < g_navSys->numBoundPaths; i++) {
		FastMemCopy(&g_navSys->boundPaths[i], fileData, 4);
		fileData += 4;
	}
	return 0;
}

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

GAME_SECTION(NAVG_NodeGetTraversalFlags) int NAVG_NodeGetTraversalFlags(unsigned short node)
{
	if (!g_navSys || g_navSys->nodeMax < node) return -1;
	return g_navSys->nodes[node].traversalFlags;
}

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
