#ifndef STASH_H
#define STASH_H

struct StashBlock { // 0x10
	/* 0x00 */ char *ram;
	/* 0x04 */ int qwc;
	/* 0x08 */ const char *comment;
	/* 0x0c */ int pad;
};

#endif
