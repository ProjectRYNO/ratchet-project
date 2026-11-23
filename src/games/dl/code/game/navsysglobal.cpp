#include "common.h"
#include "game_section.h"
#include "game_vu0.h"
#include "mobyutil.h"


typedef struct navgWp {
	/* 0x00 */ int unk00[3];
	/* 0x0c */ unsigned int node:16;
	unsigned int nodePad:16;
} navgWp_t;
void NAVG_WpSetPos(void *, int, int) __asm__("NAVG_WpSetPos");
int NAVG_WpGetNode(navgWp_t *wp) __asm__("NAVG_WpGetNode");
void NAVG_ResetNavigationVars(char *vars, int a, int b) __asm__("NAVG_ResetNavigationVars");
struct NavigationVars {
	/* 0x00 */ char unk00[0x20];
	/* 0x20 */ vec4 targetLoc;
};
/* A waypoint is a vec4 whose w word holds the node handle. */
struct navgWaypoint {
	/* 0x00 */ float x;
	/* 0x04 */ float y;
	/* 0x08 */ float z;
	/* 0x0c */ int node;
};
int NAVG_SetTargetWp(NavigationVars *navVars, vec4 &wp) __asm__("NAVG_SetTargetWp");
void NAVG_WpSet(vec4 &wp, vec4 &iPos, unsigned short node) __asm__("NAVG_WpSet");
char *navg_AllocMemory(int size, char **ptr, char *end) __asm__("navg_AllocMemory");


