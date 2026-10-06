#ifndef FONTS_H
#define FONTS_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/types/RECOVERED_TYPES.md.

// dltypes.txt:3977; ghidra-layout.
typedef struct { // 0x1c
    /* 0x00 */ short int win_top;
    /* 0x02 */ short int win_bot;
    /* 0x04 */ short int win_left;
    /* 0x06 */ short int win_right;
    /* 0x08 */ short int text_x;
    /* 0x0a */ short int text_y;
    /* 0x0c */ short int max_width;
    /* 0x0e */ short int max_height;
    /* 0x10 */ short int line_spacing;
    /* 0x12 */ short int flags;
    /* 0x14 */ short int sub_pixel_x;
    /* 0x16 */ short int sub_pixel_y;
    /* 0x18 */ short int drop_shadow_offset_x;
    /* 0x1a */ short int drop_shadow_offset_y;
} FontWindow;

// dltypes.txt:10327; ghidra-layout.
typedef struct { // 0x4
    /* 0x0 */ unsigned char u;
    /* 0x1 */ unsigned char v;
    /* 0x2 */ signed char drop;
    /* 0x3 */ signed char spacing;
} fontLetter;

#endif
