#ifndef RT_MTRANDGEN_H
#define RT_MTRANDGEN_H

// Mersenne Twister in the style of Shawn Cokus's cokus.c: state[N + 1] with a running
// index, plus a Medius output mixer (rtMtMixA, rtMtMixB, mediusMtLastOutput).
#define MT_N 624
#define MT_M 397
#define MT_K 0x9908B0DF

// Retail addresses state words and the index from one base (gMT + 0x9C4).
typedef struct { // 0x9C8
    /* 0x000 */ unsigned int state[MT_N + 1];
    /* 0x9C4 */ int left;
} RT_MT;

#ifdef __cplusplus
extern "C" {
#endif

extern RT_MT gMT;
extern unsigned int rtMtMixA;
extern unsigned int rtMtMixB;
// Last randomMT output; randomMT XORs it into the next state word before mixing.
// The debug information names it y.
extern unsigned int mediusMtLastOutput;

void seedMT(unsigned int seed);
void seedMTUsingArray(unsigned int *pSeeds, unsigned int nSeeds);
void reloadMT(void);
unsigned int randomMT(void);
void setNewSeed(unsigned int skew);
void setNewSeed_platform(unsigned int skew);

#ifdef __cplusplus
}
#endif

#endif