typedef struct navNode {
	/* 0x00 */ unsigned short type;
	/* 0x02 */ char unk02[8];
	/* 0x0a */ unsigned short traversalFlags;
	/* 0x0c */ int infolink;
	/* 0x10 */ vec4 centroid;
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
typedef struct navCluster {
	/* 0x00 */ int firstNode;
	/* 0x04 */ int unk04;
	/* 0x08 */ short sector;
	/* 0x0a */ short unk0a;
} navCluster_t;
typedef struct navElem12 {
	/* 0x00 */ int data[3];
} navElem12_t;
typedef struct navSector {
	/* 0x00 */ short firstCluster;
	/* 0x02 */ short numClusters;
	/* 0x04 */ short firstPartition;
	/* 0x06 */ short numPartitions;
	/* 0x08 */ short flags;
	/* 0x0a */ short pad;
} navSector_t;
typedef struct navgNode {
	/* 0x00 */ char unk00[8];
	/* 0x08 */ unsigned short cluster;
	/* 0x0a */ char unk0a[0x16];
} navgNodeAJ_t;
typedef struct navgCluster {
	/* 0x00 */ unsigned short firstNode;
	/* 0x02 */ unsigned short numNodes;
	/* 0x04 */ unsigned short firstPath;
	/* 0x06 */ short unk06[3];
} navgClusterAJ_t;
typedef struct navgPathList {
	/* 0x00 */ unsigned short firstPath;
	/* 0x02 */ short numPaths;
} navgPathListAJ_t;
typedef struct navgPath {
	/* 0x00 */ unsigned short nextNode;
	/* 0x02 */ unsigned short nextEdge;
	/* 0x04 */ unsigned short dist;
	/* 0x06 */ unsigned short traversalFlags;
} navgPathAJ_t;
typedef struct navSys {
	/* 0x0000 */ char unk00[0x3000];
	/* 0x3000 */ int version;
	/* 0x3004 */ navElem4_t *clusterPathLists;
	/* 0x3008 */ navElem4_t *pathLists;
	/* 0x300c */ int numClusters;
	/* 0x3010 */ navCluster_t *clusters;
	/* 0x3014 */ int nodeMax;
	/* 0x3018 */ navNode_t *nodes;
	/* 0x301c */ int numNeighbors;
	/* 0x3020 */ navElem8_t *neighbors;
	/* 0x3024 */ int edgeMax;
	/* 0x3028 */ navEdge_t *edges;
	/* 0x302c */ int numSectors;
	/* 0x3030 */ navSector_t *sectors;
	/* 0x3034 */ int numPartitions;
	/* 0x3038 */ navElem4_t *partitions;
	/* 0x303c */ int numClusterPaths;
	/* 0x3040 */ navElem12_t *clusterPaths;
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

int navg_LoadPathLists(char *, char *&, void *) __asm__("navg_LoadPathLists");
int navg_LoadClusterPathLists(char *, char *&, void *) __asm__("navg_LoadClusterPathLists");
int navg_LoadClusterPaths(char *, char *&, void *) __asm__("navg_LoadClusterPaths");
int navg_LoadPartitions(char *, char *&, void *) __asm__("navg_LoadPartitions");
int navg_LoadClusters(char *, char *&, void *) __asm__("navg_LoadClusters");

void navg_FindBestIntraClusterPath(unsigned short, unsigned short, int, unsigned short &, unsigned short &, int &) __asm__("navg_FindBestIntraClusterPath");
#define NAVG_VSET(type, lvalue, value) (*(type volatile *)&(lvalue) = (value))
int navg_LoadSectors(char *, char *&, void *) __asm__("navg_LoadSectors");

unsigned short NAVG_WpGetNode(vec4 &wp) __asm__("NAVG_WpGetNode");
/* Integer w word of a vec4; retail reads it as a full word (lw + andi), which a volatile read keeps. */
inline int vec4GetWi(vec4 &v)
{
	return *(volatile int *)&((navgWaypoint *)&v)->node;
}
void NAVG_WpSetPos(vec4 &wp, vec4 &iPos) __asm__("NAVG_WpSetPos");
void NAVG_WpMovePos(vec4 &wp, vec4 &newPos) __asm__("NAVG_WpMovePos");
unsigned short NAVG_FindClosestNode(vec4 &pos, float *dist) __asm__("NAVG_FindClosestNode");
unsigned short NAVG_NodeFindClosestNode(unsigned short node, vec4 &pos, float *dist) __asm__("NAVG_NodeFindClosestNode");
void NAVG_NodeGetCenter(unsigned short node, vec4 &oPos) __asm__("NAVG_NodeGetCenter");

float navg_CollideLineSegmentBoxLocalZeroVec(vec4f &start) __asm__("navg_CollideLineSegmentBoxLocalZeroVec");




GAME_SECTION(navg_CollideLineSegmentBoxLocalZeroVec) float navg_CollideLineSegmentBoxLocalZeroVec(vec4f &start)
{
	float fst = 0.0f;
	float *ps = &start.x;
	int i;
	for (i = 2; i >= 0; i--) {
		float si = *ps;
		float di = -si;
		float st;
		if (si < 0.0f) {
			if (si < -1.0f) st = (-1.0f - si) / di;
			else st = 0.0f;
		} else {
			if (1.0f < si) st = (1.0f - si) / di;
			else st = 0.0f;
		}
		if (fst < st) fst = st;
		ps++;
	}
	return fst;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_CollideLineSegmentSphereLocal);

JUNK_ASM(func_0048B1C0,
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_CollideLineSegmentCylinderLocal);

JUNK_ASM(func_0048B468,
	"\taddiu $29, $29, 0x50\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_CollideLineSegmentPath);

JUNK_ASM(func_0048B560,
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\tsqc2 $vf1, 0x0($6)\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x70\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_NodeGetDistSqr);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_TestInside);

JUNK_ASM(func_0048B800,
	"\tsw $0, 0x3054($3)\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x60\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n");

GAME_SECTION(navg_AllocMemory) char *navg_AllocMemory(int size, char **ptr, char *end)
{
	char *mem = *ptr;
	char *next = mem + ((size + 0xf) & -0x10);
	*ptr = next;
	if (next >= end) mem = 0;
	return mem;
}

GAME_SECTION(navg_LoadClusters) int navg_LoadClusters(char *fileData, char *&dataMem, void *endMemory)
{
	int i;
	FastMemCopy(&g_navSys->numClusters, fileData, 4);
	fileData += 4;
	NAVG_STORE(navCluster_t, clusters) = (navCluster_t *)navg_AllocMemory(g_navSys->numClusters * 12, &dataMem, (char *)endMemory);
	if (g_navSys->clusters == 0) return 1;
	for (i = 0; i < g_navSys->numClusters; i++) {
		if (g_navSys->version >= 2) {
			FastMemCopy(&g_navSys->clusters[i], fileData, 12);
			fileData += 12;
		} else {
			FastMemCopy(&g_navSys->clusters[i], fileData, 8);
			fileData += 8;
			g_navSys->clusters[i].sector = 0;
		}
	}
	return 0;
}

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

GAME_SECTION(navg_LoadClusterPaths) int navg_LoadClusterPaths(char *fileData, char *&dataMem, void *endMemory)
{
	int i;
	FastMemCopy(&g_navSys->numClusterPaths, fileData, 4);
	fileData += 4;
	NAVG_STORE(navElem12_t, clusterPaths) = (navElem12_t *)navg_AllocMemory(g_navSys->numClusterPaths * 12, &dataMem, (char *)endMemory);
	if (g_navSys->clusterPaths == 0) return 1;
	for (i = 0; i < g_navSys->numClusterPaths; i++) {
		FastMemCopy(&g_navSys->clusterPaths[i], fileData, 12);
		fileData += 12;
	}
	return 0;
}

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

GAME_SECTION(navg_LoadClusterPathLists) int navg_LoadClusterPathLists(char *fileData, char *&dataMem, void *endMemory)
{
	int count;
	int i;
	FastMemCopy(&count, fileData, 4);
	fileData += 4;
	NAVG_STORE(navElem4_t, clusterPathLists) = (navElem4_t *)navg_AllocMemory(count << 2, &dataMem, (char *)endMemory);
	if (g_navSys->clusterPathLists == 0) return 1;
	for (i = 0; i < count; i++) {
		FastMemCopy(&g_navSys->clusterPathLists[i], fileData, 4);
		fileData += 4;
	}
	return 0;
}

GAME_SECTION(navg_LoadPathLists) int navg_LoadPathLists(char *fileData, char *&dataMem, void *endMemory)
{
	int count;
	int i;
	FastMemCopy(&count, fileData, 4);
	fileData += 4;
	NAVG_STORE(navElem4_t, pathLists) = (navElem4_t *)navg_AllocMemory(count << 2, &dataMem, (char *)endMemory);
	if (g_navSys->pathLists == 0) return 1;
	for (i = 0; i < count; i++) {
		FastMemCopy(&g_navSys->pathLists[i], fileData, 4);
		fileData += 4;
	}
	return 0;
}

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

GAME_SECTION(navg_LoadPartitions) int navg_LoadPartitions(char *fileData, char *&dataMem, void *endMemory)
{
	int i;
	if (g_navSys->version < 2) {
		NAVG_STORE(navElem4_t, partitions) = 0;
		g_navSys->numPartitions = 0;
		return 0;
	}
	FastMemCopy(&g_navSys->numPartitions, fileData, 4);
	fileData += 4;
	NAVG_STORE(navElem4_t, partitions) = (navElem4_t *)navg_AllocMemory(g_navSys->numPartitions << 2, &dataMem, (char *)endMemory);
	if (g_navSys->partitions == 0) return 1;
	for (i = 0; i < g_navSys->numPartitions; i++) {
		FastMemCopy(&g_navSys->partitions[i], fileData, 4);
		fileData += 4;
	}
	return 0;
}

GAME_SECTION(navg_LoadSectors) int navg_LoadSectors(char *fileData, char *&dataMem, void *endMemory)
{
	int i;
	if (g_navSys->version < 2) {
		NAVG_STORE(navSector_t, sectors) = (navSector_t *)navg_AllocMemory(0xc, &dataMem, (char *)endMemory);
		if (g_navSys->sectors == 0) return 1;
		NAVG_VSET(int, g_navSys->numSectors, 1);
		NAVG_VSET(short, g_navSys->sectors->firstCluster, 0);
		NAVG_VSET(short, g_navSys->sectors->numClusters, g_navSys->numClusters);
		NAVG_VSET(short, g_navSys->sectors->firstPartition, 0);
		NAVG_VSET(short, g_navSys->sectors->numPartitions, 0);
		g_navSys->sectors->flags = 0;
		return 0;
	}
	FastMemCopy(&g_navSys->numSectors, fileData, 4);
	fileData += 4;
	NAVG_STORE(navSector_t, sectors) = (navSector_t *)navg_AllocMemory(g_navSys->numSectors * 12, &dataMem, (char *)endMemory);
	if (g_navSys->sectors == 0) return 1;
	for (i = 0; i < g_navSys->numSectors; i++) {
		FastMemCopy(&g_navSys->sectors[i], fileData, 12);
		fileData += 12;
	}
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_LoadFile);

JUNK_ASM(func_0048D028,
	"\taddiu $29, $29, 0x30\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x40\n"
	"\tnop\n");

GAME_SECTION(NAVG_ResetNavigationVars) void NAVG_ResetNavigationVars(char *vars, int a, int b)
{
	NAVG_WpSetPos(vars + 0x10, a, b);
}

JUNK_ASM(func_0048D058,
	"\taddiu $29, $29, 0x10\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_FindClosestNode);

JUNK_ASM(func_0048D220,
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n");

GAME_SECTION(navg_FindBestIntraClusterPath) void navg_FindBestIntraClusterPath(unsigned short source, unsigned short destination, int traversalFlags, unsigned short &bestPath, unsigned short &bestEdge, int &shortestDist)
{
	navgClusterAJ_t *cl;
	navgPathListAJ_t *pl;
	navgPathAJ_t *path;
	navgPathAJ_t *end;
	bestPath = 0xffff;
	bestEdge = 0xffff;
	shortestDist = 0xffffff;
	navgNodeAJ_t *n = &((navgNodeAJ_t *)g_navSys->nodes)[source];
	cl = (navgClusterAJ_t *)(n->cluster * 12 + (int)g_navSys->clusters);
	pl = &((navgPathListAJ_t *)g_navSys->pathLists)[cl->firstPath + (source - cl->firstNode) * cl->numNodes + (destination - cl->firstNode)];
	path = &((navgPathAJ_t *)g_navSys->paths)[pl->firstPath];
	end = path + pl->numPaths;
	for (; path < end; path++) {
		if (path->dist < shortestDist && path->nextNode != 0xffff && (path->traversalFlags & traversalFlags) == path->traversalFlags) {
			bestPath = path->nextNode;
			bestEdge = path->nextEdge;
			shortestDist = path->dist;
		}
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_FindBestInterClusterPath);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_FindBestInterSectorPathStep);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", navg_FindBestInterSectorPath);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_UpdateNavigationWpEasy);

GAME_SECTION(NAVG_SetTargetWp) int NAVG_SetTargetWp(NavigationVars *navVars, vec4 &wp)
{
	navVars->targetLoc = wp;
	return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_UpdateMe);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_UpdateNavigation);

JUNK_ASM(func_0048E650,
	"\tori $2, $0, 0xffff\n"
	"\tnop\n"
	"\tori $2, $0, 0xffff\n"
	"\tnop\n"
	"\tori $2, $0, 0xffff\n"
	"\tnop\n"
	"\tori $2, $0, 0xffff\n"
	"\tnop\n");

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

GAME_SECTION(NAVG_NodeGetCenter) void NAVG_NodeGetCenter(unsigned short node, vec4 &oPos)
{
	if (g_navSys && node <= g_navSys->nodeMax) oPos = g_navSys->nodes[node].centroid;
}

JUNK_ASM(func_0048EAB0,
	"\tdaddu $2, $7, $0\n"
	"\tnop\n"
	"\taddiu $29, $29, 0x20\n"
	"\tnop\n");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_NodeGet3DSpline);

GAME_SECTION(NAVG_EdgeGetType) int NAVG_EdgeGetType(unsigned short edge)
{
	if (!g_navSys || g_navSys->edgeMax < edge) return -1;
	return g_navSys->edges[edge].type;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_EdgeGetCliffSpline);

GAME_SECTION(NAVG_WpSet) void NAVG_WpSet(vec4 &wp, vec4 &iPos, unsigned short node)
{
	vec4 ret = iPos;
	((navgWaypoint *)&ret)->node = node;
	wp = ret;
}

GAME_SECTION(NAVG_WpSetPos) void NAVG_WpSetPos(vec4 &wp, vec4 &iPos)
{
	vec4 ret;
	unsigned short node;
	wp = iPos;
	node = NAVG_FindClosestNode(iPos, 0);
	ret = wp;
	((navgWaypoint *)&ret)->node = node;
	wp = ret;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/navsysglobal", NAVG_WpMovePos);

JUNK_ASM(func_0048EC58,
	"\tsq $2, 0x0($5)\n"
	"\tnop\n");

GAME_SECTION(NAVG_WpGetNode) unsigned short NAVG_WpGetNode(vec4 &wp)
{
	return vec4GetWi(wp);
}
