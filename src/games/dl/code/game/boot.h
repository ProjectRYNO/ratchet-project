#ifndef BOOT_H
#define BOOT_H

// Recovered data layouts from dltypes.txt and the prototype sources.
// Sizes/offsets use the PS2 ABI. See DOCS/RECOVERED_TYPES.md.

// dltypes.txt:969; retail-boot-accesses.
typedef struct { // 0x8
    /* 0x0:0 */ unsigned int wideScreen : 1;
    /* 0x0:1 */ unsigned int progressiveScan : 1;
    /* 0x0:2 */ unsigned int stereo : 1;
    /* 0x0:3 */ unsigned int musicVolume : 11;
    /* 0x1:6 */ unsigned int effectsVolume : 11;
    /* 0x3:1 */ unsigned int language : 3;
    /* 0x4 */ short unsigned int screen_offset_x;
    /* 0x6 */ short unsigned int screen_offset_y;
} GameBootOptions;

// dltypes.txt:990; prototype-layout.
typedef struct { // 0x10
    /* 0x0 */ void *address;
    /* 0x4 */ int size;
    /* 0x8 */ int type;
    /* 0xc */ void *entry;
} blockhdr;

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*BootEntry)(void);
void GetBootOptionsFromSettings(char *output);
void ApplyBootOptionsToSettings(const char *input);
BootEntry ParseBin(void);

#ifdef __cplusplus
}
#endif

#endif
