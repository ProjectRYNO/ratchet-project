#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/ClientMsg", CreateClientHelloMsg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/ClientMsg", CreateClientKeyExchangeMsg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/ClientMsg", CreateChangeCipherSpecMsg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/ClientMsg", CreateClientFinishedMsg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_ssl/src/ClientMsg", VerifyServerMAC);
