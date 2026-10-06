// Host-only behavioral test of the same source compiled for the EE.
// PERMUTER suppresses the untouched assembly includes, not the C++ main.
#define PERMUTER
#define main tested_boot_main
#include "../code/game/boot.cpp"
#undef main

extern "C" int puts(const char *);
extern "C" void abort(void);

unsigned char gParsedBootOptions;
int nwLobbyInitIntoScreen;
int g_SkipBootIntro;
const char bootOptionsPrefix[] = "BOPT=";
const char gooeyOption[] = "gooey";
const char multiOption[] = "multi";
unsigned char bootSettings[0xC0] __attribute__((aligned(4)));
unsigned int progressiveScan;
unsigned int displayX;
unsigned int displayY;

static int stage;
struct Finished {};

static void require(bool value)
{
    if (!value) abort();
}

extern "C" int strncmp(const char *a, const char *b, unsigned int count)
{
    for (unsigned int i = 0; i < count; ++i) {
        if (a[i] != b[i]) return (unsigned char)a[i] - (unsigned char)b[i];
        if (a[i] == 0) return 0;
    }
    return 0;
}

extern "C" int strcmp(const char *a, const char *b)
{
    while (*a && *a == *b) { ++a; ++b; }
    return (unsigned char)*a - (unsigned char)*b;
}

extern "C" void __main(void) { require(stage == 0); stage = 1; }
extern "C" void InitializeLobbyControllerSettingsToDefaults(void)
{
    require(stage == 1);
    stage = 2;
}
extern "C" void startlevel(void) { require(stage == 2); stage = 3; }
static void nextLevel(void) { require(stage == 6); stage = 7; }
static void finalLevel(void) { require(stage == 10); throw Finished(); }
extern "C" BootEntry ParseBin(void)
{
    if (stage == 3) { stage = 4; return nextLevel; }
    require(stage == 7);
    stage = 8;
    return finalLevel;
}
extern "C" void FlushCache(int mode)
{
    if (stage == 4 || stage == 8) require(mode == 0);
    else { require(stage == 5 || stage == 9); require(mode == 2); }
    ++stage;
}

static void run(int argc, char **argv, unsigned int parsed, int screen, int skip)
{
    stage = 0;
    gParsedBootOptions = 99;
    nwLobbyInitIntoScreen = -7;
    g_SkipBootIntro = -9;
    try {
        tested_boot_main(argc, argv);
        abort(); // main must not return
    } catch (const Finished &) {}
    require(stage == 10);
    require(gParsedBootOptions == parsed);
    require(nwLobbyInitIntoScreen == screen);
    require(g_SkipBootIntro == skip);
}

int main()
{
    run(0, 0, 0, -7, -9);
    run(-1, 0, 0, -7, -9);
    char *unknown[] = {(char *)"game.elf", (char *)"GOOEY", (char *)"BOPT", (char *)"multi-more"};
    run(4, unknown, 0, -7, -9);
    char *options[] = {(char *)"game.elf", (char *)"BOPT=1234", (char *)"gooey", (char *)"multi", (char *)"BOPT="};
    run(5, options, 4, 2, 1);
    require(progressiveScan == 0 && displayX == 0 && displayY == 0);
    char *repeated[] = {(char *)"BOPT==x", (char *)"gooey", (char *)"gooey"};
    run(3, repeated, 3, 2, -9);
    char *overflow[256];
    for (int i = 0; i < 256; ++i) overflow[i] = (char *)"gooey";
    run(256, overflow, 0, 2, -9);
    puts("PASS: six argument cases, runtime initialization, two level transitions, and cache call ordering");
}
