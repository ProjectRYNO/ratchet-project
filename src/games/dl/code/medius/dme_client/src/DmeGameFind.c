#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_client/src/DmeGameFind", LANFindGetMyPeerDesc);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_client/src/DmeGameFind", LANFindPacketHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_client/src/DmeGameFind", LANFindResultsPacketHandler);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_client/src/DmeGameFind", SendLANFindResultsOnExchange);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_client/src/DmeGameFind", SendLANFindReply);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_client/src/DmeGameFind", InitLANFindReply);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_client/src/DmeGameFind", OnReceivedLANFindRequest);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_client/src/DmeGameFind", OnReceivedLANFindReply);
