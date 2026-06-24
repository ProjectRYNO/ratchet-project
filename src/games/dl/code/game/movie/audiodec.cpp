#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/audiodec", audioDecCreate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/audiodec", audioDecDelete);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/audiodec", func_004EF788);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/audiodec", audioDecStart);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/audiodec", audioDecReset);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/audiodec", audioDecBeginPut);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/audiodec", audioDecEndPut);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/audiodec", audioDecIsPreset);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/audiodec", audioDecSend);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/audiodec", iopGetArea);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/audiodec", sendToIOP2area);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/audiodec", sendToIOP);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/audiodec", sendToSPU);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/audiodec", sendPCM);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/audiodec", sendADPCM);

void sendSPDIF(void) {
}
