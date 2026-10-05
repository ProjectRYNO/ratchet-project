#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/boot", unpackbuff);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/boot", ParsePatch);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/boot", ParseBin);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/boot", GetBootOptionsFromSettings);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/boot", ApplyBootOptionsToSettings);

extern "C" {
typedef void (*BootEntry)(void);

void __main(void);
int strncmp(const char *left, const char *right, unsigned int length);
int strcmp(const char *left, const char *right);
void ApplyBootOptionsToSettings(const char *options);
void InitializeLobbyControllerSettingsToDefaults(void);
void startlevel(void);
BootEntry ParseBin(void);

// Names recovered in Ghidra; these bind to the existing split data symbols.
extern unsigned char gParsedBootOptions __asm__("D_0021DE69");
extern int nwLobbyInitIntoScreen __asm__("D_0021DE80");
extern int g_SkipBootIntro __asm__("D_0021DC84");
extern const char bootOptionsPrefix[] __asm__("D_0021DC90"); // "BOPT="
extern const char gooeyOption[] __asm__("D_0021DC98");       // "gooey"
extern const char multiOption[] __asm__("D_0021DCA0");       // "multi"
}

// Original: 0x00157C58. This EE compiler needs the runtime call explicitly.
int main(int argc, char **argv)
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
