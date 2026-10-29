#include "common.h"

#define MEDIUS_DTYPE_SECTION(name) __attribute__((section(".medius_dtype_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_dtype_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef unsigned short MediusDFieldId;
typedef unsigned short MediusDFieldIndex;
typedef unsigned int MediusDFieldMask;

typedef struct { // 0x8
    /* 0x0 */ unsigned short fieldId;
    /* 0x2 */ unsigned short typeEnum;
    /* 0x4 */ unsigned short fieldSize;
    /* 0x6 */ unsigned short offset;
} MediusDFieldSpec;

typedef struct { // 0x8
    /* 0x0 */ MediusDFieldSpec *fieldSpec;
    /* 0x4 */ unsigned short objectSize;
    /* 0x6 */ unsigned short numFields;
} MediusDFieldMap;

typedef struct MediusDFieldDef_ MediusDFieldDef;

typedef struct { // 0x10
    /* 0x0 */ unsigned int metaTypeId;
    /* 0x4 */ unsigned short numFields;
    /* 0x8 */ MediusDFieldDef **fieldDef;
    /* 0xC */ MediusDFieldMask fieldMask;
} MediusDMetaType;

typedef struct { // 0xC
    /* 0x0 */ MediusDMetaType *pMetaType;
    /* 0x4 */ MediusDFieldMask mask;
    /* 0x8 */ unsigned short numFields;
    /* 0xA */ unsigned short objectSize;
    /* 0xC */ MediusDFieldSpec fieldSpec[0];
} MediusDType;

typedef struct { // 0x8
    /* 0x0 */ MediusDFieldDef *def;
    /* 0x4 */ void *pFieldData;
} MediusDField;

typedef struct { // 0x8
    /* 0x0 */ MediusDFieldId *fieldId;
    /* 0x4 */ unsigned int size;
} MediusDFieldIdList;


extern MediusDField undefField;

extern int rt_memory_free(void **pointer);

MediusDFieldIndex _findFieldIndex(MediusDType *pType, MediusDFieldId fieldId);
MediusDField getField(MediusDType *pType, MediusDFieldIndex fieldIndex, void *pObjData);

void MEDIUS_DTYPE_SECTION(PrintTypeId) PrintTypeId(unsigned int typeId)
{
}

unsigned int MEDIUS_DTYPE_SECTION(CreateMask_) CreateMask_(MediusDType *pType, MediusDFieldId *fieldId, unsigned short numFields)
{
    unsigned int mask = 0;
    unsigned int i;
    for (i = numFields; i != 0; i--) {
        mask |= 1 << *fieldId++;
    }
    return mask;
}

unsigned int MEDIUS_DTYPE_SECTION(CreateMaskFromMap_) CreateMaskFromMap_(MediusDFieldMap *pMap)
{
    unsigned int mask = 0;
    int i;
    for (i = 0; i < pMap->numFields; i++) {
        mask |= 1 << pMap->fieldSpec[i].fieldId;
    }
    return mask;
}

int MEDIUS_DTYPE_SECTION(CmpMediusDFieldId_) CmpMediusDFieldId_(void *first, void *second)
{
    int b = *(MediusDFieldId *)second;
    int a = *(MediusDFieldId *)first;
    return a - b;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusDList/src/MediusDType", createMask);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusDList/src/MediusDType", create___dupe2);

int MEDIUS_DTYPE_SECTION(destroy___dupe2) destroy___dupe2(MediusDType *pType)
{
    if (pType && pType->mask) {
        pType->mask = 0;
        return rt_memory_free((void **)&pType) ? -0x15 : 0;
    }
    return -0x15;
}

MediusDField MEDIUS_DTYPE_SECTION(getField) getField(MediusDType *pType, MediusDFieldIndex fieldIndex, void *pObjData)
{
    MediusDField field = { pType->pMetaType->fieldDef[pType->fieldSpec[fieldIndex].fieldId], (char *)pObjData + pType->fieldSpec[fieldIndex].offset };
    return field;
}

MediusDFieldIndex MEDIUS_DTYPE_SECTION(_findFieldIndex) _findFieldIndex(MediusDType *pType, MediusDFieldId fieldId)
{
    unsigned int bits;
    int index;
    unsigned int m = pType->mask & (0xFFFFFFFF >> (31 - fieldId));

    bits = (m & 0x55555555) + ((m >> 1) & 0x55555555);
    bits = (bits & 0x33333333) + ((bits >> 2) & 0x33333333);
    bits = (bits & 0x0F0F0F0F) + ((bits >> 4) & 0x0F0F0F0F);
    bits = (bits & 0x00FF00FF) + ((bits >> 8) & 0x00FF00FF);
    bits = (bits & 0xFFFF) + (bits >> 16);
    index = bits - 1;
    if (index < 0) index = 0;
    return pType->fieldSpec[index].fieldId == fieldId ? index : 0xFFFF;
}

MediusDField MEDIUS_DTYPE_SECTION(findField) findField(MediusDType *pType, MediusDFieldId fieldId, void *pObjData)
{
    MediusDFieldIndex fieldIndex;
    if (pType == 0 || pObjData == 0) return undefField;
    fieldIndex = _findFieldIndex(pType, fieldId);
    if (fieldIndex != 0xFFFF) return getField(pType, fieldIndex, pObjData);
    return undefField;
}

MediusDField MEDIUS_DTYPE_SECTION(getThisField___dupe2) getThisField___dupe2(MediusDType *pType, MediusDFieldIndex fieldIndex, void *pFieldData)
{
    MediusDField field = { pType->pMetaType->fieldDef[pType->fieldSpec[fieldIndex].fieldId], pFieldData };
    return field;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusDList/src/MediusDType", getFieldId___dupe2);

MediusDFieldIndex MEDIUS_DTYPE_SECTION(getFieldIndex) getFieldIndex(MediusDType *pType, MediusDFieldId fieldId)
{
    return _findFieldIndex(pType, fieldId);
}

unsigned short MEDIUS_DTYPE_SECTION(getNumFields) getNumFields(MediusDType *pType)
{
    return pType->numFields;
}

unsigned short MEDIUS_DTYPE_SECTION(getObjectSize___dupe2) getObjectSize___dupe2(MediusDType *pType)
{
    return pType->objectSize;
}

unsigned int MEDIUS_DTYPE_SECTION(getObjectDataSize) getObjectDataSize(MediusDType *pType)
{
    unsigned int size = 0;
    if (pType) size = pType->objectSize - 8;
    return size;
}

MediusDFieldMask MEDIUS_DTYPE_SECTION(getMask) getMask(MediusDType *pType)
{
    MediusDFieldMask mask = 0;
    if (pType) mask = pType->mask;
    return mask;
}

MediusDFieldMask MEDIUS_DTYPE_SECTION(getMaskFromList) getMaskFromList(MediusDType *pType, MediusDFieldIdList *idList)
{
    return CreateMask_(pType, idList->fieldId, idList->size >> 1);
}

MediusDMetaType *MEDIUS_DTYPE_SECTION(getMetaType) getMetaType(MediusDType *pType)
{
    MediusDMetaType *pMetaType = 0;
    if (pType) pMetaType = pType->pMetaType;
    return pMetaType;
}

MediusDFieldMask MEDIUS_DTYPE_SECTION(getMetaMask) getMetaMask(MediusDType *pType)
{
    return pType->pMetaType->fieldMask;
}

int MEDIUS_DTYPE_SECTION(printType) printType(MediusDType *pType)
{
    return -0x14;
}

int MEDIUS_DTYPE_SECTION(printMetaType) printMetaType(MediusDMetaType *pMetaType)
{
    return -0x14;
}
