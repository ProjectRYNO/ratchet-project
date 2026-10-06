#ifndef TABLES_H
#define TABLES_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/types/RECOVERED_TYPES.md.

// dltypes.txt:7266; prototype-layout.
typedef struct { // 0x18
    /* 0x00 */ short int oClasses[4];
    /* 0x08 */ short int localizationTag;
    /* 0x0a */ short int localizationDescTag;
    /* 0x0c */ short int localizationSizeTag;
    /* 0x0e */ short int localizationWorldTag;
    /* 0x10 */ short int barWidths[4];
} EnemyTypeTag;

#endif
