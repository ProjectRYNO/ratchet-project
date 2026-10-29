#include "common.h"

#define MEDIUS_PARSE_SECTION(name) __attribute__((section(".medius_parse_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_parse_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef struct {
    unsigned char opaque[0x30];
    void *pBuffer;
} RT_PARSE_FRAG_MSG;

#define RT_PARSE_FRAG_SLOTS 256

extern int rt_memory_free(void **pointer);
extern int rt_parse_timeout_frag_msg(void);

extern unsigned char rtParseInitialized;
extern unsigned char *rtParseMessageBuffer;
// Parser callbacks, indexed [MessageClass * rtParseMaxTypes + MessageType].
extern int (**rtParseParsers)();
// Registered message types per class (debug-info name).
extern unsigned int *gaTypeCount;
// Received-message counters, same indexing as rtParseParsers.
extern void *rtParseMessageCounts;
// 256 fragment-reassembly slots of 0x34 bytes.
extern RT_PARSE_FRAG_MSG *rtParseFragments;

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_parse", rt_parse_initialize);

int MEDIUS_PARSE_SECTION(rt_parse_shutdown) rt_parse_shutdown(void)
{
    unsigned int i;

    if (rtParseFragments) {
        for (i = 0; i < RT_PARSE_FRAG_SLOTS; i++) {
            if (rtParseFragments[i].pBuffer) rt_memory_free(&rtParseFragments[i].pBuffer);
        }
        rt_memory_free((void **)&rtParseFragments);
    }
    if (gaTypeCount) rt_memory_free((void **)&gaTypeCount);
    if (rtParseParsers) rt_memory_free((void **)&rtParseParsers);
    if (rtParseMessageBuffer) rt_memory_free((void **)&rtParseMessageBuffer);
    if (rtParseMessageCounts) rt_memory_free(&rtParseMessageCounts);
    rtParseInitialized = 0;
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_parse", rt_parse_register);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_parse", rt_parse_reg_parser);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_parse", rt_parse_execute);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_parse", rt_parse_get_callback);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_parse", rt_parse_fragment_message);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_parse", rt_parse_timeout_frag_msg);

int MEDIUS_PARSE_SECTION(rt_parse_update) rt_parse_update(void)
{
    return rt_parse_timeout_frag_msg();
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_parse", rt_parse_find_frag_msg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_parse", rt_parse_fragment_handler);
