#ifndef PAD_H
#define PAD_H

#include "../include/types.h"

struct PAD { // 0x5c0
	/* 0x000 */ u128 pad_buf[16];
	/* 0x100 */ float analog[16];
	/* 0x140 */ float hudAnalog[16];
	/* 0x180 */ unsigned char profile[4];
	/* 0x184 */ unsigned char vib_profile[4];
	/* 0x188 */ unsigned char act_direct[4];
	/* 0x18c */ short invalidTimer;
	/* 0x18e */ short ringIndex;
	/* 0x190 */ int ringValidSize;
	/* 0x194 */ int socket;
	/* 0x198 */ int phase;
	/* 0x19c */ int state;
	/* 0x1a0 */ int bits;
	/* 0x1a4 */ int bitsOn;
	/* 0x1a8 */ int bitsOff;
	/* 0x1ac */ int bitsPrev;
	/* 0x1b0 */ int digitalBits;
	/* 0x1b4 */ int digitalBitsOn;
	/* 0x1b8 */ int digitalBitsOff;
	/* 0x1bc */ int digitalBitsPrev;
	/* 0x1c0 */ int hudBits;
	/* 0x1c4 */ int hudBitsOn;
	/* 0x1c8 */ int hudBitsOff;
	/* 0x1cc */ int hudDivert;
	/* 0x1d0 */ int handsOff;
	/* 0x1d4 */ int handsOffStick;
	/* 0x1d8 */ int useAnalog;
	/* 0x1dc */ int term_id;
	/* 0x1e0 */ int bitsOnRing[30];
	/* 0x258 */ float analogAngRing[30];
	/* 0x2d0 */ float analogMagRing[30];
	/* 0x348 */ int unmaskedBits;
	/* 0x34c */ int lagIndex;
	/* 0x350 */ int lagValidSize;
	/* 0x354 */ int bits_Lagged[7];
	/* 0x370 */ int digitalBits_Lagged[7];
	/* 0x38c */ float analog_Lagged[7][16];
	/* 0x54c */ unsigned char port;
	/* 0x54d */ unsigned char repeatDelay;
	/* 0x54e */ unsigned char repeatSpeed;
	/* 0x54f */ unsigned char repeatCounter;
	/* 0x550 */ unsigned char multi_tap_connected;
	/* 0x551 */ unsigned char disconnected;
	/* 0x552 */ unsigned char act_align[6];
	/* 0x558 */ unsigned char slot;
	/* 0x559 */ unsigned char initialized;
	/* 0x55c */ int rterm_id;
	/* 0x560 */ int id;
	/* 0x564 */ int exid;
	/* 0x568 */ int lagFrames;
	/* 0x56c */ void *RawPadInputCallback;
	/* 0x570 */ void *pCallbackData;
	/* 0x574 */ unsigned char rdata[32];
	/* 0x594 */ int ipad[10];
};

#endif
