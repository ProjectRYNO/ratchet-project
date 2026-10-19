/* Host tests for boot multitap; RPC transport and IOP are mocked. */
#include <assert.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "libmtap.h"
int sdkMtapClient[16];
int sdkMtapBuffer[32];
unsigned char sdkMtapWork[128];
const char sdkMtapBindError[] = "bind";
const char sdkMtapVersionError[] = "version";
const char sdkMtapVersionFormat[] = "version format";
const char sdkMtapOpenError[] = "open";
const char sdkMtapCloseError[] = "close";
const char sdkMtapConnectionError[] = "connection";
const char sdkMtapModuleError[] = "module";
static int rpcResult, response, expectedCommand, expectedPort, expectedWork;
static int binds, bindFailure, version = 0x310, initializing, calls, logs;
void sceSifInitRpc(int mode) { assert(mode == 0); }
int sceSifBindRpc(void *client, unsigned int id, int mode)
{
    assert(client == sdkMtapClient && id == 0x80000900u && mode == 0);
    ++binds;
    sdkMtapClient[9] = binds > 1;
    return bindFailure ? -1 : 0;
}
void scePrintf(const char *format, ...)
{
    assert(format == sdkMtapVersionError || format == sdkMtapVersionFormat);
    ++logs;
}
int sceSifCallRpc(void *client, int command, int mode, void *send, int sendSize,
                  void *receive, int receiveSize, void *callback, void *argument)
{
    assert(client == sdkMtapClient && mode == 0);
    assert(send == sdkMtapBuffer && receive == sdkMtapBuffer);
    assert(sendSize == 128 && receiveSize == 128 && !callback && !argument);
    ++calls;
    if (initializing) {
        assert(command == 5 || command == 6);
        if (command == 5) sdkMtapBuffer[0] = version;
        else {
            unsigned int i;
            assert(sdkMtapBuffer[1] == (int)(uintptr_t)sdkMtapWork);
            for (i = 0; i < 128; ++i) assert(sdkMtapWork[i] == 0);
            sdkMtapBuffer[0] = response;
        }
    } else {
        assert(command == expectedCommand);
        if (command >= 1 && command <= 3) assert(sdkMtapBuffer[0] == expectedPort);
        if (command == 6) assert(sdkMtapBuffer[1] == expectedWork);
        sdkMtapBuffer[command >= 1 && command <= 3 ? 1 : 0] = response;
    }
    return rpcResult;
}
int main(void)
{
    int (*ports[])(int) = {sceMtapPortOpen, sceMtapPortClose, sceMtapGetConnection};
    int results[] = {-7, 0, 13};
    int values[] = {-1, 0, 1, 4};
    unsigned int i,j,k,cases = 0;
    for (i = 0; i < 3; ++i) for (j = 0; j < 3; ++j) for (k = 0; k < 4; ++k) {
        expectedCommand = i + 1; expectedPort = values[k]; rpcResult = results[j]; response = 0x12345678;
        assert(ports[i](expectedPort) == (rpcResult < 0 ? 0 : response));
        ++cases;
    }
    for (i = 0; i < 3; ++i) {
        rpcResult = results[i]; response = 0x314;
        expectedCommand = 5;
        assert(sceMtapGetModVersion() == (rpcResult < 0 ? 0 : response));
        expectedCommand = 6; expectedWork = 0x123400;
        assert(sceMtapSetWorkAddr((void *)(uintptr_t)expectedWork) == (rpcResult < 0 ? 0 : response));
        expectedWork = 0;
        assert(sceMtapEnd() == (rpcResult < 0 ? 0 : response));
        cases += 3;
    }
    initializing = 1; rpcResult = 0; bindFailure = 1; binds = calls = logs = 0;
    assert(sceMtapInit() == 0 && binds == 1 && calls == 0 && logs == 0); ++cases;
    bindFailure = 0; binds = calls = logs = 0; version = 0x320;
    assert(sceMtapInit() == 0 && binds == 2 && calls == 1 && logs == 2); ++cases;
    binds = calls = logs = 0; version = 0x31F;
    memset(sdkMtapWork, 0xA5, 128);
    response = 0; /* Retail init ignores SetWorkAddr's result. */
    assert(sceMtapInit() == 1 && binds == 2 && calls == 2 && logs == 0); ++cases;
    DPRINT("disabled %d", 42);
    printf("PASS: %u boot multitap host cases (mocked RPC; no hardware test)\n",cases);
    return 0;
}
