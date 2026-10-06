#ifndef NPC_H
#define NPC_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

// dltypes.txt:6095; ghidra-layout.
typedef struct { // 0x1c
    /* 0x00 */ int offer;
    /* 0x04 */ short int scene;
    /* 0x06 */ short int dest;
    /* 0x08 */ short int cond_type;
    /* 0x0a */ short int cond_val;
    /* 0x0c */ short int true_dest;
    /* 0x0e */ short int false_dest;
    /* 0x10 */ short int flags;
    /* 0x12 */ short int pad[5];
} npcStep;

#endif
