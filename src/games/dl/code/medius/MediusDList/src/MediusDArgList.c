#include "common.h"
#include "../../rt_util/rt_pack.h"

#define MEDIUS_DARGS_SECTION(name) __attribute__((section(".medius_dargs_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_dargs_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef unsigned short MediusDFieldId;
typedef unsigned int MediusDFieldMask;

typedef struct { // 0x1C
    /* 0x00 */ MediusDFieldId fieldId;
    /* 0x04 */ int rt_typeId;
    /* 0x08 */ void *constraint;
    /* 0x0C */ void *check;
    /* 0x10 */ unsigned int size;
    /* 0x14 */ void *pack;
    /* 0x18 */ unsigned int numElem;
} MediusDFieldDef;

typedef struct { // 0x10
    /* 0x0 */ unsigned int metaTypeId;
    /* 0x4 */ unsigned short numFields;
    /* 0x8 */ MediusDFieldDef **fieldDef;
    /* 0xC */ MediusDFieldMask fieldMask;
} MediusDMetaType;

typedef struct { // 0x14
    /* 0x00 */ RT_PACK_BUFFER *buffer;
    /* 0x04 */ MediusDMetaType *pMetaType;
    /* 0x08 */ unsigned int shadowMask;
    /* 0x0C */ unsigned int fieldMask;
    /* 0x10 */ MediusDFieldId firstId;
} MediusDArgList;

MediusDFieldId FindFirstFieldId_(MediusDArgList *pArgList);
MediusDFieldDef *GetTopFieldDef_(MediusDArgList *pArgList);

int MEDIUS_DARGS_SECTION(construct) construct(void *memory, RT_PACK_BUFFER *pMsg, MediusDMetaType *pMetaType, MediusDFieldMask fieldMask)
{
    int result = -0x15;
    if (memory && pMsg && pMetaType) {
        MediusDArgList *pArgList = (MediusDArgList *)memory;
        pArgList->fieldMask = fieldMask;
        pArgList->buffer = pMsg;
        pArgList->pMetaType = pMetaType;
        pArgList->shadowMask = fieldMask;
        pArgList->firstId = 0;
        result = 0;
    }
    return result;
}

int MEDIUS_DARGS_SECTION(destruct) destruct(MediusDArgList *pArgList)
{
    int result = -0x15;
    if (pArgList) {
        pArgList->fieldMask = 0;
        pArgList->pMetaType = 0;
        pArgList->buffer = 0;
        pArgList->firstId = 0xFFFF;
        result = 0;
    }
    return result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusDList/src/MediusDArgList", FindFirstFieldId_);

MediusDFieldId MEDIUS_DARGS_SECTION(getTopFieldId) getTopFieldId(MediusDArgList *pArgList)
{
    MediusDFieldId id = 0xFFFF;
    if (pArgList) id = FindFirstFieldId_(pArgList);
    return id;
}

MediusDFieldDef *MEDIUS_DARGS_SECTION(GetTopFieldDef_) GetTopFieldDef_(MediusDArgList *pArgList)
{
    MediusDFieldId id;
    if (pArgList == 0) return 0;
    id = FindFirstFieldId_(pArgList);
    if (id == 0xFFFF) return 0;
    return pArgList->pMetaType->fieldDef[id];
}

int MEDIUS_DARGS_SECTION(getTopTypeId) getTopTypeId(MediusDArgList *pArgList)
{
    MediusDFieldDef *def = GetTopFieldDef_(pArgList);
    if (def == 0) return 0;
    return def->rt_typeId;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusDList/src/MediusDArgList", popField);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusDList/src/MediusDArgList", popFieldData);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusDList/src/MediusDArgList", pushField);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusDList/src/MediusDArgList", pushRowData);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusDList/src/MediusDArgList", FlushField_);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusDList/src/MediusDArgList", MediusDArgList_popRowData);

unsigned short MEDIUS_DARGS_SECTION(getNumArguments) getNumArguments(MediusDArgList *pArgList)
{
    unsigned short count = 0;
    unsigned int bits;
    unsigned int m;
    if (pArgList) {
        m = pArgList->fieldMask;
        bits = (m & 0x55555555) + ((m >> 1) & 0x55555555);
        bits = (bits & 0x33333333) + ((bits >> 2) & 0x33333333);
        bits = (bits & 0x0F0F0F0F) + ((bits >> 4) & 0x0F0F0F0F);
        bits = (bits & 0x00FF00FF) + ((bits >> 8) & 0x00FF00FF);
        bits = (bits & 0xFFFF) + (bits >> 16);
        count = bits;
    }
    return count;
}

unsigned int MEDIUS_DARGS_SECTION(getObjectSize) getObjectSize(void)
{
    return sizeof(MediusDArgList);
}

void MEDIUS_DARGS_SECTION(rewindMask) rewindMask(MediusDArgList *pArgList)
{
    if (pArgList) {
        pArgList->firstId = 0;
        pArgList->fieldMask = pArgList->shadowMask;
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusDList/src/MediusDArgList", flush);

int MEDIUS_DARGS_SECTION(MediusDArgList_print) MediusDArgList_print(MediusDArgList *pArgList)
{
    return -0x14;
}
