#ifndef GUBER_GADGETBOX_H
#define GUBER_GADGETBOX_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

// dltypes.txt:2758; ghidra-layout.
typedef struct { // 0x8
    /* 0x0 */ unsigned int purchase_price;
    /* 0x4 */ unsigned int discount_price;
} ModPrices;

#endif
