#ifndef BOOTUTIL_H
#define BOOTUTIL_H

typedef struct { // 0x20
	/* 0x00 */ char bPercents[15];
	/* 0x0f */ char flags;
	/* 0x10 */ float oldHitPoints;
	/* 0x14 */ short int armorBits;
	/* 0x16 */ short int pad[5];
} ArmorVars;

#endif
