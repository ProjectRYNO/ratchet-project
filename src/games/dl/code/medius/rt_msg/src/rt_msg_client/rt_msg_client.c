#include "common.h"

#define MEDIUS_MSGC_SECTION(name) __attribute__((section(".medius_msgc_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_msgc_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern int rt_mutex_unlock(void *mutex, int *count);

// Message-client mutex at 0x001B69C0 (rtTimebaseQueryTimer + 0x4408).
extern int mediusMsgClientMutex[];

int FUN_01ec7878(unsigned int a);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec3288);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec3408);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec3430);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec3460);

int MEDIUS_MSGC_SECTION(rt_msg_mutex_unlock) rt_msg_mutex_unlock(void)
{
    return rt_mutex_unlock(mediusMsgClientMutex, 0);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", func_01EC34B8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", func_01EC34C8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec34d8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec36a8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec3700);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec3758);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec37d0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec3828);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec38d0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec3d98);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec3de0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec3e48);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec3ec8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec3f58);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec40c8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec4150);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec41e8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec4250);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec4290);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec4318);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec4630);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec47a8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec4898);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec49f0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec4ab8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec4d48);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec4df0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec4e30);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec5070);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec5150);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec51f8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec5248);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec5280);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec52b8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec52e0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec5328);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec54e0);

int MEDIUS_MSGC_SECTION(rt_msg_client_calc_connect_aux_udp_msg_size) rt_msg_client_calc_connect_aux_udp_msg_size(void)
{
    return 0x20;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec54f8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec5618);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec57d8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec5888);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec5a10);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec5d90);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec6008);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec6150);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec61f0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec63c0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec6498);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec64c8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec6588);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec6650);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec6728);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec6770);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec6f00);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec6f70);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec7018);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec7140);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec72e0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec7368);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec76f8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec77c0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec7878);

int MEDIUS_MSGC_SECTION(FUN_01ec78c8) FUN_01ec78c8(unsigned int a)
{
    return FUN_01ec7878(a) != 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec78e8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec7920);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec7a98);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec7b30);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec7bd0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec7cd0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec7d38);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec7dc0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec7e20);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec81a8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec8290);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec84a8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec85b8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec87e8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec8930);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec8aa8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", FUN_01ec8ba8);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_msg/src/rt_msg_client/rt_msg_client", func_01EC8E00);
