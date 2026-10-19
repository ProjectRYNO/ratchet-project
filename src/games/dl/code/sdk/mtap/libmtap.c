#include "common.h"
#include "libmtap.h"

/* Recovered directly from the retail boot instructions; no vendor source. */
#define MTAP_SECTION(name) __attribute__((section(".mtap_" #name)))
extern int sdkMtapClient[16];
extern int sdkMtapBuffer[32];
extern unsigned char sdkMtapWork[128];
extern const char sdkMtapBindError[];
extern const char sdkMtapVersionError[];
extern const char sdkMtapVersionFormat[];
extern const char sdkMtapOpenError[];
extern const char sdkMtapCloseError[];
extern const char sdkMtapConnectionError[];
extern const char sdkMtapModuleError[];
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *);
extern int sceSifBindRpc(void *, unsigned int, int);
extern void sceSifInitRpc(int);
extern void scePrintf(const char *, ...);
extern void *memset(void *, int, unsigned int);
int sceMtapGetModVersion(void);
void MTAP_SECTION(DPRINT) DPRINT(const char *format, ...) {}
int MTAP_SECTION(sceMtapSetWorkAddr) sceMtapSetWorkAddr(void *work)
{
    sdkMtapBuffer[1] = (int)work;
    if (sceSifCallRpc(sdkMtapClient,6,0,sdkMtapBuffer,128,sdkMtapBuffer,128,0,0)<0) return 0;
    return sdkMtapBuffer[0];
}
int MTAP_SECTION(sceMtapInit) sceMtapInit(void)
{
    int version, i;
    sceSifInitRpc(0);
    while (1) {
        if (sceSifBindRpc(sdkMtapClient,0x80000900,0)<0) { DPRINT(sdkMtapBindError); return 0; }
        if (sdkMtapClient[9]) break;
        i = 0x10000;
        while (i--) {}
    }
    version = sceMtapGetModVersion();
    if ((version >> 4) != 0x31) {
        scePrintf(sdkMtapVersionError);
        scePrintf(sdkMtapVersionFormat,3,0x10,version>>8,version&0xFF);
        return 0;
    }
    memset(sdkMtapWork,0,128);
    sceMtapSetWorkAddr(sdkMtapWork);
    return 1;
}
int MTAP_SECTION(sceMtapEnd) sceMtapEnd(void) { return sceMtapSetWorkAddr(0); }
int MTAP_SECTION(sceMtapPortOpen) sceMtapPortOpen(int port)
{
    sdkMtapBuffer[0] = port;
    if (sceSifCallRpc(sdkMtapClient,1,0,sdkMtapBuffer,128,sdkMtapBuffer,128,0,0)<0) { DPRINT(sdkMtapOpenError); return 0; }
    return sdkMtapBuffer[1];
}
int MTAP_SECTION(sceMtapPortClose) sceMtapPortClose(int port)
{
    sdkMtapBuffer[0] = port;
    if (sceSifCallRpc(sdkMtapClient,2,0,sdkMtapBuffer,128,sdkMtapBuffer,128,0,0)<0) { DPRINT(sdkMtapCloseError); return 0; }
    return sdkMtapBuffer[1];
}
int MTAP_SECTION(sceMtapGetConnection) sceMtapGetConnection(int port)
{
    sdkMtapBuffer[0] = port;
    if (sceSifCallRpc(sdkMtapClient,3,0,sdkMtapBuffer,128,sdkMtapBuffer,128,0,0)<0) { DPRINT(sdkMtapConnectionError); return 0; }
    return sdkMtapBuffer[1];
}
int MTAP_SECTION(sceMtapGetModVersion) sceMtapGetModVersion(void)
{
    if (sceSifCallRpc(sdkMtapClient,5,0,sdkMtapBuffer,128,sdkMtapBuffer,128,0,0)<0) { DPRINT(sdkMtapModuleError); return 0; }
    return sdkMtapBuffer[0];
}

/* One original padding word; not an independent function. */
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .mtap_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/mtap/libmtap", func_0013B1CC);
