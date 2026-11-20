#ifndef VENDOR_H
#define VENDOR_H

typedef struct { // 0x24
	/* 0x00 */ int type;
	/* 0x04 */ int id;
	/* 0x08 */ int cost;
	/* 0x0c */ int description;
	/* 0x10 */ int uc_name;
	/* 0x14 */ int name;
	/* 0x18 */ int icon;
	/* 0x1c */ int image;
	/* 0x20 */ int affordable;
} VendorItem;

#endif
