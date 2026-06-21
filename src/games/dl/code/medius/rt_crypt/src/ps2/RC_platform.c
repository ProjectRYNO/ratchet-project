#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/ps2/RC_platform", RCInitialize);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/ps2/RC_platform", RCSaltyInitialize);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/ps2/RC_platform", RCEncrypt);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_crypt/src/ps2/RC_platform", RCDecrypt);
