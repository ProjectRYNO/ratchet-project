#ifndef GUBER_GADGET_H
#define GUBER_GADGET_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/types/RECOVERED_TYPES.md.

// dltypes.txt:2603; ghidra-layout.
typedef struct { // 0x24
    /* 0x00 */ unsigned int purchase_price;
    /* 0x04 */ unsigned int discount_price;
    /* 0x08 */ short unsigned int ammo_price;
    /* 0x0a */ short unsigned int pda_ammo_price;
    /* 0x0c */ short unsigned int ammo_count;
    /* 0x0e */ short unsigned int ammo_limit;
    /* 0x10 */ short unsigned int pad;
    /* 0x12 */ short unsigned int ammo_start;
    /* 0x14 */ unsigned int gold_price;
    /* 0x18 */ unsigned int mod_shock_price;
    /* 0x1c */ unsigned int mod_acid_price;
    /* 0x20 */ unsigned int mod_lock_on_price;
} GadgetPrice;

// dltypes.txt:2677; ghidra-layout.
typedef struct { // 0x20
    /* 0x00 */ int level;
    /* 0x04 */ int levelUpExperience;
    /* 0x08 */ int mpLevelUpExperience;
    /* 0x0c */ int ipadA;
    /* 0x10 */ float gadgetDamage[4];
} GadgetLevelDef;

// dltypes.txt:2685; prototype-layout.
typedef struct { // 0x10
    /* 0x0 */ int levelUpExperience;
    /* 0x4 */ float damageIncrement;
    /* 0x8 */ int levelUpExperienceBase;
    /* 0xc */ int ipadB;
} GadgetMegaLevelInfo;

#endif
