/* Host checks for the recovered boot libdma C. Hardware callbacks are mocked. */
#define _GNU_SOURCE
#include <sys/mman.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "libdma.h"

volatile unsigned int *sdkDmaChannels[10];
const char sdkDmaTimeout[] = "libdma: sync timeout\n";
static unsigned int timeoutMessages;
static unsigned int pauses;

int scePrintf(const char *format, ...)
{
    assert(format == sdkDmaTimeout);
    ++timeoutMessages;
    return 0;
}

/* MMIO is ordinary mapped memory here: no DMA engine or W1C semantics. */
#define REG(address) (*(volatile unsigned int *)(uintptr_t)(address))
const int sdkDmaResetChannels[10] = {1,1,1,1,1,0,0,0,1,1};
const unsigned char sdkDmaSts[10] = {0,0,0,3,0,1,0,0,2,0};
const unsigned char sdkDmaStd[10] = {0,1,2,0,0,0,3,0,0,0};
const unsigned char sdkDmaMfd[10] = {0,2,3,0,0,0,0,0,0,0};
DmaEnv sdkDmaEnvironment;
static int interruptsEnabled = 1;
static unsigned int enables;
int DIntr(void) { ++pauses; return interruptsEnabled; }
int EIntr(void) { ++enables; return 0; }

static unsigned int checkEnvironment(void)
{
    DmaEnv env;
    unsigned int i, cases = 0;
    for (i = 0; i < 4; ++i) {
        unsigned char *fields;
        memset(&env, 0, sizeof(env));
        fields = (unsigned char *)&env;
        fields[i] = i == 3 ? 7 : 10;
        REG(0x1000E000) = 0x12345678;
        memset(&sdkDmaEnvironment, 0xA5, sizeof(sdkDmaEnvironment));
        assert(sceDmaPutEnv(&env) == -(int)(i + 1));
        assert(REG(0x1000E000) == 0x12345678);
        assert(((unsigned char *)&sdkDmaEnvironment)[0] == 0xA5);
        ++cases;
    }
    for (i = 0; i < 70; ++i) {
        unsigned int expected = 0xA55AFFFF;
        memset(&env, 0, sizeof(env));
        env.sts = i % 10; env.std = (i + 3) % 10; env.mfd = (i + 7) % 10;
        env.release = i / 10;
        env.priority = 0xABCD; env.enable = 0x1234;
        env.skip = 0x5678; env.transfer = 0x9ABC;
        env.ringBase = (void *)(uintptr_t)0x00123450; env.ringSize = 0xFFF0;
        REG(0x1000E000) = expected;
        expected = (expected & ~0x30u) | (sdkDmaSts[env.sts] << 4);
        expected = (expected & ~0xC0u) | (sdkDmaStd[env.std] << 6);
        expected = (expected & ~0xCu) | (sdkDmaMfd[env.mfd] << 2);
        if (env.release) expected = ((expected | 2u) & ~0x300u) | ((env.release - 1) << 8);
        else expected &= ~2u;
        assert(sceDmaPutEnv(&env) == 0);
        assert(REG(0x1000E000) == expected);
        assert(REG(0x1000E020) == 0xABCD1234);
        assert(REG(0x1000E030) == 0x9ABC5678);
        assert(REG(0x1000E050) == 0x00123450);
        assert(REG(0x1000E040) == 0xFFF0);
        assert(memcmp(&env, &sdkDmaEnvironment, sizeof(env)) == 0);
        ++cases;
    }
    return cases;
}

int main(void)
{
    volatile unsigned int channels[10][36] = {{0}};
    unsigned char buffer[258];
    unsigned int i, j, cases = 0;
    const unsigned int invalid[] = {10, 11, 0x80000000u, 0xFFFFFFFFu};
    const unsigned int controls[] = {0, 0x0C, 0xFF, 0xA55A0200u};
    void *mmio = mmap((void *)(uintptr_t)0x10000000, 0x10000,
        PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0);
    assert(mmio == (void *)(uintptr_t)0x10000000);
    for (i = 0; i < 10; ++i) {
        sdkDmaChannels[i] = channels[i];
        assert(sceDmaGetChan(i) == channels[i]);
        ++cases;
    }
    for (i = 0; i < 4; ++i) {
        assert(sceDmaGetChan(invalid[i]) == 0);
        ++cases;
    }
    for (i = 0; i < 16; ++i) {
        unsigned int address = i << 28;
        unsigned int expected = i == 7 ? 0x80000000u : address;
        assert(CheckAddress(address) == expected);
        assert(CheckAddress(address | 0x0FFFFFFFu) == (expected | 0x0FFFFFFFu));
        cases += 2;
    }
    for (i = 0; i <= 256; ++i) {
        memset(buffer, 0xA5, sizeof(buffer));
        memclr(buffer + 1, (int)i);
        assert(buffer[0] == 0xA5 && buffer[i + 1] == 0xA5);
        for (j = 1; j <= i; ++j) assert(buffer[j] == 0);
        ++cases;
    }
    WaitDma(channels[0]);
    assert(timeoutMessages == 0 && pauses == 0);
    channels[0][0] = 0x100;
    WaitDma(channels[0]);
    assert(timeoutMessages == 1 && pauses == 1 && channels[0][0] == 0);
    cases += 2;
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 2; ++j) {
            channels[0][0] = controls[i];
            channels[0][8] = 0x12345678;
            channels[0][12] = j ? 0xFFFFFFFFu : 0;
            sceDmaSend(channels[0], (void *)(uintptr_t)0x70001230);
            assert(channels[0][0] == ((controls[i] & ~12u) | 0x105));
            assert(channels[0][8] == 0);
            assert(channels[0][12] == (j ? 0xFFFFFFFFu : 0x80001230u));
            ++cases;
        }
    }
    assert(timeoutMessages == 1 && pauses == 1);
    cases += checkEnvironment();
    for (i = 0; i < 4; ++i) {
        unsigned int prior = enables;
        interruptsEnabled = i & 1;
        REG(0x1000F520) = (i & 2) ? 0x10005 : 5;
        channels[0][0] = 0xA55AFFFF;
        assert(sceDmaPause(channels[0]) == 0xA55AFFFF);
        assert(channels[0][0] == 0xA55AFEFF);
        assert(REG(0x1000F590) == REG(0x1000F520));
        assert(enables == prior + (i & 1));
        ++cases;
    }
    for (i = 0; i < 4; ++i) {
        unsigned int k;
        for (j = 0; j < 10; ++j)
            for (k = 0; k < 36; ++k) channels[j][k] = 0xA5A5A5A5;
        REG(0x1000E000) = i & 1;
        assert(sceDmaReset(i / 2) == (i & 1));
        for (j = 0; j < 10; ++j) {
            assert(channels[j][0] == (sdkDmaResetChannels[j] ? 0 : 0xA5A5A5A5));
            assert(channels[j][32] == channels[j][0]);
            assert(channels[j][12] == channels[j][0]);
            assert(channels[j][4] == channels[j][0]);
            assert(channels[j][20] == channels[j][0]);
            assert(channels[j][16] == channels[j][0]);
            assert(channels[j][8] == 0xA5A5A5A5);
        }
        assert((REG(0x1000E000) & 1) == ((i & 1) | (i / 2)));
        assert(sdkDmaEnvironment.ringBase == 0 && sdkDmaEnvironment.ringSize == 0);
        ++cases;
    }
    assert(munmap(mmio, 0x10000) == 0);
    printf("PASS: %u boot DMA host cases (mocked hardware, not a gameplay test)\n", cases);
    return 0;
}
