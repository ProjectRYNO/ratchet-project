#include "common.h"
#include "rt_mtrandgen.h"

#define MEDIUS_MTRAND_SECTION(name) __attribute__((section(".medius_mtrand_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_mtrand_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#define hiBit(u) ((u) & 0x80000000)
#define loBit(u) ((u) & 0x00000001)
#define loBits(u) ((u) & 0x7FFFFFFF)
#define mixBits(u, v) (hiBit(u) | loBits(v))

void MEDIUS_MTRAND_SECTION(seedMT) seedMT(unsigned int seed)
{
    unsigned int x = seed | 1;
    unsigned int *s = gMT.state;
    int j;

    for (gMT.left = MT_N - 1, *s++ = x, j = MT_N; --j; *s++ = (x *= 69069))
        ;
}

void MEDIUS_MTRAND_SECTION(seedMTUsingArray) seedMTUsingArray(unsigned int *pSeeds, unsigned int nSeeds)
{
    unsigned int x = 0xFFFFFFFF;
    unsigned int *s = gMT.state;
    int j;

    gMT.left = MT_N - 1;
    if (nSeeds >= MT_N) nSeeds = MT_N - 1;
    *s++ = x;
    for (j = MT_N; j; j--) {
        if (nSeeds) {
            x ^= *pSeeds++;
            nSeeds--;
        }
        x = (x << 5) | (x >> 27);
        x *= 69069;
        *s++ = x;
    }
}

void MEDIUS_MTRAND_SECTION(reloadMT) reloadMT(void)
{
    unsigned int *p0 = gMT.state, *p2 = gMT.state + 2, *pM = gMT.state + MT_M, s0, s1;
    int j;

    if (gMT.left > MT_N) setNewSeed(0x3579ABCD);
    gMT.left = 0;
    for (s0 = gMT.state[0], s1 = gMT.state[1], j = MT_N - MT_M + 1; --j; s0 = s1, s1 = *p2++)
        *p0++ = *pM++ ^ (mixBits(s0, s1) >> 1) ^ (loBit(s1) ? MT_K : 0);
    for (pM = gMT.state, j = MT_M; --j; s0 = s1, s1 = *p2++)
        *p0++ = *pM++ ^ (mixBits(s0, s1) >> 1) ^ (loBit(s1) ? MT_K : 0);
    s1 = gMT.state[0], *p0 = *pM ^ (mixBits(s0, s1) >> 1) ^ (loBit(s1) ? MT_K : 0);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_mtrandgen", func_01EA9BC0);

unsigned int MEDIUS_MTRAND_SECTION(randomMT) randomMT(void)
{
    unsigned int v;

    if (++gMT.left >= MT_N) reloadMT();
    v = mediusMtLastOutput ^ gMT.state[gMT.left];
    rtMtMixA = ((rtMtMixA << 25) | (rtMtMixA >> 7)) ^ v;
    rtMtMixB = ((v << 7) | (v >> 25)) ^ rtMtMixB;
    mediusMtLastOutput = (rtMtMixA & v) | (rtMtMixB & ~v);
    return mediusMtLastOutput;
}

void MEDIUS_MTRAND_SECTION(setNewSeed) setNewSeed(unsigned int skew)
{
    setNewSeed_platform(skew);
}
