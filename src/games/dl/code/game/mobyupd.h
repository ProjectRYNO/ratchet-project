#ifndef MOBYUPD_H
#define MOBYUPD_H

struct mobyfuncs { // 0x20
	/* 0x00 */ void *(*getMpController)();
	/* 0x04 */ void *(*getMpObject)();
	/* 0x08 */ void (*netUpdate)();
	/* 0x0c */ int (*masterUpdate)();
	/* 0x10 */ void *(*getMobyInterface)(int, int, void *);
	/* 0x14 */ void (*handleEvent)();
	/* 0x18 */ void *(*getParentPlayer)();
	/* 0x1c */ void (*setVisibility)();
};

struct mobyVtblEntry { // 0xc
	/* 0x00 */ int oClass;
	/* 0x04 */ void *update;
	/* 0x08 */ mobyfuncs *funcs;
};

#endif
