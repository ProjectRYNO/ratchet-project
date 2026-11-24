#ifndef GUBER_GUBERMOBY_H
#define GUBER_GUBERMOBY_H

struct Gid { // 0x4
	/* 0x0 */ unsigned int ObjectIndex : 12;
	/* 0x1 */ unsigned int ObjectCount : 12;
	/* 0x3 */ unsigned int ObjectType : 4;
	/* 0x3 */ unsigned int HostId : 4;
};

struct Guber { // 0x18
	/* 0x00 */ union { // 0x4
		/* 0x00 */ unsigned int UID;
		/* 0x00 */ Gid gid;
	};
	/* 0x04 */ int MasterHostId;
	/* 0x08 */ int State;
	/* 0x0c */ Guber *pNext;
	/* 0x10 */ Guber *pPrev;
	/* 0x14 */ void *__vtable;
};

#endif
