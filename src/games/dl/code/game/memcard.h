#ifndef MEMCARD_H
#define MEMCARD_H

#include "gameglobals.h"

struct memcard_saveinfo { // 0x20
	/* 0x00 */ int level;
	/* 0x04 */ int bolts;
	/* 0x08 */ int completes;
	/* 0x0c */ int elapsedTime;
	/* 0x10 */ sceCdCLOCK saveTime;
	/* 0x18 */ int savedDifficultyLevel;
	/* 0x1c */ int bad;
};

struct memcard_data { // 0xd4
	/* 0x00 */ int port;
	/* 0x04 */ int slot;
	/* 0x08 */ int type;
	/* 0x0c */ int free;
	/* 0x10 */ int changed;
	/* 0x14 */ int format;
	/* 0x18 */ short saveslot;
	/* 0x1a */ short curslot;
	/* 0x1c */ int RC1and2_weapons_checked;
	/* 0x20 */ int corrupt_size;
	/* 0x24 */ unsigned int patch_size;
	/* 0x28 */ int oldsave;
	/* 0x2c */ int gamesize;
	/* 0x30 */ int levelsize;
	/* 0x34 */ memcard_saveinfo info[5];
};

struct memcard_globals { // 0x1f4
	/* 0x000 */ memcard_data memcards[2];
	/* 0x1a8 */ int cmd;
	/* 0x1ac */ int res;
	/* 0x1b0 */ int useslot;
	/* 0x1b4 */ int slot;
	/* 0x1b8 */ int level;
	/* 0x1bc */ int sync;
	/* 0x1c0 */ int file;
	/* 0x1c4 */ int stage;
	/* 0x1c8 */ int substage;
	/* 0x1cc */ int nextstage;
	/* 0x1d0 */ int nextslot;
	/* 0x1d4 */ int err;
	/* 0x1d8 */ int errslot;
	/* 0x1dc */ char *addr;
	/* 0x1e0 */ int size;
	/* 0x1e4 */ int autosave;
	/* 0x1e8 */ int checkslot;
	/* 0x1ec */ int timer;
	/* 0x1f0 */ int savesize;
};

#endif
