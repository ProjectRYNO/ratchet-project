#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/vobuf", voBufCreate);

void voBufDelete(void) {
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/vobuf", voBufReset);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/vobuf", voBufIsFull);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/vobuf", voBufIncCount);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/vobuf", voBufGetData);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/vobuf", voBufIsEmpty);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/vobuf", voBufGetTag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/game/movie/vobuf", voBufDecCount);
