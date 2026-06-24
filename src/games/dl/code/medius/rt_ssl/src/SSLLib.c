#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/SSLLib", MemAlloc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/SSLLib", MemFree);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/SSLLib", SSL_Initialize);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/SSLLib", SSL_AddRootCertificate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/SSLLib", SSL_AddCRL);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/SSLLib", SSL_Create);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/SSLLib", SSL_Destroy);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/SSLLib", SSL_Callback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/SSLLib", SSL_Cleanup);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/SSLLib", ParseServerMsg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/SSLLib", ParseHandshake);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/SSLLib", ParseChangeCipherSpec);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/SSLLib", ParseServerHello);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/SSLLib", ParseServerHelloDone);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/SSLLib", VerifyServerFinished);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/SSLLib", ParseCertificateMsg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/SSLLib", ParseAppData);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/SSLLib", CreateFinishedMsg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/SSLLib", CalculateMAC);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/SSLLib", CreateNetMsg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/SSLLib", ParseAlertMsg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/SSLLib", CreateAlertMsg);
