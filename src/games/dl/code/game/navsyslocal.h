#ifndef NAVSYSLOCAL_H
#define NAVSYSLOCAL_H

typedef struct { // 0x10
	/* 0x0 */ char effectorMode;
	/* 0x1 */ char bunkerType;
	/* 0x2 */ char padc[2];
	/* 0x4 */ float strength;
	/* 0x8 */ int type;
	/* 0xc */ int pad;
} EffectorVars;

#endif
