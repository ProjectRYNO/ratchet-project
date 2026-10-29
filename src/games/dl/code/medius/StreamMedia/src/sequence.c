#include "common.h"
#include "../../rt_util/rt_memory.h"
#include "sequence.h"

#define MEDIUS_SEQUENCE_SECTION(name) __attribute__((section(".medius_sequence_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_sequence_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

CSequence *MEDIUS_SEQUENCE_SECTION(CreateSequence) CreateSequence(void)
{
    CSequence *pSequence = 0;
    unsigned int i;

    rt_memory_allocate_init_zero((void **)&pSequence, sizeof(CSequence));
    if (pSequence) {
        pSequence->m_eMedia = ExtraNetStreamMediaAudioType;
        pSequence->m_eThreshold = THRESHOLD_LOW;
        pSequence->m_iNext = 0;
        pSequence->m_nBlockCount = 0;
        for (i = 0; i < SEQ_BLOCKS; i++) {
            pSequence->m_Blocks[i].nSequence = 0;
            pSequence->m_Blocks[i].nSize = 0;
        }
    }
    return pSequence;
}

void MEDIUS_SEQUENCE_SECTION(DestroySequence) DestroySequence(CSequence *pSequence)
{
    if (pSequence) rt_memory_free((void **)&pSequence);
}

void MEDIUS_SEQUENCE_SECTION(InitSequence) InitSequence(CSequence *pSequence)
{
    unsigned int i;

    pSequence->m_eThreshold = THRESHOLD_LOW;
    pSequence->m_eMedia = ExtraNetStreamMediaAudioType;
    pSequence->m_iNext = 0;
    pSequence->m_nBlockCount = 0;
    for (i = 0; i < SEQ_BLOCKS; i++) {
        pSequence->m_Blocks[i].nSequence = 0;
        pSequence->m_Blocks[i].nSize = 0;
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/sequence", AddSequence);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/sequence", GetSequenceData);
