#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_client/src/DmeMessage", ClientConnectsPacketHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_client/src/DmeMessage", ServerVersionPacketHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_client/src/DmeMessage", RequestServersPacketHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_client/src/DmeMessage", ServerResponsePacketHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_client/src/DmeMessage", PingPacketHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_client/src/DmeMessage", UpdateClientStatusPacketHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_client/src/DmeMessage", RegisterDMEmessages);
