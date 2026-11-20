#ifndef LOADERS_H
#define LOADERS_H

typedef struct { // 0x20
	/* 0x00 */ int pifID;
	/* 0x04 */ int fileSize;
	/* 0x08 */ int uSize;
	/* 0x0c */ int vSize;
	/* 0x10 */ int texFormat;
	/* 0x14 */ int clutFormat;
	/* 0x18 */ int clutOrder;
	/* 0x1c */ int mipLevels;
} PifHeader;

#endif
