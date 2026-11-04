#include "common.h"

#define MEDIUS_DMETA_SECTION(name) __attribute__((section(".medius_dmeta_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_dmeta_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern int rt_memory_free(void **pointer);

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
typedef struct { // 0x8
    /* 0x0 */ MediusDFieldDef *def;
    /* 0x4 */ void *pFieldData;
} MediusDField;
extern MediusDField undefField;
extern int rt_memory_allocate(void *pointer, unsigned int size);

MediusDMetaType *MEDIUS_DMETA_SECTION(create) create(unsigned int metaTypeId, MediusDFieldDef **fieldDef, unsigned int size)
{
    MediusDMetaType *pMetaType;
    MediusDFieldMask mask = 0;
    unsigned short numFields = size / sizeof(MediusDFieldDef *);
    unsigned short i;

    if (fieldDef == 0) return 0;
    if (numFields == 0) return 0;
    for (i = 0; i < numFields; i++) {
        MediusDFieldDef *def = fieldDef[i];
        if (def == 0) return 0;
        if (def->fieldId != i) return 0;
        if (def->pack == 0) return 0;
        if (def->size == 0) return 0;
        if (def->constraint == 0) return 0;
        mask |= 1 << i;
    }
    rt_memory_allocate(&pMetaType, 0x10);
    pMetaType->metaTypeId = metaTypeId;
    pMetaType->fieldDef = fieldDef;
    pMetaType->numFields = size / sizeof(MediusDFieldDef *);
    pMetaType->fieldMask = mask;
    return pMetaType;
}

void MEDIUS_DMETA_SECTION(destroy) destroy(void *pMetaType)
{
    if (pMetaType) rt_memory_free(&pMetaType);
}

MediusDField MEDIUS_DMETA_SECTION(getThisField) getThisField(MediusDMetaType *pMetaType, MediusDFieldId id, void *pFieldData)
{
    MediusDField field;
    if (pMetaType == 0) return undefField;
    if (id >= pMetaType->numFields) return undefField;
    field.def = pMetaType->fieldDef[id];
    field.pFieldData = pFieldData;
    return field;
}
