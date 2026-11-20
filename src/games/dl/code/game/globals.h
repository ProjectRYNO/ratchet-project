#ifndef GLOBALS_H
#define GLOBALS_H

struct QueueNode { // 0x8
	/* 0x00 */ int movieId;
	/* 0x04 */ int movieType;
};

struct MovieQueue { // 0x70
	/* 0x00 */ int intro;
	/* 0x04 */ short *pIntro;
	/* 0x08 */ QueueNode mItemsToPlay[10];
	/* 0x58 */ int mHead;
	/* 0x5c */ int mTail;
	/* 0x60 */ int mItemCount;
	/* 0x64 */ unsigned char mAborted;
	/* 0x68 */ int mTypeOfRequest;
	/* 0x6c */ unsigned char mLocked;
};

#endif
