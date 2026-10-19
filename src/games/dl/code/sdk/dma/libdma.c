#include "common.h"
#include "libdma.h"

/* Recovered from Deadlocked retail boot instructions; no vendor source imported. */
#define DMA_SECTION(name) __attribute__((section(".dma_" #name)))
extern volatile unsigned int *sdkDmaChannels[10];
extern const char sdkDmaTimeout[];
extern int scePrintf(const char *, ...);
volatile unsigned int * DMA_SECTION(sceDmaGetChan) sceDmaGetChan(unsigned int channel)
{
    if (channel < 10) return sdkDmaChannels[channel];
    return 0;
}
unsigned int DMA_SECTION(CheckAddress) CheckAddress(unsigned int address)
{
    if ((address >> 28) == 7) {
        address &= 0x0FFFFFFF;
        address |= 0x80000000;
    }
    return address;
}
void DMA_SECTION(memclr) memclr(unsigned char *buffer, int size)
{
    while (size--) *buffer++ = 0;
}
void DMA_SECTION(WaitDma) WaitDma(volatile unsigned int *channel)
{
    int count = 0x1000000;
    while (*channel & 0x100) {
        if (--count < 0) {
            scePrintf(sdkDmaTimeout);
            sceDmaPause(channel);
        }
    }
}
void DMA_SECTION(sceDmaSend) sceDmaSend(volatile unsigned int *channel, void *address)
{
    unsigned int dmaAddress = CheckAddress((unsigned int)address);
    int control;
    WaitDma(channel);
    if (channel[12] != 0xFFFFFFFF) channel[12] = dmaAddress;
    control = channel[0];
    channel[8] = 0;
    channel[0] = (control & ~12) | 0x105;
}

extern int DIntr(void);
extern int EIntr(void);
extern const int sdkDmaResetChannels[10];
extern const unsigned char sdkDmaSts[10];
extern const unsigned char sdkDmaStd[10];
extern const unsigned char sdkDmaMfd[10];
extern DmaEnv sdkDmaEnvironment;

unsigned int DMA_SECTION(sceDmaPause) sceDmaPause(volatile unsigned int *channel)
{
    int intr = DIntr();
    unsigned int enable = *(volatile unsigned int *)0x1000F520;
    unsigned int control;
    if (!(enable & 0x10000)) *(volatile unsigned int *)0x1000F590 = enable | 0x10000;
    (void)*(volatile unsigned int *)0x1000E000;
    control = *channel;
    *channel = control & ~0x100U;
    *(volatile unsigned int *)0x1000F590 = enable;
    if (intr) EIntr();
    return control;
}

unsigned int DMA_SECTION(sceDmaReset) sceDmaReset(int mode)
{
    DmaEnv env;
    unsigned int enabled = *(volatile unsigned int *)0x1000E000 & 1;
    int i;
    for (i = 0; i < 10; ++i) {
        if (sdkDmaResetChannels[i]) {
            volatile unsigned int *p = sdkDmaChannels[i];
            p[32] = 0;
            p[0] = 0;
            p[12] = 0;
            p[4] = 0;
            p[20] = 0;
            p[16] = 0;
        }
    }
    *(volatile unsigned int *)0x1000E010 = 0xFF1F;
    /* Ordinary store preserves the retail memclr call delay slot. */
    *(unsigned int *)0x1000E010 = *(volatile unsigned int *)0x1000E010 & 0xFF1F0000;
    memclr((unsigned char *)&env, sizeof(env));
    sceDmaPutEnv(&env);
    if (mode == 1) *(volatile unsigned int *)0x1000E000 |= 1;
    return enabled;
}

int DMA_SECTION(sceDmaPutEnv) sceDmaPutEnv(DmaEnv *env)
{
    unsigned int ctrl = *(volatile unsigned int *)0x1000E000;
    unsigned int pcr = *(volatile unsigned int *)0x1000E020;
    unsigned int sqwc = *(volatile unsigned int *)0x1000E030;
    unsigned int rbor = *(volatile unsigned int *)0x1000E050;
    unsigned int rbsr = *(volatile unsigned int *)0x1000E040;
    if (env->sts > 9) return -1;
    if (env->std > 9) return -2;
    if (env->mfd > 9) return -3;
    if (env->release > 6) return -4;
    ctrl = (ctrl & ~0x30U) | (sdkDmaSts[env->sts] << 4);
    ctrl = (ctrl & ~0xC0U) | (sdkDmaStd[env->std] << 6);
    ctrl = (ctrl & ~0xCU) | (sdkDmaMfd[env->mfd] << 2);
    if (env->release) {
        ctrl |= 2;
        ctrl = (ctrl & ~0x300U) | ((env->release - 1) << 8);
    } else ctrl &= ~2U;
    pcr = (env->priority << 16) | env->enable;
    sqwc = (env->transfer << 16) | env->skip;
    rbsr = env->ringSize;
    *(volatile unsigned int *)0x1000E000 = ctrl;
    *(volatile unsigned int *)0x1000E020 = pcr;
    *(volatile unsigned int *)0x1000E030 = sqwc;
    rbor = (unsigned int)env->ringBase;
    *(volatile unsigned int *)0x1000E050 = rbor;
    *(volatile unsigned int *)0x1000E040 = rbsr;
    sdkDmaEnvironment = *env;
    return 0;
}

/* Discarded-code fragments retain their original fixed slots. */
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .dma_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/dma/libdma", func_00139A50);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/dma/libdma", func_00139D98);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/dma/libdma", func_00139E08);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/dma/libdma", func_00139EC0);
