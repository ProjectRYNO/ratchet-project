#include "common.h"
#include "boot.h"
#include "gameglobals.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/boot", unpackbuff);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/boot", ParsePatch);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/boot", ParseBin);

// Boot option wire format recovered from 0x1579F0 and 0x157B30.
// Eight little-endian bytes encoded as sixteen uppercase hexadecimal digits.
extern "C" {

void __attribute__((section(".boot_get_options"))) GetBootOptionsFromSettings(char *output)
{
    unsigned int words[2];
    words[0] = (bootSettings.Wide & 1)
             | ((progressiveScan & 1) << 1)
             | ((bootSettings.Stereo & 1) << 2)
             | ((bootSettings.MusicVolume & 0x7FF) << 3)
             | ((bootSettings.EffectsVolume & 0x7FF) << 14)
             | ((bootSettings.Language & 7) << 25);
    // Bits 28..31 were uninitialized stack padding in the original encoder.
    // They are ignored by the decoder; emit zero for a deterministic string.
    words[1] = (displayX & 0xFFFF) | (displayY << 16);
    for (unsigned int i = 0; i < 8; ++i) {
        unsigned int byte = (words[i >> 2] >> ((i & 3) * 8)) & 0xFF;
        unsigned int high = byte >> 4;
        unsigned int low = byte & 15;
        *output++ = high < 10 ? high + '0' : high + 'A' - 10;
        *output++ = low < 10 ? low + '0' : low + 'A' - 10;
    }
    *output = 0;
}

void __attribute__((section(".boot_apply_options"))) ApplyBootOptionsToSettings(const char *input)
{
    unsigned int words[2] = {0, 0};
    unsigned char *bytes = reinterpret_cast<unsigned char *>(words);
    // Valid game input contains exactly eight pairs. Bound malformed input
    // instead of reproducing the original stack overflow/uninitialized reads.
    for (unsigned int i = 0; i < 8 && input[0] && input[1]; ++i, input += 2) {
        unsigned int high = static_cast<unsigned char>(input[0]);
        unsigned int low = static_cast<unsigned char>(input[1]);
        high = high - '0' < 10 ? high - '0' : high - 'A' < 6 ? high - 'A' + 10 : ~0U;
        low = low - '0' < 10 ? low - '0' : low - 'A' < 6 ? low - 'A' + 10 : ~0U;
        bytes[i] = static_cast<unsigned char>((high << 4) + low);
    }
    unsigned int flags = words[0];
    progressiveScan = (flags >> 1) & 1;
    bootSettings.Wide = flags & 1;
    bootSettings.Language = (flags >> 25) & 7;
    bootSettings.Stereo = (flags >> 2) & 1;
    bootSettings.MusicVolume = (flags >> 3) & 0x7FF;
    bootSettings.EffectsVolume = (flags >> 14) & 0x7FF;
    displayX = words[1] & 0xFFFF;
    displayY = words[1] >> 16;
}
}

extern "C" {

void __main(void);
int strncmp(const char *left, const char *right, unsigned int length);
int strcmp(const char *left, const char *right);
void InitializeLobbyControllerSettingsToDefaults(void);
void startlevel(void);

// Names recovered in Ghidra; these bind to the existing split data symbols.
extern unsigned char gParsedBootOptions;
extern int nwLobbyInitIntoScreen;
extern int g_SkipBootIntro;
extern const char bootOptionsPrefix[]; // "BOPT="
extern const char gooeyOption[];       // "gooey"
extern const char multiOption[];       // "multi"
}

// Original: 0x00157C58. This EE compiler needs the runtime call explicitly.
int __attribute__((section(".boot_main"))) main(int argc, char **argv)
{
    __main();
    gParsedBootOptions = 0;
    for (; argc > 0; --argc, ++argv) {
        if (strncmp(*argv, bootOptionsPrefix, 5) == 0) {
            ApplyBootOptionsToSettings(*argv + 5);
        } else if (strcmp(*argv, gooeyOption) == 0) {
            nwLobbyInitIntoScreen = 2;
        } else if (strcmp(*argv, multiOption) == 0) {
            g_SkipBootIntro = 1;
        } else {
            continue;
        }
        ++gParsedBootOptions;
    }

    InitializeLobbyControllerSettingsToDefaults();
    BootEntry nextEntry = startlevel;
    for (;;) {
        nextEntry();
        nextEntry = ParseBin();
        FlushCache(0);
        FlushCache(2);
    }
}
