#ifndef GUBER_PADSTREAM_H
#define GUBER_PADSTREAM_H

// dltypes.txt:6331; ghidra-layout.
typedef struct { // 0x2
    /* 0x0 */ unsigned char data[2];
} pad_frame;

struct PadStream { // 0x1e0
	/* 0x000 */ unsigned short button_bits[4];
	/* 0x008 */ unsigned short analog_stick[4];
	/* 0x010 */ unsigned short right_analog_stick[4];
	/* 0x018 */ unsigned char frames_with_btn_diffs : 4;
	/* 0x019 */ unsigned char btn_bit_diffs[32];
	/* 0x03c */ int cur_btn_bit_offset;
	/* 0x040 */ pad_frame prev_frame;
	/* 0x042 */ unsigned char pad_stream_buf[2][200];
	/* 0x1d4 */ int totalPadStreamBytes;
	/* 0x1d8 */ int curFrame;
	/* 0x1dc */ int padStreamReady;
};

#endif
