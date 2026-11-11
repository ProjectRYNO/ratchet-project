#include "common.h"

#define MEDIUS_DMEREG_SECTION(name) __attribute__((section(".medius_dmereg_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_dmereg_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef enum { NetErrorNone = 0, NetErrorUnknown = 30 } NetErrorCode;
typedef enum { MessageClassApplication = 2 } NetMessageClass;
typedef void *NetTypeMessageParser;

extern int rt_parse_register(unsigned int *MessageType, NetMessageClass MessageClass, NetTypeMessageParser ThisPacketParser);
extern int rt_parse_reg_parser(unsigned int MessageType, NetMessageClass MessageClass, NetTypeMessageParser ThisPacketParser);

NetErrorCode MEDIUS_DMEREG_SECTION(NetIRegisterMessage) NetIRegisterMessage(unsigned int *MessageType, NetMessageClass MessageClass, NetTypeMessageParser ThisPacketParser)
{
    if (rt_parse_register(MessageType, MessageClass, ThisPacketParser)) return NetErrorUnknown;
    return NetErrorNone;
}

NetErrorCode MEDIUS_DMEREG_SECTION(NetIRegParseMessage) NetIRegParseMessage(unsigned int MessageType, NetMessageClass MessageClass, NetTypeMessageParser ThisPacketParser)
{
    if (rt_parse_reg_parser(MessageType, MessageClass, ThisPacketParser)) return NetErrorUnknown;
    return NetErrorNone;
}

NetErrorCode MEDIUS_DMEREG_SECTION(NetIRegisterApplicationMessage) NetIRegisterApplicationMessage(unsigned int *MessageType, NetTypeMessageParser ThisPacketParser)
{
    NetErrorCode result;

    result = NetIRegisterMessage(MessageType, MessageClassApplication, ThisPacketParser);
    return result;
}
